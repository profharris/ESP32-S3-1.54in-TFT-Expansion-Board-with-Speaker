/* ESP32-S3-rgbFade
   ESP32-S3 1.54in TFT Expansion Board with Speaker

Make an RGB LED display a rainbow of colors!

The RGB LED on the ESP32-S3-WROOM is a NeoPixel. An ‘intellegent’
device with its' own internal processor. But basically it accepts
commands to mix RGB values and display the resulting color. In this
sketch, we will treat the RGB NeoPixel as if it were actually three
LEDs (Red, Green, and Blue) in one package. If you drive the LEDs
digitally (On/Off) you get eight combinations (2^3); Black/Off, Red,
Green, Blue, Cyan, Magenta, Yellow, and White (all three on).

If you drive the assumed 3 LEDs using PWM (Pulse Width Modulation),
you can generate pseudo analog 256 levels from Off to On. You can
drive the the three LEDs at these different levels, 0 (Off) to 255
(full On) for all three RGB colors, to display a possible 16,777,216
(256^3) color combinations.
*/

/* The first user function eightColors() steps through all
 * eight of these colors. The function is called from loop()
 * and the actual function code is further down in the sketch.
 *
 * The eightColors() function turns the virtual individual LEDs
 * full-on or full-off. If you want to generate more than eight
 * colors, you can do so by varying the brightness level of the
 * individual sudo RGB LEDs between full-on, 255, and full-off, 0.
 *
 * Earlier sketches used the analogWrite() function to do this. This
 * function would let you dim a LED from full-off to full-on over
 * 255 steps.
 *
 * We will be using the neopixelWrite() function with our RGB LED,
 * which allows us to mix the RGB values digitally.
 *
 * The user function showSpectrum() smoothly steps through all
 * the colors. Again the function is called in loop() and the
 * actual code is defined further down in this sketch.
 */

//#define RGB_BUILTIN 48    // DO NOT REDEFINE RGB_BUILTIN
                            // If so, digitalWrite() will not work.

#define RGB_BRIGHTNESS 64   // Change White brightness (max 255)

int Red    = 128; // How much Red   0..255
int Green  = 128; // How much Green 0..255
int Blue   = 128; // How much Blue  0..255

int dDelay = 500; // delay/show time for the 8 Digital colors
int aDelay = 125; // delay between the blended RGB colors
int aStep  =  32; // the number of colors to skip per increment

void setup() {
  Serial.begin(115200);          // initialize Serial communication
  while(!Serial);                // wait for the Serial port to open

  #ifdef RGB_BUILTIN
  Serial.println("RGB_BUILTIN");
  #else
  Serial.println("no RGB_BUILTIN");
  #endif

  // No need to initialize the RGB LED!
}

void loop() {
  eightColors();    // display the eight Digital colors
    delay(dDelay);
  showSpectrum();   // display the 16MB Analog colors
    delay(dDelay);
}

/* eightColors() -- displays the eight Digital (Full-On/Off) colors
 * that the RGB LED can produce. The primary colors Red, Green, Blue;
 * are followed by the secondary 2-On colors Magenta, Green, Cyan;
 * White is all three colors On, and Black/Off is no-color.
 */
void eightColors() {
  Red    = 128; // How much Red   0..255, adjust for brightness.
  Green  = 128; // How much Green 0..255, adjust for brightness.
  Blue   = 128; // How much Blue  0..255, adjust for brightness.

  neopixelWrite(RGB_BUILTIN, 0, 0, 0);          // Black? (all Off - no color)
    delay(dDelay*4);
  neopixelWrite(RGB_BUILTIN, Red, 0, 0);        // Red
    delay(dDelay);
  neopixelWrite(RGB_BUILTIN, 0, Green, 0);      // Green
    delay(dDelay);
  neopixelWrite(RGB_BUILTIN, 0, 0, Blue);       // Blue
    delay(dDelay);
  neopixelWrite(RGB_BUILTIN, Red, 0, Blue);     // Magenta (Red and Blue)
    delay(dDelay);
  neopixelWrite(RGB_BUILTIN, Red, Green, 0);    // Yellow (Red and Green)
    delay(dDelay);
  neopixelWrite(RGB_BUILTIN, 0, Green, Blue);   // Cyan (Green and Blue)
    delay(dDelay);
  neopixelWrite(RGB_BUILTIN, Red, Green, Blue); // White (all three colors)
    delay(dDelay);
  neopixelWrite(RGB_BUILTIN, 0, 0, 0);          // Black? (all Off-no color)
    delay(dDelay);
}

/* showSpectrum() -- to generate a full spectrum of colors, we will
 * increment (via a step rate) through 16,777,216 possible colors;
 * 0..255 parts Red, Green and Blue. This function uses 3 nested
 * 'for' loops, and a defined step rate increment aStep.
 */
void showSpectrum() {
  for (Blue=0; Blue < 256; Blue += aStep) {
    for (Green=0; Green < 256; Green += aStep) {
      for (Red=0; Red < 256; Red += aStep) {
        neopixelWrite(RGB_BUILTIN, Red, Green, Blue);
        delay(aDelay);
      }
    }
  }
  neopixelWrite(RGB_BUILTIN, 0, 0, 0);  // Black? (all Off-no color)
  delay(dDelay);
}
