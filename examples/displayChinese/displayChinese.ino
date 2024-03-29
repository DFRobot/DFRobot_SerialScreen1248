/*!
  * file displayChinese.ino
  * 
  * Display Chinese characters in different ways and colors
  * @Display Chinese characters:"创客科技"
  *
  * Copyright   [DFRobot](http://www.dfrobot.com), 2016
  * Copyright   GNU Lesser General Public License
  *
  * version  V1.0
  * date  2019-7-4
  */

#include <Arduino.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include "DFRobot_SerialScreen1248.h"

#ifdef ARDUINO_AVR_UNO
SoftwareSerial Serial1(2, 3); //RX, TX
#endif

DFRobot_SerialScreen1248 screen;

unsigned char dis[]={0x10,0x20,0x40,0x10,0x82,0x10,0x28,0x2F,0xFE,0xE4,0x82,0x10,0x44,0xA9,0x02,0x22,
                     0x82,0xFE,0x82,0xA1,0xF8,0x20,0x8F,0x10,0x7C,0xA2,0x08,0xFC,0x82,0x10,0x44,0xA5,
                     0x10,0x22,0x82,0xFC,0x44,0xA0,0xE0,0x70,0x83,0x44,0x44,0xAF,0x1E,0x68,0xEE,0x44,
                     0x58,0xA3,0xF8,0xA7,0x82,0x28,0x42,0x22,0x08,0x20,0x82,0x10,0x42,0x23,0xF8,0x20,
                     0x82,0x28,0x3E,0x62,0x08,0x20,0x86,0xC6,};//Font type Song body 9 font "创客科技"

void setup() {
    Serial.begin(115200);
    Serial1.begin(19200);
    screen.begin(Serial1);
    screen.setDbgSerial(Serial);
    /*eMoveMode_t:   eMove_left = left
                     eMove_right = right
                     eMove_hold = hold
                     eMove_down = down
                     eMove_up = up
                     eMove_flash = flash
                     eMove_marquee = marquee
      eColorMode_t:  eColor_red = red
                     eColor_yellow = yellow
                     eColor_green = green
                     eColor_cyan = cyan
                     eColor_blue = blue
                     eColor_purple = purple
                     eColor_white = white
    */
    screen.disChiCharacter(eMove_hold,eColor_red,dis,sizeof(dis));//Still display red "创客科技"
}

void loop() {

}
