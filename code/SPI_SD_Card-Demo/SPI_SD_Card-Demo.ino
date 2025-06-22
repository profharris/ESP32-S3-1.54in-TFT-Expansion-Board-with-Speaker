/* SPI_SD_Card-Demo.ino
 * Requires an SPI microSD_Card reader/writer
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 * ESP32-S3 Handling Files with a microSD_Card Module
 *
 * There are two different libraries for the ESP32 (included in the
 * Arduino core for the ESP32):
 *  1. the SD library
 *  2. the SDD_MMC.h library.
 *
 * If you use the SD library, you’re using the “SPI” controller.
 * If you use the SDD_MMC library you’re using the ESP32 SD/SDIO/MMC
 * controller. Learn more about the ESP32 SD/SDIO/MMC driver here:
 * https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/sdmmc.html
 *
 * This sketch will use the SPI SD library and demo these functions:
 * 1. listDir   (dir)
 * 2. createDir (mkdir)
 * 3. removeDir (rmdir)
 * 4. readFile
 * 5. writeFile
 * 6. appendFile
 * 7. renameFile
 * 8. deleteFile
 *
 * Complete project details at:
 * https://RandomNerdTutorials.com/esp32-microsd-card-arduino/
 * This sketch can be found at: Examples > SD(esp32) > SD_Test
 *
 * Wiring:
 *
 *  | ESP32-S3 Dev Board | SPI microSD_Card pins  |
 *  |-------------------:|------------------------|
 *  |     3V3            | 1. 3V3  (Power)        |
 *  |     GPIO10         | 2. CS   (Chip Select)  |
 *  |     GPIO11         | 4. MOSI (SPI SDI)      |
 *  |     GPIO12         | 5. SCK  (SPI Clock)    |
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

void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  Serial.printf("Listing Directory: %s\n", dirname);
  File root = fs.open(dirname);
  if(!root) {
    Serial.println("Failed to open Directory!");
    return;
  }
  if(!root.isDirectory()) {
    Serial.println("Not a Directory!");
    return;
  }
  File file = root.openNextFile();
  while(file) {
    if(file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if(levels) {
        listDir(fs, file.name(), levels -1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void createDir(fs::FS &fs, const char *path) {
  Serial.printf("Creating Dir: %s\n", path);
  if(fs.mkdir(path)) {
    Serial.println("Dir created.");
  } else {
    Serial.println("mkdir failed!");
  }
}

void removeDir(fs::FS &fs, const char *path) {
  Serial.printf("Removing Dir: %s\n", path);
  if(fs.rmdir(path)) {
    Serial.println("Dir removed.");
  } else {
    Serial.println("rmdir failed!");
  }
}

void readFile(fs::FS &fs, const char *path) {
  Serial.printf("Reading file: %s\n", path);
  File file = fs.open(path);
  if(!file) {
    Serial.println("Failed to Open file for Reading!");
    return;
  }
  Serial.print("Read from file: ");
  while(file.available()) {
    Serial.write(file.read());
  }
  file.close();
}

void writeFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Writing file: %s\n", path);
  File file = fs.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to Open file for Writing!");
    return;
  }
  if(file.print(message)) {
    Serial.println("File Written.");
  } else {
    Serial.println("Write failed!");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Appending to file: %s\n", path);
  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to Open file for Appending!");
    return;
  }
  if(file.print(message)) {
      Serial.println("Message Appended.");
  } else {
    Serial.println("Append failed!");
  }
  file.close();
}

void renameFile(fs::FS &fs, const char *path1, const char *path2) {
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println("File Renamed.");
  } else {
    Serial.println("Rename failed!");
  }
}

void deleteFile(fs::FS &fs, const char *path) {
  Serial.printf("Deleting file: %s\n", path);
  if(fs.remove(path)) {
    Serial.println("File Deleted.");
  } else {
    Serial.println("Delete failed!");
  }
}

void testFileIO(fs::FS &fs, const char *path) {
  File file = fs.open(path);
  static uint8_t buf[512];      // 512 bytes = 1 sector
  size_t len = 0;
  uint32_t start = millis();
  uint32_t end = start;
  if(file) {
    len = file.size();
    size_t flen = len;
    start = millis();
    while(len) {
      size_t toRead = len;
      if(toRead > 512) {
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    end = millis() - start;
    Serial.printf("%u bytes Read in %u ms\n", flen, end);
    file.close();
  } else {
    Serial.println("Failed to Open file for Reading!");
  }
  file = fs.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to Open file for Writing!");
    return;
  }
  size_t i;
  start = millis();
  for(i=0; i < 2048; i++) {     // 2048 bytes = 1 cluster
    file.write(buf, 512);
  }
  end = millis() - start;
  Serial.printf("%u bytes Written in %u ms\n", 2048 * 512, end);
  file.close();
}


void setup() {
  Serial.begin(15200);              // Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  // Initialize SPI bus SD_Card
  SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  pinMode(SD_CS,      OUTPUT);      // SPI SD_Card Chip Select
  digitalWrite(SD_CS, HIGH);        // Active LOW!

  if(!SD.begin(SD_CS)) {            // SPI SD_Card Chip Select
    Serial.println("SD_Card Mount Failed!");
    return;
  }
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE) {
    Serial.println("No SD_Card attached!");
    return;
  }

  Serial.print("SD_Card Type: ");
  if(cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if(cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if(cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN!");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD_Card Size: %lluMB\n", cardSize);

  listDir(SD, "/", 0);
  createDir(SD, "/mydir");
  listDir(SD, "/", 0);
  removeDir(SD, "/mydir");
  listDir(SD, "/", 2);
  writeFile(SD, "/hello.txt",  "Hello, ");
  appendFile(SD, "/hello.txt", "World!\n");
  readFile(SD, "/hello.txt");
  deleteFile(SD, "/foo.txt");  // This should fail! foo.txt doesn’t exist yet!
  renameFile(SD, "/hello.txt", "/foo.txt");
  readFile(SD, "/foo.txt");
  testFileIO(SD, "/test.txt");
  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf(" Used space: %lluMB\n", SD.usedBytes()  / (1024 * 1024));
}

void loop() {
  // Nothing happens after setup() finishes.
}

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
00:51:06.063 -> SD_Card Type: SDHC
00:51:06.063 -> SD_Card Size: 59645MB
00:51:06.063 -> Listing Directory: /
00:51:06.063 ->   FILE: test.txt  SIZE: 1048576
00:51:06.063 ->   FILE: foo.txt  SIZE: 14
00:51:06.183 ->   DIR : System Volume Information
00:51:06.183 ->   FILE: .dbxignore  SIZE: 545
00:51:06.183 ->   FILE: .dropbox.external.fileid  SIZE: 26
00:51:06.063 -> Creating Dir: /mydir
00:51:06.183 -> Dir created.
00:51:06.183 -> Removing Dir: /mydir
00:51:06.183 -> Dir removed.
00:51:06.183 -> Listing Directory: /
00:51:06.183 ->   FILE: test.txt  SIZE: 1048576
00:51:06.183 ->   FILE: foo.txt  SIZE: 14
00:51:06.183 ->   DIR : System Volume Information
00:51:06.183 -> Listing Directory: System Volume Information
00:51:06.183 -> Failed to open Directory!
00:51:06.183 ->   FILE: .dbxignore  SIZE: 545
00:51:06.183 ->   FILE: .dropbox.external.fileid  SIZE: 26
00:51:06.183 -> Writing file: /hello.txt
00:51:06.183 -> File Written.
00:51:06.183 -> Appending to file: /hello.txt
00:51:06.183 -> Message Appended.
00:51:06.183 -> Reading file: /hello.txt
00:51:06.183 -> Read from file: Hello, World!
00:51:06.183 -> Deleting file: /foo.txt
00:51:06.183 -> File Deleted.
00:51:06.183 -> Renaming file /hello.txt to /foo.txt
00:51:06.183 -> File Renamed.
00:51:06.183 -> Reading file: /foo.txt
00:51:06.183 -> Read from file: Hello, World!
00:51:08.527 -> 1048576 bytes Read in 2371 ms
00:51:11.102 -> 1048576 bytes Written in 2473 ms
00:51:11.102 -> Total space: 59629MB
00:51:11.102 ->  Used space: 1MB

--------------------------------------------------------------------
Output:
¯¯¯¯¯¯¯
Sketch uses 385878 bytes (12%) of program storage space. 
Maximum is 3145728 bytes.
Global variables use 21892 bytes (6%) of dynamic memory, 
            leaving 305788 bytes for local variables. 
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
Flash will be erased from 0x00010000 to 0x0006efff...
Compressed 20208 bytes to 13058...
Writing at 0x00000000... (100 %)
Wrote 20208 bytes (13058 compressed) at 0x00000000 in 0.4 seconds 
 (effective 437.8 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 144...
Writing at 0x00008000... (100 %)
Wrote 3072 bytes (144 compressed) at 0x00008000 in 0.1 seconds 
 (effective 445.2 kbit/s)...
Hash of data verified.
Compressed 8192 bytes to 47...
Writing at 0x0000e000... (100 %)
Wrote 8192 bytes (47 compressed) at 0x0000e000 in 0.1 seconds 
 (effective 619.6 kbit/s)...
Hash of data verified.
Compressed 386016 bytes to 216048...
Writing at 0x00010000... (7 %)
Writing at 0x0001b459... (14 %)
Writing at 0x000297e1... (21 %)
Writing at 0x0002ef23... (28 %)
Writing at 0x00034d7b... (35 %)
Writing at 0x0003ac3c... (42 %)
Writing at 0x0004041b... (50 %)
Writing at 0x00045ee1... (57 %)
Writing at 0x0004ae5e... (64 %)
Writing at 0x000508e8... (71 %)
Writing at 0x00056f4d... (78 %)
Writing at 0x00061376... (85 %)
Writing at 0x00066df2... (92 %)
Writing at 0x0006cee5... (100 %)
Wrote 386016 bytes (216048 compressed) at 0x00010000 in 3.8 seconds 
 (effective 817.8 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting with RTC WDT...
*******************************************************************/
