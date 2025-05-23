// TFT_eSPI_Mandlebrot.ino
// ESP32-S3 1.54in TFT Expansion Board with Speaker
// LCD 1.54in 240×240 color IPS TFT (ST7789T3)

// This sketch may run quite slowly due to the large number of
// floating-point calculations per pixel.

#include <TFT_eSPI.h>           // Hardware-specific library
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

#define TFT_GREY 0x7BEF

unsigned long runTime = 0;

float    sx = 0, sy = 0;
uint16_t x0 = 0, x1 = 0, yy0 = 0, yy1 = 0;

void setup() {
  Serial.begin(115200);          // initialize Serial communication
  while(!Serial);                // wait for the Serial port to open

  //randomSeed(analogRead(A0));
  Serial.println("TFT_eSPI Mandlebrot demo");
  tft.init();                                   // Setup the LCD
  tft.setRotation(3);                           // Landscape
}

void loop() {
  runTime = millis();
  tft.fillScreen(TFT_BLACK);                    // Clear the screen

  tft.startWrite();
  for(int px=1; px < 240; px++) {
    for(int py=0; py < 240; py++) {
      float x0 = (map(px, 0, 240, -250000/2, -242500/2)) / 100000.0;
      //scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.5, 1))
      float yy0 = (map(py, 0, 240, -75000/4, -61000/4)) / 100000.0;
      //scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1, 1))
      float xx = 0.0;
      float yy = 0.0;
      int iteration = 0;
      int max_iteration = 128;
      while(((xx * xx + yy * yy) < 4)  &&  (iteration < max_iteration)) {
        float xtemp = xx * xx - yy * yy + x0;
        yy = 2 * xx * yy + yy0;
        xx = xtemp;
        iteration++;
      }
      int color = rainbow((3*iteration+64)%128);
      yield(); tft.drawPixel(px,py, color);
    }
  }
  tft.endWrite();

  Serial.println(millis()-runTime);
  while(1) yield();
}

unsigned int rainbow(int value) {
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = Blue through to Red = Blue
  // RGB565 Conversion
  byte red   = 0;   // Red is the top 5 bits of a 16-bit color value
  byte green = 0;   // Green is the middle 6 bits
  byte blue  = 0;   // Blue is the bottom 5 bits

  byte quadrant = value / 32;

  if(quadrant == 0) {
    blue  = 31;
    green = 2 * (value % 32);
    red   = 0;
  }
  if(quadrant == 1) {
    blue  = 31 - (value % 32);
    green = 63;
    red   = 0;
  }
  if(quadrant == 2) {
    blue  = 0;
    green = 63;
    red   = value % 32;
  }
  if(quadrant == 3) {
    blue  = 0;
    green = 63 - 2 * (value % 32);
    red   = 31;
  }
  return (red << 11) + (green << 5) + blue;
}
