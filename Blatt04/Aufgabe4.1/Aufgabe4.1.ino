int master = 1;
int pin_led = 13;
int pin_button = 12;

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
	}else{
			pinMode(pin_led, OUTPUT);
	}
	Serial.println("Setup complete");
}

void loop(){
	if(master==1){
	    Serial3.print(brightness);
	}else{
		analogWrite(pin_led, Serial3.read());
	}
	delay(100);
}

void TC6_Handler()
{
	uint32_t status;
	status = TC2->TC_CHANNEL[0].TC_SR;

  	if (digitalRead(pin_button) == LOW)
  	{
  		++button_count;
  		if (button_count >= 30) {
  			pressed();
  			button_count = 0;
  		}
  	}
}

void pressed(){
	if(rising == 1){
		brightness += 10;
	}else{
		brightness -= 10;
	}
	if(brightness>=255){
		brightness = 255;
		rising = 0;
	}
	if(brightness<=0){
		brightness = 0;
		rising = 1;
	}
}