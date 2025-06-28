/* MAX98357-I2S-Amp-SD-MP3-Player.ino     (I²S MP3 Player)
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 * Requires a MAX98357 I²S Audio Amplifier/Speaker
 * Requires a SPI microSD_Card Reader
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
 * NOTE¹:  You will NOT hear the MP3 file playing
 * ¯¯¯¯¯¯  until you open the Serial Monitor!!!
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
 * DroneBot Workshop 2022
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
              Flash Size: "16MB 128Mb"
USB Firmware MSC On Boot: "Disabled"
        Partition Scheme: "16M Flash (3MB APP/9.9MB FATFS)"
                   PSRAM: "OPI PSRAM"
             Upload Mode: "UART0/Hardware CDC"
            Upload Speed: "115200"
                USB Mode: "Hardware CDC and JTAG"
*******************************************************************/

#include <FS.h>                     // File System library
#include <SPI.h>                    // SPI library
#include <SD.h>                     // SD Card library
#include "Audio.h"                  // ESP32-audioI2S Library

#define I2S_DOUT     7              // MAX98357A I²S Data_Out
#define I2S_BCLK    15              // MAX98357A I²S Bit_Clock
#define I2S_LRC     16              // MAX98357A I²S WS/Left_Right_Clock
#define I2S_MCLK     0              // not used

#define SD_CS       10              // microSD_Card SPI Chip Select
#define SD_MOSI     11              // ESP32-S3 Default Pins SPI MOSI
#define SD_SCK      12              //              "        SPI SCK
#define SD_MISO     13              //              "        SPI MISO

// SD_Card Filename, MP3 Music File (8.3 short names required)
const char* filename = "/OlsenBan.mp3";

Audio audio;                        // Create ESP32-audioI2S Audio object

void setup() {
  Serial.begin(15200);              // Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open
/*
 * NOTE:  You will NOT hear the MP3 file playing
 * ¯¯¯¯¯  until you open the Serial Monitor!!!
 */

  // Initialize SPI bus and deactivate SD_Card Chip Select
  pinMode(SD_CS,      OUTPUT);      // SPI SD_Card Chip Select
  digitalWrite(SD_CS, HIGH);        // Active LOW!
  SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  SPI.setFrequency(1000000);

  if(!SD.begin(SD_CS)) {            // SPI SD_Card Chip Select
    Serial.println("Error accessing microSD_Card!");
    while(true); // Don't do anything more:
  }

  // Setup MAX98357A I²S Audio Amp using ESP32-audioI2S library
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(12);              // Range: 0..21
  audio.connecttoFS(SD, filename);  // Open SD_Card MP3 music file
}

void loop() {
    audio.loop();                   // Play SD_Card MP3 music file
}

// ESP32-audioI2S Optional bits...
void audio_info(const char *info) {     // Description
    Serial.print("Info        "); Serial.println(info);
}
void audio_id3data(const char *info) {  // ID3 metadata
    Serial.print("ID3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info) {  // End-Of-File
    Serial.print("EOF_mp3     ");Serial.println(info);
}
void audio_showstation(const char *info) { // Station
    Serial.print("Station     ");Serial.println(info);
}
void audio_showstreamtitle(const char *info) { // Stream Title
    Serial.print("streamTitle ");Serial.println(info);
}
void audio_bitrate(const char *info) {  // Bit Rate
    Serial.print("Bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info) { // Duration in sec
    Serial.print("Commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info) {   // URL homepage
    Serial.print("icyURL      ");Serial.println(info);
}
void audio_lasthost(const char *info) { // Stream URL played
    Serial.print("lastHost    ");Serial.println(info);
}

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
23:58:11.403 -> Info        audioI2S Version 3.3.0
23:58:11.403 -> Info        PSRAM found, inputBufferSize: 630773 bytes
23:58:11.403 -> Info        buffers freed, free Heap: 259376 bytes
23:58:11.436 -> Info        Reading file: "/OlsenBan.mp3"
23:58:11.436 -> Info        MP3Decoder has been initialized,
                              free Heap: 254748 bytes, free stack 5700 DWORDs
23:58:12.167 -> Info        Content-Length: 328963
23:58:12.167 -> Info        ID3 framesSize: 265
23:58:12.167 -> Info        ID3 version: 2.4
23:58:12.167 -> Info        ID3 extended header
23:58:12.167 -> ID3data     Year: 2014
23:58:12.167 -> ID3data     Album: Olsen-Banden
23:58:12.167 -> ID3data     Artist: Bjarne Liller - Olsen Banden (Titelmusik der Olsenbande)
23:58:12.167 -> Info        Audio-Length: 328698
23:58:12.167 -> Info        stream ready
23:58:12.167 -> Info        syncword found at pos 0
23:58:12.167 -> Info        MPEG-2.5, Layer I
23:58:12.167 -> Info        Channels: 2
23:58:12.167 -> Info        SampBitsPerSample: 16
23:58:12.167 -> Info        BitRate: 128000
23:58:30.499 -> Info        Closing audio file "OlsenBan.mp3"
23:58:30.499 -> EOF_mp3     OlsenBan.mp3
23:58:30.499 -> Info        End of file "OlsenBan.mp3"

--------------------------------------------------------------------
Output:
¯¯¯¯¯¯¯
Sketch uses 1511178 bytes (48%) of program storage space.
 Maximum is 3145728 bytes.
Global variables use 63884 bytes (19%) of dynamic memory,
            leaving 263796 bytes for local variables.
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c

Leaving...
Hard resetting with RTC WDT...
*******************************************************************/
