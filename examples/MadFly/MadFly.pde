#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinDIN = 12;
int pinClk = 13;
int pinCS = 10;
int numberOfHorizontalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinDIN, pinClk, pinCS, numberOfHorizontalDisplays);

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
      case 0: xNext = constrain(x + 1, 0, numberOfHorizontalDisplays * 8 - 1); yNext = y; break;
      case 1: xNext = constrain(x - 1, 0, numberOfHorizontalDisplays * 8 - 1); yNext = y; break;
      case 2: yNext = constrain(y + 1, 0, 7); xNext = x; break;
      case 3: yNext = constrain(y - 1, 0, 7); xNext = x; break;
    }
  }
  while ( x == xNext && y == yNext ); // Repeat until we find a new coordinate

  x = xNext;
  y = yNext;  
}

