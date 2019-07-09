/*!
  * file setSpeed.ino
  * Set the speed at which the string moves.
  * @Set the displayed moving speed level.
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
eBrightLevel_t bright;

void setup() {
    /*Initialize communication interface (Serial1) and debug interface (Serial)*/
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
    screen.disString(eMove_left,eColor_red,"DFROBOT",strlen("DFROBOT"));
    /*Set the displayed moving speed level*/
    /*eBrightLevel_t: eSpeedLevel_1 = Speed class 1
                      eSpeedLevel_2 = Speed class 2
                      eSpeedLevel_3 = Speed class 3
                      eSpeedLevel_4 = Speed class 4
                      eSpeedLevel_5 = Speed class 5
                      eSpeedLevel_6 = Speed class 6
                      eSpeedLevel_7 = Speed class 7
                      eSpeedLevel_8 = Speed class 8
    */
    screen.setMoveSpeed(eSpeedLevel_1);

}

void loop() {
    screen.setMoveSpeed(eSpeedLevel_1);
    delay(5000);
    screen.setMoveSpeed(eSpeedLevel_8);
    delay(5000);
}