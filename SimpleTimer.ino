#include <Wire.h>
#include "RTClib.h"

// PIN definitions
#define RELAY_PIN 2

// FSM states
#define STATE_OFF  0
#define STATE_ON   1

// Timer settings
#define START_TIME  2144
#define END_TIME    2146

// variables
RTC_DS1307 RTC;
int fsm_state;

void setup() {
  
  Serial.begin(57600);
  Serial.println("SimpleTimer running...");
  Serial.println();

  Wire.begin();
  RTC.begin();  

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  fsm_state = STATE_OFF;
}

void loop() {

  DateTime now = RTC.now();
  int nowHourMinute = now.hour() * 100 + now.minute();

  // FSM states
  switch(fsm_state) {
    
    case STATE_OFF:
      if(nowHourMinute > START_TIME && nowHourMinute < END_TIME) {
        Serial.print(now.hour(), DEC);
        Serial.print(':');
        Serial.print(now.minute(), DEC);
        Serial.println(", it's time to wake up!");
        digitalWrite(RELAY_PIN, HIGH);
        fsm_state = STATE_ON;
      }
      break;
    
    case STATE_ON:
      if(nowHourMinute > END_TIME) {
        Serial.print(now.hour(), DEC);
        Serial.print(':');
        Serial.print(now.minute(), DEC);        
        Serial.println(", it's time to go to sleep!");
        digitalWrite(RELAY_PIN, LOW);
        fsm_state = STATE_OFF;
      }    
      break;
  }
}

