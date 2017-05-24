//simple Tx on pin D12
//Written By : Mohannad Rawashdeh
// 3:00pm , 13/6/2013
//http://www.genotronex.com/
//..................................
#include <VirtualWire.h>
#include <SoftwareSerial.h>
#define Yaxispin 5 
#define simTx 7
#define simRx 8

    SoftwareSerial gsm(simTx,simRx);

void setup()
{
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_set_rx_pin(12);
    vw_setup(4000);  // Bits per sec
    pinMode(13, OUTPUT);
    gsm.begin(9600);
    vw_rx_start();       // Start the receiver PLL running
    delay(1000);
    Serial.println("Setup Complete");
}
    void loop(){
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
    if(buf[0]=='1'){
       digitalWrite(13,1);
       Serial.println("Alcohol under limit");
    }
      
    if(buf[0]=='0'){
      digitalWrite(13,0);
      Serial.println("DANGER: Alcohol above limit");
    }
    
    int pinval = analogRead(Yaxispin);
    int pinvalabs = abs(500-pinval);//abs = absolute value
    // values 630 is -60 degree slanting and 370 is +60 degree slanting
    // we allow the bike to bend but if it falls down the message is sent
    if(pinvalabs>130){
        Serial.println("Bike Might have fallen");
        Serial.println("Sending SMS...");
        //Set SMS format to ASCII
        gsm.write("AT+CMGF=1\r\n");
        delay(1000);
       
        //Send new SMS command and message number
        gsm.write("AT+CMGS=\"07194XXXXX\"\r\n");//Replace with your mobile number
        delay(1000);
         
        //Send SMS content
        gsm.write("Alert: Bike might have fallen");
        delay(1000);
         
        //Send Ctrl+Z / ESC to denote SMS message is complete
        gsm.write((char)26);
        delay(1000);
           
        Serial.println("SMS Sent!");
    }

    }
    }
