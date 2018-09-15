#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
// i.e. connect CS to 10, DIN to 11, CLK to 13 for Arduino Uno
int numberOfHorizontalDisplays = 8;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

String tape = "Hello :)";
int wait = 20; // In milliseconds

void setup() {

  matrix.setIntensity(7); // Use a value between 0 and 15 for brightness

/*
 * the two for loops below may need to be modified
 * depending on the ordering and orientation of your displays
 */

 // the setPosition function is responsible for the ordering of displays
  for(int i = 0; i < 4; i++) {
    matrix.setPosition(i, i, 0);  // The i'th display is at <i, 0>
  }

  // the setRotation function is responsible for the orientation of displays
  for(int i = 0; i < 8; i++) {
    matrix.setRotation(i, 1);     // rotate all displays 90 degrees
  }
}

void loop() {
  matrix.printToDisplay(tape, wait);
}
