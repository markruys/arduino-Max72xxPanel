#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

Max72xxPanel matrix = Max72xxPanel(12, 11, 10); // DIN pin, CLK pin, CS pin

String tape = "Arduino";
int wait = 200; // In milliseconds

int spacer = 1;
int width = 5 + spacer; // Our font is 5 pixel width

void setup() {
  matrix.setIntensity(7); // Use a value between 0 and 15 for brightness
}

void loop() {
  
  for ( int i = 0 ; i < width * tape.length() + 7 - spacer; i++ ) {
    
    int letter = i / width;
    int x = i % width;
    
    matrix.doubleBuffering(true); // Prevent screen flicker
    
    matrix.fillScreen(LOW);
    
    if ( letter < tape.length() ) {
      matrix.drawChar(7 - x, 0, tape[letter], HIGH, LOW, 1);
    }
    
    if ( letter > 0 ) {
      matrix.drawChar(7 - x - width, 0, tape[letter - 1], HIGH, LOW, 1);
    }

    matrix.doubleBuffering(false); // Send drawing to display
    
    delay(wait);
  }
}

