#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

Max72xxPanel matrix = Max72xxPanel(12, 11, 10);

const int pinRandom = A0;

const int wait = 100; // in milli seconds
const int length = 8;

int x[length], y[length];
int ptr, nextPtr;

void setup() {
  matrix.setIntensity(4); // Set brightness between 0 and 15

  // Reset all variables
  for ( ptr = 0; ptr < length; ptr++ ) {
    x[ptr] = y[ptr] = 0;
  }
  nextPtr = 0;

  // Initialize random generator
  randomSeed(analogRead(pinRandom));
}

void loop() {

  // Shift pointer to the next segment
  ptr = nextPtr;
  nextPtr = next(ptr);
  
  matrix.drawPixel(x[ptr], y[ptr], HIGH); // Draw the head of the snake

  delay(wait);

  if ( ! occupied(nextPtr) ) {
    matrix.drawPixel(x[nextPtr], y[nextPtr], LOW); // Remove the tail of the snake
  }

  for ( int attempt = 0; attempt < 10; attempt++ ) {
     
    // Jump at random one step up, down, left, or right
    switch ( random(4) ) {
    case 0: x[nextPtr] = constrain(x[ptr] + 1, 0, 7); y[nextPtr] = y[ptr]; break;
    case 1: x[nextPtr] = constrain(x[ptr] - 1, 0, 7); y[nextPtr] = y[ptr]; break;
    case 2: y[nextPtr] = constrain(y[ptr] + 1, 0, 7); x[nextPtr] = x[ptr]; break;
    case 3: y[nextPtr] = constrain(y[ptr] - 1, 0, 7); x[nextPtr] = x[ptr]; break;
    }
    
    if ( ! occupied(nextPtr) ) {
      break; // The spot is empty, break out the for loop
    }
  }
}

boolean occupied(int ptrA) {
  for ( int ptrB = 0 ; ptrB < length; ptrB++ ) {
    if ( ptrA != ptrB ) {
      if ( equal(ptrA, ptrB) ) {
        return true;
      }
    }
  }

  return false;
}

int next(int ptr) {
  return (ptr + 1) % length;
}

boolean equal(int ptrA, int ptrB) {
  return x[ptrA] == x[ptrB] && y[ptrA] == y[ptrB];
}

