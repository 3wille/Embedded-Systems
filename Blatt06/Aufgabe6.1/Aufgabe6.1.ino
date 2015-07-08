#include <SPI.h>
#include <SD.h>

const int displayPin = 10; // SCE
const int ledPin = 2; // LED
const int resetPin = 6; // RST
const int dcPin = 5; // D/C

const int shieldPin = 4; //SDCS

const int rowLength = 84;
const int columnLength = 48;
const int columnBlocks = 6;

uint8_t buf[columnBlocks][rowLength];
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
  SPI.begin(displayPin);
  SPI.setClockDivider(displayPin, clockDivider);
  
  //Display Setup
  delay(500);
  digitalWrite(resetPin, LOW);
  delay(500);
  digitalWrite(resetPin, HIGH);
  delay(500);
  //init
  digitalWrite(dcPin, LOW);
  SPI.transfer(displayPin, 0x21);
  SPI.transfer(displayPin, 0x14);
  SPI.transfer(displayPin, 0b10110000); //0xE0
  SPI.transfer(displayPin, 0x20);
  SPI.transfer(displayPin, 0x0c);
  digitalWrite(dcPin, HIGH);
  
  Serial.println(SD.begin(shieldPin));
  Serial.println("Setup done");
  
  //int result = parseTextFile("/text2.txt");
  //Serial.print("Result: ");
  //Serial.println(result);
  //printTextFile("text2.txt");
}

void sendCommand(unsigned int command){
  digitalWrite(dcPin, LOW);
  SPI.transfer(displayPin, command);
}

void sendData(uint8_t data){
  digitalWrite(dcPin, HIGH);
  SPI.transfer(displayPin, data);
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
  //Serial.println("Buffer");
}

int printChar(int x, int y, char value){
  if(x >= 42 && x<=0 || y >= 78 && y<=0){//check bounds
    return -1;
  }else if(x%8==0){
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

void printStringCentered(int x, String string){
  int y;
  Serial.println(string);
  Serial.print("Size: ");
  Serial.println(string.length());
  y = (84 - (string.length()*6)) / 2;
  
  for(int i=0;i<string.length();++i){
    Serial.println(x);
    Serial.println(y);
    Serial.println(string[i]);
    Serial.print("return: ");
    Serial.print(printChar(x,y,string[i]));
    Serial.print("\n");
    y += 6;
  }
}

void printString(int row, String string){
  int y=0;
  for(int i=0; i<string.length();++i){
    printChar(row,y,string[i]);
    y += 6;
  }
}

void clearDisplay(){
  //Serial.println("clearing");
  for(int x=0;x<6;++x){
    for(int y=0;y<84;++y){
      buf[x][y] = 0;
    }
  }
  sendBuffer();
  //Serial.println("cleared");
}
/*
void printTextFile(char* fileName){
  int result = parseTextFile(fileName);
  if(result == 0){
    Serial.println("too many characters");
  }
}*/

/*
// max chars: 84
int parseTextFile(char* fileName){
  clearDisplay();
  Serial.println("parsing");
  if(!SD.exists(fileName)){
    Serial.println("not existing");
    return  0;
  }
  File textFile = SD.open(fileName,FILE_READ);
  
  //initializers
  char chars[84];
  int charCount=0;
  String words[84];
  int wordCount=0;
  String rows[6];
  int rowCount=0;
  String currentWord;
  char currentChar;
  bool newRow=true;
  bool endOfFile = false;
  
  
  while(textFile.available() && !endOfFile){
    currentChar = textFile.read();
    chars[charCount]=currentChar;
    
    if(currentChar == '\n'){
      endOfFile = true;
      return 1;
    }else if(currentChar == ' '){
      //END OF WORD
      if(rows[rowCount].length()+currentWord.length()+1<rowLength/6){//word fits into current row
        if(newRow){
          rows[rowCount] += currentWord;//append full word to new row
          newRow = false;
        }else{
          rows[rowCount] += " " + currentWord;//append empty space and full word to row  
        }
      }else{
        //Serial.print("Row end: ");
        //Serial.println(rowCount);
        ++rowCount;//move to next row
        if(rowCount > 5){
          return 0;
        }
        rows[rowCount] = currentWord;//start new row with full word
        //Serial.println(rows[rowCount]);
        newRow = true;
      }
      //Serial.println(currentWord);
      currentWord="";//reset current word
      //Serial.println("end of word");
    }
    else{
      //Serial.println(currentChar);
      currentWord += currentChar;//append char to current word
    }
    charCount++;
  }

  textFile.close();
  
  for(int i=0; i<charCount; ++i){
    Serial.print(chars[i]);
  }
  for(int i=0; i<6;++i){
    Serial.print("Row: ");
    Serial.println(i);
    Serial.println(rows[i]);
  }
  for(int i=0; i < 6;++i){
    printString(i*8,rows[i]);
  }
  return 1;
}*/

void printTextFile(char* fileName){
  clearDisplay();

  if(!SD.exists(fileName)){
    Serial.println("not existing");
    return;
  }
  Serial.println("Printing text file");
  File textFile = SD.open(fileName,FILE_READ);
  
  String text="";
  String rows[6];
  for(int  i=0; i<6;++i){
    rows[i]="";
  }
  int currentRow=0;

  Serial.println(textFile.available());
  while(textFile.available()){
    char currentChar = textFile.read();
    if(currentRow>5){
      Serial.println("too many characters");
      printString(0, "too many characters");
      return;
    }
    if(currentChar=='\n'){
      Serial.println("EOF");
      break;
    }else{
      //Serial.println(currentChar);
      int currentLength = rows[currentRow].length();
      //Serial.println(currentLength);
      
      if(currentLength>=13){
        //Serial.print("bar ");
        //Serial.println(currentChar);
        //Serial.println(currentChar==' ');
        if(currentChar==' '||rows[currentRow][12]==' '){
          //Serial.println("fuck");
          rows[currentRow]+=' ';
          ++currentRow;
        }else{
          //Serial.println("foo");
          rows[currentRow]+='-';
          ++currentRow;
          rows[currentRow]+=currentChar;
        }
      }else{
        //Serial.println("foo");
        rows[currentRow]+=currentChar;
      }
    }
    //Serial.print("end of: ");
    //Serial.println(currentChar);
    //Serial.println("bla");
  }

  //Serial.println("test");
  textFile.close();
  for(int i=0; i<6;++i){
    //Serial.print("Row: ");
    //Serial.println(i);
    //Serial.println(rows[i]);
  }
  //Serial.println("test1");
  for(int i=0; i < 6;++i){
    printString(i*8,rows[i]);
  }
}



void printImageFile(char* fileName){
  clearDisplay();  
  if(!SD.exists(fileName)){
    Serial.println("not existing");
    return;
  }
  Serial.println("Printing image file");
  File textFile = SD.open(fileName,FILE_READ);
  
  int xsize;
  int ysize;
  int mode=0;
  String xs;
  String ys;
  
  while(textFile.available()&&mode!=2){
    char currentChar = textFile.read();
    Serial.print(currentChar);
    if(mode==0){
      if(currentChar==','){
        mode=1;
      }else{
        xs+=currentChar;
      }
    }else if(mode == 1){
      if(currentChar=='\n'){
        mode=2;
      }else{
        ys+=currentChar;
      }
    }
  }
  
  xsize = xs.toInt();
  ysize = ys.toInt();
  Serial.print(xsize);
  Serial.print(":");
  Serial.println(ysize);
  int bild[xsize][ysize];
  int currentXPos=0;
  int currentYPos=0;
  while(textFile.available()){
    char currentChar = textFile.read();
    if(currentChar!=','){
      //Serial.print(currentChar);
      if(currentChar=='0'){
        bild[currentXPos][currentYPos] = 0;
      }else if(currentChar=='1'){
        bild[currentXPos][currentYPos] = 1;  
      }
      
      ++currentXPos;
      if(currentXPos==xsize){
        currentXPos = 0;
        ++currentYPos;
      }
    }
  }
  
  Serial.println("");
  int xBorder = (84-xsize)/2;
  int yBorder = (48-ysize)/2;
  for(int i = 0; i<xsize;++i){
    for(int j = 0; j<ysize;++j){
      //Serial.print(bild[i][j]);
      setPixel(yBorder+j,xBorder+i,bild[i][j]);
      //setPixel(j,i,bild[i][j]);      
    }

  }
  sendBuffer();
}

void getInput(){
  String input="";
  char currentChar='a';
  while(Serial.available()>0 && currentChar!='\n'){
    currentChar = Serial.read();
    Serial.println(currentChar);
    input+=currentChar;
    //Serial.println(input);
  }
  
  String command="";
  String file="";
  //Serial.println(input.length());
  for(int i=0;i<input.length();++i){
    if(input[i]==' '){
      command = input.substring(0,i);
      file = input.substring(i+1,input.length());
    }
  }
  
  Serial.println(command);
  Serial.println(file);
  char fileName[file.length()];
  file.toCharArray(fileName, file.length());
  Serial.println(fileName);
  if(command == "exists" || command == "e"){
    Serial.println("Command exists");
    Serial.println(SD.exists(fileName));
  }else if(command == "printText" || command == "pt"){
    Serial.println("Command text");
    printTextFile(fileName);
  }else if(command == "printImage" || command == "pi"){
    Serial.println("Command Image");
    printImageFile(fileName);
  }else{
    Serial.println("unknown command");
  }
  while(Serial.available()>0){
    Serial.println("kacke");
    Serial.println(Serial.read());
  }
}

void loop() {
  if(Serial.available()){
    //Serial.println("call");
    getInput();
  }
  /*
  printImageFile("tams.img");
  delay(1000);
  printImageFile("smile1.img");
  delay(1000);
  printImageFile("smile2.img");
  delay(1000);
  printImageFile("smile3.img");
  delay(1000);
  printTextFile("text1.txt");
  delay(1000);
  printTextFile("text2.txt");*/
}
