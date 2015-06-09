#include <Wire.h>
#include <DueTimer.h>
#include "avr/ServoTimers.h"
#include "sam/ServoTimers.h"
#include "Servo.h"




int dev = 0; // 0 = master, 1=slave


//Master
Servo servo;
int pinServo = 4;
int upperBound = 159;
int lowerBound = 0;
int slaveAddr = 1;

//Slave
int pinX = 5;
int pinVref = 7;
int pinAZ = 8;
int vrefValue; 
int valueX = 0;
int alignment = 90;
float sensitivity = 9.1;
int8_t rate = 0;
bool valChanged = false;



void setup()
{
	Serial.begin(9600);
	if(dev==0){//master: servo
		Wire.begin();
		pinMode(pinServo, OUTPUT);
		servo.attach(pinServo);
	}else{//slave: gyro
		pinMode(pinX, INPUT);
		pinMode(pinVref, INPUT);
		pinMode(pinAZ, OUTPUT);
		digitalWrite(pinAZ, LOW);
		//Timer1: 0,2,3,4,5 does not work due to servo lib
		//uncomment #define USING_SERVO_LIB	true in DueTimer.h
		Timer1.attachInterrupt(getGyroX);
		Timer1.setFrequency(10);
		Timer1.start();
		Wire.begin(1);
		Wire.onRequest(requestHandler);
	}
}

void loop()
{
	Serial.println(rate);
}

void getGyroX(){
	valueX = analogRead(pinX)*5000.0/1024.0;
	vrefValue = analogRead(pinVref)*5000.0/2024.0;
	float difference = vrefValue - valueX;
	float rotationRate = difference/sensitivity;
	rate = (int8_t) rotationRate;
	valChanged = true;
}

void requestHandler(){
	if(valChanged){
	    Wire.write(rate);
	    valChanged = false;
	}else{
		Wire.write(0);
	}
}