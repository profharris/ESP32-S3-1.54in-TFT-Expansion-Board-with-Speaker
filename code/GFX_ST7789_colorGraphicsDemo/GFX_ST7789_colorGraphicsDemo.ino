// GFX_ST7789_colorGraphicsDemo.ino (a dozen GFX graphics demos)
// ESP32-S3 1.54in TFT Expansion Board with Speaker
// LCD 1.54in 240×240 color IPS TFT (ST7789V)

/* This demo works with several “pin-compliant” Ðevelopment boards:
 *  1.  ESP32-S3-DevKitC-1          (ESP32S3 Dev Module — no camera)
 *  2.  ESP32-S3-WROOM CAM
 *  3.  FREENOVE ESP32-S3-WROOM CAM
 *  4.  ESP32-S3-CAM                (ESP32S3 Dev Module clone + CAM)
 *  5.  ESP32-S3-WROOM-1-N16R8      (ESP32S3 Dev Module — no camera)
 */

/*  TFT LCD 1.54in 240×240 color SPI IPS (ST7789V)     [WIRING]
 *
 *  TFT LCD                      Pins ESP32-S3-WROOM-1
 *  Pins: GND  GND               GND                    1. Brown
 *        VCC  3V3               3V3                    2. Red
 *        BLK  BackLight         GPIO42  TFT_BL         3. Orange
 *        CS   Chip Select       GPIO41  TFT_CS         4. Yellow
 *        DC   Data/Command      GPIO40  TFT_DC         5. Green
 *        RST  Reset             GPIO45  TFT_RST        6. Blue
 *        SDA  SPI Data (MOSI)   GPIO47  TFT_MOSI       7. Violet
 *        SCL  SPI Clock         GPIO21  TFT_SCLK       8. Grey
 *
 *       -1 MISO (N/C)
 */

/*******************************************************************
GOOUUU ESP32-S3-CAM
(Same pinout as ESP32-S3-WROOM (CAM Module), & ESP32-S3-DevKitC-1)

Xtensa® 32-bit              ESP32-S3-CAM      ESP32-S3-WROOM-1 N16R8
dual-core LX7              _______________
                          |  ___   _   __¯|      IO##~   SD-Card
    DVP Camera IO##_      | | | |_| |_|   |      IO##*   PSRAM
                       .——| | |           |——.                      TFT
            ——> 3V3   1|•:|————————————/:@|:•|40 IO43 TX›[U0TXD LED]
[RESET    ]      EN   2|•:|  .··. .    '——|:•|39 IO44 RX‹[U0RXD LED]
[CAM_SIOD ]SDA  IO4_  3|•:|  WiFi ß       |:o|38 IO1  I²C[ADC0  SDA]
[CAM_SIOC ]SCL  IO5_  4|•:|  ˜¨¨˜ °       |:o|37 IO2  I²C[ADC1  SCL]
[CAM_VSYNC]     IO6_  5|•:|ESP32-S3-N16R8 |:o|36 IO42    [       BL]<——
[CAM_HREF ]     IO7_  6|•:|               |:o|35 IO41    [       CS]<——
[CAM_XCLK ]    IO15_  7|•:|  ŒÆ     F©    |:•|34 IO40~   [       DC]<——
[CAM_Y9   ]D7  IO16_  8|•:'———————————————':•|33 IO39~   [SD_CLK  •]
[CAM_Y8   ]D6  IO17_  9|• ._______________. •|32 IO38~   [SD_CMD  •]
[CAM_Y7   ]D5  IO18_ 10|• | ::::::::::::: | •|31 IO37*   [PSRAM   •]
[CAM_Y4   ]D2   IO8_ 11|• |    Camera     | •|30 IO36*   [PSRAM   •]
[         ]     IO3  12|o ¯¯:::::::::::::¯¯ •|29 IO35*   [PSRAM   •]
[         ]    IO46  13|o   ESP32-S3-CAM    o|28 IO0     [BOOT     ]
[CAM_Y3   ]D1   IO9_ 14|•   ¬ ¬  PWR¤ ¤ [¤] o|27 IO45    [      RST]<——
[CAM_Y5   ]D3  IO10_ 15|•   ¨ ¨.......TX 48 ¤|26 IO48 RGB[WS2812   ]
[CAM_Y2   ]D0  IO11_ 16|• RST |CH304G | BOOTo|25 IO47    [     MOSI]<——
[CAM_Y6   ]D4  IO12_ 17|• [Ø]  '''''''  [Ø] o|24 IO21    [      SCL]<——
[CAM_PCLK ]    IO13_ 18|• .......O T....... ø|23 IO20 D- [ADC2_C9  ]   —————————
[ADC3     ]    IO14  19|o | USB |T T| USB | ø|22 IO19 D+ [ADC2_C8  ]   I²C QWIIC
                5V0  20|• |  C  |G L|  C  | •|21 GND                <  —————————
                       '——'ESP32'———'CH343'——'   IO48 RGB NeoPixel    1  *  GND
                                                                      2  *  3V3
ESP32-S3 Pins: 0…18 GPIO, 19…20 D+/D-, 21 GPIO, 22…25 Do Not Exist,   3 IO1 SDA
26…32 QSPI ƒlash, 33…34 Missing, 35…42 GPIO, 43…44 TX/RX, 45…48 GPIO  4 IO2 SCL

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
    via that socket's Serial Port labled "TTL" or "UART":

When you have Tools > USB CDC On Boot > Enabled
    selected from the Arduino IDE menus, serial communication will
    instead be done via the Serial Port of the USB socket labeled
    "USB":
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
// SPI Pins declared for the TFT display (right-side ESP32-S3-WROOM)
#define TFT_SCLK     21     // SPI Clock out (SCL)
#define TFT_DC       40     // SPI Data/Command
#define TFT_CS       41     // SPI Chip Select
#define TFT_BL       42     // BackLight
#define TFT_RST      45     // Or set to -1 and connect to RESET pin
#define TFT_MOSI     47     // SPI Data out  (SDA)

Adafruit_ST7789 tft=Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI,
                                    TFT_SCLK, TFT_RST);

float pi = 3.1415926;

void setup(void) {
  Serial.begin(115200);             // Serial Monitor
  while(!Serial);                   // wait for Serial Port to open
  
  rgbLedWrite(RGB_BUILTIN, 0,0,0);  // Make sure RGB NeoPixel is Off

  tft.init(TFT_HEIGHT, TFT_WIDTH);  // Init ST7789V 240×240 TFT OLED
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  Serial.println(F("\n...ST7789V Screen Initialized"));

  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library,
  // you can override it here. Note that the speed allowable depends
  // on the chip and quality of wiring, if you go too fast, you may
  // end up with a Black/Blank screen some times, or all the time.
  // tft.setSPISpeed(40000000);

  tft.setRotation(2);               // Rotation(0..3) 0°, 90°, 180°, 270°
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

  // Demo 11. Draw sample Media Buttons (for a touch screen)
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

Sketch uses 367952 bytes (17%) of program storage space.
  Maximum is 2097152 bytes.
Global variables use 21064 bytes (6%) of dynamic memory,
  leaving 306616 bytes for local variables. Maximum is 327680 bytes.
esptool.py v4.8.1
Serial port COM6
Connecting.....
Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: cc:ba:97:05:10:8c
Uploading stub...
Running stub...
Stub running...
Configuring flash size...
Flash will be erased from 0x00000000 to 0x00004fff...
Flash will be erased from 0x00008000 to 0x00008fff...
Flash will be erased from 0x0000e000 to 0x0000ffff...
Flash will be erased from 0x00010000 to 0x00069fff...
Compressed 20160 bytes to 12987...
Writing at 0x00000000... (100 %)
Wrote 20160 bytes (12987 compressed) at 0x00000000 in 1.4 seconds
  (effective 114.1 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 143...
Writing at 0x00008000... (100 %)
Wrote 3072 bytes (143 compressed) at 0x00008000 in 0.1 seconds
  (effective 386.7 kbit/s)...
Hash of data verified.
Compressed 8192 bytes to 47...
Writing at 0x0000e000... (100 %)
Wrote 8192 bytes (47 compressed) at 0x0000e000 in 0.1 seconds
  (effective 632.4 kbit/s)...
Hash of data verified.
Compressed 368064 bytes to 199669...
Writing at 0x00010000... (7 %)
Writing at 0x0001b87d... (15 %)
Writing at 0x0002a00d... (23 %)
Writing at 0x0002f875... (30 %)
Writing at 0x000353fe... (38 %)
Writing at 0x0003b149... (46 %)
Writing at 0x00040b26... (53 %)
Writing at 0x000464b2... (61 %)
Writing at 0x0004be43... (69 %)
Writing at 0x00052afb... (76 %)
Writing at 0x0005cca4... (84 %)
Writing at 0x00062787... (92 %)
Writing at 0x0006878b... (100 %)
Wrote 368064 bytes (199669 compressed) at 0x00010000 in 17.5 seconds
  (effective 167.9 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
*******************************************************************/

/* -----------------------------------------------------------------
Serial Monitor:

17:46:44.500 -> ESP-ROM:esp32s3-20210327
18:25:39.997 -> 
18:25:39.997 -> ...ST7789V Screen Initialized
18:25:39.997 -> Hello! a dozen ST7789 GFX color Graphics Demos:
18:25:39.997 -> Start time: 0
18:27:46.969 ->   End time: 129
18:27:48.590 -> Done.
18:27:48.590 -> 
----------------------------------------------------------------- */
