#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() {
  matrix.setIntensity(0);
}

int wait = 50;
int inc = -2;

void loop() {

  for ( int x = 0; x < matrix.xMax; x++ ) {
    matrix.fillScreen(LOW);
    matrix.drawLine(x, 0, matrix.xMax - x, matrix.yMax, HIGH);
    delay(wait);
  }

  for ( int y = 0; y < matrix.yMax; y++ ) {
    matrix.fillScreen(LOW);
    matrix.drawLine(matrix.xMax, y, 0, matrix.yMax - y, HIGH);
    delay(wait);
  }

  wait = wait + inc;
  if ( wait == 0 ) inc = 2;
  if ( wait == 50 ) inc = -2;
}
