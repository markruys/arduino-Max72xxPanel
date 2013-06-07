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
  Max72xxPanel::doubleBuffer = false;
  Max72xxPanel::bufferSize = hDisplays * vDisplays * 8;
  Max72xxPanel::buffer = (byte*)malloc(bufferSize);

  SPI.begin();
//SPI.setBitOrder(MSBFIRST);
//SPI.setDataMode(SPI_MODE0);
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

  constructor(hDisplays << 3, vDisplays << 3);
}

void Max72xxPanel::shutdown(boolean b) {
  spiTransfer(OP_SHUTDOWN, b ? 0 : 1);
}

void Max72xxPanel::setIntensity(int intensity) {
  spiTransfer(OP_INTENSITY, intensity);
}

void Max72xxPanel::drawPixel(int16_t x, int16_t y, uint16_t color) {
  drawLine(x, y, x, y, color);
}

void Max72xxPanel::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {

	if ( rotation >= 2 ) {										// rotation == 2 || rotation == 3
		x0 = _width - 1 - x0;
		x1 = _width - 1 - x1;
	}

	if ( rotation == 1 || rotation == 2 ) {		// rotation == 1 || rotation == 2
		y0 = _height - 1 - y0;
		y1 = _height - 1 - y1;
	}

	if ( rotation & 1 ) {     								// rotation == 1 || rotation == 3
		drawLineHelper(y0, x0, y1, x1, color);
	}
	else {
		drawLineHelper(x0, y0, x1, y1, color);
	}
}

void Max72xxPanel::drawLineHelper(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
	if ( x0 == x1 ) {
		if ( x0 < 0 || x0 >= WIDTH ) {
			return;
		}
		if ( y0 > y1 ) {
			swap(y0, y1);
		}
		y0 = constrain(y0, 0, HEIGHT - 1);
		int h = constrain(y1 - y0 + 1, 0, HEIGHT - y0);

		byte *ptr = (byte *)buffer + x0 + WIDTH * (y0 >> 3);
		y0 &= 0b111;

    while ( h > 0 ) {
      int hPart = min(8 - y0, h); // Ranging from 0 to 8
			byte val = ((1 << hPart) - 1) << y0;

			if ( color ) {
				*ptr |= val;
			}
			else {
				*ptr &= ~val;
			}

			h -= hPart;
			y0 = 0;
			ptr += WIDTH;
		}

		spiTransfer(OP_DIGIT0 + (x0 & 0b111));
	}
	else {
	  Adafruit_GFX::drawLine(x0, y0, x1, y1, color);
	}
}

void Max72xxPanel::fillScreen(uint16_t color) {

  for ( int x = bufferSize - 1; x >= 0; x-- ) {
    buffer[x] = color ? 0xff : 0;
  }

  for ( int opcode = OP_DIGIT0; opcode <= OP_DIGIT7; opcode++ ) {
    spiTransfer(opcode);
  }
}

void Max72xxPanel::doubleBuffering(boolean enabled) {

  boolean old = doubleBuffer;

  doubleBuffer = enabled;

  if ( old && ! doubleBuffer ) {
    for ( int row = OP_DIGIT7; row >= OP_DIGIT0; row-- ) {
    	spiTransfer(row);
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
    for ( int display = (bufferSize / 8) - 1; display >= 0; display-- ) {
      SPI.transfer(opcode);
      SPI.transfer(opcode <= OP_DIGIT7 ? buffer[display * 8 + (opcode - OP_DIGIT0)] : data);
    }

    // Latch the data onto the display(s)
    digitalWrite(SPI_CS, HIGH);
  }
}
