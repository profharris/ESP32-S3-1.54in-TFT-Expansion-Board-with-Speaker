/* MAX98357_Synchronised-Lyrics.ino
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 * 1. Requires a MAX98357 I²S Amplifier/Speaker.
 * 2. Requires a SPI microSD_Card Reader using the SD library.
 *
 * NOTE: The commented out code for using the SD_MMC library insted.
 * ¯¯¯¯¯
 *
 * TODO: Redirect the text Lyrics output from the Serial Monitor, to
 * ¯¯¯¯¯ the onboard 1.54in TFT Display.
 *
 * ESP32-audioI2S Library   https://docs.arduino.cc/libraries/audio/
 *                          https://github.com/schreibfaul1/ESP32-audioI2S
 *
 * Ticker library           https://docs.arduino.cc/libraries/ticker/
 *                          https://github.com/sstaub/Ticker
 *
 * 📌 Synchronized Lyrics or also called “Lyrics3” is a format for storing
 * Lyrics in the ‘ID3 metadata’ of audio files such as MP3s. The synched
 * texts are saved in a special ID3 tag called “SYLT” (Sychronized
 * Lyric/text Transcription).
 *
 * Unlike plain Lyrics, ‘synced Lyrics’ can contain not only the Lyrics
 * of the song, but also information about when each section of Lyrics
 * should be displayed. This information is stored in the form of time
 * stamps that indicate when each piece of text should begin and end.
 *
 * Once the synced, Lyrics are stored in the ‘ID3 metadata’, they can
 * be viewed by a compatible audio player. The audio player reads the
 * “SYLT” tags and display the Lyrics of the song in real time while
 * the song is playing. This allows the listener to follow the Lyrics
 * of the song in real time and sing along.
 *
 * @moononournation had the idea of reading the “SYLT” tag with the
 * ESP32-audioI2S library, and he also wrote the necessary source code.
 * https://github.com/schreibfaul1/ESP32-audioI2S/tree/master/examples/Synchronised%20lyrics
 *
 * The example shown here reads an mp3 file containing the “SYLT” tag,
 * plays the mp3 file AND displays the Lyrics according to the timestamps
 * on the Serial Monitor.
 *
 * // SD_Card Filename, MP3 Music File with the “SYLT” tag for Synchronised-Lyrics
 * const char* filename = "/Little London Girl(lyrics).mp3";
 * // https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/code/MAX98357-I2S-Amp_Synchronised-Lyrics/Little%20London%20Girl(lyrics).mp3
 *
 *
 * NOTE¹:  You may NOT hear the MP3 file playing
 * ¯¯¯¯¯¯  until you open the Serial Monitor!!!
 *
 * NOTE²:  Be sure to follow the [CONFIGURATION] instructions below.
 * ¯¯¯¯¯¯  In particular, make sure to enable "OPI PSRAM" as the
 *         ESP32-audioI2S Library will use PSRAM stream buffering.
 *
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
 *  OPTIONAL: (SDIO SD_MMC microSD_Card 3-wire interface)
 *  | ESP32-S3 Dev Board | SDIO SD_MMC microSD_Card Pins |
 *  |-------------------:|-------------------------------|
 *  |     GPIO38         | 1. SD_CMD      (SDIO Command) |
 *  |     GPIO39         | 2. SD_MMC_CLK  (SDIO Clock)   |
 *  |     GPIO40         | 3. SD_MMC_D0   (SDIO Data0)   |
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
//#include "SD_MMC.h"               // OPTIONAL: SD_MMC Card library
#include "Audio.h"                  // ESP32-audioI2S Library
#include "Ticker.h"                 // Ticker/Lyrics Sync library

#define I2S_DOUT       7            // MAX98357 Data_Out
#define I2S_BCLK      15            // MAX98357 Bit_Clock
#define I2S_LRC       16            // MAX98357 WS/Left_Right_Clock
#define I2S_MCLK       0            // not used

#define SD_CS         10            // SPI microSD_Card Pins
#define SD_MOSI       11            // ESP32-S3 Default SPI Pins
#define SD_SCK        12            //              "
#define SD_MISO       13            //              "

//#define SD_MMC_CMD  38            // OPTIONAL: SDIO 3-wire interface
//#define SD_MMC_CLK  39            //              "
//#define SD_MMC_D0   40            //              "

Audio    audio;                     // Create ESP32-audioI2S Audio object
Ticker   ticker;                    // Create Synchronised-Lyrics object

char    *lyricsText;                // audio_id3lyrics() Global ariables
size_t   lyricsTextSize = 0;        //              "
uint16_t lyricsPtr      = 0;        //              "
uint32_t timeStamp      = 0;        //              "
uint32_t ms             = 0;        //              "
char     chbuf[512];                //              "

// SD_Card Filename, MP3 Music File with the “SYLT” tag for Synchronised-Lyrics
const char* filename = "/Little London Girl(lyrics).mp3";
// https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/code/MAX98357-I2S-Amp_Synchronised-Lyrics/Little%20London%20Girl(lyrics).mp3

size_t bigEndian(char* base, uint8_t numBytes, uint8_t shiftLeft = 8) {
  uint64_t result = 0;
  if(numBytes < 1 || numBytes > 8) return 0;
  for(int i=0; i < numBytes; i++) {
    result += *(base + i) << (numBytes -i - 1) * shiftLeft;
  }
  if(result > SIZE_MAX) { // ❓
    log_e("bigEndian range Overflow");
    result = 0;
  } // Overflow
  return (size_t)result;
}

void tckr() {                     // Synchronize Lyrics every 100ms
  if(audio.isRunning()) {
    ms += 100;
    if(ms >= timeStamp) {
      Serial.print(chbuf);
      strcpy(chbuf, lyricsText + lyricsPtr);
      lyricsPtr += strlen(chbuf) + 1; // strlen + '\0'
      timeStamp  = bigEndian(lyricsText + lyricsPtr, 4);
      lyricsPtr += 4;
    }
  } else {
    if(lyricsText) {
      free(lyricsText);
      lyricsText = NULL;
      lyricsTextSize = 0;
    }
    ticker.detach();
  }
}

void setup() {
  Serial.begin(15200);              // Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open
  /*
   * NOTE¹:  You may NOT hear the MP3 file playing
   * ¯¯¯¯¯¯  until you open the Serial Monitor!!!
   *
   * NOTE²:  Be sure to follow the [CONFIGURATION] instructions,
   * ¯¯¯¯¯¯  In particular, make sure to enable the "OPI PSRAM".
   */

  // Initialize SPI bus and deactivate SD_Card Chip Select
  pinMode(SD_CS,      OUTPUT);      // SPI SD_Card Chip Select
  digitalWrite(SD_CS, HIGH);        // Active LOW!
  SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  SPI.setFrequency(1000000);

  //pinMode(SD_MMC_D0, INPUT_PULLUP);
  //SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0, -1, -1, -1);

  if(!SD.begin(SD_CS)) {            // SPI SD_Card Chip Select
    Serial.println("Error accessing microSD_Card!"); // ❓
    while(true); // Don't do anything more:
  }

  //if(!SD_MMC.begin( "/sdcard", true, false, 20000)) {
  //  Serial.println("SD_Card Mount Failed!"); // ❓
  //  return;
  //}

  // Setup MAX98357A I²S Audio Amp
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(12);              // Range: 0..21
  audio.connecttoFS(SD, filename);  // Open SD_Card MP3 music file

  //audio.connecttoFS(SD_MMC, "/Little London Girl(lyrics).mp3");
}

void loop() {
  vTaskDelay(1);
  // https://www.freertos.org/Documentation/02-Kernel/04-API-references/02-Task-control/01-vTaskDelay
  audio.loop();                     // Play MP3 music file
}

// Referenced from within ESP32-audioI2S “Audio.h”
void audio_id3lyrics(File &file, const size_t pos, const size_t size) {
  Serial.printf("\n   audio_ID3Lyrics, pos: %d, size: %d\n", pos, size);
  lyricsText = (char *)malloc(size);
  lyricsTextSize = size;
  file.seek(pos);
  file.read((uint8_t *)lyricsText, size);
  Serial.printf("     Text Encoding: %i\n",   lyricsText[0]); // 0: ASCII, 3: UTF-8
  char lang[14]; memcpy(lang, (const char*)lyricsText + 1, 3); lang[3] = '\0';
  Serial.printf("          Language: %s\n",   lang);
  Serial.printf(" Time Stamp format: %i\n",   lyricsText[4]);
  Serial.printf("      Content type: %i\n",   lyricsText[5]);
  Serial.printf("Content Descriptor: %i\n\n", lyricsText[6]);
  lyricsPtr = 7;
  strcpy(chbuf, lyricsText + lyricsPtr); lyricsPtr += strlen(chbuf) + 1; // strlen + '\0'
  timeStamp = bigEndian(lyricsText + lyricsPtr, 4);
  ticker.attach(0.1, tckr);
  lyricsPtr += 4;
}

// Functions Referenced from within ESP32-audioI2S “Audio.h”
void audio_info(const char *info) {
  Serial.print("Audio Info "); Serial.println(info);
}
void audio_id3data(const char *info) {  // ID3 metadata
//  if(strncmp(info, "Year: ", 6) == 0) Serial.println(info + 6);
  Serial.print("   ID3data "); Serial.println(info);
}
void audio_eof_mp3(const char *info) {   // MP3 End-Of-File
  Serial.print("   EOF_MP3 "); Serial.println(info);
}

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
00:13:30.533 -> ESP-ROM:esp32s3-20210327
00:13:30.533 -> Build:Mar 27 2021

00:21:26.256 -> Audio Info audioI2S Version 3.3.0
00:21:26.257 -> Audio Info PSRAM found, inputBufferSize: 630773 bytes
00:21:26.257 -> Audio Info buffers freed, free Heap: 258824 bytes
00:21:26.257 -> Audio Info Reading file: "/Little London Girl(lyrics).mp3"
00:21:26.257 -> Audio Info MP3Decoder has been initialized, free Heap:
00:21:26.257 -> Audio Info Content-Length: 2879496
00:21:26.257 -> Audio Info ID3 framesSize: 2893
00:21:26.257 -> Audio Info ID3 version: 2.4
00:21:26.257 -> Audio Info ID3 normal frames
00:21:26.257 ->    ID3data SettingsForEncoding: Lavf57.19.100
00:21:26.257 -> Audio Info Audio-Length: 2876603
00:21:26.257 ->
00:21:26.257 ->    audio_ID3Lyrics, pos: 134, size: 1783
00:21:26.263 ->      Text Encoding: 0
00:21:26.263 ->           Language: eng
00:21:26.263 ->  Time Stamp format: 2
00:21:26.263 ->       Content type: 1
00:21:26.263 -> Content Descriptor: 0
00:21:26.263 ->
00:21:26.263 -> Audio Info stream ready
00:21:26.263 -> Audio Info syncword found
00:21:26.263 -> Audio Info M
00:21:26.263 ->  Channels: 2
00:21:26.263 -> Audio Info SampleRate: 44100
00:21:26.263 -> Audio Info BitsPerSample: 16
00:21:26.263 -> Audio Info BitRate: 64000
00:21:26.464 ->
00:21:26.464 ->
00:21:26.464 -> Little London Girl
00:21:30.345 ->
00:21:30.345 -> I shut the door
00:21:33.348 -> And I step outside
00:21:36.626 -> It's close to midnight
00:21:37.858 -> And the fog is dimming
00:21:39.367 -> The street light.
00:21:41.366 -> With the sound of Big Ben
00:21:44.336 -> It reminded me
00:21:47.161 -> It was only yesterday
00:21:48.825 -> When we first met in that cafe
00:21:52.946 -> And our worlds entwined.
00:21:56.841 -> Oh don't you know?
00:22:01.046 -> I'm gonna shout it from the rooftops now, baby
00:22:05.024 -> I'm ready to go.
00:22:07.538 -> Oh don't you know?
00:22:11.748 -> It doesn't matter if the sun is going down on me
00:22:15.926 -> You light my world
00:22:17.142 -> My little London girl.
00:22:22.755 -> Sunglasses on
00:22:28.526 -> You take me to Camden Town
00:22:28.526 -> As you share your headphones
00:22:30.049 -> It's the Kinks and the Rolling Stones.
00:22:33.123 -> As you walk around
00:22:36.034 -> In your leather boots
00:22:39.053 -> All the boys are staring
00:22:40.524 -> But you're not caring
00:22:47.347 -> 'Cause you're so Rock and Roll (so Rock and Roll).
00:22:47.347 -> Woahhh...
00:22:48.859 -> Oh don't you know?
00:22:53.044 -> I'm gonna shout it from the rooftops now, baby
00:22:57.024 -> I'm ready to go.
00:22:59.565 -> Oh don't you know?
00:23:03.569 -> It doesn't matter if the sun is going down on me
00:23:08.922 -> You light my world
00:23:08.922 -> My little London girl.
00:23:14.466 -> (She lights my world)
00:23:15.744 -> You light my world.
00:23:34.151 -> Oh don't you know?
00:23:38.451 -> We're gonna shout it from the rooftops now, baby
00:23:42.463 -> Are you ready to go?
00:23:44.745 -> Oh don't you know?
00:23:48.933 -> It doesn't matter if the sun is going down on me
00:23:53.155 -> You light my world
00:23:54.419 -> My little London...
00:23:55.427 -> Girl don't you know?
00:23:59.723 -> I'm gonna shout it from the rooftops now, baby
00:24:03.621 -> I'm ready to go.
00:24:06.160 -> Oh don't you know?
00:24:14.338 -> It doesn't matter if the sun is going down on me
00:24:14.338 -> You light my world
00:24:15.618 -> My little London girl.
00:24:16.319 ->
00:24:16.428 -> Audio Info Closing audio file "Little London Girl(lyrics).mp3"
00:24:25.873 ->    EOF_MP3 Little London Girl(lyrics).mp3
00:24:25.873 -> Audio Info End of file "Little London Girl(lyrics).mp3"
00:24:25.873 ->

--------------------------------------------------------------------
Output:
¯¯¯¯¯¯¯
Sketch uses 1512486 bytes (48%) of program storage space.
 Maximum is 3145728 bytes.
Global variables use 64436 bytes (19%) of dynamic memory,
            leaving 263244 bytes for local variables.
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c
...
Leaving...
Hard resetting with RTC WDT...
*******************************************************************/
