#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

int pinRandom = A0;

int wait = 100; // In milliseconds

void setup() {
  matrix.setIntensity(4); // Set brightness between 0 and 15

  randomSeed(analogRead(pinRandom)); // Initialize random generator
}

int x, y = 0;
int xNext, yNext;

void loop() {

  matrix.drawPixel(x, y, HIGH);

  delay(wait);

  matrix.drawPixel(x, y, LOW); // Erase the old position of our dot

  do {
    switch ( random(4) ) {
      case 0: xNext = constrain(x + 1, 0, matrix.xMax); yNext = y; break;
      case 1: xNext = constrain(x - 1, 0, matrix.xMax); yNext = y; break;
      case 2: yNext = constrain(y + 1, 0, matrix.yMax); xNext = x; break;
      case 3: yNext = constrain(y - 1, 0, matrix.yMax); xNext = x; break;
    }
  }
  while ( x == xNext && y == yNext ); // Repeat until we find a new coordinate

  x = xNext;
  y = yNext;
}
