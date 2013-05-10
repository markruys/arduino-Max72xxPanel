/******************************************************************
 A library for controling a set of 8x8 LEDs with a MAX7219 or 
 MAX7221.
 This is a plugin for Adafruit's core graphics library, providing
 basic graphics primitives (points, lines, circles, etc.).
 You need to download and install Adafruit_GFX to use this library.
 
 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source hardware
 by purchasing products from Adafruit!
 
 Written by Mark Ruys.
 BSD license, check license.txt for more information.
 All text above must be included in any redistribution.
 ******************************************************************/

#ifndef Max72xxPanel_h
#define Max72xxPanel_h

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
  #include "pins_arduino.h"
#endif
#include <Adafruit_GFX.h>

class Max72xxPanel : public Adafruit_GFX {

public:

  /* 
   * Create a new controler 
   * Params :
   * dataPin		pin on the Arduino where data gets shifted out
   * clockPin		pin for the clock
   * csPin		pin for selecting the device 
   * hDisplays          number of displays horizontally
   * vDisplays          number of displays vertically -- ONLY 1 VERTICAL DISPLAY IS SUPPORTED
   */
  Max72xxPanel(int dataPin, int clkPin, int csPin, int hDisplays=1, int vDisplays=1);

  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  void fillScreen(uint16_t color);

  /* 
   * Set the shutdown (power saving) mode for the device
   * Params :
   * status	If true the device goes into power-down mode. Set to false
   *		for normal operation.
   */
  void shutdown(boolean status);

  /* 
   * Set the brightness of the display.
   * Params:
   * intensity	the brightness of the display. (0..15)
   */
  void setIntensity(int intensity);

  /*
   * To prevent flicker, enable double buffering while drawing.
   * When you disable double buffering, your drawing is copied
   * to the display(s).
   * Params :   If true double buffering is enabled
   */
  void doubleBuffering(boolean enabled);

private:
  int SPI_MOSI;    /* Data is shifted out of this pin*/
  int SPI_CLK;     /* The clock is signaled on this pin */
  int SPI_CS;      /* This one is driven LOW for chip selectzion */
  int hDisplays;   /* The number of horizontal displays */
  int vDisplays;   /* The number of vertical displays */

  /* Send out a single command to the device */
  void spiTransfer(byte opcode, byte data, int addr=-1);

  /* We keep track of the led-status for all max 8 devices in this array */
  byte *buffer;
  boolean doubleBuffer;
};

#endif	// Max72xxPanel_h



