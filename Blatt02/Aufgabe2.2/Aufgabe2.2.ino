int pin_Standby = 13;
int pin_Motor_In2 = 12;
int pin_Motor_In1 = 11;
int pin_Motor_PWM = 10;
int PWM_Value = 0;
int mode = 0; // 0 = steigend CW, 1 = fallend CW, 2/3 = CCW

void setup() {
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC7);
  
  TC2->TC_CHANNEL[1].TC_RC = 12868;
  TC_Configure(TC2, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
  TC2->TC_CHANNEL[1].TC_IER = TC_IER_CPCS;
  TC2->TC_CHANNEL[1].TC_IDR = ~TC_IER_CPCS;

  NVIC_ClearPendingIRQ(TC7_IRQn);
  NVIC_EnableIRQ(TC7_IRQn);
  TC_Start(TC2, 1);

  pinMode(pin_Standby, OUTPUT);
  pinMode(pin_Motor_In2, OUTPUT);
  pinMode(pin_Motor_In1, OUTPUT);
  pinMode(pin_Motor_PWM, OUTPUT);
  
  digitalWrite(pin_Motor_In1, HIGH);
  digitalWrite(pin_Motor_In2, LOW);
  digitalWrite(pin_Standby, HIGH);

  Serial.begin(9600);
}

void loop() {
  Serial.println(mode);
  Serial.println(PWM_Value);
  delay(100);
}

void TC7_Handler() {
  uint32_t status;
  status = TC2->TC_CHANNEL[1].TC_SR;
  Serial.println("handler");
  if (mode == 0)
  {
    PWM_Value += 1;
    if (PWM_Value > 255) {
      PWM_Value = 255;
      mode = 1;
      digitalWrite(pin_Motor_In1, HIGH);
      digitalWrite(pin_Motor_In2, LOW);
    }
    analogWrite(pin_Motor_PWM, PWM_Value);
  }
  else if (mode == 1)
  {
    PWM_Value -= 1;
    if (PWM_Value < 0) {
      PWM_Value = 0;
      mode = 2;
      digitalWrite(pin_Motor_In1, LOW);
      digitalWrite(pin_Motor_In2, HIGH);
    }
    analogWrite(pin_Motor_PWM, PWM_Value);
  }
  else if (mode == 2)
  {
    PWM_Value += 1;
    if (PWM_Value < 255) {
      PWM_Value = 255;
      mode = 3;
      digitalWrite(pin_Motor_In1, LOW);
      digitalWrite(pin_Motor_In2, HIGH);
    }
    analogWrite(pin_Motor_PWM, PWM_Value);
  }
  else if (mode == 3)
  {
    PWM_Value -= 1;
    if (PWM_Value < 0) {
      PWM_Value = 0;
      mode = 0;
      digitalWrite(pin_Motor_In1, HIGH);
      digitalWrite(pin_Motor_In2, LOW);
    }
    analogWrite(pin_Motor_PWM, PWM_Value);
  }
}
