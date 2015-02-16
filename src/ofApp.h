#pragma once

#include "ofMain.h"
#include "mindSlotPlayer.h"
#include "partidaSlot.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
public:
    
    void setup();
    void update();
    void draw();
    
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    void guardaGui();
    
    void playerOneNewLap();
    void playerTwoNewLap();
    
    // mindplay brainband bluetooth device
    mindSlotPlayer playerOne, playerTwo;
    partidaSlot game;
    
    ofImage bg;
    
    ofxPanel gui;
    ofxToggle useAttention;
    ofxToggle useMeditation;
    ofxToggle useBooth;
    
    
    bool showGui;
};