/* GFX-Mandelbrot-graphics-demo.ino
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 * built-in: TFT 1.54in 240×240 ST7789 LCD Display
 *
 * Exercise the 240×240 ST7789 TFT LCD
 * Based loosely on an Adafruit Mandelbrot Set example.
 *
 * Uses the built-in user [BOOT] button (GPIO0) for Zoom.
 *
 * The Mandelbrot set is well-known, even outside mathematics, for 
 * how it exhibits complex ‘fractal’ structures when visualized and 
 * magnified. The Mandelbrot set is defined as a set of complex 
 * numbers for which the iterated function “Z^2 + C” doesn’t diverge 
 * to infinity. Therefor the Mandelbrot set is essentially a visual 
 * representation of how the behavior of a simple equation changes 
 * depending on the starting complex number.
 *
 * When plotted on the complex plane, the Mandelbrot set forms a 
 * distinctive shape, with points within the set colored black, and 
 * points outside the set colored based on how quickly they diverge.
 *
 * The Mandelbrot set is a “fractal”, meaning it exhibits self-
 * similarity at different scales, meaning that zooming in on any 
 * part of the set reveals similar, but smaller, patterns. 
 *
 * The Mandelbrot set is not just a pretty picture; it's deeply 
 * connected to various mathematical fields like number theory, 
 * topology, and even physics. It's also a great example of how a 
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

#include <Adafruit_GFX.h>    // Adafruit GFX Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // SPI library

// SPI Pins declared for the TFT display (Right-side ESP32-S3-WROOM)
#define TFT_BL       42     // BackLight
#define TFT_CS       41     // SPI Chip Select
#define TFT_DC       40     // SPI Data/Command
#define TFT_RST      45     // SPI Reset
#define TFT_MOSI     47     // SPI Data  (SDA)
#define TFT_SCLK     21     // SPI Clock (SCL)

// Adafruit software SPI GFX Constructor for object ‘tft’
Adafruit_ST7789 tft=Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI,
                                    TFT_SCLK, TFT_RST);
#define TFT_WIDTH   240     // Width  in pixels
#define TFT_HEIGHT  240     // Height in pixels

const int btnPin    = 0;    // User [BOOT] button GPIO0
      int btnState  = 0;    // [BOOT] pushbutton status

const int16_t               // Mandelbrot control variables
  bits        =  12,        // Fractional resolution
  pixelWidth  = 240,        // TFT dimensions
  pixelHeight = 240,        //      "
  iterations  =  30;        // Fractal iteration limit or 'dwell'
float
  centerReal  = -0.5,       // Image center point in complex plane
  centerImag  =  0.0,       //      "
  rangeReal   =  3.0,       // Image coverage in complex plane
  rangeImag   =  3.0;       //      "


void setup() {
  Serial.begin(115200);     // Initialize Serial communication
  while(!Serial);           // Wait for the Serial port to open
  pinMode(btnPin, INPUT);   // Initialize the [BOOT] button

  Serial.println("GFX Mandelbrot image demo...");
  Serial.println("At Pass Complete: Press [BOOT] to increase Zoom.");

  tft.init(TFT_HEIGHT, TFT_WIDTH); // Init ST7789V2 240×320 TFT LCD
  tft.setRotation(3);              // TFT LCD Landscape orientation
  tft.fillScreen(ST77XX_BLACK);    // Clear the screen
}

void loop() {
  int64_t  n, a, b, a2, b2, posReal, posImag;
  uint32_t startTime, elapsedTime;

  int32_t
    startReal = (int64_t)((centerReal - rangeReal * 0.5)   * (float)(1 << bits)),
    startImag = (int64_t)((centerImag + rangeImag * 0.5)   * (float)(1 << bits)),
    incReal   = (int64_t)((rangeReal / (float)pixelWidth)  * (float)(1 << bits)),
    incImag   = (int64_t)((rangeImag / (float)pixelHeight) * (float)(1 << bits));

  startTime = millis(); // Calculate time to create a Mandelbrot image
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
      /*
       * Change the 29 and/or 67 to affect colors...
       */
      posReal += incReal;
    }
    posImag -= incImag;
  }

  elapsedTime = millis() - startTime;
  Serial.print("Mandelbrot image took ");
  Serial.print(elapsedTime/1000.0); Serial.println(" seconds.");

  tft.setCursor(2,10);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.print("Pass Complete: ");
  tft.println(rangeReal);

  // Wait 2 seconds for a [BOOT] button Press, to Zoom in Mandelbrot
  int32_t btnTimer = millis()+2000; // 2 second [BOOT] Button timer
  btnState = digitalRead(btnPin);   // Read [BOOT] Button
  while(millis() < btnTimer && btnState == HIGH) {
    btnState = digitalRead(btnPin); // Read [BOOT] Button
    delay(10);
  }
  if(btnState == HIGH) {           // [BOOT] button pressed for Zoom
    tft.fillScreen(ST77XX_BLACK);  // Clear screen
    rangeReal *= 0.90;             // Zoom amount for each Pass
    rangeImag *= 0.90;             //       "
    btnState   = !btnState;        // Reset btnState flag
    if(rangeReal < 1.3) {          // Reset Zoom if over Zoom limit
      rangeReal = 3.0;             //       "
      rangeImag = 3.0;             //       "
    }
  }
}

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
04:06:17.360 -> GFX Mandelbrot image demo
04:06:17.360 -> At Pass Complete: Press [BOOT] to increase Zoom.
04:06:30.682 -> Mandelbrot image took 11.15 seconds.
04:06:45.564 -> Mandelbrot image took 11.17 seconds.
04:06:57.277 -> Mandelbrot image took 11.17 seconds.
04:07:12.176 -> Mandelbrot image took 11.21 seconds.
...
--------------------------------------------------------------------
OUTPUT:
¯¯¯¯¯¯¯
Sketch uses 366198 bytes (11%) of program storage space. 
Maximum is 3145728 bytes.
Global variables use 22692 bytes (6%) of dynamic memory, 
            leaving 304988 bytes for local variables. 
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c
...
Leaving...
Hard resetting with RTC WDT...
*******************************************************************/
