// YD-ESP32-S3_BlinkAllLEDs.ino
// YD-ESP32-S3 (ESP32-S3-WROOM-1 Dev)

#include <Adafruit_NeoPixel.h>  // Adafruit NeoPixel Graphics lib

#define LED_TX_PIN  43          // Define pins for the LEDs
#define LED_RX_PIN  44
#define RGB_LED_PIN 48

#define NUM_RGB_LEDS 1          // Assume 1 WS2812 NeoPixel LED

// Create an instance of the Adafruit_NeoPixel class
Adafruit_NeoPixel rgb_led =
  Adafruit_NeoPixel(NUM_RGB_LEDS, RGB_LED_PIN, NEO_GRB+NEO_KHZ800);

void setup() {
  Serial.begin(115200);         // Initialize Serial Monitor
  while(!Serial);               // wait for the Serial port to open

  pinMode(LED_TX_PIN, OUTPUT);  // Initialize the TX/RX LED pins
  pinMode(LED_RX_PIN, OUTPUT);

  rgb_led.begin();              // Initialize the NeoPixel RGB LED
  rgb_led.show();               // Initialize all Pixels to 'Off'
  Serial.println("Starting LED test sequence...");
}


void loop() {
  digitalWrite(LED_TX_PIN, HIGH);   // Blink the TX LED
  delay(500);
  digitalWrite(LED_TX_PIN, LOW);
  delay(500);

  digitalWrite(LED_RX_PIN, HIGH);   // Blink the RX LED
  delay(500);
  digitalWrite(LED_RX_PIN, LOW);
  delay(500);

  BlinkRGBLED();                    // Blink the NeoPixel RGB LED
}


void BlinkRGBLED() {
  // Set the NeoPixel RGB LED to Red
  rgb_led.setPixelColor(0, rgb_led.Color(255, 0, 0));   // Red
  rgb_led.show();
  delay(500);

  // Set the NeoPixel RGB LED to Green
  rgb_led.setPixelColor(0, rgb_led.Color(0, 255, 0));   // Green
  rgb_led.show();
  delay(500);

  // Set the NeoPixel RGB LED to Blue
  rgb_led.setPixelColor(0, rgb_led.Color(0, 0, 255));   // Blue
  rgb_led.show();
  delay(500);

  // Turn Off the NeoPixel RGB LED
  rgb_led.setPixelColor(0, rgb_led.Color(0, 0, 0));     // Off
  rgb_led.show();
  delay(500);
}
