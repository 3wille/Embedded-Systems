int pin_Standby = 13;
int pin_Motor_In2 = 12;
int pin_Motor_In1 = 11;
int pin_Motor_PWM = 10;
int PWM_Value= 0;
int mode = 0; // 0 = steigend CW, 1 = fallend CW, 2/3 = CCW 

void setup() {
  pinMode(pin_Standby ,OUTPUT);
  pinMode(pin_Motor_In2 ,OUTPUT);
  pinMode(pin_Motor_In1 ,OUTPUT);
  pinMode(pin_Motor_PWM ,OUTPUT);
  digitalWrite(pin_Motor_In1, HIGH);
  digitalWrite(pin_Motor_In2, LOW);
  digitalWrite(pin_Standby, HIGH);
}

void loop() {
  if(mode == 0)
  {
    PWM_Value += 1;
    if (PWM_Value > 255) {
        PWM_Value = 255;
        mode = 1;
        digitalWrite(pin_Motor_In1, HIGH);
        digitalWrite(pin_Motor_In2, LOW);        
        delay(20);
    }
    analogWrite(pin_Motor_PWM, PWM_Value);
  }
  else if(mode == 1)
  {
    PWM_Value -= 1;
    if (PWM_Value < 0) {
        PWM_Value = 0;
        mode = 2;
        digitalWrite(pin_Motor_In1, LOW);
        digitalWrite(pin_Motor_In2, HIGH); 
        delay(20);
    }
    analogWrite(pin_Motor_PWM, PWM_Value);
  }
  else if(mode == 2)
  {
    PWM_Value += 1;
    if (PWM_Value < 255) {
        PWM_Value = 255;
        mode = 3;
        digitalWrite(pin_Motor_In1, LOW);
        digitalWrite(pin_Motor_In2, HIGH);
        delay(20); 
    }
    analogWrite(pin_Motor_PWM, PWM_Value);
  }  
  else if(mode == 3)
  {
    PWM_Value += 1;
    if (PWM_Value < 255) {
        PWM_Value = 255;
        mode = 0;
        digitalWrite(pin_Motor_In1, HIGH);
        digitalWrite(pin_Motor_In2, LOW); 
        delay(20);
    }
    analogWrite(pin_Motor_PWM, PWM_Value);
  }
}
