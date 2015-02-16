//
//  partidaSlot.h
//  TagSlot
//
//  Created by Natxo Pedreira gonzalez on 12/2/15.
//
//

#ifndef __TagSlot__partidaSlot__
#define __TagSlot__partidaSlot__

#include "ofMain.h"
#include "ofxSerial.h"

class partidaSlot {
    
public:
    enum estadoPartida {
        READY_TO_RUN, // esta listo para comenzar
        START_ENGINES, // paso 1 manda valor de sonido y servo siempre a 0
        COUNTDOWN, // paso 2 lanza la cuenta atras
        RACING // paso 3 manda sonido y valor del servo
    };
    
    
    void setup(string arduPort);
    void update();
    
    void talkToArdu();
    void listenToArdu();
    
    void setPlayerOnePower(int p);
    void setPlayerTwoPower(int p);
    
    void readyToRun();
    void startEngines();
    void countdown();
    void racing();
    
    void cierra();
    
    ofx::IO::SerialDevice arduino;
   // ofx::IO::SerialDevice arduino;
    //void onSerialBuffer(const ofx::IO::SerialBufferEventArgs& args);
    //void onSerialError(const ofx::IO::SerialBufferErrorEventArgs& args);
    
    
    ofSoundPlayer sndCountDown;
    
    estadoPartida gameStatus;
    
    int mentalPowers[2];
    
    float timeSinceLastLapOne, timeSinceLastLapTwo, minTimePerLap;
    
    ofPoint ptoServoPlayerOne, ptoServoPlayerTwo;
    
    ofEvent<void> pasoPorVueltaOne;
    ofEvent<void> pasoPorVueltaTwo;
};

#endif /* defined(__TagSlot__partidaSlot__) */
