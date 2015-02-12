//
//  partidaSlot.cpp
//  TagSlot
//
//  Created by Natxo Pedreira gonzalez on 12/2/15.
//
//

#include "partidaSlot.h"




//--------------------------------------------------------------
void partidaSlot::setup(string arduPort){
    
    mentalPowers[0] = 0; // el mental power del player 1
    mentalPowers[1] = 0; // el mental power del player 2
    
    
    timeSinceLastLapOne = ofGetElapsedTimeMillis();
    timeSinceLastLapTwo = ofGetElapsedTimeMillis();
    
    minTimePerLap = 2000; // no puede tardar menos de 2 segundos en dar una vuelta
    
    // los margenes para los servos
    ptoServoPlayerOne.set(0, 0); // margen para el servo1
    ptoServoPlayerTwo.set(0, 0); // margen para el servo2
    
    
    // nos conectamos al arduino
    bool success = arduino.setup(arduPort, 9600);
    
    if(success)
    {
        ofLogNotice("partidaSlot::setup") << "Successfully setup " << arduPort;
    }
    else
    {
        ofLogNotice("partidaSlot::setup") << "Unable to setup " << arduPort;
    }

    
    readyToRun();
}

//--------------------------------------------------------------
void partidaSlot::update(){
    
    listenToArdu(); // eschicha los pasos por vuelta
    
    talkToArdu(); // dile al arduino que hay que hacer
   
}

//--------------------------------------------------------------
void partidaSlot::listenToArdu(){
    // nos dice el paso por vuelta de cada coche
    // dos valores separados por punto y coma
    // The serial device can throw exeptions.
    try
    {
        // Read all bytes from the device;
        uint8_t buffer[2];
        
        while (arduino.available() > 0)
        {
            // tienes algo que decirme
            std::size_t sz = arduino.readBytes(buffer, 2);
            
            cout << "me dices que son " << sz << " bytes?? ";
            
            // compruebas que este todo lo que quieres oir
            if(buffer[0]==1 && ofGetElapsedTimeMillis()> (timeSinceLastLapOne + minTimePerLap)){
                // el coche 1 pasa por el sensor
                ofNotifyEvent(pasoPorVueltaOne);
                timeSinceLastLapOne = ofGetElapsedTimeMillis();
            }
            
            if(buffer[1]==1 && ofGetElapsedTimeMillis()> (timeSinceLastLapTwo + minTimePerLap)){
                // el coche 2 pasa por el sensor
                ofNotifyEvent(pasoPorVueltaTwo);
                timeSinceLastLapTwo = ofGetElapsedTimeMillis();
            }
            
            arduino.flushInput(); // borramos el buffer
            
        }
        
    }
    catch (const std::exception& exc)
    {
        ofLogError("ofApp::update") << exc.what();
    }
}

//--------------------------------------------------------------
void partidaSlot::talkToArdu(){
    
    // siempre 4 int separados por punto y coma
    // sonido0 ; sonido1 ; servo0; servo 1
    std::string msg="0;0;0;0";
    
    ofx::IO::ByteBuffer Buffer;
    
    // los valores de salida de los servos hay que ajustarlos entre el recorrido posible
    int servoPower0 = ofMap(mentalPowers[0], 0, 100, 0, 255);
    int servoPower1 = ofMap(mentalPowers[1], 0, 100, 0, 255);
    
    int sonidoPower0 = ofMap(mentalPowers[0], 0, 100, 0, 255);
    int sonidoPower1 = ofMap(mentalPowers[1], 0, 100, 0, 255);
    
    
    switch (gameStatus) {
        case READY_TO_RUN:
            // mandas todo a 0 no se esta jugando
            msg = "0;0;0;0";
            
            break;
            
        case START_ENGINES:
            // te pones el casco, se conecta y pruebas el blink para acelerar
            // solo tiene que sonar no se puede mover
            // mandas el valor del power para el sonido el servo siempre a 0
            msg = ofToString(sonidoPower0) + ";" +  ofToString(sonidoPower1) + ";0;0";
            break;
            
            
        case COUNTDOWN:
            // esta sonando la cuenta atras aun no puedes mover el servo
            // mandas el valor del power para el sonido el servo siempre a 0
            msg = ofToString(sonidoPower0) + ";" +  ofToString(sonidoPower1) + ";0;0";
            
            break;
            
            
        case RACING:
            // feeeerrro a fondo
            // mandas el valor del power para el sonido el del servo
            msg = ofToString(sonidoPower0) + ";" +  ofToString(sonidoPower1) +
            ";"  + ofToString(servoPower0) + ";" +  ofToString(servoPower1) + ";";
            
            break;

    }

    // crea el buffer conel msg que sea
    
    Buffer = ofx::IO::ByteBuffer(msg);
    
    // intenta dicirle algo
    try{
        arduino.writeBytes(Buffer);
        arduino.writeByte('\n');
    }catch (const std::exception& exc){
        ofLogError("partidaSlot::talkToArdu") << exc.what();
    }
    
}


//--------------------------------------------------------------
void partidaSlot::draw(){

}

//--------------------------------------------------------------
void partidaSlot::setPlayerOnePower(int p){
    mentalPowers[0] = p;
}


//--------------------------------------------------------------
void partidaSlot::setPlayerTwoPower(int p){
    mentalPowers[1] = p;
}


//--------------------------------------------------------------
void partidaSlot::readyToRun(){
    gameStatus = READY_TO_RUN;
}

//--------------------------------------------------------------
void partidaSlot::startEngines(){
    gameStatus = START_ENGINES;
}

//--------------------------------------------------------------
void partidaSlot::countdown(){
    gameStatus = COUNTDOWN;
}

//--------------------------------------------------------------
void partidaSlot::racing(){
    gameStatus = RACING;
}