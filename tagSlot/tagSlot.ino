#include <Wire.h>//Include the Wire library to talk I2C
#include "MCP4725.h"
#include "Servo.h"


//This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
//Please note that this breakout is for the MCP4725A0. 
#define MCP4725_ADDR 0x60   
#define MCP4725_ADDR_2 0x61 

#define pinPlayerOne A1
#define pinPlayerTwo A2

MCP4725 DAC_PLAYER_ONE(MCP4725_ADDR);  // 0x62 or 0x63
MCP4725 DAC_PLAYER_TWO(MCP4725_ADDR_2);  // 0x62 or 0x63

int sonido1;
int sonido2;

int servo1;
int servo2;

Servo servoPlayerOne;
Servo servoPlayerTwo;

long ultimaLecturaPlayerOne = 0;
long ultimaLecturaPlayerTwo = 0;

long minTiempoXvuelta = 1500; // tiempo para debiunce del sensor
int thresholdFotoInterruptor = 500; // si la lectura del interruptor es menor, pasa el coche


void setup()
{
  
  Wire.begin();
  Serial.begin(115200);

  servoPlayerOne.attach(10);
  servoPlayerTwo.attach(11);

  initLapSensorOne();
  initLapSensorTwo();

  sonido1 = 0;
  sonido2 = 0;

  servo1 = 0;
  servo2 = 0;

}


void loop()
{

  while (Serial.available() > 0)  
  {
  		// pillas los valores que te manda oF

  		// cajas de sonido
  		sonido1 = Serial.parseInt(); //primer int de sonido del mensaje
  		sonido2 = Serial.parseInt(); //segundo int de sonido del mensaje

  		// servos de los mandos
  		servo1 = Serial.parseInt(); //primer int de servo del mensaje
  		servo2 = Serial.parseInt(); //segundo int de servo del mensaje

      setVoltageSoundPlayerOne(sonido1);
      setVoltageSoundPlayerTwo(sonido2);
      //
      setServoPlayerOne(servo1);
      setServoPlayerOne(servo2);
  }
  // check lap sensors

  checkLapSensorOne();
  checkLapSensorTwo();
  //delay(10);  
}

//// ------------------------------------ /////
//// ------------------------------------ /////
//// ---------- SERVOS E I2C ------------ /////
//// ------------------------------------ /////
void setServoPlayerOne(int v){
  servoPlayerOne.write(v);
}

void setServoPlayerTwo(int v){
  servoPlayerTwo.write(v);
}

void setVoltageSoundPlayerOne(int i){
  DAC_PLAYER_ONE.setValue(i );
}
void setVoltageSoundPlayerTwo(int i){
  DAC_PLAYER_TWO.setValue(i);
}



//// ------------------------------------ /////
//// ------------------------------------ /////
//// --------- FOTO INTERRUPTOR --------- /////
//// ------------------------------------ /////
void initLapSensorOne(){
  pinMode( pinPlayerOne,INPUT );
  digitalWrite( pinPlayerOne,LOW );

  ultimaLecturaPlayerOne = millis();
}
//// ---------------------------------
void initLapSensorTwo(){
  pinMode( pinPlayerTwo,INPUT );
  digitalWrite( pinPlayerTwo,LOW );

  ultimaLecturaPlayerTwo = millis();
}

//// ---------------------------------
void checkLapSensorOne(){
  int v1 = analogRead( pinPlayerOne );
  
  if(v1<thresholdFotoInterruptor){
    // paso por meta
    if ((millis() - ultimaLecturaPlayerOne) > minTiempoXvuelta) {
        // comprueba que hay un minimo de tiempo entre lectura 
        // envia el mensaje
        Serial.write('A');
        ultimaLecturaPlayerOne = millis();
        //Serial.print("player one new lap");
      }
  }
}
//// ---------------------------------
void checkLapSensorTwo(){
  int v2 = analogRead( pinPlayerTwo );
  
  if(v2<thresholdFotoInterruptor){
    // paso por meta
    if ((millis() - ultimaLecturaPlayerTwo) > minTiempoXvuelta) {
        // comprueba que hay un minimo de tiempo entre lectura 
        // envia el mensaje
        Serial.write('B');
        ultimaLecturaPlayerTwo = millis();
        //Serial.print("player two new lap");
      }
  }
}




int smooth2Value(uint16_t value, uint8_t steps)
{
  static int _lastValue = 0;

  // speed optimization
  if (value == _lastValue) return 0;
  if (value > MCP4725_MAXVALUE) return MCP4725_VALUE_ERROR;
  if (steps == 0) steps++;

  uint16_t delta = (value - _lastValue)/steps;
  if (delta > 0)
  {
    uint16_t v = _lastValue;
    for (int i=0; i < steps-1; i++)
    {
      v += delta;
      DAC_PLAYER_ONE.setValue(v);
    }
  }
  // be sure to get the end value right
  int rv = DAC_PLAYER_ONE.setValue(value);
  _lastValue = value;
  return rv;
}
