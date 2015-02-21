#pragma once

#include "ofMain.h"
#include "mindSlotPlayer.h"
#include "partidaSlot.h"
#include "ofxGui.h"
#include "countDown.h"
#include "ofxSecondWindow.h"

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
    
    void drawPlayerOne();
    void drawPlayerTwo();
    
    
    ofxSecondWindow secondWindow;
    
    // mindplay brainband bluetooth device
    mindSlotPlayer playerOne, playerTwo;
    partidaSlot game;
    countDown semaforo;
    ofImage bg;
    
    ofImage fondoLogo;
    ofImage salpicadero;
    ofImage esfera;
    ofImage mascaraBarra;
    ofImage winnerImg;
    
    ofxPanel gui;
    ofxToggle useAttention;
    ofxToggle useMeditation;
    ofxToggle useBooth;
    
    bool showGui;
    int whoWins;
};