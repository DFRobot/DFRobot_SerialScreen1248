/*!
  * file power.ino
  * 
  * Switching machine.
  * @Booted after 5s shutdown.
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
void setup() {
    Serial.begin(115200);
    Serial1.begin(19200);
    screen.begin(Serial1);
    screen.setDbgSerial(Serial);
    delay(1000);
    screen.shutDown();      //shut down
    delay(5000);
    screen.powerOn();   //power ON
}

void loop() {

}
