#pragma once

#include "ofMain.h"
#include "mindSlotPlayer.h"
#include "partidaSlot.h"
#include "ofxGui.h"
#include "countDown.h"

class ofApp : public ofBaseApp{
public:
    
    void setup();
    void update();
    void draw();
    
    void exit();
    
    ///
    void nuevaPartida();
    void encederMotoresPartida();
    void empezarPartida();
    
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    void guardaGui();
    
    void playerOneNewLap();
    void playerTwoNewLap();
    
    void playerOneWins();
    void playerTwoWins();
    
    void finishedSemaforo();
    void loadedSemaforo();
    
    // mindplay brainband bluetooth device
    mindSlotPlayer playerOne, playerTwo;
    partidaSlot game;
    countDown semaforo;
    ofImage bg;
    
    ofImage fondoLogo;
    ofImage salpicadero;
    ofImage esfera;
    ofImage mascaraBarra;
    
    ofxPanel gui;
    ofxToggle useAttention;
    ofxToggle useMeditation;
    ofxToggle useBooth;
    
    bool showGui;
};