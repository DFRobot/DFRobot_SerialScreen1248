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

unsigned char dis[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF3,0xEF,0x1C,0xF1,
                        0xCF,0x80,0x49,0x24,0xA2,0x4A,0x2A,0x80,0x49,0x44,0xA2,0x4A,0x22,0x00,0x49,0xC7,
                        0x22,0x72,0x22,0x00,0x49,0x45,0x22,0x4A,0x22,0x00,0x49,0x04,0xA2,0x4A,0x22,0x00,
                        0x49,0x04,0xA2,0x4A,0x22,0x00,0xF3,0x8E,0xDC,0xF1,0xC7,0x00,0x00,0x00,0x00,0x00,
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//Font type Song body 9 font "DFROBOT"

void setup() {
    Serial.begin(115200);
    Serial1.begin(19200);
    screen.begin(Serial1);
    screen.setDbgSerial(Serial);
    screen.disChiCharacter(eMove_hold,eColor_red,dis,sizeof(dis));//Still display red "DFROBOT"
}

void loop() {
    /*Switch a mobile display mode every 2s*/
    eMoveMode_t buf[]= {eMove_left,eMove_right,eMove_hold,eMove_down,eMove_up,eMove_flash,eMove_marquee};
    for(int i = 0; i < sizeof(buf)/sizeof(eMoveMode_t); i++){
        screen.disChiCharacter(buf[i],eColor_red,dis,sizeof(dis));
        delay(2000);
}
}
