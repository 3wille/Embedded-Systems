int pinLED = 13;

void setup() {
  pinMode(pinLED,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()>0){
    getInput();
  }
}

void getInput(){
  String command="";
  char currentChar='a';
  while(Serial.available()>0 && currentChar!='\n'){
    currentChar = Serial.read();
    if(currentChar!='\n'){
      Serial.print("Char: ");
      Serial.println(currentChar);
      Serial.println((int)currentChar);
      command+=currentChar;
    }
    //Serial.println(input);
  }
  
  Serial.print("Command: ");
  Serial.println(command);
  if(command == "n" || command == "LED_ON"){
    Serial.println("Command on");
    digitalWrite(pinLED, HIGH);
  }else if(command == "f" || command == "LED_OFF"){
    Serial.println("Command off");
    digitalWrite(pinLED,LOW);
  }else{
    Serial.println("unknown command");
  }
}
