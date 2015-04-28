int brightness = 0;
int led_output = 13;
int led_lower = 11;
int led_higher = 9;
int button_lower_count =0;

void setup()
{
    pinMode(led_output, OUTPUT);
    pinMode(led_lower, INPUT);
    pinMode(led_higher, INPUT);


    pmc_set_writeprotect(false);
    pmc_enable_periph_clk(ID_TC0);

    TC_Configure(TC0, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
    TC_SetRC(TC0,0,100);
    
    

    
    Serial.begin(9600);
    analogWrite(led_output, brightness);

    TC0->TC_CHANNEL[0].TC_IER=TC_IER_CPCS;
    TC0->TC_CHANNEL[0].TC_IDR=~TC_IER_CPCS;
    NVIC_ClearPendingIRQ(TC0_IRQn);
    NVIC_EnableIRQ(TC0_IRQn);
    TC_Start(TC0,0);
}

void loop(){
  Serial.println(brightness);
  delay(500);
}
void TC0_Handler()
{
    TC_GetStatus(TC0,1);
    //Serial.println("Timer");
    if(digitalRead(led_lower) == LOW)
    {
      button_lower_count++;
      if(button_lower_count >=500) {
        brightness -= 10;
        if (brightness < 0)
        {
            brightness = 0;
        }
        analogWrite(led_output, brightness);
        button_lower_count = 0;
      }
    }
    if(digitalRead(led_higher) == LOW)
    {
        brightness += 10;
        if (brightness > 255)
        {
            brightness = 255;
        }
        analogWrite(led_output, brightness);
    }
}
