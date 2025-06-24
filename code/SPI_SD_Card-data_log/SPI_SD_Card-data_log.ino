/* SPI_SD_Card-data_log.ino
 * Requires an SPI microSD Card reader/writer
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 * ESP32-S3 Handling “data_log” Files with a microSD_Card Module
 * 1. Check_and_Create_data_log()
 * 2. Write_data_log()
 * 3. Read_data_log()
 *
 * Wiring:
 *
 *  | ESP32-S3 Dev Board | SPI microSD_Card pins  |
 *  |-------------------:|------------------------|
 *  |     3V3            | 1. 3V3  (Power)        |
 *  |     GPIO10         | 2. CS   (Chip Select)  |
 *  |     GPIO11         | 4. MOSI (SPI SDI)      |
 *  |     GPIO12         | 5. CLK  (SPI Clock)    |
 *  |     GPIO13         | 3. MISO (SPI SDO)      |
 *  |     GND            | 6. GND                 |
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

#include <FS.h>                         // File System library
#include <SPI.h>                        // SPI library
#include <SD.h>                         // SD Card library

#define SD_CS   10                      // SPI microSD_Card Pins
#define SD_MOSI 11                      // ESP32-S3 Default Pins
#define SD_SCK  12
#define SD_MISO 13

// SD_Card Filename to use for data_log (8.3 short names required)
const String filename = "/data_log.txt";
// File object to represent the SD_Card file
File myFile;

void setup() {
  Serial.begin(15200);              // Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  // Initialize SPI bus and deactivate SD_Card Chip Select
  SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  pinMode(SD_CS,      OUTPUT);      // SPI SD_Card Chip Select
  digitalWrite(SD_CS, HIGH);        // Active LOW!

  Check_and_Create_data_log();
  Write_data_log();
  Read_data_log();
}

void loop() {
  // nothing happens after setup() finishes.
}

void Check_and_Create_data_log() {
  Serial.print("SD_Card: Initializing... ");
  /* Check if the SD_Card exist or not */
  if(!SD.begin(SD_CS)) {            // SPI SD_Card Chip Select
    Serial.println("Initialization Failed!");
    while(1); // Don't do anything more:
  } else {
    Serial.println("Initialization done.");
  }
  
  Serial.print("SD_CARD: ");
  Serial.print(filename);
  if(SD.exists(filename))
    Serial.println(" exists.");
  else
    Serial.println(" doesn't exist!");

  /* Open a new file and immediately Close it, this
     will Create a new data_log file on the SD_Card */
  Serial.print("SD_CARD: Creating ");
  Serial.println(filename);
  myFile = SD.open(filename);
  myFile.close();

  /* Now Check again if the data_log exists on the SD_Card */
  Serial.print("SD_CARD: ");
  Serial.print(filename);
  if(SD.exists(filename))
    Serial.println(" exists.");
  else
    Serial.println(" doesn't exist!");
}

void Write_data_log() {
  myFile = SD.open(filename, FILE_WRITE);
  // If the data_log Opened Ok, Write to it...
  if(myFile) {
    Serial.print("SD_CARD: Writing to ");
    Serial.println(filename);
    myFile.println("Testing 1, 2, 3...");
    // Close the data_log...
    myFile.close();
    Serial.println("Done.");
  } else {
    // If the data_log didn’t Open, print an Error...
    Serial.print("SD_CARD: Error Opening ");
    Serial.print(filename);
    Serial.println(" to Write!");
  }
}

void Read_data_log() {
  // Re-Open the data_log for Reading...
  myFile = SD.open(filename, FILE_READ);
  if(myFile) {
    Serial.print("SD_CARD: Reading from ");
    Serial.println(filename);
    // Read from the data_log until there’s nothing else in it...
    while(myFile.available()) {
      Serial.write(myFile.read());
    }
    // Close the data_log...
    Serial.println("");
    myFile.close();
    Serial.println("Done.");
  } else {
    // If the data_log didn’t Open, print an Error...
    Serial.print("SD_CARD: Error Opening ");
    Serial.print(filename);
    Serial.println(" to Read!");
  }
}

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
17:40:34.172 -> SD_Card: Initializing... Initialization done.
17:40:34.172 -> SD_CARD: /data_log.txt doesn't exists.
17:40:34.172 -> SD_CARD: Creating /data_log.txt
17:40:34.172 -> SD_CARD: /data_log.txt exists.
17:40:34.192 -> SD_CARD: Writing to /data_log.txt
17:40:34.192 -> Done.
17:40:34.192 -> SD_CARD: Reading from /data_log.txt
17:40:34.192 -> Testing 1, 2, 3...
17:40:34.192 -> 
17:40:34.192 -> Done.

--------------------------------------------------------------------
Output:
¯¯¯¯¯¯¯
Sketch uses 382702 bytes (12%) of program storage space.
Maximum is 3145728 bytes.
Global variables use 21404 bytes (6%) of dynamic memory,
            leaving 306276 bytes for local variables.
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
Flash will be erased from 0x00010000 to 0x0006dfff...
Compressed 20208 bytes to 13058...
Writing at 0x00000000... (100 %)
Wrote 20208 bytes (13058 compressed) at 0x00000000 in 0.4 seconds
  (effective 440.6 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 144...
Writing at 0x00008000... (100 %)
Wrote 3072 bytes (144 compressed) at 0x00008000 in 0.1 seconds
  (effective 467.2 kbit/s)...
Hash of data verified.
Compressed 8192 bytes to 47...
Writing at 0x0000e000... (100 %)
Wrote 8192 bytes (47 compressed) at 0x0000e000 in 0.1 seconds
  (effective 621.3 kbit/s)...
Hash of data verified.
Compressed 382848 bytes to 214163...
Writing at 0x00010000... (7 %)
Writing at 0x0001b4c9... (14 %)
Writing at 0x000296e5... (21 %)
Writing at 0x0002ee8b... (28 %)
Writing at 0x00034b45... (35 %)
Writing at 0x0003a9c9... (42 %)
Writing at 0x0004017c... (50 %)
Writing at 0x00045c55... (57 %)
Writing at 0x0004abf9... (64 %)
Writing at 0x00050696... (71 %)
Writing at 0x000572e3... (78 %)
Writing at 0x0006124c... (85 %)
Writing at 0x00066bcf... (92 %)
Writing at 0x0006d14d... (100 %)
Wrote 382848 bytes (214163 compressed) at 0x00010000 in 3.7 seconds
  (effective 827.2 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting with RTC WDT...
*******************************************************************/
