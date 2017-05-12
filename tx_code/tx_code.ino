//simple Tx on pin D12
//Written By : Mohannad Rawashdeh
// 3:00pm , 13/6/2013
//http://www.genotronex.com/
//..................................
#include <VirtualWire.h>
char *controller;
int MQ3pin = 0; //A0
int IRpin = 1;//A1
void setup() {
  pinMode(13,OUTPUT);
vw_set_ptt_inverted(true); //
vw_set_tx_pin(12);
vw_setup(4000);// speed of data transfer Kbps
}

void loop(){
  if(analogRead(MQ3pin)<200 && analogRead(IRpin)>900){ //set "200" according to your limit (0 is the lowest ||| 1023 is the highest level of alcohol content)
    //IRpin is digital but we are using it as analogRead here (900 is high)
    controller="1"  ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13,1);
    Serial.println("Alcohol content under limit and helmet is ON");
    delay(2000);
  }
  else{
    controller="0"  ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13,0);
    Serial.println("BIKE OFF");
    delay(2000);
  }


} 
