//
//  countDown.h
//  TagSlot
//
//  Created by Natxo Pedreira gonzalez on 17/2/15.
//
//

#ifndef TagSlot_countDown_h
#define TagSlot_countDown_h

#include "ofMain.h"

class countDown {
    
public:
    int tiempoPorLetra;
    int tiempoDesdeInicio;
    int cuentaAtras;
    float alphaInicio;
    
    ofImage semaforoRojo;
    ofImage semaforoVerde;
    
    ofTrueTypeFont fuente;
    
    ofEvent<void> terminado;
    ofEvent<void> cargado;
    
    ofSoundPlayer sonido;
    
    bool running;
    bool booting;
    bool luzVerde;
    
    //--------------------------------------------------------------
    void setup(){
        tiempoPorLetra = 1000; // 2 segundos por cada letra
        tiempoDesdeInicio = ofGetElapsedTimeMillis();
        cuentaAtras = 6; // desde donde empieza a contar
        
        semaforoRojo.loadImage("semaforo-rojo.png");
        semaforoVerde.loadImage("semaforo-verde.png");
        
        fuente.loadFont("Helvetica.ttf", 200);
        
        running = false;
        luzVerde = false;
        booting = false;
        alphaInicio = 0.0;
        
        sonido.loadSound("Countdown with Sound.mp3");
        sonido.setVolume(.5);
    }
    
    //--------------------------------------------------------------
    void go(){
        
        luzVerde = false;
        booting = true;
        running = true;
        
        alphaInicio = 0.0;
        cuentaAtras = 6;
    }
    
    //--------------------------------------------------------------
    void start(){
        tiempoDesdeInicio = ofGetElapsedTimeMillis();

        sonido.play();
        
    }
    
    //--------------------------------------------------------------
    void stop(){
        running = false;
        luzVerde = false;
        booting = false;
        alphaInicio = 0.0;
    }
    
    //--------------------------------------------------------------
    void draw(float _x, float _y){
         if(!running) return;
        
        ofPushStyle();
        
        ofSetColor(255, 255, 255, alphaInicio*255);
        if (luzVerde) {
            semaforoVerde.draw(_x, _y);
        }else{
            semaforoRojo.draw(_x, _y);
        }
        int alpha = ofMap((tiempoDesdeInicio+tiempoPorLetra) - ofGetElapsedTimeMillis(), tiempoPorLetra, 1, 255 , 10);
        
        ofSetColor(255, 255, 255, alpha);
        fuente.drawString(ofToString(cuentaAtras), 300, 500);
        ofPopStyle();
    }
    
    //--------------------------------------------------------------
    void update(){
        if(!running) return;

        
        if(ofGetElapsedTimeMillis()> (tiempoDesdeInicio+tiempoPorLetra)){
            // modificas la cuenta atras porque esta corriendo y ha pasado un segundo
            if(cuentaAtras>0){
                cuentaAtras--;
                
            }
            
            // cuenta atras esta en 0
            if(cuentaAtras==0){
                if(luzVerde){
                    ofNotifyEvent(terminado);
                    cout <<  "terminado" << endl;
                }
                luzVerde = true;
                
            }
            
            tiempoDesdeInicio = ofGetElapsedTimeMillis();
        }
        
        if(!booting) return;
        
        if((alphaInicio<1)){
            alphaInicio+=.1;
        }else{
            booting = false;
            ofNotifyEvent(cargado);
            start();
            
        }
    }
    
};

#endif
