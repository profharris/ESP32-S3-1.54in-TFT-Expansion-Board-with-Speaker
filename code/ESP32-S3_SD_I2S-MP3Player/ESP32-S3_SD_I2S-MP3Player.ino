/* ESP32-S3_SD_I2S-MP3Player.ino
 * Requires a MAX98357 I²S Amplifier/Speaker
 * Requires a SPI microSD_Card Reader
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 * Play MP3 file from a microSD card
 * Uses ESP32-audioI2S Library:
 *      https://github.com/schreibfaul1/ESP32-audioI2S
 *
 * NOTE¹:  You will NOT hear the MP3 file playing
 * ¯¯¯¯¯¯  until you open the Serial Monitor!!!
 *
 * DroneBot Workshop 2022
 * https://dronebotworkshop.com/esp32-i2s/
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

#define SD_CS       10              // SPI microSD_Card Pins
#define SD_MOSI     11              // ESP32-S3 Default Pins
#define SD_SCK      12
#define SD_MISO     13
                                    // MAX98357A I²S Audio Amp pins
#define I2S_DOUT     7              // Data_Out
#define I2S_BCLK    15              // Bit_Clock
#define I2S_LRC     16              // WS/Left_Right_Clock
#define I2S_MCLK     0              // not used

// SD_Card Filename, MP3 Music File (8.3 short names required)
const char* filename = "/OlsenBan.mp3";
//            Artest: Bjarne Liller - Olsen Banden
//          Bit Rate: 142 kbps
//          Channels: 2 (stereo)
// Audio Sample Rate: 44.100 kHz
//         File size: 321 kB

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

  // Setup MAX98357A I²S Audio Amp
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(12);              // Range: 0..21

  audio.connecttoFS(SD, filename);  // Open SD_Card MP3 music file
//audio.connecttoFS(SD, "test.wav");
//audio.connecttohost("http://mp3.ffh.de/radioffh/hqlivestream.mp3"); // 128k mp3
}

void loop() {
    audio.loop();                   // Play SD_Card MP3 music file
}

// Optional bits...
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
void audio_commercial(const char *info) { // duration in sec
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
esptool.py v4.8.1
Serial port COM8
Connecting...

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c

Uploading stub...
Running stub...
Stub running...

Configuring flash size...
Flash will be erased from 0x00000000 to 0x00004fff...
Flash will be erased from 0x00008000 to 0x00008fff...
Flash will be erased from 0x0000e000 to 0x0000ffff...
Flash will be erased from 0x00010000 to 0x00180fff...
Compressed 20208 bytes to 13058...
Writing at 0x00000000... (100 %)
Wrote 20208 bytes (13058 compressed) at 0x00000000 in 0.4 seconds
  (effective 418.3 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 144...
Writing at 0x00008000... (100 %)
Wrote 3072 bytes (144 compressed) at 0x00008000 in 0.1 seconds
  (effective 422.2 kbit/s)...
Hash of data verified.
Compressed 8192 bytes to 47...
Writing at 0x0000e000... (100 %)
Wrote 8192 bytes (47 compressed) at 0x0000e000 in 0.1 seconds
  (effective 618.3 kbit/s)...
Hash of data verified.
Compressed 1511328 bytes to 997894...
Writing at 0x00010000... (1 %)
Writing at 0x0001be62... (3 %)
Writing at 0x00028fdb... (4 %)
Writing at 0x0002e9d5... (6 %)
Writing at 0x00033dcd... (8 %)
Writing at 0x0003836c... (9 %)
Writing at 0x0003fde8... (11 %)
Writing at 0x000460ae... (13 %)
Writing at 0x0004a594... (14 %)
Writing at 0x0004e6fd... (16 %)
Writing at 0x00052ca4... (18 %)
Writing at 0x0005aac0... (19 %)
Writing at 0x0006c808... (21 %)
Writing at 0x0007a187... (22 %)
Writing at 0x0007fe8b... (24 %)
Writing at 0x00085d1b... (26 %)
Writing at 0x0008b113... (27 %)
Writing at 0x000905d9... (29 %)
Writing at 0x00096073... (31 %)
Writing at 0x0009b1bf... (32 %)
Writing at 0x000a0773... (34 %)
Writing at 0x000a5e7c... (36 %)
Writing at 0x000ab418... (37 %)
Writing at 0x000b0141... (39 %)
Writing at 0x000b5264... (40 %)
Writing at 0x000ba3a0... (42 %)
Writing at 0x000bfc91... (44 %)
Writing at 0x000c5fca... (45 %)
Writing at 0x000cb5e2... (47 %)
Writing at 0x000d0fab... (49 %)
Writing at 0x000d6ca6... (50 %)
Writing at 0x000dbe01... (52 %)
Writing at 0x000e10ff... (54 %)
Writing at 0x000e6570... (55 %)
Writing at 0x000eb9ac... (57 %)
Writing at 0x000f1171... (59 %)
Writing at 0x000f63fc... (60 %)
Writing at 0x000fb811... (62 %)
Writing at 0x00100ced... (63 %)
Writing at 0x00105dc3... (65 %)
Writing at 0x0010b3ff... (67 %)
Writing at 0x001103bc... (68 %)
Writing at 0x0011588d... (70 %)
Writing at 0x0011af8c... (72 %)
Writing at 0x00120776... (73 %)
Writing at 0x00125b1e... (75 %)
Writing at 0x0012a8ca... (77 %)
Writing at 0x0012f8c7... (78 %)
Writing at 0x00134c0d... (80 %)
Writing at 0x00139f74... (81 %)
Writing at 0x0013f053... (83 %)
Writing at 0x00144193... (85 %)
Writing at 0x001498c2... (86 %)
Writing at 0x0014f6f2... (88 %)
Writing at 0x00154e98... (90 %)
Writing at 0x0015a493... (91 %)
Writing at 0x00164b27... (93 %)
Writing at 0x0016b1b5... (95 %)
Writing at 0x0017059b... (96 %)
Writing at 0x00175b11... (98 %)
Writing at 0x0017b55c... (100 %)
Wrote 1511328 bytes (997894 compressed) at 0x00010000 in 14.2 seconds
  (effective 850.5 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting with RTC WDT...
*******************************************************************/
