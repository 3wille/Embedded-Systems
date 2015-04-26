#define DELAY 2

// TODO
/* 
Takte etc bestimmen
*/

int control = 10;

void setup()
{
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC0);
  
  TC_Configure(TC0, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK2);
  
  NVIC_ClearPendingIRQ(TC0_IRQn);
  NVIC_EnableIRQ(TC0_IRQn);
  
  TC_SetRC(TC0, 0, 131200);
  TC_Start(TC0, 0);
    
  pinMode(13, OUTPUT);
  pinMode(9, INPUT);
  pinMode(11, INPUT);
  //attachInterrupt(3, increase, RISING);
  //attachInterrupt(5, decrease, RISING);
}

void loop()
{

}

void increase() {
  if (control <= 245) {
    control += 10;
  }
}

void decrease() {
  if (control >= 10) {
    control -= 10;
  }
}

void TC0_Handler()
{
  TC_GetStatus(TC0, 1);
  if (digitalRead(9) == 0) {
    increase();
  }
  if (digitalRead(11) == 0) {
    decrease();
  }
  analogWrite(13, control % 256);
}
