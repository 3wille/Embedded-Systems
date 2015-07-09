//#include <Servo.h>

#include <Wire.h>
#include "DueTimer.h"
//#include "avr/ServoTimers.h"
//#include "sam/ServoTimers.h"
#include "Servo.h"


int dev = 0; // 0 = master, 1=slave


int pinLED = 13;

//Master
Servo servo;
int pinServo = 9;
int upperBound = 170;
int lowerBound = 20;
int slaveAddr = 1;
int angle = 90;

//Slave
float rotationRate = 0;
int pinX = 5;
int pinVref = 7;
int pinAZ = 8;
int vrefValue; 
int valueX = 0;
int alignment = 90;
float sensitivity = 9.1;
uint8_t rate = 0;
int calRate;
bool valChanged = false;
int winkel = 90;



void setup()
{
  Serial.begin(9600);
  Serial.println("Start");
      
  pinMode(pinServo, OUTPUT);
  servo.attach(pinServo);
      		Serial.println("Master Setup done");
              //servo.write(90);
              
      		pinMode(pinX, INPUT);
      		pinMode(pinVref, INPUT);
      		pinMode(pinAZ, OUTPUT);
      		digitalWrite(pinAZ, LOW);
      pinMode(pinLED, OUTPUT);
      
      		valueX = analogRead(pinX)*5000.0/1024.0;
      		vrefValue = analogRead(pinVref)*5000.0/1024.0;
      		float difference = vrefValue - valueX;
      		calRate = difference/sensitivity;
      
      		//Timer1: 0,2,3,4,5 does not work due to servo lib
      		//uncomment #define USING_SERVO_LIB	true in DueTimer.h
      		Serial.println("Timer");
      		Timer6.attachInterrupt(getGyroX);
      		Timer6.setFrequency(10);
      		Timer6.start();
      		Serial.println("Slave Setup done");
      	digitalWrite(pinLED,LOW);
}

void loop()
{
  servo.write(angle);
}

void led(){

  for(int i=0;i<3;++i){
    digitalWrite(pinLED,HIGH);
    Serial.println("LED1");    
    //delay(50);
    Serial.println("LED3");
    digitalWrite(pinLED,LOW);
    //delay(50);
  }
  Serial.println("LED2");
}

void getGyroX(){

	valueX = analogRead(pinX)*5000.0/1024.0;
	vrefValue = analogRead(pinVref)*5000.0/1024.0;
	int difference = (int)vrefValue - valueX;
	rotationRate = (difference/sensitivity - calRate)/4;
        rotationRate = (int) rotationRate; 
	valChanged = true;
        angle += rotationRate;
        Serial.println(angle);
        if(angle > upperBound){
		angle = upperBound-1;
  led();
        }else if(angle < lowerBound){
		angle = lowerBound+1;
  led();
	}
}
/*
void slaveRequestHandler(){
 	//Serial.println("recv");
	//if(valChanged){
	    Wire.write(winkel);
	    valChanged = false;
	//}else{
	//    Wire.write(0);
	//}
}
 
void sendRequest(){
	//Serial.println("send");
	Wire.requestFrom(2, 2);
	if(Wire.available()>0){
		//Serial.println("recv");
		angle = Wire.read();
		Serial.println(angle);
		
	servo.write(angle);
	}
	else{
		Serial.println("nothing available");
	}
}*/
