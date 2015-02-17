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
    bool success = arduino.setup(arduPort, 115200);
    
    if(success)
    {
        ofLogNotice("partidaSlot::setup") << "Successfully setup " << arduPort;
        
       // arduino.registerAllEvents(this);
    }
    else
    {
        ofLogNotice("partidaSlot::setup") << "Unable to setup " << arduPort;
    }

    
    //countdown();
}

//--------------------------------------------------------------
void partidaSlot::update(){
    
    listenToArdu(); // escucha los pasos por vuelta
    
    talkToArdu(); // dile al arduino que hay que hacer
   
}


//--------------------------------------------------------------
void partidaSlot::drawDebug(){
    switch (gameStatus) {
        case READY_TO_RUN:
            // mandas todo a 0 no se esta jugando
            ofDrawBitmapStringHighlight("estado de pardida READY TO RUN", 50,30);
            
            break;
            
        case START_ENGINES:
            // te pones el casco, se conecta y pruebas el blink para acelerar
            // solo tiene que sonar no se puede mover
            ofDrawBitmapStringHighlight("estado de pardida START YOUR ENGINES", 50,30);
            
            
            break;
            
            
        case COUNTDOWN:
            // esta sonando la cuenta atras aun no puedes mover el servo
            // mandas el valor del power para el sonido el servo siempre a 0
            ofDrawBitmapStringHighlight("estado de pardida COUNTDOWN", 50,30);
            
            break;
            
            
        case RACING:
            // feeeerrro a fondo
            // mandas el valor del power para el sonido el del servo
           ofDrawBitmapStringHighlight("estado de pardida RACING", 50,30);
            
            break;
            
    }
    
    
    
    

}

//--------------------------------------------------------------
void partidaSlot::listenToArdu(){
    // nos dice el paso por vuelta de cada coche
    // dos valores 0 or 1
    // 0 es na de na
    // 1 es tengo señal de paso por meta !!
    
    try
    {
        // Read all bytes from the device;
        uint8_t buffer[2];
        
        while (arduino.available() > 0)
        {
            // tienes algo que decirme
            std::size_t sz = arduino.readBytes(buffer, 2);
            
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
        ofLogError("partidaSlot::listenToArdu") << exc.what();
    }
}

//--------------------------------------------------------------
void partidaSlot::talkToArdu(){
    
    
    // -------------------------------------------- //
    // -------------------------------------------- //
    // -------------------------------------------- //
    // siempre 4 int separados por punto y coma     //
    // sonido0 ; sonido1 ; servo0; servo1           //
    // -------------------------------------------- //
    // -------------------------------------------- //
    // -------------------------------------------- //
    std::string msg="0;0;0;0";
    
    ofx::IO::ByteBuffer Buffer;
    
    // los valores de salida de los servos hay que ajustarlos entre el recorrido posible
    // ptoServoPlayerOne.set(min, max); // margen para el servo1
    // ptoServoPlayerTwo.set(min, max); // margen para el servo2
    
    int sonidoPower0 = ofMap(mentalPowers[0], 0, 100, 0, 3000, true); //4095
    int sonidoPower1 = ofMap(mentalPowers[1], 0, 100, 0, 3000, true); // 4095
    
    int servoPower0 = ofMap(mentalPowers[0], 0, 100, ptoServoPlayerOne.x, ptoServoPlayerOne.y, true);
    int servoPower1 = ofMap(mentalPowers[1], 0, 100, ptoServoPlayerTwo.x, ptoServoPlayerTwo.y, true);

    
    
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
       // cout << msg << endl;
        arduino.writeBytes(msg);
        arduino.writeByte('\n');
        
    }catch (const std::exception& exc){
        ofLogError("partidaSlot::talkToArdu") << exc.what();
    }
    
}


//--------------------------------------------------------------
void partidaSlot::cierra(){
   // arduino.unregisterAllEvents(this);
}

//--------------------------------------------------------------
void partidaSlot::setPlayerOnePower(int p){
    mentalPowers[0] = p;
    //cout << "setPlayerOnePower() " << p << endl;
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