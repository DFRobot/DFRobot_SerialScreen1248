# 12x48 Flexible RGB LED Matrix.

This RGB soft screen is composed of 12x48 RGB lights. It communicates with the main control through the serial port to display strings and change the font color.
You can set the display brightness and moving speed, modify and display the Chinese Characters.

## DFRobot_SerialScreen1248 Library for Arduino
---------------------------------------------------------
Provide an Arduino library for the 1248 RGB flexible Screen.

## Table of Contents

* [Summary](#summary)
* [Feature](#feature)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [Credits](#credits)
<snippet>
<content>

## Summary
This is a library for the Arduino IDE, which can help Arduino to communicate with 12x48 Flexible RGB LED Matrix.<br>
The library makes it easy to configure the sensor via Serial<br>

## Feature
1. Support soft and hard serial communication, baud rate 19200
2. Support Chinese display.
3. Support string display

# Installation

Download the library ZIP file and unzip it to the Arduino folder of the library.<br>

## Methods

```C++

#include "DFRobot_SerialScreen1248.h"

/*!
 * @brief Initialize the communication serial port
 *
 * @param &s_  Stream port
 * @return  true if execute successfully, false otherwise.
 */
bool begin(Stream &s_);

/*!
 * @brief Set the debug serial port
 *
 * @param &s_  Stream port
 * @return  true if execute successfully, false otherwise.
 */
void setDbgSerial(Stream &s_){dbg = &s_;}

/*!
 * @brief Booted display
 *
 * @return  true if execute successfully, false otherwise.
 */
bool powerOn();

/*!
 * @brief shut down
 *
 * @return  true if execute successfully, false otherwise.
 */
bool shutDown();

/*!
 * @brief Set the display brightness level
 *
 * @param b_  Brightness level
 *    eBrightLevel_1 
 *    eBrightLevel_2
 *    eBrightLevel_3 
 *    eBrightLevel_4 
 *    eBrightLevel_5
 *    eBrightLevel_6
 *    eBrightLevel_7 
 *    eBrightLevel_8 
 * @return  true if execute successfully, false otherwise.
 */
bool setBrightness(eBrightLevel_t b_);

/*!
 * @brief Set display speed level
 *
 * @param s_  Speed level
 *    eSpeedLevel_1 
 *    eSpeedLevel_2
 *    eSpeedLevel_3 
 *    eSpeedLevel_4 
 *    eSpeedLevel_5
 *    eSpeedLevel_6
 *    eSpeedLevel_7 
 *    eSpeedLevel_8 
 * @return  true if execute successfully, false otherwise.
 */

/*!
 * @brief Display Chinese characters.
 *
 * @param m_  Direction of movement
 *    eMove_left : Move to the left
 *    eMove_right : Move to the right
 *    eMove_hold : hold
 *    eMove_up : Move to the up
 *    eMove_down : Move to the down
 *    eMove_flash : flicker
 * @param c_  font color
 *    eColor_red : red
 *    eColor_yellow : yellow
 *    eColor_green : green
 *    eColor_cyan : cyan
 *    eColor_blue : blue
 *    eColor_purple : purple
 *    eColor_white : white
 * @param message_  
 * @param len_   length of message_
 * @return  true if execute successfully, false otherwise.
 */
bool disChiCharacter(eMoveMode_t m_, eColorMode_t c_,const unsigned char *message_, uint16_t len_);

/*!
 * @brief Display string.
 *
 * @param m_  Direction of movement
 *    eMove_left : Move to the left
 *    eMove_right : Move to the right
 *    eMove_hold : hold
 *    eMove_up : Move to the up
 *    eMove_down : Move to the down
 *    eMove_flash : flicker
 * @param c_  font color
 *    eColor_red : red
 *    eColor_yellow : yellow
 *    eColor_green : green
 *    eColor_cyan : cyan
 *    eColor_blue : blue
 *    eColor_purple : purple
 *    eColor_white : white
 * @param message_  
 * @param len_   length of message_
 * @return  true if execute successfully, false otherwise.
 */
bool disString(eMoveMode_t m_, eColorMode_t c_,const unsigned char *message_, uint16_t len_);

/*!
 * @brief Full screen lights up to show a certain color
 *
 * @param color_  RGB color
 *    eColor_red : red
 *    eColor_yellow : yellow
 *    eColor_green : green
 *    eColor_cyan : cyan
 *    eColor_blue : blue
 *    eColor_purple : purple
 *    eColor_white : white
 * @return  true if execute successfully, false otherwise.
 */
bool setFullScreenColor(eColorMode_t color_);
```

## Compatibility
Not compatible with Arduino IDE 1.0.x


MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno |       √      |             |            | 
Arduino Leonardo |       √      |             |            | 
Arduino Mega2560  |       √      |             |            | 

## Credits

·author [Arya xue.peng@dfrobot.com]
