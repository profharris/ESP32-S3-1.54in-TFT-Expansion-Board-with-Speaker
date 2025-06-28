// GFX_ST7789_colorGraphicsDemo.ino (a dozen GFX graphics demos)
// ESP32-S3 1.54in TFT Expansion Board with Speaker
// LCD 1.54in 240×240 color IPS TFT (ST7789V)
// Prof. Michael P. Harris

/* This demo works with several “pin-compliant” Ðevelopment boards:
 *  1. Espressif ESP32-S3-DevKitC-1 (no camera, no SD card)
 *  2. YD-ESP32-S3 (ESP32-S3-WROOM-1 Dev) (DevKitC-1 clone)
 *  3. WeAct Studio ESP32-S3-A/B Core     (DevKitC-1 clone)
 *  4. WaveShare ESP32-S3-DEV-KIT-N8R8    (DevKitC-1 clone)
 *  5. GOOUUU ESP32-S3-CAM     (DevKitC-1 clone + CAM + SD)
 *  6. ESP32-S3-WROOM CAM   (FREENOVE ESP32-S3-WROOM clone)
 *  7. FREENOVE ESP32-S3-WROOM (CAM) 
 *  8. FREENOVE ESP32-S3-WROOM-Lite (no camera)
 */

/*  TFT LCD 1.54in 240×240 color SPI IPS (ST7789V)     [WIRING]
 *
 *  Pins: TFT LCD             Pins: ESP32-S3-WROOM-1
 *  1. GND  GND               GND 
 *  2. VCC  3V3               3V3
 *  3. SCL  SPI Clock         GPIO21  TFT_SCLK
 *  4. SDA  SPI Data (MOSI)   GPIO47  TFT_MOSI
 *  5. RES  TFT Reset         GPIO45  TFT_RST
 *  6. RS   Data/Command      GPIO40  TFT_DC
 *  7. CS   Chip Select       GPIO41  TFT_CS
 *  8. BLK  BackLight         GPIO42  TFT_BL
 *
 *     -1   SPI MISO (N/C)
 */

/*******************************************************************
               ESP32-S3 1.54in TFT Expansion Board with Speaker
Xtensa® 32-bit         ESP32-S3-DevKitC-1     ESP32-S3-WROOM-1 N16R8
Dual-core LX7               (44-pins)
Dual-core LX7            _______________
 16MB Flash             |  ___   _   __¯|         NO CAMERA MODULE
  8MB PSRAM             | | | |_| |_|   |         NO SD-CARD
 512K SRAM           .——| | |           |——.
               3V3  1|o:|   Espressif   |:•|44 GND                Hardware
               3V3  2|o:|ESP32S3-WROOM-1|:•|43 G43 TX›            SPI2 HSPI
[RST]          ENT  3|o:|               |:•|42 G44 RX‹            —————————
A3  (Mic WS)   G4   4|o:| Œ Æ   N16R8   |:o|41 G1  A0             G10 SS/CS
A4  (Mic SCK)  G5   5|o:| .··. .   ____ |:o|40 G2  A1             G11 MOSI
A5  (Mic SD)   G6   6|o:| WiFi ß  |QRCD||:o|39 G42     (TFT BL)   G12 SCK
A6  (Amp DIN)  G7   7|o:| °   F©  |____||:o|38 G41     (TFT CS)   G13 MISO
A14 (Amp BCLK) G15  8|o:'———————————————':o|37 G40     (TFT DC)
A15 (Amp LRC)  G16  9|o ·. ¨¨|¯¯¯¬        o|36 G39                Software
A16            G17 10|o ¯  ¨¨|LDO[]   PWR o|35 G38                SPI -ALT-
A17            G18 11|o ¯  ¨¨|___-     ¤  o|34 G37 PSRAM          —————————
I²C SDA        G8  12|o RGB     ¬ ¬       o|33 G36 PSRAM           -1  MISO
A2             G3  13|o ‹¤›IO48 ¨ ¨       o|32 G35 PSRAM          G42  BL
LOG            G46 14|o      ........ ·   o|31 G0  [BOOT]         G41  CS
I²C SCL        G9  15|o ¨ ¨  |CP2102| ¨   o|30 G45     (TFT RST)  G40  DC
SPI SS/CS      G10 16|o ¨¨   '''''''' ¨   ¤|29 G48 RGB LED        G45  RST
SPI MOSI       G11 17|o BOOT .......  RST o|28 G47    (TFT MOSI)  G47  MOSI
SPI SCK        G12 18|o ‹•›  '''''''  ‹•› o|27 G21    (TFT SCLK)  G21  SCK
SPI MISO       G13 19|o                   ø|26 G20 A19 USB_D-
A13            G14 20|o  _____ O T _____  ø|25 G19 A20 USB_D+     I²C -ALT-
               5V0 21|o | USB |T T| USB | o|24 GND                —————————
               GND 22|o |  C  |G L|  C  | o|23 GND                1. *  GND
                     '——'ESP32'———'UART0'——'                      2. *  3V3
                                               G48 RGB_BUILTIN,   3. G1 SDA
                                               LED_BUILTIN        4. G2 SCL

*******************************************************************/

/*******************************************************************
Arduino IDE > Tools                                  [CONFIGURATION]
                       Board: "ESP32S3 Dev Module"
             USB CDC On Boot: "Disabled"    *** Sketch locks up if ENABLED ***
               CPU Frequency: "240MHz (WiFi)"
             USB DFU On Boot: "Disabled"
                  Flash Mode: "QIO 80MHz"
                  Flash Size: "16MB 128Mb"
    USB Firmware MSC On Boot: "Disabled"
              Partion Scheme: "16M Flash (2MB APP/12.5MB FATFS)"
                       PSRAM: "OPI PSRAM"
                Upload Speed: "115200"
*******************************************************************/

/*******************************************************************
When you have Tools > USB CDC On Boot > Disabled
    selected from the Arduino IDE menus, calling Serial.println etc.
    in your sketch will cause the serial communication to be done
    via that socket's Serial Port labled "USB-TTL" or "UART":

When you have Tools > USB CDC On Boot > Enabled
    selected from the Arduino IDE menus, serial communication will
    instead be done via the ESP32-S3 internal Serial Port, the USB 
    socket labeled "USB-OTG":
 ******************************************************************/

#include <Adafruit_GFX.h>    // Core GFX Graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

/* Some ready-made 16-bit ('565') color settings:
#define ST77XX_BLACK    0x0000
#define ST77XX_WHITE    0xFFFF
#define ST77XX_RED      0xF800
#define ST77XX_GREEN    0x07E0
#define ST77XX_BLUE     0x001F
#define ST77XX_CYAN     0x07FF
#define ST77XX_MAGENTA  0xF81F
#define ST77XX_YELLOW   0xFFE0
#define ST77XX_ORANGE   0xFC00
*/

// Define the 240×240 ST7789V TFT LCD display size
#define TFT_WIDTH   240     // TFT LCD Width  in pixels
#define TFT_HEIGHT  240     // TFT LCD Height in pixels

// OPTION 2: Lets you interface the display using ANY 2 or 3 Pins,
// tradeoff being that performance is not as fast as hardware SPI.
// SPI Pins declared for the TFT display (Right-side ESP32-S3-WROOM)
#define TFT_BL       42     // BackLight
#define TFT_CS       41     // SPI Chip Select
#define TFT_DC       40     // SPI Data/Command
#define TFT_RST      45     // SPI Reset
#define TFT_MOSI     47     // SPI Data  (SDA)
#define TFT_SCLK     21     // SPI Clock (SCL)

Adafruit_ST7789 tft=Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI,
                                    TFT_SCLK, TFT_RST);
float pi = 3.1415926;

void setup(void) {
  Serial.begin(115200);             // Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open
  
  rgbLedWrite(RGB_BUILTIN, 0,0,0);  // Make sure RGB NeoPixel is Off

  tft.init(TFT_HEIGHT, TFT_WIDTH);  // Init ST7789V 320×240 TFT OLED
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  Serial.println(F("\n...ST7789V Screen Initialized"));

  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library,
  // you can override it here. Note that the speed allowable depends
  // on the chip and quality of wiring, if you go too fast, you may
  // end up with a Black/Blank screen some times, or all the time.
  // tft.setSPISpeed(40000000);

  tft.setRotation(3);               // Rotation(0..3) 0°, 90°, 180°, 270°
  Serial.println(F("Hello! a dozen ST7789 GFX color Graphics Demos:"));

  uint16_t time = millis();
  time = millis() - time;
  Serial.print(F("Start time: ")); Serial.println(time, DEC);
  delay(1000);

  // Demo 1. two large blocks of text in two sizes
  tft.setTextSize(1);               // TextSize (1..3) 1=5×8 pixels
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  testDrawText("Lorem ipsum dolor sit amet, consectetur adipiscing "
               "elit. Curabitur adipiscing ante sed nibh tincidunt "
               "feugiat. Maecenas enim massa, fringilla sed malesuada "
               "et, malesuada sit amet turpis. Sed porttitor neque ut "
               "ante pretium vitae malesuada nunc bibendum. Nullam "
               "aliquet ultrices massa eu hendrerit. Ut sed nisi "
               "lorem. In vestibulum purus a tortor imperdiet posuere.",
               ST77XX_WHITE); delay(1000);

  tft.setTextSize(2);               // TextSize (1..3) 2=10×16 pixels
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  testDrawText("Lorem ipsum dolor sit amet, consectetur adipiscing "
               "elit. Curabitur adipiscing ante sed nibh tincidunt "
               "feugiat. Maecenas enim massa, fringilla sed malesuada "
               "et, malesuada sit amet turpis. Sed porttitor neque ut "
               "ante pretium vitae malesuada nunc bibendum. Nullam "
               "aliquet ultrices massa eu hendrerit. Ut sed nisi "
               "lorem. In vestibulum purus a tortor imperdiet posuere.",
               ST77XX_CYAN); delay(2000);

  // Demo 2. A single Pixel centered on the display
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  tft.drawPixel(tft.width()/2,tft.height()/2, ST77XX_GREEN);
  delay(1000);

  // Demo 3. Draw Lines (in 8 colors)
  testDrawLines(ST77XX_WHITE, ST77XX_RED, ST77XX_GREEN, ST77XX_BLUE,
                ST77XX_CYAN, ST77XX_MAGENTA, ST77XX_YELLOW,
                ST77XX_ORANGE); delay(1000);

  // Demo 4. Draw optimized Lines
  testFastLines(ST77XX_RED, ST77XX_BLUE); delay(1000);

  // Demo 5. Draw Rectangles
  testDrawRects(ST77XX_ORANGE); delay(1000);

  // Demo 6. Draw Filled Rectangles
  testFillRects(ST77XX_YELLOW, ST77XX_MAGENTA); delay(1000);

  // Demo 8. Draw Filled Circles
  testFillCircles(10, ST77XX_BLUE); delay(1000);

  // Demo 7. Draw Circles
  testDrawCircles(10, ST77XX_WHITE); delay(1000);

  // Demo 9. Draw Round Rectangles
  testRoundRects(); delay(1000);

  // Demo 10. Draw Triangles
  testTriangles(); delay(1000);

  // Demo 11. Draw sample Media Buttons (for a Touchscreen)
  mediaButtons(); delay(1000);

  // Demo 12. TFT Print Test function!
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  tftPrintTest(); delay(3000);

  time = millis()/1000;
  Serial.print(F("  End time: ")); Serial.println(time, DEC);

  tft.setTextSize(2);
  tft.println(" ");
  tft.setTextColor(ST77XX_WHITE);
  tft.println("This Sketch has been");
  tft.println("running for:\n");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis()/1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.\n"); delay(1500);
  Serial.println("Done.\n"); delay(2000);
}

void loop() {
  tft.invertDisplay(true);
  delay(1000);
  tft.invertDisplay(false);
  delay(1000);
}

void testDrawText(char *text, uint16_t color) {
  tft.setCursor(0,0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testDrawLines(uint16_t color1, uint16_t color2,
                   uint16_t color3, uint16_t color4,
                   uint16_t color5, uint16_t color6,
                   uint16_t color7, uint16_t color8) {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0,0, x,tft.height()-1, color1);
    delay(0);
  }
  for(int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0,0, tft.width()-1,y, color2);
    delay(0);
  }
  delay(500);
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1,0, x,tft.height()-1, color3);
    delay(0);
  }
  for(int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1,0, 0,y, color4);
    delay(0);
  }
  delay(500);
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0,tft.height()-1, x,0, color5);
    delay(0);
  }
  for(int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0,tft.height()-1, tft.width()-1,y, color6);
    delay(0);
  }
  delay(500);
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1,tft.height()-1, x,0, color7);
    delay(0);
  }
  for(int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1,tft.height()-1, 0,y, color8);
    delay(0);
  }
  delay(500);
}

void testFastLines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0,y, tft.width(), color1);
  }
  for(int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x,0, tft.height(), color2);
  }
}

void testDrawRects(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2-x/2,tft.height()/2-x/2, x,x, color);
  }
}

void testFillRects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2-x/2,tft.height()/2-x/2, x,x, color1);
    tft.drawRect(tft.width()/2-x/2,tft.height()/2-x/2, x,x, color2);
  }
}

void testDrawCircles(uint8_t radius, uint16_t color) {
  for(int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for(int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x,y, radius, color);
    }
  }
}

void testFillCircles(uint8_t radius, uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t x=radius; x < tft.width(); x+=radius*2) {
    for(int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x,y, radius, color);
    }
  }
}

void testTriangles() {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  uint16_t color = 0xF800;          // ST77XX_RED
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0; t <= 15; t++) {
    tft.drawTriangle(w,y, y,x, z,x, color);
    x-=4;
    y+=4;
    z-=4;
    color += 200;                   // color change
  }
}

void testRoundRects() {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  uint16_t color = 100;
  int i;
  int t;
  for(t=0; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(i=0; i <= 16; i+=1) {
      tft.drawRoundRect(x,y, w,h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void mediaButtons() {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  // Play Button
  tft.fillRoundRect(25,10, 78,60, 8, ST77XX_WHITE);
  tft.fillTriangle( 42,20, 42,60, 90,40, ST77XX_RED);
  delay(1000);
  // Pause Button
  tft.fillRoundRect(25,90, 78,60, 8, ST77XX_WHITE);
  tft.fillRoundRect(39,98, 20,45, 5, ST77XX_GREEN);
  tft.fillRoundRect(69,98, 20,45, 5, ST77XX_GREEN);
  delay(1000);
  // Play Button color1
  tft.fillTriangle(42,20, 42,60, 90,40, ST77XX_BLUE);
  delay(1000);
  // Pause Button color
  tft.fillRoundRect(39,98, 20,45, 5, ST77XX_RED);
  tft.fillRoundRect(69,98, 20,45, 5, ST77XX_RED);
  // Play Button color2
  tft.fillTriangle(42,20, 42,60, 90,40, ST77XX_GREEN);
  delay(1000);
}

void tftPrintTest() {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  tft.setTextWrap(false);
  tft.setCursor(0,30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hello, World!");
  tft.println(" ");
  tft.setTextColor(ST77XX_ORANGE);
  tft.setTextSize(2);
  tft.println("Hello, World!");
  tft.println(" ");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello, World!");
  tft.println(" ");
  tft.setTextColor(ST77XX_BLUE);
  tft.print(1234.567);
  delay(4500);
  tft.setCursor(0,0);
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.println("Hello, World!");
  tft.println(" ");
  tft.setTextSize(3);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(pi, 6);
  tft.println("\n Want Pi?");
  delay(1500);
  tft.setTextSize(1);
  tft.println(" ");
  tft.print(8675309, HEX);      // print 8,675,309 out in HEX!
  tft.println(" Printing in HEX!");
  tft.println(" ");
}

/*******************************************************************
Sketch uses 369854 bytes (28%) of program storage space. 
  Maximum is 1310720 bytes.
Global variables use 22100 bytes (6%) of dynamic memory, 
  leaving 305580 bytes for local variables. Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c

Leaving...
Hard resetting via RTS pin...
*******************************************************************/

/* -----------------------------------------------------------------
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
18:23:31.333 -> ESP-ROM:esp32s3-20210327
18:23:31.333 -> Build:Mar 27 2021
18:23:31.333 -> rst:0x1 (POWERON),boot:0x8 (SPI_FAST_FLASH_BOOT)
18:23:31.333 -> SPIWP:0xee
18:23:31.333 -> mode:DIO, clock div:1
18:23:31.333 -> load:0x3fce2820,len:0x118c
18:23:31.333 -> load:0x403c8700,len:0x4
18:23:31.333 -> load:0x403c8704,len:0xc20
18:23:31.333 -> load:0x403cb700,len:0x30e0
18:23:31.333 -> entry 0x403c88b8
18:23:33.637 -> 
18:23:33.637 -> ...ST7789V Screen Initialized
18:23:33.637 -> Hello! a dozen ST7789 GFX color Graphics Demos:
18:23:33.637 -> Start time: 0
18:25:18.740 ->   End time: 107
18:25:20.405 -> Done.
18:25:20.405 -> 
----------------------------------------------------------------- */

/*******************************************************************
Adafruit_GFX Graphics library -=- Quick Function Summary:
Parameters are assumed to be ‘int16_t’ unless otherwise specified.

Default Argument List:
    x,y         primary screen coordinates
    x1,y1       secondary screen coordinates
    x2,y2       tertiary screen coordinates
    w,h         Width and Height (also used for Length)
    r           circle or rounded entity radius
    color, bg   16-bit 565Color color for fgColor or bgColor
    ch          unsigned char ch (ASCII character)
    s           uint8_t pixel ratio multiplier, e.g. 2 = 2:1

Adafruit_GFX(w, h);                 // Constructor
// Assumes setRotation() is 0.

width(void), height(void)           // return w,h -current rotation

setCursor(x,y)                      // coords need not be visable
getCursorX(void);
getCursorY(void);

setRotation(r);                     // 0-3 Cardinal 0°,90°,180°,270°
getRotation(void);                  // 0-3 Cardinal 0°,90°,180°,270°

invertDisplay(bool i);              // True or False

setFont(const GFXfont *f = NULL)

setTextSize(s);                     // ratio multiplier to default
setTextWrap(bool w)                 // True or False

drawPixel(x,y, color);
getPixel(x,y);

drawChar(x,y, ch, color[, bg][, size]);
drawLine(x,y, x1,y1, color);
drawFastVLine(x,y, h, color);
drawFastHLine(x,y, w, color);
drawRect(x,y, w,h, color);
drawRoundRect(x,y, w,h, r, color);
drawCircle(x,y, r, color);
drawTriangle(x,y, x1,y1, x2,y2, color);

fillScreen(color);
fillRect(x,y, w,h, color);
fillRoundRect(x,y, w,h, r, color);
fillCircle(x,y, r, color);
fillTriangle(x,y, x1,y1, x2,y2, color);

drawBitmap(x,y, uint8_t [*]bitmap[], w,h, color[, bg]);
drawRGBBitmap((x,y, uint8_t [*]bitmap[], w,h);

byteSwap(void);
*******************************************************************/

