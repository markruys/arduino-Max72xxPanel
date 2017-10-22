/******************************************************************
 A library for controling a set of 8x8 LEDs with a MAX7219 or
 MAX7221 displays.

 This is a plugin for Adafruit's core graphics library, providing
 basic graphics primitives (points, lines, circles, etc.).
 You need to download and install Adafruit_GFX to use this library.

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source hardware
 by purchasing products from Adafruit!

 Written by Mark Ruys, 2013.
 BSD license, check license.txt for more information.
 All text above must be included in any redistribution.

 "Panel_No_Adafruit" extension by Andreas Horneffer, 2016

 Datasheet: http://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf

 ******************************************************************/

#ifndef Max72xxPanel_h
#define Max72xxPanel_h

/* 
 * Uncomment the following line if you do not want to 
 * include the Adafruit_GFX class. 
*/
// #define Panel_No_Adafruit

/* 
 * Uncomment the following line if you do not want to use
 * the SPI library and do bit-banging transfer instead
 * (E.g. because the SPI interface is already used by other hardware.)
*/
// #define BitBang_SPI

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
  #include "pins_arduino.h"
#endif

#ifndef Panel_No_Adafruit
  #include <Adafruit_GFX.h>
  class Max72xxPanel : public Adafruit_GFX {
#else
  class Max72xxPanel {
#endif

public:

  /*
   * Create a new controler
   * Parameters:
   * csPin         pin for selecting the device
   * hDisplays     number of displays horizontally
   * vDisplays     number of displays vertically
   * NOTE: The last two parameters are only used when using bit-banging! When using the 
   *       SPI library (the default!) these values are ignored and you need to check the 
   *       documentation of your hardware to see which pins you need to connect the Max72xx to.
   * dataPin       pin used to transfer the data when using bit-banging
   * clkPin        pin used for the clock when using bit-banging
   */
    //Max72xxPanel(byte csPin, byte hDisplays=1, byte vDisplays=1);
    Max72xxPanel(byte csPin, byte hDisplays=1, byte vDisplays=1, byte dataPin=0, byte clkPin=0);

  /*
   * Define how the displays are ordered. The first display (0)
   * is the one closest to the Arduino.
   */
  void setPosition(byte display, byte x, byte y);

  /*
   * Define if and how the displays are rotated. The first display
   * (0) is the one closest to the Arduino. rotation can be:
   *   0: no rotation
   *   1: 90 degrees clockwise
   *   2: 180 degrees
   *   3: 90 degrees counter clockwise
   */
  void setRotation(byte display, byte rotation);

#ifndef Panel_No_Adafruit
  /*
   * Implementation of Adafruit's setRotation(). Probably, you don't
   * need this function as you can achieve the same result by using
   * the previous two functions.
   */
  void setRotation(byte rotation);
#endif

  /*
   * Draw a pixel on your canvas. Note that for performance reasons,
   * the pixels are not actually send to the displays. Only the internal
   * bitmap buffer is modified.
   */
  void drawPixel(int16_t x, int16_t y, uint16_t color);

  /*
   * As we can do this much faster then setting all the pixels one by
   * one, we have a dedicated function to clear the screen.
   * The color can be 0 (blank) or non-zero (pixel on).
   */
  void fillScreen(uint16_t color);

  /*
   * Set the shutdown (power saving) mode for the device
   * Paramaters:
   * status     If true the device goes into power-down mode. Set to false
   *            for normal operation.
   */
  void shutdown(boolean status);

  /*
   * Set the brightness of the display.
   * Paramaters:
   * intensity  the brightness of the display. (0..15)
   */
  void setIntensity(byte intensity);

  /*
   * After you're done filling the bitmap buffer with your picture,
   * send it to the display(s).
   */
  void write();

private:
  byte SPI_CS; /* SPI chip selection */

  /* Send out a single command to the device */
  void spiTransfer(byte opcode, byte data=0);

#ifdef Panel_No_Adafruit
  /* Panel width and height in pixels, otherwise part of the Adafruit class. */
  int WIDTH, HEIGHT;
#endif

#ifdef BitBang_SPI
  /* pin numbers for data (Master-Out-Slave-In) and Clock */
  byte SPI_MOSI, SPI_CLK;
#endif


  /* We keep track of the led-status for 8 devices in this array */
  byte *bitmap;
  byte bitmapSize;

  byte hDisplays;
  byte *matrixPosition;
  byte *matrixRotation;
};

#endif  // Max72xxPanel_h



