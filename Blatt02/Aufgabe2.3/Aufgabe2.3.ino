#include <stdbool.h>

const int pin_Standby = 5;
const int pin_Motor_In2 = 4;
const int pin_Motor_In1 = 3;
const int pin_Motor_PWM = 2;

const int button_cycle = 6;
const int button_PWM = 7;

volatile int PWM_Value = 0;
volatile int mode = 0; // 0 = steigend CW, CW, 2 = stop

volatile int button_cycle_count = 0;
volatile int button_PWM_count = 0;
volatile bool PWM_rising = true;


void setup()
{
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC6);

  TC2->TC_CHANNEL[0].TC_RC = 2625;
  TC_Configure(TC2, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
  TC2->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
  TC2->TC_CHANNEL[0].TC_IDR = ~TC_IER_CPCS;

  NVIC_ClearPendingIRQ(TC6_IRQn);
  NVIC_EnableIRQ(TC6_IRQn);

  TC_Start(TC2, 0);
  Serial.begin(9600);

  pinMode(pin_Standby, OUTPUT);
  pinMode(pin_Motor_In2, OUTPUT);
  pinMode(pin_Motor_In1, OUTPUT);
  pinMode(pin_Motor_PWM, OUTPUT);

  pinMode(button_cycle, INPUT);
  pinMode(button_PWM, INPUT);

  //Start: CW
  digitalWrite(pin_Motor_In1, HIGH);
  digitalWrite(pin_Motor_In2, LOW);
  digitalWrite(pin_Standby, HIGH);

  Serial.println("Setup complete");
}

void ch_mode()
{
  if(mode == 0)
  {
    mode = 1;
    digitalWrite(pin_Motor_In1, LOW);
    digitalWrite(pin_Motor_In2, HIGH);
  }
  else if (mode == 1)
  {
    mode = 2;
    digitalWrite(pin_Motor_In1, LOW);
    digitalWrite(pin_Motor_In2, LOW);
  }
  else if (mode == 2)
  {
    mode = 0;
    digitalWrite(pin_Motor_In1, HIGH);
    digitalWrite(pin_Motor_In2, LOW);
  }
}

void TC6_Handler()
{
  uint32_t status;
  status = TC2->TC_CHANNEL[0].TC_SR;

  //Serial.println("Timer");
  if (digitalRead(button_PWM) == LOW)
  {
    ++button_PWM_count;
    if (button_PWM_count >= 30) {
      if(PWM_rising){
        PWM_Value += 10;
      }
      else {
        PWM_Value -= 10;
      }
      if(PWM_Value>=255)
      {
        PWM_rising = !PWM_rising;
        PWM_Value = 255;
      }else if(PWM_Value<=0)
      {
        PWM_rising = !PWM_rising;
        PWM_Value= 0;
      }
      button_PWM_count = 0;
      Serial.println("PWM");
    }
  }
  else if(digitalRead(button_PWM) == HIGH){
      button_PWM_count = 0;
  }
  if (digitalRead(button_cycle) == LOW)
  {
    ++button_cycle_count;
    if (button_cycle_count >= 30) {
      button_cycle_count = 0;
      ch_mode();
      Serial.println("Mode");
    }
  }
  else if(digitalRead(button_cycle)==HIGH)
  {
    button_cycle_count = 0;
  }
  //Serial.println(button_cycle_count);

}

void loop()
{
  Serial.println(mode);
  Serial.println(PWM_Value);
  delay(100);
  analogWrite(pin_Motor_PWM, PWM_Value);
}