//
//  mindSlotPlayer.cpp
//  ofxThinkgearExample
//
//  Created by Natxo Pedreira gonzalez on 10/2/15.
//
//

#include "mindSlotPlayer.h"


mindSlotPlayer::mindSlotPlayer(){
    poorSignal = 200;
    meditation = 0;
    attention = 0;
    turboLink = 0;
    numVuelta = 0;
    
    useAttention = false;
    useMeditation= false;
    useBooth= true;
    
    playerName = "";
}

void mindSlotPlayer::closeMindWave(){
    mindWave.close();
    mindWave.removeEventListener(this);
}

//---------------------//---------------------//---------------------
//---------------------//---------------------//---------------------
//---------------------//---------------------//---------------------

void mindSlotPlayer::setup(string _name, string _playerName){
    mindWave.setup(_name, 57600, TG_COMMS_DRIVER);
    mindWave.addEventListener(this);
    
    mentalPower.setup(); // mindPower es el valor que controla el slot
    
    playerName = _playerName;
    
    gauge.loadImage("aguja.png");
    gauge.setAnchorPoint(60, 84);
    
    ajustes.setName("servo player " + _playerName);
    ajustes.add(servoMin.set("minimo", 0, 0, 179));
    ajustes.add(servoMax.set("maximo", 0, 0, 179));
    
    fuenteLaps.loadFont("EurostileRegular.ttf", 100);
    
    fuenteGrande.loadFont("EurostileRegular.ttf", 100);
    fuenteGrande.setLetterSpacing(0.8);
    
    fuentePequena.loadFont("EurostileBold.ttf", 19);
    fuentePequena.setLetterSpacing(1.14);
    
    fuenteMedia.loadFont("EurostileRegular.ttf", 79);
    fuenteMedia.setLetterSpacing(0.9);
    fuenteMedia.setSpaceSize(0.4);
}

//--------------------------------------------------------------
void mindSlotPlayer::update(){
    mindWave.update();
   
    mentalPower.update();
    
    if(getQualityConnection() == 100){
        
        if (useAttention) {
            mentalPower.setDesiredValue(attention);
        }else if (useMeditation){
            mentalPower.setDesiredValue(meditation);
        }else if (useBooth){
            mentalPower.setDesiredValue((meditation+attention)/2);
        }
        
        
        
    }else{
        mentalPower.setDesiredValue(0);
    }
    
    
}

//--------------------------------------------------------------
void mindSlotPlayer::drawDebug(int _x, int _y){
    ofPushMatrix();
    ofTranslate(_x, _y);
    
    if(isReady()){
        
        if(getQualityConnection()<100){
            ofDrawBitmapStringHighlight("PLAYER:: " + getPlayerName(), ofPoint(20,0), ofColor(252,125,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("READY?:: " + ofToString(isReady()), ofPoint(20,20), ofColor(252,125,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("CON QUALITY:: " + ofToString(getQualityConnection()), ofPoint(20,40), ofColor(252,125,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("ATTENTION:: " + ofToString(getAttention()), ofPoint(20,60), ofColor(252,125,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("MEDITATION:: " + ofToString(getMeditation()), ofPoint(20,80), ofColor(252,125,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("MENTAL POWER:: " + ofToString(mentalPower.getPower()), ofPoint(20,100), ofColor(252,125,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("LAPS:: " + ofToString(numVuelta), ofPoint(20,120), ofColor(252,125,0), ofColor(0,0,0));
            ofRect(20, 140, mentalPower.getPower(), 20);
        }else{
            ofDrawBitmapStringHighlight("PLAYER:: " + getPlayerName(), ofPoint(20,0), ofColor(0,255,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("READY?:: " + ofToString(isReady()), ofPoint(20,20), ofColor(0,255,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("CON QUALITY:: " + ofToString(getQualityConnection()), ofPoint(20,40), ofColor(0,255,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("ATTENTION:: " + ofToString(getAttention()), ofPoint(20,60), ofColor(0,255,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("MEDITATION:: " + ofToString(getMeditation()), ofPoint(20,80), ofColor(0,255,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("MENTAL POWER:: " + ofToString(mentalPower.getPower()), ofPoint(20,100), ofColor(0,255,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("LAPS:: " + ofToString(numVuelta), ofPoint(20,120), ofColor(0,255,0), ofColor(0,0,0));
            ofRect(20, 140, mentalPower.getPower(), 20);
        }
        
    }else{
        ofDrawBitmapStringHighlight("PLAYER:: " + getPlayerName(), ofPoint(20,0), ofColor(255,0,0), ofColor(0,0,0));
        ofDrawBitmapStringHighlight("READY?:: " + ofToString(isReady()), ofPoint(20,20), ofColor(255,0,0), ofColor(0,0,0));
        ofDrawBitmapStringHighlight("CON QUALITY:: " + ofToString(getQualityConnection()), ofPoint(20,40), ofColor(255,0,0), ofColor(0,0,0));
        ofDrawBitmapStringHighlight("ATTENTION:: " + ofToString(getAttention()), ofPoint(20,60), ofColor(255,0,0), ofColor(0,0,0));
        ofDrawBitmapStringHighlight("MEDITATION:: " + ofToString(getMeditation()), ofPoint(20,80), ofColor(255,0,0), ofColor(0,0,0));
        ofDrawBitmapStringHighlight("MENTAL POWER:: " + ofToString(mentalPower.getPower()), ofPoint(20,100), ofColor(255,0,0), ofColor(0,0,0));
        ofDrawBitmapStringHighlight("LAPS:: " + ofToString(numVuelta), ofPoint(20,120), ofColor(255,0,0), ofColor(0,0,0));
    }
    
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void mindSlotPlayer::drawGauge(ofPoint pt){
    //img->draw(0, 0);
    
    ofPushMatrix();
    ofTranslate(pt);
    
    ofRotate(mentalPower.getRotationGauge());
    
    gauge.draw(0,0);
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void mindSlotPlayer::drawConnection(){
    //rectangulo de calidad de conexion
    ofPushStyle();
    
    if(isReady())
        ofSetColor(196, 106, 27); //naranja
    else
        ofSetColor(255, 0, 0); //rojo pq no esta conectado
    
    ofRect(700, 985, 521, 200);
    
    
    ofSetColor(7, 188, 75); //verde
    ofRect(700, 985, 521 * getQualityConnectionPct(), 200);
    
    ofPopStyle();
}

//--------------------------------------------------------------
void mindSlotPlayer::pasoPorVuelta(){
    if(numVuelta == 10){
        ofNotifyEvent(playerWin);
    }else{
        numVuelta++;
    }
}

//--------------------------------------------------------------
void mindSlotPlayer::resetLapCounter(){
    numVuelta = 0;
}


//--------------------------- DRAW -----------------------------//
//--------------------------------------------------------------
void mindSlotPlayer::drawPlayerNumber(){
    ofPushStyle();
    ofSetColor(91, 91, 91);
    fuenteGrande.drawString(playerName, 45, 160);
    ofPopStyle();
}

//--------------------------------------------------------------
void mindSlotPlayer::drawConcentrationMeditation(){
    ofPushStyle();
    ofSetColor(255, 255, 255);
    fuentePequena.drawString("ATTENTION", 45, 900);
    fuentePequena.drawString("MEDITATION", 325, 900);
    
    ofSetColor(162, 162, 162);
    
    // concentracion
    if(getAttention()<10){
        fuenteMedia.drawString("0" + ofToString(getAttention()) + " %", 41, 980);
    }else{
        fuenteMedia.drawString(ofToString(getAttention()) + " %", 41, 980);
    }
    
    // meditacion
    if (getMeditation()<10) {
        fuenteMedia.drawString("0" + ofToString(getMeditation()) + " %", 321, 980);
    }else{
        fuenteMedia.drawString(ofToString(getMeditation()) + " %", 321, 980);
    }
    
    
    ofPopStyle();
}

//--------------------------------------------------------------
void mindSlotPlayer::drawlapsData(){
    ofPushStyle();
    ofSetColor(91, 91, 91);
    fuenteLaps.drawString("00:00:00", 1310, 980);
    fuenteMedia.drawString("LAP", 1510, 855);
    
    ofSetColor(255, 255, 255);
    if(numVuelta<10){
        fuenteLaps.drawString("0"+ofToString(numVuelta), 1690, 855);
    }else{
        fuenteLaps.drawString("10", 1690, 855);
    }
    
    
    ofPopStyle();
}


//--------------------------------------------------------------//
//--------------------------- GETTTERS -------------------------//
//--------------------------------------------------------------//

int mindSlotPlayer::getPlayerPower(){
    return mentalPower.getPower();
}
//--------------------------------------------------------------
int mindSlotPlayer::getAttention(){
    return attention;
}
//--------------------------------------------------------------
int mindSlotPlayer::getMeditation(){
    return meditation;
}
//--------------------------------------------------------------
bool mindSlotPlayer::isReady(){
    return mindWave.isReady;
}
//--------------------------------------------------------------
int mindSlotPlayer::getQualityConnection(){
    return ofMap(poorSignal, 200, 0, 0, 100);
}
//--------------------------------------------------------------
float mindSlotPlayer::getQualityConnectionPct(){
    return ofMap(poorSignal, 200, 0, 0, 1);
}
//--------------------------------------------------------------
string mindSlotPlayer::getPlayerName(){
    return playerName;
}
//--------------------------------------------------------------//
//--------------------------------------------------------------//
//--------------------- EVENTOS DEL MINDWAVES ------------------//
//--------------------------------------------------------------//

void mindSlotPlayer::onThinkgearPoorSignal(ofxThinkgearEventArgs& args){
    poorSignal = (int)args.poorSignal;
}
//--------------------------------------------------------------
void mindSlotPlayer::onThinkgearAttention(ofxThinkgearEventArgs& args){
    attention = (int)args.attention;
    

}
//--------------------------------------------------------------
void mindSlotPlayer::onThinkgearMeditation(ofxThinkgearEventArgs& args){
    meditation = (int)args.meditation;
}
//--------------------------------------------------------------
void mindSlotPlayer::onThinkgearError(ofMessage& err){
}
//--------------------------------------------------------------
void mindSlotPlayer::onThinkgearBlinkStrength(ofxThinkgearEventArgs& args){
    if((int)args.blinkStrength > 50 && (int)args.blinkStrength < 100) mentalPower.turboBlink(15);
}
//--------------------------------------------------------------
void mindSlotPlayer::onThinkgearConnecting(ofxThinkgearEventArgs& args){}
//--------------------------------------------------------------
void mindSlotPlayer::onThinkgearReady(ofxThinkgearEventArgs& args){}
//--------------------------------------------------------------
void mindSlotPlayer::onThinkgearRaw(ofxThinkgearEventArgs& args){}
//--------------------------------------------------------------
void mindSlotPlayer::onThinkgearBattery(ofxThinkgearEventArgs& args){
   
}
//--------------------------------------------------------------
void mindSlotPlayer::onThinkgearEeg(ofxThinkgearEventArgs& args){}



