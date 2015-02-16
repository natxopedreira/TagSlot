//
//  mindPower.h
//  ofxThinkgearExample
//
//  Created by Natxo Pedreira gonzalez on 11/2/15.
//
//

#ifndef ofxThinkgearExample_mindPower_h
#define ofxThinkgearExample_mindPower_h

class mindPower {
    
public:
    
    //---------------------
    void setup(){
        valor = 0;
        desiredValue = 0;
        turboValue = 0;
    }
    
    //---------------------
    void update(){
        
        // subimos un punto por cada frame y bajamos un punto cada 30 frames
        if(valor<desiredValue && valor<100){
            valor ++;
        }else if(valor>desiredValue && valor>0){
           // if(ofGetFrameNum() % 2 ==0)valor --;
            valor --;
        }
        
        // turbo
        valor = valor + turboValue;
        
        // comprueba que esta dentro del rando valido de 0-100
        if(valor>100){
            valor = 100;
        }else if (valor<0){
            valor = 0;
        }
        
        // baja el turbo
        if(turboValue>0) turboValue--;
        
    }
    
    //---------------------
    void setDesiredValue(int d){
        desiredValue = d;
    }
    
    //---------------------
    int getPower(){
        //cout << "mindPower::getPower " << valor << endl;
        return valor;
        
        
    }
    
    //--------------------
    int getRotationGauge(){
        return ofMap(valor,0,100,0,230);
    }
    
    int turboBlink(int tb){
        turboValue = tb;
        
       // cout << turboValue << endl;
    }
    
private:
    int valor;
    int desiredValue;
    int turboValue;
};
#endif
