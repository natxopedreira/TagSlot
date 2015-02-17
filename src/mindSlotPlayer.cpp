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
    ajustes.add(servoMin.set("minimo", 0, 0, 255));
    ajustes.add(servoMax.set("maximo", 0, 0, 255));
    
    ofParameterGroup ajustes;
    ofParameter<int> servoMin;
    ofParameter<int> servoMax;
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
    numVuelta++;
}

//--------------------------------------------------------------
void mindSlotPlayer::resetLapCounter(){
    numVuelta = 0;
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



