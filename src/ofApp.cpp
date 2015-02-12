#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // imagen de fondo del salpicadero
    bg.loadImage("bg.jpg");
    
    // inicias el control de la partida
    game.setup("/dev/tty.Bluetooth-Incoming-Port");
    
    // inicias los players diciendole cual es su mindwaves
    playerOne.setup("/dev/tty.MindWaveMobile-DevA", "playerOne");
    playerTwo.setup("/dev/tty.MindWaveMobile-DevA-1", "playerTwo");
    
    // cada vez que el coche pasa por el sensor de vuelta se ejecuta este listener
    ofAddListener(game.pasoPorVueltaOne, this, &ofApp::playerOneNewLap);
    ofAddListener(game.pasoPorVueltaTwo, this, &ofApp::playerTwoNewLap);
    
    // gui con las posiciones de los servos
    gui.setup();
    gui.setName("AJUSTES");
    gui.add(playerOne.ajustes);
    gui.add(playerTwo.ajustes);
    gui.loadFromFile("settings.xml");
    
    // pasamos las posiciones al game
    game.ptoServoPlayerOne.set(playerOne.servoMin, playerOne.servoMax);
    game.ptoServoPlayerOne.set(playerTwo.servoMin, playerTwo.servoMax);
    
    // listener para refrescar las posiciones de los servos mientras ajustas, pulsando leer
    ofAddListener(gui.savePressedE, this, &ofApp::guardaGui);
    
    // muestra el gui
    showGui = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // actualiza los players
    playerOne.update();
    
    // actualiza el power de los jugadores
    game.setPlayerOnePower(playerOne.getPlayerPower());
    game.setPlayerTwoPower(playerTwo.getPlayerPower());
    
    // actualizas el juego que manda lo que sea al ardu
    game.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    playerOne.drawGauge(&bg); // aguja del indicador de velocidad pasas el puntero del dashboard
    playerOne.drawDebug(50, 50); // info de debug
    
    if(showGui) gui.draw();
}



//--------------------------------------------------------------
void ofApp::playerOneNewLap(){
    // vuelta nueva coche 1
    playerOne.pasoPorVuelta();
}

//--------------------------------------------------------------
void ofApp::playerTwoNewLap(){
    // vuelta nueva coche 2
    playerTwo.pasoPorVuelta();
}

//--------------------------------------------------------------
void ofApp::guardaGui(){
    // pasamos las posiciones al game
    game.ptoServoPlayerOne.set(playerOne.servoMin, playerOne.servoMax);
    game.ptoServoPlayerOne.set(playerTwo.servoMin, playerTwo.servoMax);
}

//--------------------------------------------------------------
void ofApp::exit(){
    playerOne.closeMindWave();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'd') showGui = !showGui;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}


