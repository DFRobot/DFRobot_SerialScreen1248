/*!
  * file setMoveMode.ino
  * 
  * Display characters in different ways and colors
  * @Display Chinese characters:"DFROBOT"
  *
  * Copyright   [DFRobot](http://www.dfrobot.com), 2016
  * Copyright   GNU Lesser General Public License
  *
  * version  V1.0
  * date  2019-7-6
  */

#include <Arduino.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include "DFRobot_SerialScreen1248.h"

#ifdef ARDUINO_AVR_UNO
SoftwareSerial Serial1(2, 3); //RX, TX
#endif

DFRobot_SerialScreen1248 screen;

const char *s="DFROBOT";
void setup() {
    Serial.begin(115200);
    Serial1.begin(19200);
    screen.begin(Serial1);
    screen.setDbgSerial(Serial);
}

void loop() {
    /*Switch a mobile display mode every 2s*/
    eMoveMode_t buf[]= {eMove_left,eMove_right,eMove_hold,eMove_down,eMove_up,eMove_flash,eMove_marquee};
    for(int i = 0; i < sizeof(buf)/sizeof(eMoveMode_t); i++){
        screen.disString(buf[i],eColor_red,s,strlen(s));  //display string "DFROBOT"
        delay(2000);
    }
}
