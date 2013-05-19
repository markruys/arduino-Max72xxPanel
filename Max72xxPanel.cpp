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

#include <Adafruit_GFX.h>
#include "Max72xxPanel.h"
#include <SPI.h>

// The opcodes for the MAX7221 and MAX7219
#define OP_NOOP         0
#define OP_DIGIT0       1
#define OP_DIGIT1       2
#define OP_DIGIT2       3
#define OP_DIGIT3       4
#define OP_DIGIT4       5
#define OP_DIGIT5       6
#define OP_DIGIT6       7
#define OP_DIGIT7       8
#define OP_DECODEMODE   9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

Max72xxPanel::Max72xxPanel(int csPin, int hDisplays, int vDisplays) {

  Max72xxPanel::SPI_CS = csPin;
  Max72xxPanel::hDisplays = hDisplays;
  Max72xxPanel::vDisplays = vDisplays;

  Max72xxPanel::doubleBuffer = false;
  Max72xxPanel::buffer = (byte*)malloc(hDisplays * vDisplays * 8);

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  pinMode(SPI_CS, OUTPUT);

  // Clear the screen
  fillScreen(0);

  // Make sure we are not in test mode
  spiTransfer(OP_DISPLAYTEST, 0);

  // We need the multiplexer to scan all segments
  spiTransfer(OP_SCANLIMIT, 7);

  // We don't want the multiplexer to decode segments for us
  spiTransfer(OP_DECODEMODE, 0);

  // Enable display
  shutdown(false);

  // Set the brightness to a medium value
  setIntensity(7);

  constructor(Max72xxPanel::hDisplays * 8, Max72xxPanel::vDisplays * 8);
}

void Max72xxPanel::shutdown(boolean b) {
  spiTransfer(OP_SHUTDOWN, b ? 0 : 1);
}

void Max72xxPanel::setIntensity(int intensity) {
  spiTransfer(OP_INTENSITY, intensity & 0x0f);
}

void Max72xxPanel::drawPixel(int16_t x, int16_t y, uint16_t color) {
  drawFastVLine(x, y, 1, color);
}

void Max72xxPanel::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
  if ( x >= 0 && x < width() && y >= 0 && y < height() ) {
		byte *ptr = (byte *)buffer + x + y / 8 * hDisplays * 8;
		y %= 8;
    while ( h > 0 ) {
      int hPart = min(8 - y, h); // Ranging from 0 to 8
			byte val = ((1 << hPart) - 1) << y;

			if ( color ) {
				*ptr |= val;
			}
			else {
				*ptr &= ~val;
			}

			h -= hPart;
			y = 0;
			ptr += hDisplays * 8;
		}

		spiTransfer(OP_DIGIT0 + x % 8);
  }
}

void Max72xxPanel::fillScreen(uint16_t color) {

  for ( int x = hDisplays * vDisplays * 8 - 1; x >= 0; x-- ) {
    buffer[x] = color ? 0xff : 0;
  }

  for ( int opcode = OP_DIGIT0; opcode <= OP_DIGIT7; opcode++ ) {
    spiTransfer(opcode);
  }
}

void Max72xxPanel::doubleBuffering(boolean enabled) {

  boolean flush = ! enabled && doubleBuffer;

  doubleBuffer = enabled;

  if ( flush ) {
    for ( int row = 0; row < 8; row++ ) {
    	spiTransfer(OP_DIGIT0 + row, 0);
    }
  }
}

void Max72xxPanel::spiTransfer(byte opcode, byte data) {
	// If opcode > OP_DIGIT7, send the opcode and data to all displays
	// If opcode <= OP_DIGIT7, display the column with data in our buffer for all displays.
	// We do not support (nor need) to use the OP_NOOP opcode.

  if ( ! doubleBuffer ) {
    // Enable the line
    digitalWrite(SPI_CS, LOW);

    // Now shift out the data
    for ( int display = hDisplays * vDisplays - 1; display >= 0; display-- ) {
      SPI.transfer(opcode);
      SPI.transfer(opcode <= OP_DIGIT7 ? buffer[display * 8 + (opcode - OP_DIGIT0)] : data);
    }

    // Latch the data onto the display(s)
    digitalWrite(SPI_CS, HIGH);
  }
}
