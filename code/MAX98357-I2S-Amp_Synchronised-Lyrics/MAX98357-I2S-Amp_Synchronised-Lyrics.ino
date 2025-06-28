/* MAX98357_Synchronised-Lyrics.ino
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 * 1. Requires a MAX98357 I²S Amplifier/Speaker.
 * 2. Requires a SPI microSD_Card Reader using the SD library.
 * NOTE: The commented out code for using the SD_MMC library insted.
 * ¯¯¯¯¯
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
 * “SYLT” tags and display the lyrics of the song in real time while
 * the song is playing. This allows the listener to follow the lyrics
 * of the song in real time and sing along.
 *
 * @moononournation had the idea of reading the “SYLT” tag with the
 * ESP32-audioI2S library, and he also wrote the necessary source code.
 * https://github.com/schreibfaul1/ESP32-audioI2S/tree/master/examples/Synchronised%20lyrics
 *
 * The example shown here reads an mp3 file containing the “SYLT” tag,
 * plays the mp3 file and displays the Lyrics according to the timestamps
 * on the Serial Monitor.
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
#define SD_MOSI       11            // ESP32-S3 Default Pins
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
   * NOTE:  You will NOT hear the MP3 file playing
   * ¯¯¯¯¯  until you open the Serial Monitor!!!
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
  Serial.printf("\n audio_ID3Lyrics, pos: %d, size: %d\n", pos, size);
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

// Optional bits: Referenced from within ESP32-audioI2S “Audio.h”
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
