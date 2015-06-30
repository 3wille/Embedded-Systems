#include <SPI.h>

const int slavePin = 10; // SCE
const int ledPin = 2; // LED
const int resetPin = 5; // RST
const int dcPin = 6; // D/C

uint8_t buf[6][84];


// clock
// 21 -> 4MHz
// 84 -> 1MHz??
const int clockDivider = 84;

void setup() {
  Serial.begin(9600);
  //Pin Setup
  pinMode(ledPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  pinMode(dcPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  digitalWrite(dcPin, LOW);
  
  //SPI Setup
  SPI.begin(slavePin);
  SPI.setClockDivider(slavePin, clockDivider);
  
  //Display Setup
  delay(500);
  digitalWrite(resetPin, LOW);
  delay(500);
  digitalWrite(resetPin, HIGH);
  delay(500);
  //init
  digitalWrite(dcPin, LOW);
  SPI.transfer(slavePin, 0x21);
  SPI.transfer(slavePin, 0x14);
  SPI.transfer(slavePin, 0xE0); //0xE0
  SPI.transfer(slavePin, 0x20);
  SPI.transfer(slavePin, 0x0c);
  digitalWrite(dcPin, HIGH);
  Serial.println("Setup done");
}

void sendCommand(unsigned int command){
  digitalWrite(dcPin, LOW);
  SPI.transfer(slavePin, command);
}

void sendData(uint8_t data){
  digitalWrite(dcPin, HIGH);
  SPI.transfer(slavePin, data);
}

void setPixel(int x, int y, int value){
 // Serial.println("Set Pixel");
  if(value==1){
    buf[x/8][y] |= 1 << (x % 8);
  }else{
    buf[x/8][y] &= ~(1 << (x % 8));
  }
}
/*
void setPixel(int x, int y, bool value){
  Serial.println("Set Pixel");
  if(value){
    buf[x/8][y] |= 1 << (x % 8);
  }else{
    buf[x/8][y] &= ~(1 << (x % 8));
  }
  //sendBuffer();
}*/

void printBuffer(){
  for(int x=0;x<6;++x){
    for(int y=0; y<84; y++){
      Serial.print(buf[x][y]);
    }
    Serial.print("\n");
  }
}

void sendBuffer(){
  for(int x=0;x<6;++x){
    for(int y=0; y<84; y++){
      sendData((uint8_t)buf[x][y]);
    }
  }
  Serial.println("Buffer");
}

void loop() {
  printBuffer();
  delay(1000);
  for(int j=0; j<84; j++){
    Serial.print("j: ");
    Serial.print(j);
    Serial.print("\n");
    for(int i=0; i<48; i++){
      //Serial.print("i: ");
      //Serial.print(i);
      //Serial.print("\n");
      setPixel(i,j,1);
    }
    sendBuffer();
    printBuffer();
    delay(20);      
  }
  printBuffer();
  delay(100);
  for(int j=0; j<84; j++){
    for(int i=0; i<48; i++){
      setPixel(i,j,0);
    }
    sendBuffer();
    delay(20);      
  }
  delay(100);
  printBuffer();
}
