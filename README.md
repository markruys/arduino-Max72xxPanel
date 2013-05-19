Max72xxPanel
============

An Arduino library for controlling a matrix of 8x8 LEDs with a MAX7219 or MAX7221 display driver. [Kits][hardware] sold for below 10 USD.

This is a plugin for Adafruit's core graphics library GFX, providing basic graphics primitives (points, lines, circles, characters, etc.). So besides this library, you need to download and install [Adafruit_GFX][gfx-download]. 

Written by Mark Ruys, <mark@paracas.nl>.

Usage
-----

Read [overview][gfx-docs] for instructions how to use Adafruit_GFX. Check out our [examples][examples] to get some inspiration.

Installation
------------

Place the [Max72xxPanel][download] and [Adafruit_GFX][gfx-download] library folders in your `<arduinosketchfolder>/libraries/` folder. You may need to create the `libraries` subfolder if its your first library. Restart the Arduino IDE. 


Features
--------
- Double buffering to prevent screen flicker. Check out ticker tape example for usage.
- Support for multiple matrix displays, connected in cascade.
- Uses the [SPI library][spi] to address the display(s).
- Very low memory footprint.

[download]: https://github.com/markruys/arduino-Max72xxPanel/archive/master.zip "Download Max72xxPanel library"
[gfx-download]: https://github.com/adafruit/Adafruit-GFX-Library "Download Adafruit GFX Graphics Library"
[gfx-docs]: http://learn.adafruit.com/adafruit-gfx-graphics-library/overview "Documentation Adafruit GFX Graphics Library"
[examples]: https://github.com/markruys/arduino-Max72xxPanel/tree/master/examples "Show Max72xxPanel examples"
[hardware]: https://www.google.com/search?q=MAX7219+Red+Dot+Matrix+Module "For kits, google MAX7219 Red Dot Matrix Module"
[spi]: http://arduino.cc/en/Reference/SPI "SPI library"

