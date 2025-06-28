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
 * This sketch will use the SPI SD library and Demo these functions:
 * https://docs.arduino.cc/libraries/sd/
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
    Serial.printf("%u bytes Read    in %u ms\n", flen, end);
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

  // Initialize SPI bus and deactivate SD_Card Chip Select
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
15:55:13.946 -> SD_Card Type: SDHC
15:55:13.946 -> SD_Card Size: 59645MB
15:55:13.946 -> Listing Directory: /
15:55:13.946 ->   FILE: foo.txt  SIZE: 14
15:55:13.946 ->   DIR : System Volume Information
15:55:13.946 ->   FILE: .dbxignore  SIZE: 545
15:55:13.946 ->   FILE: .dropbox.external.fileid  SIZE: 26
15:55:13.946 ->   FILE: .dropbox.device  SIZE: 56
15:55:13.946 -> Creating Dir: /mydir
15:55:14.390 -> Dir created.
15:55:14.390 -> Listing Directory: /
15:55:14.390 ->   DIR : mydir
15:55:14.390 ->   FILE: foo.txt  SIZE: 14
15:55:14.390 ->   DIR : System Volume Information
15:55:14.390 ->   FILE: .dbxignore  SIZE: 545
15:55:14.390 ->   FILE: .dropbox.external.fileid  SIZE: 26
15:55:14.390 ->   FILE: .dropbox.device  SIZE: 56
15:55:14.390 -> Removing Dir: /mydir
15:55:14.390 -> Dir removed.
15:55:14.390 -> Listing Directory: /
15:55:14.390 ->   FILE: foo.txt  SIZE: 14
15:55:14.390 ->   DIR : System Volume Information
15:55:14.390 -> Failed to open Directory!
15:55:14.390 ->   FILE: .dbxignore  SIZE: 545
15:55:14.390 ->   FILE: .dropbox.external.fileid  SIZE: 26
15:55:14.390 ->   FILE: .dropbox.device  SIZE: 56
15:55:14.390 -> Writing file: /hello.txt
15:55:14.390 -> File Written.
15:55:14.390 -> Appending to file: /hello.txt
15:55:14.390 -> Message Appended.
15:55:14.390 -> Reading file: /hello.txt
15:55:14.390 -> Read from file: Hello, World!
15:55:14.390 -> Deleting file: /foo.txt
15:55:14.390 -> File Deleted.
15:55:14.390 -> Renaming file /hello.txt to /foo.txt
15:55:14.390 -> File Renamed.
15:55:14.390 -> Reading file: /foo.txt
15:55:14.390 -> Read from file: Hello, World!
15:55:14.527 -> 1048576 bytes Read    in 2371 ms
15:55:16.697 -> 1048576 bytes Written in 2474 ms
15:55:16.697 -> Total space: 59629MB
15:55:16.697 ->  Used space: 1MB

--------------------------------------------------------------------
Output:
¯¯¯¯¯¯¯
Sketch uses 385878 bytes (12%) of program storage space. 
Maximum is 3145728 bytes.
Global variables use 21892 bytes (6%) of dynamic memory, 
            leaving 305788 bytes for local variables. 
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c

Leaving...
Hard resetting with RTC WDT...
*******************************************************************/
