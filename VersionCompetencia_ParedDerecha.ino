/*
  Tablero node32S
*/
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
 

#include <ESP32Encoder.h>
#define PUSH 12
#define LED 05
#define MOTOR_RIGTH_POSITIVE 16
#define MOTOR_RIGTH_NEGATIVE 17
#define MOTOR_RIGTH_A 34
#define MOTOR_RIGTH_B 35
#define MOTOR_LEFT_POSITIVE 18
#define MOTOR_LEFT_NEGATIVE 04
#define MOTOR_LEFT_A 23
#define MOTOR_LEFT_B 19
#define SPEED 70//70//55

#define CNY_0 36
#define CNY_1 33
#define CNY_2 25
#define CNY_3 26
#define CNY_4 27
#define CNY_5 32
#define CNY_6 39
#define LED_ON 13
#define RANGE 400//400
const String deviceName = "leviatan_esp32";
bool pushState = 0;
int btnPresionado = 1;
bool menuOption1=false;
bool menuOption2=false;
bool menuOption3=false;
// the setup routine runs once when you press reset:
void setup() {


  // initialize serial communication at 9600 bits per second:
//  Serial.begin(9600);

  adcAttachPin(CNY_0);
  adcAttachPin(CNY_1);
  adcAttachPin(CNY_2);
  adcAttachPin(CNY_3);
  adcAttachPin(CNY_4);
  adcAttachPin(CNY_5);
  adcAttachPin(CNY_6);
  analogReadResolution(10);

  /* Boton de control*/
  pinMode(PUSH, INPUT_PULLUP);
  /* Led de control*/
  pinMode(LED, OUTPUT);
  /* Control de encendido de los led emisores*/
  pinMode(LED_ON, OUTPUT);
  digitalWrite(LED_ON, 0);
  /* Motores sin movimiento*/
  analogWrite(MOTOR_RIGTH_POSITIVE, 0);
  analogWrite(MOTOR_RIGTH_NEGATIVE, 0);
  analogWrite(MOTOR_LEFT_POSITIVE, 0);
  analogWrite(MOTOR_LEFT_NEGATIVE, 0);

  //MANDAR DATOS POR BT A SERIAL DE PC
  SerialBT.begin(deviceName);
  Serial.println(deviceName + " está listo para emparejarse");
  while(digitalRead(PUSH)){
    
  }
  delay(50);
}

// the loop routine runs over and over again forever:
void loop() {

  /* Encendido de de leds emisoresr*/
  digitalWrite(LED_ON, 1);
  /* Lectura e impresion de los sensores*/
  
  Serial.println(String(analogRead(CNY_0)) + "-" + String(analogRead(CNY_1)) + "-" + String(analogRead(CNY_2)) + "-" + String(analogRead(CNY_3)) + "-" + String(analogRead(CNY_4)) + "-" + String(analogRead(CNY_5)) + "-" + String(analogRead(CNY_6)));
  int sensor0 = analogRead(CNY_0);
  int sensor6 = analogRead(CNY_6);
  int sensor3 = analogRead(CNY_3);
  int sensor4 = analogRead(CNY_4);
  int sensor2 = analogRead(CNY_2);
  int sensor1 = analogRead(CNY_1);
  int sensor5 = analogRead(CNY_5);

 SerialBT.println(String(analogRead(CNY_0)) + "-" + String(analogRead(CNY_1)) + "-" + String(analogRead(CNY_2)) + "-" + String(analogRead(CNY_3)) + "-" + String(analogRead(CNY_4)) + "-" + String(analogRead(CNY_5)) + "-" + String(analogRead(CNY_6)));
 //Serial.println(String(sensor6) + "-" + String(sensor4)+ "-" + String(sensor3)+ "-" + String(sensor2)+ "-" + String(sensor0));
  /* Apagado de de leds emisoresr*/
  digitalWrite(LED_ON, 0);
  /* Encendido de de leds emisoresr*/

 // if (pushState) {
        if (sensor0 < RANGE && sensor2 < RANGE && sensor1 < 800) {
          SerialBT.println("DERECHA");
    
          derechaRueda();
        } else if (sensor1 > 800 && sensor0 > RANGE || sensor2 && sensor3>800) {
          SerialBT.println("IZQUIERDA");
          izquierda();
          }else if(sensor4 > RANGE && sensor2>RANGE && sensor5>RANGE && sensor1>RANGE ){
          SerialBT.println("IZQUIERDA 2");
          izquierda();
    
        } else {
          Serial.println("if 11"); SerialBT.println("AVANZAR");
          avanzarCD(sensor2);
        }

 // }else{
 // analogWrite(MOTOR_RIGTH_POSITIVE, 0);
 // analogWrite(MOTOR_RIGTH_NEGATIVE, 0);

  //analogWrite(MOTOR_LEFT_POSITIVE, 0);
  //analogWrite(MOTOR_LEFT_NEGATIVE, 0);
 // }


  // BT LEER DATOS DE SERIAL
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
}


void avanzarCD(int sensor2) {
  if (sensor2 < RANGE ) {
    avanzarCentrado(SPEED , SPEED * .75);
    
  } else if (sensor2 > RANGE ) {
    avanzarCentrado(SPEED*.75, SPEED );
  } else {
    avanzarCentrado(SPEED, SPEED);
  }
}

void avanzarCI(int sensor4) {
  if (sensor4 < RANGE) {
    //avanzarCentrado(SPEED *.8, SPEED);
 avanzarCentrado(SPEED *.75, SPEED);
  } else if (sensor4 > RANGE) {

   // avanzarCentrado(SPEED, SPEED*.8);
    avanzarCentrado(SPEED, SPEED*.75);
  } else {
    avanzarCentrado(SPEED, SPEED);
  }


}
void izquierdaRueda() {
  /* Motor derecho con movimiento a enfrente*/
  analogWrite(MOTOR_RIGTH_POSITIVE,  0);
  analogWrite(MOTOR_RIGTH_NEGATIVE, SPEED + SPEED * 1.9);
  /* Motor izequierdo con movimiento a enfrente*/
  analogWrite(MOTOR_LEFT_POSITIVE, 0);
  analogWrite(MOTOR_LEFT_NEGATIVE, SPEED - SPEED * .7);
  //        delay(110);
}

void derechaRueda() {
  /* Motor derecho con movimiento a enfrente*/
  analogWrite(MOTOR_RIGTH_POSITIVE,  0);
  analogWrite(MOTOR_RIGTH_NEGATIVE, SPEED - SPEED * .7);
  /* Motor izequierdo con movimiento a enfrente*/
  analogWrite(MOTOR_LEFT_POSITIVE, 0);
  analogWrite(MOTOR_LEFT_NEGATIVE, SPEED + SPEED * 1.8);
  //        delay(110);
}

void derecha() {

  analogWrite(MOTOR_RIGTH_POSITIVE, 50);//analogWrite(MOTOR_RIGTH_POSITIVE, 40);
  analogWrite(MOTOR_RIGTH_NEGATIVE, 0);

  analogWrite(MOTOR_LEFT_POSITIVE, 0);
  analogWrite(MOTOR_LEFT_NEGATIVE, 50);
}

void izquierda() {

  analogWrite(MOTOR_RIGTH_POSITIVE, 0);
 analogWrite(MOTOR_RIGTH_NEGATIVE, 45);
  //analogWrite(MOTOR_LEFT_POSITIVE, 40);
  analogWrite(MOTOR_LEFT_POSITIVE, 45);
  analogWrite(MOTOR_LEFT_NEGATIVE, 0);
}



void detener(int mIzq, int mDer) {
  analogWrite(MOTOR_RIGTH_POSITIVE, mDer);
  analogWrite(MOTOR_RIGTH_NEGATIVE, 0);

  analogWrite(MOTOR_LEFT_POSITIVE, mIzq);
  analogWrite(MOTOR_LEFT_NEGATIVE, 0);
  delay(100);
}

void avanzarCentrado(int mIzq, int mDer) {
  analogWrite(MOTOR_RIGTH_POSITIVE, 0);
  analogWrite(MOTOR_RIGTH_NEGATIVE, mDer);

  analogWrite(MOTOR_LEFT_POSITIVE, 0);
  analogWrite(MOTOR_LEFT_NEGATIVE, mIzq);
}

void sonido(){
  delay(200);
      analogWrite(MOTOR_RIGTH_POSITIVE, 0);
    analogWrite(MOTOR_RIGTH_NEGATIVE, 20);
    analogWrite(MOTOR_LEFT_POSITIVE, 0);
    analogWrite(MOTOR_LEFT_NEGATIVE, 20);
    delay(100);
      analogWrite(MOTOR_RIGTH_POSITIVE, 0);
    analogWrite(MOTOR_RIGTH_NEGATIVE, 0);
    analogWrite(MOTOR_LEFT_POSITIVE, 0);
    analogWrite(MOTOR_LEFT_NEGATIVE, 0);
        delay(200);
      analogWrite(MOTOR_RIGTH_POSITIVE, 0);
    analogWrite(MOTOR_RIGTH_NEGATIVE, 20);
    analogWrite(MOTOR_LEFT_POSITIVE, 0);
    analogWrite(MOTOR_LEFT_NEGATIVE, 20);
    delay(100);
          analogWrite(MOTOR_RIGTH_POSITIVE, 0);
    analogWrite(MOTOR_RIGTH_NEGATIVE, 0);
    analogWrite(MOTOR_LEFT_POSITIVE, 0);
    analogWrite(MOTOR_LEFT_NEGATIVE, 0);
    delay(200);
    analogWrite(MOTOR_RIGTH_POSITIVE, 0);
    analogWrite(MOTOR_RIGTH_NEGATIVE, 20);
    analogWrite(MOTOR_LEFT_POSITIVE, 0);
    analogWrite(MOTOR_LEFT_NEGATIVE, 20);
    delay(100);
}
