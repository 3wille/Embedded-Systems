#include <Wire.h>
#include <DueTimer.h>

int dev = 0; // 0=master 1=slave
int pin_led = 12;
int led=0;

void setup()
{

	Serial.begin(9600);
	if(dev == 0){
		Wire.begin();
		Timer3.attachInterrupt(allezweisekunden);
		Timer3.start(2000000);
	}
	else{
		pinMode(pin_led, OUTPUT);
		digitalWrite(pin_led, 0);
		Wire.begin(1);
		Wire.onReceive(dev1Receive);
		Wire.onRequest(dev1Request);
	}
}

void loop(){}

void dev1Receive(int recv){
	int mode = Wire.read();
	led = mode;
	if(mode == 1){
		digitalWrite(pin_led, HIGH);
	}
	else if(mode == 0){
		digitalWrite(pin_led, LOW);
	}
}

void dev1Request(){
	Wire.write(led);
}

void allezweisekunden(){
	Serial.println("interrupt");
	Wire.beginTransmission(1);
	if(led==0){
		Wire.write(1);
		//Serial.println("Wrote 1");
		led=1;
	}else{
		Wire.write(0);
		//Serial.println("Wrote 0");
		led=0;
	}
	Wire.endTransmission();


	Wire.requestFrom(1,1);
	while(Wire.available())    // slave may send less than requested
  	{ 
    	int c = Wire.read(); // receive a byte as character
    	Serial.print("Request: ");
    	Serial.print(c);         // print the character
    	Serial.print("\n");
  	}
}