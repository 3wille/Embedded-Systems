#include <SPI.h>

const int slavePin = 10; // SCE
const int ledPin = 2; // LED
const int resetPin = 5; // RST
const int dcPin = 6; // D/C

char alexFirst[ ] = "Alexander";
char alexLast[ ] = "Timmermann";
char alexMat[ ] = "6524072";

char freddyFirst[ ] = "Frederik";
char freddyLast[ ] = "Wille";
char freddyMat[ ] = "6533918";




uint8_t buf[6][84];
// 32-126
unsigned char font[95][6] =
{
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // space
{ 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00 }, // !
{ 0x00, 0x07, 0x00, 0x07, 0x00, 0x00 }, // "
{ 0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00 }, // #
{ 0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00 }, // $
{ 0x23, 0x13, 0x08, 0x64, 0x62, 0x00 }, // %
{ 0x36, 0x49, 0x55, 0x22, 0x50, 0x00 }, // &
{ 0x00, 0x00, 0x07, 0x00, 0x00, 0x00 }, // '
{ 0x00, 0x1C, 0x22, 0x41, 0x00, 0x00 }, // (
{ 0x00, 0x41, 0x22, 0x1C, 0x00, 0x00 }, // )
{ 0x0A, 0x04, 0x1F, 0x04, 0x0A, 0x00 }, // *
{ 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00 }, // +
{ 0x00, 0x50, 0x30, 0x00, 0x00, 0x00 }, // ,
{ 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 }, // -
{ 0x00, 0x60, 0x60, 0x00, 0x00, 0x00 }, // .
{ 0x20, 0x10, 0x08, 0x04, 0x02, 0x00 }, // slash
{ 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00 }, // 0
{ 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00 }, // 1
{ 0x42, 0x61, 0x51, 0x49, 0x46, 0x00 }, // 2
{ 0x21, 0x41, 0x45, 0x4B, 0x31, 0x00 }, // 3
{ 0x18, 0x14, 0x12, 0x7F, 0x10, 0x00 }, // 4
{ 0x27, 0x45, 0x45, 0x45, 0x39, 0x00 }, // 5
{ 0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00 }, // 6
{ 0x03, 0x71, 0x09, 0x05, 0x03, 0x00 }, // 7
{ 0x36, 0x49, 0x49, 0x49, 0x36, 0x00 }, // 8
{ 0x06, 0x49, 0x49, 0x29, 0x1E, 0x00 }, // 9
{ 0x00, 0x36, 0x36, 0x00, 0x00, 0x00 }, // :
{ 0x00, 0x56, 0x36, 0x00, 0x00, 0x00 }, // ;
{ 0x08, 0x14, 0x22, 0x41, 0x00, 0x00 }, // <
{ 0x14, 0x14, 0x14, 0x14, 0x14, 0x00 }, // =
{ 0x00, 0x41, 0x22, 0x14, 0x08, 0x00 }, // >
{ 0x02, 0x01, 0x51, 0x09, 0x06, 0x00 }, // ?
{ 0x32, 0x49, 0x79, 0x41, 0x3E, 0x00 }, // @
{ 0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00 }, // A
{ 0x7F, 0x49, 0x49, 0x49, 0x36, 0x00 }, // B
{ 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00 }, // C
{ 0x7F, 0x41, 0x41, 0x41, 0x3E, 0x00 }, // D
{ 0x7F, 0x49, 0x49, 0x49, 0x41, 0x00 }, // E
{ 0x7F, 0x09, 0x09, 0x09, 0x01, 0x00 }, // F
{ 0x3E, 0x41, 0x41, 0x49, 0x7A, 0x00 }, // G
{ 0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00 }, // H
{ 0x00, 0x41, 0x7F, 0x41, 0x00, 0x00 }, // I
{ 0x20, 0x40, 0x41, 0x3F, 0x01, 0x00 }, // J
{ 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00 }, // K
{ 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00 }, // L
{ 0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x00 }, // M
{ 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00 }, // N
{ 0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00 }, // O
{ 0x7F, 0x09, 0x09, 0x09, 0x06, 0x00 }, // P
{ 0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00 }, // Q
{ 0x7F, 0x09, 0x19, 0x29, 0x46, 0x00 }, // R
{ 0x26, 0x49, 0x49, 0x49, 0x32, 0x00 }, // S
{ 0x01, 0x01, 0x7F, 0x01, 0x01, 0x00 }, // T
{ 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00 }, // U
{ 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00 }, // V
{ 0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00 }, // W
{ 0x63, 0x14, 0x08, 0x14, 0x63, 0x00 }, // X
{ 0x07, 0x08, 0x70, 0x08, 0x07, 0x00 }, // Y
{ 0x61, 0x51, 0x49, 0x45, 0x43, 0x00 }, // Z
{ 0x00, 0x7F, 0x41, 0x41, 0x00, 0x00 }, // [
{ 0x02, 0x04, 0x08, 0x10, 0x20, 0x00 }, // backslash
{ 0x00, 0x41, 0x41, 0x7F, 0x00, 0x00 }, // ]
{ 0x04, 0x02, 0x01, 0x02, 0x04, 0x00 }, // ^
{ 0x40, 0x40, 0x40, 0x40, 0x40, 0x00 }, // _
{ 0x00, 0x01, 0x02, 0x04, 0x00, 0x00 }, // `
{ 0x20, 0x54, 0x54, 0x54, 0x78, 0x00 }, // a
{ 0x7F, 0x48, 0x44, 0x44, 0x38, 0x00 }, // b
{ 0x38, 0x44, 0x44, 0x44, 0x20, 0x00 }, // c
{ 0x38, 0x44, 0x44, 0x48, 0x7F, 0x00 }, // d
{ 0x38, 0x54, 0x54, 0x54, 0x18, 0x00 }, // e
{ 0x08, 0x7E, 0x09, 0x01, 0x02, 0x00 }, // f
{ 0x08, 0x54, 0x54, 0x54, 0x3C, 0x00 }, // g
{ 0x7F, 0x08, 0x04, 0x04, 0x78, 0x00 }, // h
{ 0x00, 0x48, 0x7D, 0x40, 0x00, 0x00 }, // i
{ 0x20, 0x40, 0x44, 0x3D, 0x00, 0x00 }, // j
{ 0x7F, 0x10, 0x28, 0x44, 0x00, 0x00 }, // k
{ 0x00, 0x41, 0x7F, 0x40, 0x00, 0x00 }, // l
{ 0x7C, 0x04, 0x78, 0x04, 0x78, 0x00 }, // m
{ 0x7C, 0x08, 0x04, 0x04, 0x78, 0x00 }, // n
{ 0x38, 0x44, 0x44, 0x44, 0x38, 0x00 }, // o
{ 0x7C, 0x14, 0x14, 0x14, 0x08, 0x00 }, // p
{ 0x08, 0x14, 0x14, 0x18, 0x7C, 0x00 }, // q
{ 0x7C, 0x08, 0x04, 0x04, 0x08, 0x00 }, // r
{ 0x48, 0x54, 0x54, 0x54, 0x20, 0x00 }, // s
{ 0x04, 0x3F, 0x44, 0x40, 0x20, 0x00 }, // t
{ 0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00 }, // u
{ 0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00 }, // v
{ 0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00 }, // w
{ 0x44, 0x28, 0x10, 0x28, 0x44, 0x00 }, // x
{ 0x0C, 0x50, 0x50, 0x50, 0x3C, 0x00 }, // y
{ 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00 }, // z
{ 0x00, 0x08, 0x36, 0x41, 0x00, 0x00 }, // {
{ 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00 }, // |
{ 0x00, 0x41, 0x36, 0x08, 0x00, 0x00 }, // }
{ 0x10, 0x08, 0x08, 0x10, 0x08, 0x00 } // ~
};

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
  SPI.transfer(slavePin, 0b10110000); //0xE0
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
    for(int y=0; y<84; ++y){
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

int printChar(int x, int y, char value){
  Serial.println(value);
  if(x >= 42 && x<=0 || y >= 78 && y<=0){//check bounds
    return -1;
  }else if(x%6==0){
    int ascii = value;
    int tablePosition = ascii - 32;
    for(int i=0;i<6;++i){
      buf[x/8][y+i]=font[tablePosition][i];
    }
    sendBuffer();
    return 0;
  }else{
    int ascii = value;
    int tablePosition = ascii - 32;
    for(int i=0;i<6;++i){
      uint8_t block = font[tablePosition][i];
      
      uint8_t upperLeast = buf[x/8][y+i]; //upper Block, less significant bits
      upperLeast = upperLeast << x % 8; //set all bits but first x%8 to 0
      upperLeast = upperLeast >> x % 8; //reset to actual positions
      uint8_t upperMost = block << x % 8 ; //upper Block, more significant bits
      uint8_t upper = upperLeast | upperMost; //upper block
      buf[x/8][y+i] = upper;
      
      uint8_t lowerMost = buf[x/8+1][y+i]; //upper Block, more significant bits
      lowerMost = lowerMost >> x % 8; //set all bits but last x%8 to 0
      lowerMost = lowerMost << x % 8; //reset to actual positions
      uint8_t lowerLeast = block >> x % 8 ; //lower Block, less significant bits
      uint8_t lower = lowerLeast | lowerMost; //lower block
      buf[x/8+1][y+i] = lower;
    }
    sendBuffer();
    return 1;
  }

}

void printStringCentered(int x, char* string){
  int y;
  y = 84/2 - (sizeof(string)/2);
  int temp = y;
  for(int i=0;i<sizeof(string);++i){
    printChar(x,y,string[i]);
    temp += 6;
  }
  temp = y;
}

void loop() {
  int x=0;
  printStringCentered(x, alexFirst);
  ++x;
  printStringCentered(x, alexLast);
  ++x;
  printStringCentered(x, alexMat);
  delay(5000);
  
  x=0;
  printStringCentered(x, freddyFirst);
  ++x;
  printStringCentered(x, freddyLast);
  ++x;
  printStringCentered(x, freddyMat);
  delay(5000);
}
