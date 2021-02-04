/// Timer switch for control of the opus via a relay switch
/// Kieran Khamis - k.khamis@bham.ac.uk
//  04/02/21
//  For wiring see github https://github.com/kkhamis/Opus_relay_switch/blob/main/Opus%20relay%20switch_bread%20board%20wiring.pdf
/// For equipment list see https://github.com/kkhamis/Opus_relay_switch/blob/main/Bill%20of%20Materials.docx


// **** Libraries to include*****
#include <Wire.h>
#include "RTClib.h"
#include "LowPower.h" /
//------------------------------------------------------------

//constants-----------------------
const int relay_switch = 11;///digital pin for control of relay switch

//RTClib defines
RTC_DS1307 rtc; 
DateTime now;

///////
///------------------------------------------------------------------------------
///function to create a clean datatime string

void PrintTime(){
  DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println(",");
 //--------------------------------------------------------------------------------   
}



void setup() {
 Serial.begin(9600);     
 Serial.println("Starting clock.......");
 pinMode(relay_switch, OUTPUT);
   rtc.begin();                                    // start clock
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // set clock to time laptop time
  // January 21, 2014 at 3am you would call:
  //rtc.adjust(DateTime(2019, 5, 14, 17, 38, 0));
   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  }
 while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Check time:");
  PrintTime();
  digitalWrite(relay_switch, LOW);
}



void loop() {
 DateTime now = rtc.now();
 //if ((now.minute()==0)|(now.minute()==10)|(now.minute()==20)|(now.minute()==30)(now.minute()==40)|(now.minute()==50)){//10 min resolution
if ((now.minute()==0)|(now.minute()==15)|(now.minute()==45)|(now.minute()==45)){ ///15 min resolution
  PrintTime();
  Serial.println("sample");
digitalWrite(relay_switch, HIGH);
delay(90000);///power for 1 min 30 to ensure at least one measurment 
digitalWrite(relay_switch, LOW);
LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); //sleep to save power
}
else { 
  PrintTime();
  Serial.println("sleepy");
delay(200);
LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);//sleep to save power
}
}
