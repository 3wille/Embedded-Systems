int master = 0; // master=1, slave=0
int pin_led = 12;
int pin_button = 11;
int pin_intern_led = 13;

int button_count = 0;
int brightness = 0;
int rising = 1;

void setup(){
	Serial.begin(9600);
	Serial3.begin(4800);

	if(master == 1){
		pmc_set_writeprotect(false);
		pmc_enable_periph_clk(ID_TC6);

		TC2->TC_CHANNEL[0].TC_RC = 2625;
		TC_Configure(TC2, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
		TC2->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
		TC2->TC_CHANNEL[0].TC_IDR = ~TC_IER_CPCS;

		NVIC_ClearPendingIRQ(TC6_IRQn);
		NVIC_EnableIRQ(TC6_IRQn);

		TC_Start(TC2, 0);

		pinMode(pin_button, INPUT);
		pinMode(pin_intern_led, OUTPUT);
		digitalWrite(pin_intern_led, 0);

	}else{
		pinMode(pin_led, OUTPUT);
		analogWrite(pin_led, 0);
	}



	Serial.println("Setup complete");
}

void loop(){
	if(Serial3.available()>0){
	    if(master==1){
	        int recv = Serial3.read();
	        if(recv == 1){
	            master_led_foo();
	        }
	    }else if(master==0){
	    	int recv = Serial3.read();
	    	if(recv == 1){
	    		slave_led_foo();
	    	}
	    }
	}
}

void TC6_Handler()
{
	//Serial.println("Handler");
	uint32_t status;
	status = TC2->TC_CHANNEL[0].TC_SR;

	if (digitalRead(pin_button) == LOW)
	{
		//Serial.println("LOW");
		++button_count;
		if (button_count >= 30) {
			sendOne();
			button_count = 0;
		}
	}else if(digitalRead(pin_button) == HIGH){
		//Serial.println("HIGH");
		button_count = 0;
	}
}

void sendOne(){
	Serial3.write(1);
}

void slave_led_foo(){
	//int i = 0;
	for(int i=0;i<256;i++){
		analogWrite(pin_led, i);
		delay(10);
		Serial.println(i);
	}
	sendOne();
	for(int i=255;i>0;i--){
	    analogWrite(pin_led, i);
	    delay(10);
	    Serial.println(i);
	}
	sendOne();
}

void master_led_foo(){
	int i;
	for(i=0; i<3; i++){
	    digitalWrite(pin_intern_led, HIGH);
	    delay(50);
	    digitalWrite(pin_intern_led, LOW);
	    delay(50);
	}
}
