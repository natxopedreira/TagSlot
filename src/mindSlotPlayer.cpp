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
    
    gauge.loadImage("gauge.png");
    gauge.setAnchorPoint(91+9, -15);
    
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
        mentalPower.setDesiredValue((meditation+attention)/2);
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
            ofDrawBitmapStringHighlight("player:: " + getPlayerName(), ofPoint(20,0), ofColor(252,125,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("isReady:: " + ofToString(isReady()), ofPoint(20,20), ofColor(252,125,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("con quality:: " + ofToString(getQualityConnection()), ofPoint(20,40), ofColor(252,125,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("attention:: " + ofToString(getAttention()), ofPoint(20,60), ofColor(252,125,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("meditation:: " + ofToString(getMeditation()), ofPoint(20,80), ofColor(252,125,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("metalPower:: " + ofToString(mentalPower.getPower()), ofPoint(20,100), ofColor(252,125,0), ofColor(0,0,0));
            ofRect(20, 120, mentalPower.getPower(), 20);
        }else{
            ofDrawBitmapStringHighlight("player:: " + getPlayerName(), ofPoint(20,0), ofColor(0,255,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("isReady:: " + ofToString(isReady()), ofPoint(20,20), ofColor(0,255,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("con quality:: " + ofToString(getQualityConnection()), ofPoint(20,40), ofColor(0,255,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("attention:: " + ofToString(getAttention()), ofPoint(20,60), ofColor(0,255,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("meditation:: " + ofToString(getMeditation()), ofPoint(20,80), ofColor(0,255,0), ofColor(0,0,0));
            ofDrawBitmapStringHighlight("metalPower:: " + ofToString(mentalPower.getPower()), ofPoint(20,100), ofColor(0,255,0), ofColor(0,0,0));
            ofRect(20, 120, mentalPower.getPower(), 20);
        }
    }else{
        ofDrawBitmapStringHighlight("player:: " + getPlayerName(), ofPoint(20,0), ofColor(255,0,0), ofColor(0,0,0));
        ofDrawBitmapStringHighlight("isReady:: " + ofToString(isReady()), ofPoint(20,20), ofColor(255,0,0), ofColor(0,0,0));
        ofDrawBitmapStringHighlight("con quality:: " + ofToString(getQualityConnection()), ofPoint(20,40), ofColor(255,0,0), ofColor(0,0,0));
        ofDrawBitmapStringHighlight("attention:: " + ofToString(getAttention()), ofPoint(20,60), ofColor(255,0,0), ofColor(0,0,0));
        ofDrawBitmapStringHighlight("meditation:: " + ofToString(getMeditation()), ofPoint(20,80), ofColor(255,0,0), ofColor(0,0,0));
        ofDrawBitmapStringHighlight("metalPower:: " + ofToString(mentalPower.getPower()), ofPoint(20,100), ofColor(255,0,0), ofColor(0,0,0));
    }
    
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void mindSlotPlayer::drawGauge(ofImage * img){
    img->draw(0, 0);
    
    ofPushMatrix();
    ofTranslate(631,385);
    
    ofRotate(mentalPower.getRotationGauge());
    
    gauge.draw(0,0);
    
    ofPopMatrix();
}

//--------------------------------------------------------------//
//--------------------------- GETTTERS -------------------------//
//--------------------------------------------------------------//

int mindSlotPlayer::getPlayerPower(){
    mentalPower.getPower();
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



