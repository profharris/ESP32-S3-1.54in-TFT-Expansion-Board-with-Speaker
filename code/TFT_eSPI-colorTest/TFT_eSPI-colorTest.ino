/* TFT_eSPI-colorTest.ino
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 * LCD 1.54in 240×240 color IPS TFT (ST7789V2)
 *
 * Diagnostic test for the displayed “Color Order”.
 * Written by Bodmer 17/2/19 for the TFT_eSPI library:
 * https://github.com/Bodmer/TFT_eSPI
 *
 * Wiring:
 * ¯¯¯¯¯¯¯
 *  | ESP32-S3 Dev Board | SPI ST7789 1.54” 240×240 TFT |
 *  |-------------------:|------------------------------|
 *  |     GND            | 1. GND                       |
 *  |     3V3            | 2. VDD (Power)               |
 *  |     GPIO21         | 3. SCL SPI Clock      (SCLK) |
 *  |     GPIO47         | 4. SDA SPI Data       (MOSI) |
 *  |     GPIO45         | 5. RES TFT Reset       (RST) |
 *  |     GPIO40         | 6. RS  Data/Command     (DC) |
 *  |     GPIO41         | 7. CS  Chip Select      (CS) |
 *  |     GPIO42         | 8. BLK BackLight        (BL) |
 */

/*  Different hardware manufacturers use different Color Order
    configurations at the hardware level.  This may result in
    incorrect colors being displayed.

    Incorrectly displayed colors could also be the result of
    using the wrong display driver in the library setup file.

    Typically displays have a control register (MADCTL) that can
    be used to set the Red Green Blue (RGB) Color Order to RGB
    or BRG so that Red and Blue are swapped on the display.

    This control register is also used to manage the display
    rotation and coordinate mirroring. The control register
    typically has 8 bits, for the ILI9341 these are:

    Bit Function
        7   Mirror Y coordinate (Row address order)
        6   Mirror X coordinate (Column address order)
        5   Row/column exchange (for Rotation)
        4   Refresh direction (Top to Bottom or Bottom to Top in Portrait orientation)
        3   RGB order (swaps Red and Blue)
        2   Refresh direction (Top to Bottom or Bottom to Top in Landscape orientation)
        1   Not used
        0   Not used

    The control register bits can be written with this example command sequence:

        tft.writecommand(TFT_MADCTL);
        tft.writedata(0x48);          // Bits 6 and 3 set

    ‘0x48’ is the default value for ILI9341 (0xA8 for ESP32 M5STACK)
    in rotation 0 orientation.

    Another control register can be used to “Invert” colors,
    this swaps Black and White as well as other colours (e.g.
    Green to Magenta, Red to Cyan, Blue to Yellow).

    To Invert colors, insert this line after tft.init() or tft.begin():

        tft.invertDisplay( Invert ); // Where Invert is true or false
*/

#include <SPI.h>            // Don’t forget to update “User_Setup.h”
#include <TFT_eSPI.h>       // Hardware-specific eSPI library

TFT_eSPI tft = TFT_eSPI();  // Invoke custom eSPI library

// TFT configurations are defined in the eSPI “User_Setup.h” file.
// ... a minimum “User_Setup.h” file is included below.
//#define TFT_SCLK      21      // LCD ST7789 1.54” 240×240 TFT SCK
//#define TFT_MOSI      47      // SDI          "           TFT MOSI
//#define TFT_RST       45      // Reset        "           TFT RST
//#define TFT_DC        40      // D/C          "           TFT DC
//#define TFT_CS        41      // CS           "           TFT CS
//#define TFT_BL        42      // BackLight    "           TFT BL
//#define TFT_BACKLIGHT_ON HIGH

//#define TFT_WIDTH  240
//#define TFT_HEIGHT 240

//#define ST7789_DRIVER 
//#define TFT_RGB_ORDER TFT_BGR  // ESP32-S3-WROOM Blue/Red reversed
//#define TFT_INVERSION_ON       // ESP32-S3-WROOM-1
//#define USE_HSPI_PORT          // Second Hardware SPI Port

void setup(void) {
  Serial.begin(15200);              // Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open
  Serial.println("TFT_eSPI Color Order Test.");  
  
  tft.init();                       // Initialize the TFT Display
  tft.setRotation(1);               // Landscape orientation
  tft.fillScreen(TFT_BLACK);        // Clear the screen
  tft.drawRect(0,0, TFT_WIDTH,TFT_HEIGHT, TFT_GREEN);

  // Set “cursor” at top-left corner of display (0,4) and select Font 4
  tft.setCursor(0,4, 4);

  // Set the font color to be White with a Black background
  tft.setTextColor(TFT_WHITE);

  // We can now plot text on screen using the “print” class
  tft.println(" Initialised default\n");
  tft.println(" White text?");

  tft.setTextColor(TFT_RED);
  tft.println(" Red text");

  tft.setTextColor(TFT_GREEN);
  tft.println(" Green text");

  tft.setTextColor(TFT_BLUE);
  tft.println(" Blue text");
  yield(); delay(5000);
}

void loop() {
  tft.invertDisplay( false );   // Where parm is true or false
  tft.fillScreen(TFT_BLACK);    // Clear the screen
  tft.drawRect(0,0, TFT_WIDTH,TFT_HEIGHT, TFT_GREEN);

  tft.setCursor(0,4, 4);
  tft.setTextColor(TFT_WHITE);
  tft.println(" Invert OFF\n");
  tft.println(" White text?");

  tft.setTextColor(TFT_RED);
  tft.println(" Red text?");

  tft.setTextColor(TFT_GREEN);
  tft.println(" Green text?");

  tft.setTextColor(TFT_BLUE);
  tft.println(" Blue text?");
  yield(); delay(5000);

  // Binary Inversion of colors
  tft.invertDisplay( true );    // Where parm is true or false
  tft.fillScreen(TFT_BLACK);    // Clear the screen
  tft.drawRect(0,0, TFT_WIDTH,TFT_HEIGHT, TFT_GREEN);

  tft.setCursor(0,4, 4);
  tft.setTextColor(TFT_WHITE);
  tft.println(" Invert ON\n");
  tft.println(" White text?");

  tft.setTextColor(TFT_RED);
  tft.println(" Red text?");

  tft.setTextColor(TFT_GREEN);
  tft.println(" Green text?");

  tft.setTextColor(TFT_BLUE);
  tft.println(" Blue text?");
  yield(); delay(5000);
}

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
23:40:34.852 -> ESP-ROM:esp32s3-20210327
23:40:34.852 -> Build:Mar 27 2021

01:13:19.666 -> TFT_eSPI Color Order Test.
--------------------------------------------------------------------
Output:
¯¯¯¯¯¯¯
Sketch uses 368006 bytes (11%) of program storage space. 
Maximum is 3145728 bytes.
Global variables use 21500 bytes (6%) of dynamic memory, 
            leaving 306180 bytes for local variables. 
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c

Leaving...
Hard resetting with RTC WDT...
*******************************************************************/

/*******************************************************************
// User_Setup.h (minimal)
// ESP32-S3 1.54in TFT Expansion Board with Speaker
// LCD 1.54in 240×240 color IPS TFT (ST7789V2)

// Except for the intros, only “uncommented” lines are included.

//                            USER DEFINED SETTINGS
//   Set driver type, fonts to be loaded, pins used and SPI control method etc.
//
//   See the User_Setup_Select.h file if you wish to be able to define multiple
//   setups and then easily select which setup file is used by the compiler.
//
//   If this file is edited correctly then all the library example sketches should
//   run without the need to make any more changes for a particular hardware setup!
//   Note that some sketches are designed for a particular TFT pixel width/height

// User defined information reported by "Read_User_Setup" test & diagnostics example
#define USER_SETUP_INFO "User_Setup"

// #############################################################################
// Section 1. Call up the right driver file and any options for it
// #############################################################################

#define ST7789_DRIVER      // Full configuration option, define additional parameters below for this display
//#define ST7789_2_DRIVER    // Minimal configuration option, define additional parameters below for this display

// #define TFT_RGB_ORDER TFT_RGB  // Colour order Red-Green-Blue
#define TFT_RGB_ORDER TFT_BGR  // Colour order Blue-Green-Red

// For ST7789, ST7735, ILI9163 and GC9A01 ONLY, define the pixel Width and Height in Portrait orientation
#define TFT_WIDTH  240 // ST7789 240 x 240 and 240 x 320
#define TFT_HEIGHT 240 // ST7789 240 x 240

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

#define TFT_SCLK 21  // SPI Clock pin
#define TFT_MOSI 47  // SPI Duplex Data pin
#define TFT_RST  45  // Reset pin (could connect to RST pin)
#define TFT_DC   40  // Data/Command control pin
#define TFT_CS   41  // Chip Select control pin
#define TFT_BL   42  // LED BackLight pin

#define TOUCH_CS -1  // Chip Select pin (T_CS) for the Touch Screen

// #############################################################################
// Section 3. Define the fonts that are to be used here
// #############################################################################

#define LOAD_GLCD     // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2    // Font 2. Small 16 pixel high font,      needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4    // Font 4. Medium 26 pixel high font,     needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6    // Font 6. Large 48 pixel font,     needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7    // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
//#define LOAD_FONT8  // Font 8. Large 75 pixel font      needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8N   // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF    // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

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

// The ESP32 has 2 free SPI ports i.e. VSPI and HSPI, VSPI is the default.
#define USE_HSPI_PORT

#define SUPPORT_TRANSACTIONS
*******************************************************************/
