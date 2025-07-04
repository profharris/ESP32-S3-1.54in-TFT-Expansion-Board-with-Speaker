/* TFT_eSPI_Mandlebrot2.ino
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 * LCD 1.54in 240×240 color IPS TFT (ST7789V2)
 *
 * TFT_eSPI Graphics library: written by Bodmer 17/2/19
 *       https://github.com/Bodmer/TFT_eSPI
 * Don’t forget to update your TFT_eSPI “User_Setup.h” config file.
 *
 * NOTE¹:  You may NOT see the TFT_eSPI Mandlebrot Set plotted to
 * ¯¯¯¯¯¯  your Display, until you open the Serial Monitor!!!
 *
 * This sketch is a second Mandlebrot Set demo. It was written using
 * the TFT_eSPI graphics driver. It may run a little slow due to the
 * large number of floating-point calculations per pixel.
 *
 * The Mandelbrot set is well-known, even outside mathematics, for
 * how it exhibits complex ‘fractal’ structures when visualized and
 * magnified. The Mandelbrot set is defined as a set of complex
 * numbers for which the iterated function “Z^2 + C” doesn’t diverge
 * to infinity. Therefor the Mandelbrot set is essentially a visual
 * representation of how the behavior of a simple equation changes
 * depending on the starting complex number.
 *
 * NOTE: when plotted on the complex plane, the Mandelbrot Set forms
 * a distinctive shape, with points within the Set colored Black, &
 * points outside the Set colored based on how quickly they diverge.
 *
 * The Mandelbrot set is a “fractal”, meaning it exhibits self-
 * similarity at different scales, meaning that zooming in on any
 * part of the set reveals similar, but smaller, patterns.
 *
 * The Mandelbrot set is not just a pretty picture; it’s deeply
 * connected to various mathematical fields like number theory,
 * topology, and even physics. It is also a great example of how a
 * simple equation can lead to incredible complexity and beautiful,
 * intricate patterns.
 *
 * Wiring:      ST7789 1.54” 240×240 TFT Display
 * ¯¯¯¯¯¯¯
 * | ESP32-S3 Dev Board | SPI ST7789 1.54” 240×240 TFT |
 * |-------------------:|------------------------------|
 * |     GND            | 1. GND                       |
 * |     3V3            | 2. VDD (Power)               |
 * |     GPIO21         | 3. SCL SPI Clock      (SCLK) |
 * |     GPIO47         | 4. SDA SPI Data       (MOSI) |
 * |     GPIO45         | 5. RES TFT Reset       (RST) |
 * |     GPIO40         | 6. RS  Data/Command     (DC) |
 * |     GPIO41         | 7. CS  Chip Select      (CS) |
 * |     GPIO42         | 8. BLK BackLight        (BL) |
 */

#include <TFT_eSPI.h>       // Hardware-specific TFT_eSPI library
#include <SPI.h>            // Don’t forget to update “User_Setup.h”

TFT_eSPI tft = TFT_eSPI();  // Invoke custom TFT_eSPI library object

/* Configuration info defined in the TFT_eSPI “User_Setup.h” file.
 * ... a minimul TFT_eSPI “User_Setup.h” file is attached below.
 *
 * #define TFT_SCLK      21      // LCD ST7789 1.54 240×240 TFT SCK
 * #define TFT_MOSI      47      // SDI          "          TFT MOSI
 * #define TFT_RST       45      // Reset        "          TFT RST
 * #define TFT_DC        40      // D/C          "          TFT DC
 * #define TFT_CS        41      // CS           "          TFT CS
 * #define TFT_BL        42      // BackLight    "          TFT BL
 * #define TFT_BACKLIGHT_ON HIGH
 *
 * #define ST7789_DRIVER
 * #define TFT_RGB_ORDER TFT_BGR // ESP32-S3-WROOM Blue/Red reversed
 * #define TFT_INVERSION_ON      // ESP32-S3-WROOM-1
 * #define USE_HSPI_PORT         // Second Hardware SPI Port
 */

#define TFT_GREY   0x7BEF       // 16-bit 565RGB color
#define TFT_WIDTH     240       // Width  in pixels, Portrait mode
#define TFT_HEIGHT    240       // Height in pixels, Portrait mode

unsigned long runTime = 0;      // Mandlebrot2 calculation timer
float      sx = 0, sy = 0;      // Mandlebrot2 graphing variables
uint16_t   x0 = 0, x1 = 0, yy0 = 0, yy1 = 0;


void setup() {
  Serial.begin(115200);          // initialize Serial communication
  while(!Serial);                // wait for the Serial port to open

  //randomSeed(analogRead(A0));
  Serial.println(F("\nTFT_eSPI Mandlebrot2 demo:"));
  tft.init();                    // Setup the 1.54 240×240 color LCD
  tft.setRotation(3);            // Landscape orientation
}

void loop() {
  runTime = millis();            // Start the timer...
  tft.fillScreen(TFT_BLACK);     // Clear the screen

  tft.startWrite();
  for(int px=1; px < TFT_WIDTH; px++) {
    for(int py=0; py < TFT_HEIGHT; py++) {
      float x0 = (map(px, 0,TFT_WIDTH, -250000/2,-242500/2)) /100000.0;
      // Scaled x-coordinate of the pixel
      // (scaled to lie in the Mandelbrot X scale (-2.5, 1))
      float yy0 = (map(py, 0,TFT_HEIGHT, -75000/4,-61000/4)) /100000.0;
      // Scaled y-coordinate of the pixel
      // (scaled to lie in the Mandelbrot Y scale (-1, 1))
      float xx = 0.0;
      float yy = 0.0;
      int iteration     =   0;
      int max_iteration = 128;
      while(((xx*xx+yy*yy) < 4)  &&  (iteration < max_iteration)) {
        float xtemp = xx * xx - yy * yy + x0;
        yy = 2 * xx * yy + yy0;
        xx = xtemp;
        iteration++;
      }
      int color = rainbow((3 * iteration + 64) %128);
      yield(); tft.drawPixel(px,py, color);
    }
  }
  tft.endWrite();
  Serial.print(F("Run Time: "));
  Serial.print(millis() - runTime);
  Serial.println(F(" miliseconds (1/1000 sec)."));
  Serial.println(F("Press [RESET] to run again."));
  while(1) yield();
}

unsigned int rainbow(int value) { // 16-bit RGB565 Conversion.
  // Value is expected to be in range 0-127.
  // The value is converted to a spectrum color from 0 = Blue,
  // through to Red = Blue. 8+8+8(24-bit) to RGB565 Conversion.
  byte Red   = 0;   // Red   top 5 bits of a 16-bit color value,
  byte Green = 0;   // Green middle 6 bits,
  byte Blue  = 0;   // Blue  bottom 5 bits.

  byte quadrant = value / 32;
  if(quadrant == 0) {
    Blue  = 31;
    Green = 2 * (value % 32);
    Red   = 0;
  }
  if(quadrant == 1) {
    Blue  = 31 - (value % 32);
    Green = 63;
    Red   = 0;
  }
  if(quadrant == 2) {
    Blue  = 0;
    Green = 63;
    Red   = value % 32;
  }
  if(quadrant == 3) {
    Blue  = 0;
    Green = 63 - 2 * (value % 32);
    Red   = 31;
  }
  return (Red << 11) + (Green << 5) + Blue;
}

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
22:10:43.096 -> 
22:10:43.096 -> TFT_eSPI Mandlebrot2 demo:
22:10:44.752 -> Run Time: 1208 miliseconds (1/1000 sec).
22:10:44.752 -> Press [RESET] to run again.
22:10:55.840 -> 
22:10:55.840 -> TFT_eSPI Mandlebrot2 demo:
22:10:57.606 -> Run Time: 1208 miliseconds (1/1000 sec).
22:10:57.606 -> Press [RESET] to run again.
...
--------------------------------------------------------------------
OUTPUT:
¯¯¯¯¯¯¯
Sketch uses 372922 bytes (11%) of program storage space.
Maximum is 3145728 bytes.
Global variables use 21532 bytes (6%) of dynamic memory,
            leaving 306148 bytes for local variables.
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c

Leaving...
Hard resetting with RTC WDT...

*******************************************************************/

/*******************************************************************
// User_Setup.h (TFT_eSPI minimal)
// ¯¯¯¯¯¯¯¯¯¯¯¯
// ESP32-S3 1.54in TFT Expansion Board with Speaker
// LCD 1.54in 240×240 color IPS TFT (ST7789V2)

// Except for the intros, only “uncommented” lines are included.

//              TFT_eSPI USER DEFINED SETTINGS
// Set driver type, fonts to be loaded, pins used and SPI control method etc.
//
// See the “User_Setup_Select.h” file if you wish to be able to define multiple
// setups and then easily select which setup file is used by the compiler.
//
// If this file is edited correctly, all the library example sketches should
// run without any need to make more changes for a particular hardware setup!
// NOTE: some sketches are designed for a particular TFT pixel width/height

// User defined information reported by "Read_User_Setup" test & diagnostics
#define USER_SETUP_INFO "User_Setup"

// #############################################################################
// Section 1. Call up the right driver file and any options for it
// #############################################################################

#define ST7789_DRIVER       // Full configuration option, define additional parameters below for this display
//#define ST7789_2_DRIVER   // Minimal configuration option, define additional parameters below for this display

// #define TFT_RGB_ORDER TFT_RGB    // Colour order Red-Green-Blue
#define TFT_RGB_ORDER TFT_BGR       // Colour order Blue-Green-Red

// For ST7789, ST7735, ILI9163 and GC9A01 ONLY, define the pixel Width and Height in Portrait orientation
#define TFT_WIDTH  240              // ST7789 240x240 and 240x320
#define TFT_HEIGHT 240              // ST7789 240x240

// If colours are inverted (white shows as black) then uncomment one of the next
// 2 lines try both options, one of the options should correct the inversion.

#define TFT_INVERSION_ON            // ESP32-S3-WROOM-1
//#define TFT_INVERSION_OFF

// #############################################################################
// Section 2. Define the pins that are used to interface with the display here
// #############################################################################

// If a Backlight control signal is available then define the TFT_BL pin in
// Section 2 below. The backlight will be turned ON when tft.begin() is called,
// but the library needs to know if the LEDs are ON with the pin HIGH or LOW.

#define TFT_BL   42            // LED BackLight control pin
#define TFT_BACKLIGHT_ON HIGH  // Level to turn ON back-light (HIGH or LOW)

// For the ESP32-S3 Dev boards
// Hardware SPI can be mapped to any pins

#define TFT_SCLK 21         // SPI Clock pin
#define TFT_MOSI 47         // SPI Duplex Data pin
#define TFT_RST  45         // Reset pin (could connect to RST pin)
#define TFT_DC   40         // Data/Command control pin
#define TFT_CS   41         // Chip Select control pin
#define TFT_BL   42         // LED BackLight pin

#define TOUCH_CS -1         // Chip Select pin (T_CS) for the Touch Screen

// #############################################################################
// Section 3. Define the fonts that are to be used here
// #############################################################################

#define LOAD_GLCD    // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2   // Font 2. Small 16 pixel high font,      needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4   // Font 4. Medium 26 pixel high font,     needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6   // Font 6. Large 48 pixel font,     needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7   // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
//#define LOAD_FONT8 // Font 8. Large 75 pixel font      needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8N  // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF   // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT

// #############################################################################
// Section 4. Other options
// #############################################################################

// Define the SPI clock frequency, this affects the graphics rendering speed.
// Too fast and the TFT driver will not keep up and display corruption appears.
// With an ILI9341 display 40MHz works OK, 80MHz sometimes fails
// With a ST7735 display more than 27MHz may not work (spurious pixels and lines)
// With an ILI9163 display 27 MHz works OK.

#define SPI_FREQUENCY     27000000
// #define SPI_FREQUENCY  40000000
// #define SPI_FREQUENCY  80000000

// The ESP32-S3 has 2 free SPI ports i.e. VSPI and HSPI, VSPI is the default.
#define USE_HSPI_PORT

#define SUPPORT_TRANSACTIONS
*******************************************************************/
