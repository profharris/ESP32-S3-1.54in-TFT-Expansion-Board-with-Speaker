/* TFT_eSPI_Read_User_Setup.ino
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 * LCD 1.54in 240×240 color IPS TFT (ST7789V2)
 *
 * This sketch reads the User Setup information from the processor
 * via the Serial Port
 *
 * This is a support and diagnostic sketch for the TFT_eSPI library:
 *      https://github.com/Bodmer/TFT_eSPI
 *
 * The output is essentially a copy of the User_Setep configuration
 * so can be used to verify the correct settings are being picked up
 * by the compiler.
 *
 * If support is needed the output can be cut and pasted into an
 * Arduino Forum post and already includes the formatting
 * [code]...[/ode] markups.
 *
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

#ifdef ARDUINO_ARCH_ESP8266
  ADC_MODE(ADC_VCC);        // Read the supply voltage
#endif

setup_t user; // The library defines the type "setup_t" as a struct
              // Calling tft.getSetup(user) populates it with the settings
//-------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);          // initialize Serial communication
  while(!Serial);                // wait for the Serial port to open

  Serial.println(F("\nTFT_eSPI Read User Setup:"));
  tft.init();                    // Setup the 1.54 240×240 color LCD
}

//------------------------------------------------------------------

void loop(void) {
  tft.getSetup(user); // populate "setup_t" struct with the settings

  Serial.print("\n[code]\n");
  Serial.print ("TFT_eSPI ver = "); Serial.println(user.version);

  printProcessorName();
#if defined (ESP32) || defined (ARDUINO_ARCH_ESP8266)
  if(user.esp < 0x32F000 || user.esp > 0x32FFFF) {
    Serial.print("Frequency    = ");
    Serial.print(ESP.getCpuFreqMHz());
    Serial.println("MHz");
  }
#endif

#ifdef ARDUINO_ARCH_ESP8266
  Serial.print("Voltage      = ");
  Serial.print(ESP.getVcc() / 918.0);  // 918 empirically determined
  Serial.println("V");
#endif

  Serial.print("Transactions = ");
  Serial.println((user.trans  ==  1) ? "Yes" : "No");
  Serial.print("Interface    = ");
  Serial.println((user.serial ==  1) ? "SPI" : "Parallel");

#ifdef ARDUINO_ARCH_ESP8266
  if(user.serial ==  1) {
    Serial.print("SPI overlap  = ");
    Serial.println((user.overlap == 1) ? "Yes\n" : "No\n");
  }
#endif

// For ePaper displays the size is defined in the sketch
  if(user.tft_driver != 0xE9D) {
    Serial.print("Display driver = ");
    Serial.println(user.tft_driver, HEX); // Hexadecimal code
    Serial.print("Display width  = ");
    Serial.println(user.tft_width);  // Rotation 0 width and height
    Serial.print("Display height = ");
    Serial.println(user.tft_height);
    Serial.println();
  } else if(user.tft_driver == 0xE9D)
    Serial.println("Display driver = ePaper\n");

  // Offsets, not all used yet
  if(user.r0_x_offset != 0) { Serial.print("R0 x offset = "); Serial.println(user.r0_x_offset); }
  if(user.r0_y_offset != 0) { Serial.print("R0 y offset = "); Serial.println(user.r0_y_offset); }
  if(user.r1_x_offset != 0) { Serial.print("R1 x offset = "); Serial.println(user.r1_x_offset); }
  if(user.r1_y_offset != 0) { Serial.print("R1 y offset = "); Serial.println(user.r1_y_offset); }
  if(user.r2_x_offset != 0) { Serial.print("R2 x offset = "); Serial.println(user.r2_x_offset); }
  if(user.r2_y_offset != 0) { Serial.print("R2 y offset = "); Serial.println(user.r2_y_offset); }
  if(user.r3_x_offset != 0) { Serial.print("R3 x offset = "); Serial.println(user.r3_x_offset); }
  if(user.r3_y_offset != 0) { Serial.print("R3 y offset = "); Serial.println(user.r3_y_offset); }

  if(user.pin_tft_mosi != -1) {
    Serial.print("MOSI    = "); Serial.print("GPIO ");
    Serial.println(getPinName(user.pin_tft_mosi));
  }
  if(user.pin_tft_miso != -1) {
    Serial.print("MISO    = ");
    Serial.print("GPIO ");
    Serial.println(getPinName(user.pin_tft_miso));
  }
  if(user.pin_tft_clk  != -1) {
    Serial.print("SCK     = ");
    Serial.print("GPIO ");
    Serial.println(getPinName(user.pin_tft_clk));
  }

#ifdef ARDUINO_ARCH_ESP8266
  if(user.overlap == true) {
    Serial.println("Overlap selected, following pins MUST be used:");
    Serial.println("MOSI     = SD1 (GPIO 8)");
    Serial.println("MISO     = SD0 (GPIO 7)");
    Serial.println("SCK      = CLK (GPIO 6)");
    Serial.println("TFT_CS   = D3  (GPIO 0)\n");
    Serial.println("TFT_DC and TFT_RST pins can be user defined");
  }
#endif

  String pinNameRef = "GPIO ";
#ifdef ARDUINO_ARCH_ESP8266
  pinNameRef = "PIN_D";
#endif

  if(user.esp == 0x32F) {
    Serial.println("\n>>>>> Note: STM32 pin references above D15 may not reflect board markings <<<<<");
    pinNameRef = "D";
  }
  if(user.pin_tft_cs != -1) {
    Serial.print("TFT_CS   = " + pinNameRef); Serial.println(getPinName(user.pin_tft_cs));
  }
  if(user.pin_tft_dc != -1) {
    Serial.print("TFT_DC   = " + pinNameRef); Serial.println(getPinName(user.pin_tft_dc));
  }
  if(user.pin_tft_rst!= -1) {
    Serial.print("TFT_RST  = " + pinNameRef); Serial.println(getPinName(user.pin_tft_rst));
  }

  if(user.pin_tch_cs != -1) {
    Serial.print("TOUCH_CS = " + pinNameRef); Serial.println(getPinName(user.pin_tch_cs));
  }

  if(user.pin_tft_wr != -1) {
    Serial.print("TFT_WR   = " + pinNameRef); Serial.println(getPinName(user.pin_tft_wr));
  }
  if(user.pin_tft_rd != -1) {
    Serial.print("TFT_RD   = " + pinNameRef); Serial.println(getPinName(user.pin_tft_rd));
  }

  if(user.pin_tft_d0 != -1) {
    Serial.print("\nTFT_D0   = " + pinNameRef); Serial.println(getPinName(user.pin_tft_d0));
  }
  if(user.pin_tft_d1 != -1) {
    Serial.print("TFT_D1   = " + pinNameRef); Serial.println(getPinName(user.pin_tft_d1));
  }
  if(user.pin_tft_d2 != -1) {
    Serial.print("TFT_D2   = " + pinNameRef); Serial.println(getPinName(user.pin_tft_d2));
  }
  if(user.pin_tft_d3 != -1) {
    Serial.print("TFT_D3   = " + pinNameRef); Serial.println(getPinName(user.pin_tft_d3));
  }
  if(user.pin_tft_d4 != -1) {
    Serial.print("TFT_D4   = " + pinNameRef); Serial.println(getPinName(user.pin_tft_d4));
  }
  if(user.pin_tft_d5 != -1) {
    Serial.print("TFT_D5   = " + pinNameRef); Serial.println(getPinName(user.pin_tft_d5));
  }
  if(user.pin_tft_d6 != -1) {
    Serial.print("TFT_D6   = " + pinNameRef); Serial.println(getPinName(user.pin_tft_d6));
  }
  if(user.pin_tft_d7 != -1) {
    Serial.print("TFT_D7   = " + pinNameRef); Serial.println(getPinName(user.pin_tft_d7));
  }

#if defined (TFT_BL)
  Serial.print("\nTFT_BL           = " + pinNameRef);
  Serial.println(getPinName(user.pin_tft_led));
  #if defined (TFT_BACKLIGHT_ON)
    Serial.print("TFT_BACKLIGHT_ON = ");
    Serial.println(user.pin_tft_led_on == HIGH ? "HIGH" : "LOW");
  #endif
#endif

  uint16_t fonts = tft.fontsLoaded();
  Serial.println();
  if(fonts & (1 << 1))  Serial.print("Font GLCD   loaded\n");
  if(fonts & (1 << 2))  Serial.print("Font 2      loaded\n");
  if(fonts & (1 << 4))  Serial.print("Font 4      loaded\n");
  if(fonts & (1 << 6))  Serial.print("Font 6      loaded\n");
  if(fonts & (1 << 7))  Serial.print("Font 7      loaded\n");
  if(fonts & (1 << 9))  Serial.print("Font 8N     loaded\n");
  else if(fonts & (1 << 8)) Serial.print("Font 8      loaded\n");
  if(fonts & (1 << 15)) Serial.print("Smooth font enabled\n");
  Serial.print("\n");

  if(user.serial==1) { 
    Serial.print("Display SPI frequency = "); 
    Serial.println(user.tft_spi_freq/10.0); 
  }
  if(user.pin_tch_cs != -1) { 
    Serial.print("Touch SPI frequency   = "); 
    Serial.println(user.tch_spi_freq/10.0); 
  }

  Serial.println("[/code]");
  delay(3000);
}

void printProcessorName(void) {
  Serial.print("Processor    = ");
  if( user.esp == 0x8266) Serial.println("ESP8266");
  if( user.esp == 0x32)   Serial.println("ESP32");
  if( user.esp == 0x32F)  Serial.println("STM32");
  if( user.esp == 0x2040) Serial.println("RP2040");
  if( user.esp == 0x0000) Serial.println("Generic");
}

// Get Pin name
int8_t getPinName(int8_t pin) {
  // For ESP32 and RP2040 pin labels on boards use the GPIO number
  if(user.esp == 0x32 || user.esp == 0x2040) return pin;

  if(user.esp == 0x8266) {
    // For ESP8266 the pin labels are not the same as the GPIO number
    // These are for the NodeMCU pin definitions:
    //        GPIO       Dxx
    if(pin == 16) return 0;
    if(pin ==  5) return 1;
    if(pin ==  4) return 2;
    if(pin ==  0) return 3;
    if(pin ==  2) return 4;
    if(pin == 14) return 5;
    if(pin == 12) return 6;
    if(pin == 13) return 7;
    if(pin == 15) return 8;
    if(pin ==  3) return 9;
    if(pin ==  1) return 10;
    if(pin ==  9) return 11;
    if(pin == 10) return 12;
  }

  if(user.esp == 0x32F) return pin;
  return pin; // Invalid pin
}

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
22:58:32.774 ->
22:58:32.774 -> [code]
22:58:32.774 -> TFT_eSPI ver = 2.5.43
22:58:32.774 -> Processor    = ESP32
22:58:32.774 -> Frequency    = 240MHz
22:58:32.774 -> Transactions = Yes
22:58:32.774 -> Interface    = SPI
22:58:32.774 -> Display driver = 7789
22:58:32.774 -> Display width  = 240
22:58:32.774 -> Display height = 240
22:58:32.774 ->
22:58:32.774 -> MOSI    = GPIO 47
22:58:32.774 -> SCK     = GPIO 21
22:58:32.774 -> TFT_CS   = GPIO 41
22:58:32.774 -> TFT_DC   = GPIO 40
22:58:32.774 -> TFT_RST  = GPIO 45
22:58:32.774 ->
22:58:32.774 -> TFT_BL           = GPIO 42
22:58:32.774 -> TFT_BACKLIGHT_ON = HIGH
22:58:32.774 ->
22:58:32.774 -> Font GLCD   loaded
22:58:32.774 -> Font 2      loaded
22:58:32.774 -> Font 4      loaded
22:58:32.774 -> Font 6      loaded
22:58:32.774 -> Font 7      loaded
22:58:32.774 -> Font 8N     loaded
22:58:32.774 -> Smooth font enabled
22:58:32.774 ->
22:58:32.774 -> Display SPI frequency = 27.00
22:58:32.774 -> [/code]
...
--------------------------------------------------------------------
OUTPUT:
¯¯¯¯¯¯¯
Sketch uses 377474 bytes (11%) of program storage space.
Maximum is 3145728 bytes.
Global variables use 21620 bytes (6%) of dynamic memory,
            leaving 306060 bytes for local variables.
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c
...
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
