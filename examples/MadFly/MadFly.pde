#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

Max72xxPanel matrix = Max72xxPanel(12, 11, 10);

int pinRandom = A0;

int wait = 100; // in milli seconds

void setup() {
  matrix.setIntensity(4); // You may raise brightness upto 15 if needed
  
  // Initialize random generator
  randomSeed(analogRead(pinRandom));
}

int x, y = 0;
int xNext, yNext;

void loop() {
  
  matrix.drawPixel(x, y, HIGH);
  
  delay(wait);
  
  matrix.drawPixel(x, y, LOW); // erase the old position of our dot
  
  do {
    switch ( random(4) ) {
      case 0: xNext = constrain(x + 1, 0, 7); yNext = y; break;
      case 1: xNext = constrain(x - 1, 0, 7); yNext = y; break;
      case 2: yNext = constrain(y + 1, 0, 7); xNext = x; break;
      case 3: yNext = constrain(y - 1, 0, 7); xNext = x; break;
    }
  }
  while ( x == xNext && y == yNext ); // repeat until we find a new coordinate

  x = xNext;
  y = yNext;  
}

