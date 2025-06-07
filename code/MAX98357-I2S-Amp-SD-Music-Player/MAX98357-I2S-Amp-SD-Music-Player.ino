/* MAX98357-I2S-Amp-SD-Music-Player.ino
 *
 * Simple ESP32-S3 microSD_Card I²S Music Player:
 *  Play MP3 files from a microSD_Card
 *  Uses a MAX98357 I²S Amplifier
 *  Uses the ESP32-audioI2S Library:
 *      https://github.com/schreibfaul1/ESP32-audioI2S
 *
 * Using the MAX98357 I²S Amplifier:
 *   The sound source will be an MP3 file that is stored on a
 *   microSD_Card.  This is an extremely basic MP3 player, for
 *   practical use you would need to make a system for navigating
 *   the microSD_Card to play more than one selection.  This sketch
 *   is just to illustrate how to use the MAX98357 I²S Amplifier,
 *   as well as a library that makes working with I²S audio
 *   applications a bit easier.
 *
 * Wiring:
 *
 * MAX98357 I²S Amp                 ESP32-S3-WROOM-1
 * 1. LRC  (Left Right Clock)   --> GPIO16
 * 2. BCLK (Bit Clock)          --> GPIO15
 * 3. DIN  (Digital Signal In)  --> GPIO7
 * 4. GAIN                      --> Connect to GND (9 dB gain)
 * 5. SD   (L/R Channel Select) --> Connect to GND (select Left)
 * 6. GND                       --> GND
 * 7. VIN  (Power)              --> 3V3
 *
 * External Speaker interface: (+ —)
 * Audio+  Connect to Speaker Positive (usually Red wire)
 * Audio-  Connect to Speaker Negative
 *
 * microSD Card                     ESP32-S3-WROOM-1
 * 1. 3V3  (Power)              --> 3V3
 * 2. CS   (Chip Select)        --> GPIO10
 * 3. MOSI (SPI SDI)            --> GPIO11
 * 4. CLK  (SPI Clock)          --> GPIO12
 * 5. MISO (SPI SDO)            --> GPIO13
 * 6. GND                       --> GND
 *
 * https://dronebotworkshop.com/esp32-i2s/
 */

#include "Arduino.h"                // Include required libraries
#include "Audio.h"
#include "SD.h"
#include "FS.h"
                                    // microSD_Card pins
#define SD_CS         10            // microSD_Card Chip Select
#define SPI_MOSI      11            // SPI Data In  (SDI)
#define SPI_SCK       12            // SPI Clock    (CLK)
#define SPI_MISO      13            // SPI Data Out (SDO)

                                    // MAX98357 I²S Amp pins
#define I2S_DOUT       7            // MAX98357 I²S Amp pins (DIN)
#define I2S_BCLK      15            //      "
#define I2S_LRC       16            //      "

Audio audio;                        // ESP32-audioI2S Audio object

void setup() {
  Serial.begin(115200);             // Initialize Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  pinMode(SD_CS,      OUTPUT);      // Set microSD_Card CS as OUTPUT
  digitalWrite(SD_CS, HIGH);        // Disable (Active LOW)

  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI); // Initialize the SPI bus

  if(!SD.begin(SD_CS)) {            // Start the microSD_Card
    Serial.println("Error accessing microSD_Card!");
    while(true);
  }

  // Setup MAX98357 I²S Amplifier & Volume control
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(5);               // Set Volume

  // Open .mp3 music file on microSD_Card
  audio.connecttoFS(SD,"/MYMUSIC.mp3"); // Change to name of chosen
}                                       // .mp3 file on microSD_Card

void loop() {
  audio.loop();
}
