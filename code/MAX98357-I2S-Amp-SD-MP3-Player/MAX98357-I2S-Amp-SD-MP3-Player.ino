/* MAX98357-I2S-Amp-SD-MP3-Player.ino     (I²S MP3 Player)
 * Requires a MAX98357 I²S Audio Amplifier/Speaker
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 * The MAX98357A (3 Watt Audio Amplifier with DAC), connectes three
 * lines (DOUT, BLCK, LRC) to the I²S bus. The I²S output frequency
 * is always 48kHz regardless of the input source, so Bluetooth
 * devices can also be connected without any problems. To get stereo
 * two MAX98357A are necessary. Using “AudioI2S” you can play MP3s,
 * Icy-streams, GoogleTTS, OpenAIspeech, and more.
 *
 * This sketch is a simple ESP32-S3 microSD_Card I²S MP3 Player:
 *
 *  Play your MP3 files from a microSD_Card
 *      1. Micro SD Card   (less than 2G)
 *      2. Micro SDHC Card (less than 32G)
 *  Uses a MAX98357 I²S Amplifier
 *  Uses the ESP32-audioI2S Library:
 *      https://github.com/schreibfaul1/ESP32-audioI2S
 *
 * Using the MAX98357 I²S Audio Amplifier and Speaker:
 *
 *   The sound source will be an MP3 file that is stored on a
 *   microSD_Card.  This is an extremely basic MP3 player, for
 *   practical use you would need to make a system for navigating
 *   the microSD_Card to play more than one selection.  This sketch
 *   is just to illustrate how to use the MAX98357 I²S Audio Amplifier,
 *   as well as a library that makes working with I²S Audio apps a
 *   bit easier.
 *
 * Wiring:
 * ¯¯¯¯¯¯¯
 *  | ESP32-S3 Dev Board | I²S MAX98357A Amplifier/Speaker |
 *  |-------------------:|---------------------------------|
 *  |    3V3             | 1. VIN                          |
 *  |    GND             | 2. GND                          |
 *  |    VIN (0Ω = Left) | 3. SD   (L/R Channel Select)    |
 *  |    GND (12dB Gain) | 4. GAIN (Signal Amp)            |
 *  |    GPIO7           | 5. DIN  Digital Signal In       |
 *  |    GPIO15          | 6. BCLK Bit Clock               |
 *  |    GPIO16          | 7. LRC  Left Right Clock        |
 *  |                    |                                 |
 *  |    Audio ⧾         | Speaker Positive  (+)           |
 *  |    Audio ⧿         | Speaker Negative  (-)           |
 *
 *  | ESP32-S3 Dev Board | SPI microSD_Card Pins           |
 *  |-------------------:|---------------------------------|
 *  |     3V3            | 1. 3V3  (Power)                 |
 *  |     GPIO10         | 2. CS   (Chip Select)           |
 *  |     GPIO11         | 4. MOSI (SPI SDI)               |
 *  |     GPIO12         | 5. SCK  (SPI Clock)             |
 *  |     GPIO13         | 3. MISO (SPI SDO)               |
 *  |     GND            | 6. GND                          |
 *
 * Reference: Sound with ESP32 – I²S Protocol
 * https://dronebotworkshop.com/esp32-i2s/
 */

/*******************************************************************
Type-C USB Data cable plugged into Left-side ESP32-S3 USB-OTG port.
                                   ¯¯¯¯¯¯¯¯¯          ¯¯¯¯¯¯¯
Arduino IDE > Tools                                  [CONFIGURATION]
                   Board: "ESP32S3 Dev Module"
         USB CDC On Boot: "Enabled"  **Cable plugged into Left USB**
           CPU Frequency: "240MHz (WiFi)"                 ¯¯¯¯
         USB DFU On Boot: "Disabled"
              Flash Mode: "QIO 80MHz"
              Flash Size: "16MB 128Mb"  【or】
              Flash Size: "8MB 64Mb"    ...check your board!
USB Firmware MSC On Boot: "Disabled"
        Partition Scheme: "16M Flash (2MB APP/12.5MB FATFS)"  【or】
        Partition Scheme: "8MB with spiffs (3MB APP/1.5MB SPIFFS)"
                   PSRAM: "OPI PSRAM"
             Upload Mode: "UART0/Hardware CDC"
            Upload Speed: "115200"
                USB Mode: "Hardware CDC and JTAG"
*******************************************************************/

#include <FS.h>                     // File System library
#include <SPI.h>                    // SPI library
#include <SD.h>                     // SD Card library
#include "Audio.h"                  // ESP32-audioI2S Library

#define SD_CS         10            // microSD_Card Chip Select
#define SPI_MOSI      11            // SPI Data In  (SDI)
#define SPI_SCK       12            // SPI Clock    (CLK)
#define SPI_MISO      13            // SPI Data Out (SDO)

#define I2S_DOUT       7            // MAX98357 I²S Data IN/OUT
#define I2S_BCLK      15            // MAX98357 I²S Bit Clock
#define I2S_LRC       16            // MAX98357 I²S Left Right Clock

Audio audio;                        // ESP32-audioI2S Audio object

void setup() {
  Serial.begin(115200);             // Initialize Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  pinMode(SD_CS,      OUTPUT);      // Set microSD_Card CS as OUTPUT
  digitalWrite(SD_CS, HIGH);        // Disable (Active LOW)

  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI); // Initialize the SPI bus

  if(!SD.begin(SD_CS)) {            // Initialize the microSD_Card
    Serial.println("Error accessing microSD_Card!");
    while(true);
  }
 
  // Determine what type of MicroSD card is mounted
  uint8_t cardType = SD.cardType();
 
  if(cardType == CARD_NONE) {
    Serial.println("No MicroSD card inserted!");
    return;
  }
  Serial.print("MicroSD Card Type: "); // Print card type
  if(cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if(cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if(cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }
  sd_status = true;                 // MicroSD is good, set status
  

  // Setup the MAX98357 I²S Amplifier & Volume control
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(5);                   // Set Volume

  // Open your .mp3 music file from the microSD_Card
  audio.connecttoFS(SD,"/MYMUSIC.mp3"); // Change to name of chosen
}                                       // .mp3 file on microSD_Card

void loop() {
  audio.loop();
}
