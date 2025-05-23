/* GFX-Mandelbrot-graphics-demo.ino
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 * Exercise the 240×240 ST7789 TFT LCD
 * Based loosely on an Adafruit Mandelbrot example
 */

#include <Adafruit_GFX.h>    // Adafruit GFX Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // SPI library
//#include "XPT2046_Touchscreen.h"    // XPT2046 Touch Screen library

// SPI Pinout
#define TFT_MISO     -1      // 1.54in 240×240 ST7789 LCD pins
#define TFT_BL       42      // BLK BackLight       ESP32-S3-WROOM-1
#define TFT_CS       41      // CS  Chip Select       "Right-Side"
#define TFT_DC       40      // RS  Data/Command      "Availiable"
#define TFT_RST      45      // RES Reset                 "Pins"
#define TFT_MOSI     47      // SDA SPI Data
#define TFT_SCK      21      // SCL SPI Clock
//#define TOUCH_CS    1      //     

#define TFT_WIDTH   240
#define TFT_HEIGHT  240

// Adafruit software SPI GFX Constructor for object ‘tft’
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS,TFT_DC,TFT_MOSI,TFT_SCLK,TFT_RST);
//XPT2046_Touchscreen ts(TOUCH_CS);

const int16_t
  bits        =  12,    // Fractional resolution
  pixelWidth  = 240,    // TFT dimensions
  pixelHeight = 240,    //      "
  iterations  =  30;    //  Fractal iteration limit or 'dwell'
float
  centerReal  = -0.5,   // Image center point in complex plane
  centerImag  =  0.0,
  rangeReal   =  3.0,   // Image coverage in complex plane
  rangeImag   =  3.0;

boolean istouched = false;


void setup() {
  Serial.begin(115200);          // Initialize Serial communication
  while(!Serial);                // Wait for the Serial port to open
  
  Serial.println("GFX Mandelbrot demo");
  //Serial.println("Tap screen to increase zoom");

  tft.begin();                   // Init TFT LCD screen
  tft.setRotation(1);            // TFT LCD Landscape orientation
  tft.fillScreen(ST77XX_BLACK);  // Clear the screen
//  ts.begin();                    // Init Touch Screen controller
//  ts.setRotation(3);             // Match Touch Screen orientation
}

void loop() {
  int64_t  n, a, b, a2, b2, posReal, posImag;
  uint32_t startTime, elapsedTime;

  int32_t
    startReal = (int64_t)((centerReal - rangeReal * 0.5)   * (float)(1 << bits)),
    startImag = (int64_t)((centerImag + rangeImag * 0.5)   * (float)(1 << bits)),
    incReal   = (int64_t)((rangeReal / (float)pixelWidth)  * (float)(1 << bits)),
    incImag   = (int64_t)((rangeImag / (float)pixelHeight) * (float)(1 << bits));

  startTime = millis();   // Calculate time taken to create an image
  posImag   = startImag;
  for(int y=0; y < pixelHeight; y++) {
    posReal = startReal;
    for(int x=0; x < pixelWidth; x++) {
      a = posReal;
      b = posImag;
      for(n=iterations; n > 0 ; n--) {
        a2 = (a * a) >> bits;
        b2 = (b * b) >> bits;
        if((a2 + b2) >= (4 << bits)) break;
        b  = posImag + ((a * b) >> (bits - 1));
        a  = posReal + a2 - b2;
      }
      tft.drawPixel(x,y, (n * 29)<<8 | (n * 67));
      // Change the 29 and/or 67 to affect colors...
      posReal += incReal;
    }
    posImag -= incImag;
  }

  elapsedTime = millis() - startTime;
  Serial.print("Took ");
  Serial.print(elapsedTime/1000.0); Serial.println(" secs");

  tft.setCursor(2,10);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.print("Pass Complete: ");
  tft.println(rangeReal);

  while(istouched == false) { // When drawing complete, wait for Touch
    //istouched = ts.touched();
    delay(2000);
    istouched = true;
  }
  if(istouched) {
    tft.fillScreen(ST77XX_BLACK); // Blank screen
    //TS_Point p = ts.getPoint();   // Send Touch info to Serial Monitor
    //Serial.print("Pressure = ");
    //Serial.print(p.z);
    //Serial.print(", x = ");
    //Serial.print(p.x);
    //Serial.print(", y = ");
    //Serial.println(p.y);
    rangeReal *= 0.90;              // Zoom in each iteration
    rangeImag *= 0.90;
    istouched = false;              // Reset Touch flag
    if(rangeReal < 1.3) {           // Reset the Zoom
      rangeReal = 3.0;
      rangeImag = 3.0;
    }
  }
}
