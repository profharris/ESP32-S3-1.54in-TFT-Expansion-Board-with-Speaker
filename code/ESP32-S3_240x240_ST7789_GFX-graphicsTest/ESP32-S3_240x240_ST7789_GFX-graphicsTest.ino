/* ESP32-S3_240x240_ST7789_GFX-graphicsTest.ino
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 * NOTE¹:  The GFX Graphics Test may not start
 * ¯¯¯¯¯¯  until you open the Serial Monitor!!!
 *
 * ESP32-S3_240×240_ST7789_GFX-graphicsTest.ino — is based on this Adafruit example...
 * https://github.com/adafruit/Adafruit-ST7735-Library/blob/master/examples/graphicstest/graphicstest.ino
 */

#include <Adafruit_GFX.h>    // Adafruit GFX Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // SPI library

// SPI Pinout
#define TFT_BL       42      // BLK BackLight       ESP32-S3-WROOM-1
#define TFT_CS       41      // CS  Chip Select       "Right-Side"
#define TFT_DC       40      // RS  Data/Command      "Availiable"
#define TFT_RST      45      // RES Reset                 "Pins"
#define TFT_MOSI     47      // SDA SPI Data
#define TFT_SCLK     21      // SCL SPI Clock

#define TFT_WIDTH   240
#define TFT_HEIGHT  240

// Adafruit software SPI GFX Constructor for object ‘tft’
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS,TFT_DC,TFT_MOSI,TFT_SCLK,TFT_RST);

void setup(void) {
  Serial.begin(115200);           // Initialize Serial communication
  while(!Serial);                 // Wait for Serial port to open

  pinMode(TFT_BL, OUTPUT);        // Enable BackLight
  digitalWrite(TFT_BL, HIGH);     // Turn On BackLight
  tft.init(TFT_HEIGHT,TFT_WIDTH); // Initialize ST7789 240×240
  
  // NOTE¹:  The GFX Graphics Test may not start
  // ¯¯¯¯¯¯  until you open the Serial Monitor!!!

  Serial.print(F("ST7789 GFX Graphics Test"));
  tft.setRotation(3);             // Rotate Display 270°, Landscape
  tft.setTextSize(2);                           // Text-size x2
  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  tft.setTextColor(ST77XX_ORANGE);
  tft.setCursor(10,10);
  tft.print("Hello, World! ");
  Serial.println(F(" Initialized!"));           delay(2000);
}

void loop() {
  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  Serial.print(F("Start time:  "));
  time = millis() - time;
  Serial.println(time, DEC);
  tft.setCursor(0,0);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_CYAN);
  tft.print(F("Start time:  "));
  tft.setTextColor(ST77XX_WHITE);
  tft.println(time, DEC);                       delay(4000);

  // Large block of text
  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  tft.setTextSize(1);                           // Text-size normal
  testDrawText("Lorem ipsum dolor sit amet, consectetur adipiscing "
               "elit. Curabitur adipiscing ante sed nibh tincidunt "
               "feugiat. Maecenas enim massa, fringilla sed "
               "malesuada et, malesuada sit amet turpis. Sed "
               "porttitor neque ut ante pretium vitae malesuada "
               "nunc bibendum. Nullam aliquet ultrices massa eu "
               "hendrerit. Ut sed nisi lorem. In vestibulum purus "
               "a tortor imperdiet posuere. ", ST77XX_WHITE);
                                                delay(2000);

  // A single pixel centered on the screen
  tft.drawPixel(tft.width()/2, tft.height()/2, ST77XX_GREEN); 
                                                delay(2000);

  testDrawLines(ST77XX_YELLOW);                 delay(500);
  testFastLines(ST77XX_RED, ST77XX_BLUE);       delay(500);
  testDrawRects(ST77XX_GREEN);                  delay(500);
  testFillRects(ST77XX_MAGENTA, ST77XX_WHITE);  delay(500);

  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  testFillCircles(10, ST77XX_BLUE);
  testDrawCircles(10, ST77XX_WHITE);            delay(500);

  testRoundRects();                             delay(500);
  testTriangles();                              delay(500);

  mediaButtons();                               delay(2000);
  //tft.invertDisplay(true); delay(500);
  //tft.invertDisplay(false); delay(500);

  tftPrintTest();                               delay(2000);

  time = millis() - time;
  Serial.print(F("\n  End time: "));
  Serial.println(time, DEC);
  tft.setCursor(0,0);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_CYAN);
  tft.print(F("\n  End time: "));
  tft.setTextColor(ST77XX_WHITE);
  tft.println(time, DEC);
  Serial.println("\nRepeat\n");                 delay(2000);
}

//--- Functions ----------------------------------------------------
// https://learn.adafruit.com/adafruit-gfx-graphics-library

void testDrawLines(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  for(int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0,0, x,tft.height()-1, color);
    delay(0);
  }
  for(int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0,0, tft.width()-1,y, color);
    delay(0);
  }
  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  color = ST77XX_MAGENTA;
  for(int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1,0, x,tft.height()-1, color);
    delay(0);
  }
  for(int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1,0, 0,y, color);
    delay(0);
  }
  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  color = ST77XX_ORANGE;
  for(int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0,tft.height()-1, x,0, color);
    delay(0);
  }
  for(int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0,tft.height()-1, tft.width()-1,y, color);
    delay(0);
  }
  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  color = ST77XX_CYAN;
  for(int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1,tft.height()-1, x,0, color);
    delay(0);
  }
  for(int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1,tft.height()-1, 0,y, color);
    delay(0);
  }
} // END: testDrawLines()

void testDrawText(char *text, uint16_t color) {
  tft.setCursor(0,0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
} // END: testDrawText()

void testFastLines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  for(int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0,y, tft.width(), color1);
  }
  for(int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x,0, tft.height(), color2);
  }
} // END: testFastLines()

void testDrawRects(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  for(int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2-x/2,tft.height()/2-x/2, x,x, color);
  }
} // END: testDrawRects()

void testFillRects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  for(int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2-x/2,tft.height()/2-x/2, x,x, color1);
    tft.drawRect(tft.width()/2-x/2,tft.height()/2-x/2, x,x, color2);
  }
} // END: testFillRects()

void testFillCircles(uint8_t radius, uint16_t color) {
  for(int16_t x=radius; x < tft.width(); x+=radius*2) {
    for(int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x,y, radius, color);
    }
  }
} // END: testFillCircles()

void testDrawCircles(uint8_t radius, uint16_t color) {
  for(int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for(int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x,y, radius, color);
    }
  }
} // END: testDrawCircles()

void testTriangles() {
  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  uint16_t color = 0xF800;                      // Chartreuse
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y=0;
  int z = tft.width();
  for(t=0; t <= 15; t++) {
    tft.drawTriangle(w,y, y,x, z,x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
} // END: testTriangles()

void testRoundRects() {
  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  uint16_t color = 100;
  int i;
  int t;
  for(t=0; t <= 4; t+=1) {
    int x=0;
    int y=0;
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
} // END: testRoundRects()

void mediaButtons() {
  tft.setRotation(2);             // Rotate Display 180°, Portrait
  // Play
  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  tft.fillRoundRect(25,10, 78,60, 8, ST77XX_WHITE);
  tft.fillTriangle(42,20, 42,60, 90,40, ST77XX_RED);
                                                delay(500);
  // Pause
  tft.fillRoundRect(25,90, 78,60, 8, ST77XX_WHITE);
  tft.fillRoundRect(39,98, 20,45, 5, ST77XX_GREEN);
  tft.fillRoundRect(69,98, 20,45, 5, ST77XX_GREEN);
                                                delay(500);
  // Play color
  tft.fillTriangle(42,20, 42,60, 90,40, ST77XX_BLUE);
                                                delay(500);
  // Pause color
  tft.fillRoundRect(39,98, 20,45, 5, ST77XX_RED);
  tft.fillRoundRect(69,98, 20,45, 5, ST77XX_RED);
  // Play color
  tft.fillTriangle(42,20, 42,60, 90,40, ST77XX_GREEN);
                                                delay(2000);
} // END: mediaButtons()

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.setRotation(3);             // Rotate Display 270°, Landscape
  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  tft.setCursor(0,30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hello, World!");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello, World!");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello, World!");
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);                          delay(1500);
  
  tft.setCursor(0,0);
  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.println("Hello, World!");
  tft.setTextSize(2);
  tft.println("Hello, World!");
  tft.setTextColor(ST77XX_GREEN);
  
  float Pi = 3.1415926;                         // do not delete!
  tft.print(Pi, 6);
  tft.println(" Want Pi?");
  tft.println(" ");
  tft.print(8675309, HEX);          // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");                             delay(2000);

  tft.fillScreen(ST77XX_BLACK);                 // Clear the screen
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(0,0);
  tft.setTextSize(2);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis()/1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.");                       delay(2000);
} // END: tftPrintTest()

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

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
02:19:49.569 -> ST7789 GFX Graphics Test Initialized!
02:19:54.950 -> Start time:  1654
02:21:31.640 -> 
02:21:31.640 ->   End time: 58318
02:21:31.719 -> 
02:21:31.719 -> Repeat
...
--------------------------------------------------------------------
Output:
¯¯¯¯¯¯¯
ESP32-S3_240x240_ST7789_GFX-graphicsTest.ino:61:16: WARNING: 
ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings]

   61 |   testDrawText("Lorem ipsum dolor sit amet, consectetur adipiscing "
      |                ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   62 |                "elit. Curabitur adipiscing ante sed nibh tincidunt "
      |                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   63 |                "feugiat. Maecenas enim massa, fringilla sed "
      |                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   64 |                "malesuada et, malesuada sit amet turpis. Sed "
      |                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   65 |                "porttitor neque ut ante pretium vitae malesuada "
      |                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   66 |                "nunc bibendum. Nullam aliquet ultrices massa eu "
      |                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   67 |                "hendrerit. Ut sed nisi lorem. In vestibulum purus "
      |                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   68 |                "a tortor imperdiet posuere. ", ST77XX_WHITE);
      |                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      
Sketch uses 370406 bytes (11%) of program storage space. 
Maximum is 3145728 bytes.
Global variables use 22668 bytes (6%) of dynamic memory, 
            leaving 305012 bytes for local variables. 
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c

Leaving...
Hard resetting with RTC WDT...
*******************************************************************/
