#include <Servo.h>

Servo servo;

void setup(){
	Serial.begin(9600);
	Serial.println("Setup");
	servo.attach(4);

}

void loop(){
	for(int i=90; i<181; i++){
	    servo.write(i);
	    delay(5);
	}
	for(int i=180; i>0; --i){
	    servo.write(i);
	    delay(5);
	}
        for(int i=0; i<89; i++){
	    servo.write(i);
	    delay(5);
	}
}
