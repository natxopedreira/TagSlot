//
//  mindSlotPlayer.h
//  ofxThinkgearExample
//
//  Created by Natxo Pedreira gonzalez on 10/2/15.
//
//

#ifndef __mindSlotPlayer__
#define __mindSlotPlayer__


#include "ofxThinkgear.h"
#include "mindPower.h"

class mindSlotPlayer{
    
public:
    mindSlotPlayer();

    void setup(string _name, string _playerName);
    void update();
    void drawDebug(int _x, int _y);
    void drawGauge(ofImage * img);
    void closeMindWave();
    
    
    
    bool isReady();
    
    int getAttention();
    int getMeditation();
    int getQualityConnection();
    int getPlayerPower();
    
    string getPlayerName();
    
    // mindwave events
    void onThinkgearError(ofMessage& err);
    void onThinkgearPoorSignal(ofxThinkgearEventArgs& args);
    void onThinkgearBlinkStrength(ofxThinkgearEventArgs& args);
    void onThinkgearAttention(ofxThinkgearEventArgs& args);
    void onThinkgearMeditation(ofxThinkgearEventArgs& args);
    void onThinkgearConnecting(ofxThinkgearEventArgs& args);
    
    // mindwave events que no funsionan
    void onThinkgearReady(ofxThinkgearEventArgs& args);
    void onThinkgearRaw(ofxThinkgearEventArgs& args);
    void onThinkgearBattery(ofxThinkgearEventArgs& args);
    void onThinkgearEeg(ofxThinkgearEventArgs& args);
    
    // parametros para el gui
    ofParameterGroup ajustes;
    ofParameter<int> servoMin;
    ofParameter<int> servoMax;
    
private:
    ofxThinkgear mindWave;
    ofxThinkgearEventArgs mindWaveData;
    
    mindPower mentalPower;
    
    int poorSignal, meditation, attention;
    int turboLink;
    
    string playerName;
    
    ofImage gauge;

};

#endif /* defined(__ofxThinkgearExample__mindSlotPlayer__) */