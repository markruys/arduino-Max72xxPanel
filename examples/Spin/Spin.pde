#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinDIN = 12;
int pinClk = 13;
int pinCS = 10;
int numberOfHorizontalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinDIN, pinClk, pinCS, numberOfHorizontalDisplays);

void setup() {
  matrix.setIntensity(0);
}

int wait = 50;
int inc = -2;

void loop() {
  
  for ( int x = 0; x < 8 * numberOfHorizontalDisplays - 1; x++ ) {
    matrix.fillScreen(LOW);
    matrix.drawLine(x, 0, 8 * numberOfHorizontalDisplays - 1 - x, 7, HIGH);
    delay(wait);
  }

  for ( int y = 0; y < 7; y++ ) {
    matrix.fillScreen(LOW);
    matrix.drawLine(8 * numberOfHorizontalDisplays - 1, y, 0, 7 - y, HIGH);
    delay(wait);
  }
  
  wait = wait + inc;
  if ( wait == 0 ) inc = 2;
  if ( wait == 50 ) inc = -2;
}