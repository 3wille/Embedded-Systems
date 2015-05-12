int pinX = 5;
int pinZ = 6;
int pinVref = 7;
int vrefValue; 
int valueX = 0;
int valueZ = 0;


void setup(){
  Serial.begin(9600);
  Serial.println("Setup start");

  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC0);
  Serial.println("1");
  int freq = VARIANT_MCK/128/10;

  TC_Configure(TC0, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
  TC_SetRA(TC0, 0, freq/2);
  TC_SetRC(TC0, 0, freq);
Serial.println("2");
  TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
  TC0->TC_CHANNEL[0].TC_IDR = ~TC_IER_CPCS;
Serial.println("3");
  NVIC_ClearPendingIRQ(TC0_IRQn);
  NVIC_EnableIRQ(TC0_IRQn);
Serial.println("4");
  TC_Start(TC0, 0);
Serial.println("5");
  pinMode(pinX, INPUT);
  pinMode(pinZ, INPUT);
  pinMode(pinVref, INPUT);
Serial.println("6");
  vrefValue = analogRead(pinVref);
  Serial.println("Vref: ");
  Serial.println(vrefValue);
//  Serial.print("\n");
}

void loop(){
  Serial.print("X: ");
  Serial.print(valueX);
  Serial.print("\n");
  Serial.print("Z: ");
  Serial.print(valueZ);
  Serial.print("\n");
  Serial.print("Abweichung X: ");
  Serial.print(vrefValue - valueX);
  Serial.print("\n");
  Serial.print("Abweichung Z: ");
  Serial.print(vrefValue - valueZ);
  Serial.print("\n");
  Serial.print("Drehrate X: ");
  Serial.print((valueX - vrefValue)/2);
  Serial.print("\n");
  Serial.print("Drehrate Z: ");
  Serial.print((valueZ - vrefValue)/2);
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("\n"); 
  delay(100);
}

void TC0_Handler(){
  valueX = analogRead(pinX);
  valueZ = analogRead(pinZ);
  TC_GetStatus(TC0,0);
/*  Serial.print("X: ");
  Serial.print(valueX);
  Serial.print("\n");
  Serial.print("Z: ");
  Serial.print(valueZ);
  Serial.print("\n");
  Serial.print("Abweichung X: ");
  Serial.print(vrefValue - valueX);
  Serial.print("\n");
  Serial.print("Abweichung Z: ");
  Serial.print(vrefValue - valueZ);
  Serial.print("\n");
  Serial.print("Drehrate X: ");
  Serial.print((valueX - vrefValue)/2);
  Serial.print("\n");
  Serial.print("Drehrate Z: ");
  Serial.print((valueZ - vrefValue)/2);
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("\n");*/
}