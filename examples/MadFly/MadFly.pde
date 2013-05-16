#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

Max72xxPanel matrix = Max72xxPanel(12, 11, 10); // DIN pin, CLK pin, CS pin

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
      case 0: xNext = constrain(x + 1, 0, 7); yNext = y; break;
      case 1: xNext = constrain(x - 1, 0, 7); yNext = y; break;
      case 2: yNext = constrain(y + 1, 0, 7); xNext = x; break;
      case 3: yNext = constrain(y - 1, 0, 7); xNext = x; break;
    }
  }
  while ( x == xNext && y == yNext ); // Repeat until we find a new coordinate

  x = xNext;
  y = yNext;  
}

