#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

String tape = "Arduino";
int wait = 200; // In milliseconds

int spacer = 1;
int width = 5 + spacer; // Our font is 5 pixel width

void setup() {
  matrix.setIntensity(7); // Use a value between 0 and 15 for brightness
}

void loop() {

  for ( int i = 0 ; i < width * tape.length() + matrix.width() - spacer; i++ ) {

    matrix.doubleBuffering(true); // Prevent screen flicker

    matrix.fillScreen(LOW);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;

    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < tape.length() ) {
        matrix.drawChar(x, (matrix.height() - 8) / 2, tape[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= width;
    }

    matrix.doubleBuffering(false); // Send drawing to display

    delay(wait);
  }
}

