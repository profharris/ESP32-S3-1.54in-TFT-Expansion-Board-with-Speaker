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
