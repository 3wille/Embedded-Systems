int led_output = 13;
int led_lower = 11;
int led_higher = 9;

volatile int button_lower_count = 0;
volatile int button_higher_count = 0;
volatile uint8_t brightness = 0;

void setup()
{
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC6);

  pinMode(led_output, OUTPUT);
  pinMode(led_lower, INPUT);
  pinMode(led_higher, INPUT);

  TC2->TC_CHANNEL[0].TC_RC = 2625;
  TC_Configure(TC2, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
  TC2->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
  TC2->TC_CHANNEL[0].TC_IDR = ~TC_IER_CPCS;

  NVIC_ClearPendingIRQ(TC6_IRQn);
  NVIC_EnableIRQ(TC6_IRQn);

  TC_Start(TC2, 0);
  Serial.begin(9600);

  Serial.println("Setup completed");
}

void loop() {
  delay(100);
  analogWrite(led_output, brightness);
  Serial.println(brightness);
}

void TC6_Handler()
{
  uint32_t status;
  status = TC2->TC_CHANNEL[0].TC_SR;

  //Serial.println("Timer");
  if (digitalRead(led_lower) == LOW)
  {
    ++button_lower_count;
    if (button_lower_count >= 100) {
      brightness -= 10;
      button_lower_count = 0;
    }
  }
  if (digitalRead(led_higher) == LOW)
  {
    ++button_higher_count;
    if (button_higher_count >= 100) {
      brightness += 10;
      button_higher_count = 0;
    }
  }

}
