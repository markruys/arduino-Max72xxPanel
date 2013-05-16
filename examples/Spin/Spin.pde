#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

Max72xxPanel matrix = Max72xxPanel(12, 11, 10); // DIN pin, CLK pin, CS pin

void setup() {
  matrix.setIntensity(15);
}

int wait = 50;
int inc = -2;

void loop() {
  
  for ( int i = 0; i < 7; i++ ) {
    matrix.fillScreen(LOW);
    matrix.drawLine(i, 0, 7 - i, 7, HIGH);
    delay(wait);
  }

  for ( int i = 0; i < 7; i++ ) {
    matrix.fillScreen(LOW);
    matrix.drawLine(7, i, 0, 7 - i, HIGH);
    delay(wait);
  }
  
  wait = wait + inc;
  if ( wait == 0 ) inc = 2;
  if ( wait == 50 ) inc = -2;
}
