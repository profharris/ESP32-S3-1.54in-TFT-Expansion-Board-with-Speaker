/* microSD_Card-Demo.ino
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 * pin 1 - not used          |  microSD_Card      |
 * pin 2 - SS  (CS)          |                   /
 * pin 3 - DI  (MOSI)        |                  |_
 * pin 4 - VDD (3V3)         |                    |
 * pin 5 - SCK (SCK)         | 8 7 6 5 4 3 2 1   /
 * pin 6 - VSS (GND)         | ▄ ▄ ▄ ▄ ▄ ▄ ▄ ▄  /
 * pin 7 - DO  (MISO)        | ▀ ▀ █ ▀ █ ▀ ▀ ▀ |
 * pin 8 - not used          |_________________|
 *                             ║ ║ ║ ║ ║ ║ ║ ║
 *                     ╔═══════╝ ║ ║ ║ ║ ║ ║ ╚═════════╗
 *                  |  ║         ║ ║ ║ ║ ║ ╚══════╗    ║  |
 * Connections for  |  ║   ╔═════╝ ║ ║ ║ ╚═════╗  ║    ║  |
 * full-sized       |  ║   ║   ╔═══╩═║═║═══╗   ║  ║    ║  |
 * SD_Card:         |  ║   ║   ║   ╔═╝ ║   ║   ║  ║    ║  |
 *                  |  ║   ║   ║   ║   ║   ║   ║  ║    ║  |
 *      Pin name:   |  -  DO  VSS SCK VDD VSS DI CS    -  |
 * SD pin number:   |  8   7   6   5   4   3   2   1   9 /
 *                  |                                  █/
 *                  |__▍___▊___█___█___█___█___█___█___/
 *
 * NOTE:  The SPI pins can be manually configured by using:
 * ¯¯¯¯¯    `SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS).`
 *        Alternatively, you can change the CS pin and use the other
 *        default settings by using:  `SD.begin(SD_CS)`.
 *
 * .------------.---------.--------.----------.----------.----------.----------.----------.
 * | SPI Pin    | ESP8266 | ESP32  | ESP32-S2 | ESP32-S3 | ESP32-C3 | ESP32-C6 | ESP32-H2 |
 * +============+=========+========+==========+==========+==========+==========+==========+
 * | CS  (SS)   | GPIO15  | GPIO5  | GPIO34   | GPIO10   | GPIO7    | GPIO18   | GPIO0    |
 * +------------+---------+--------+----------+----------+----------+----------+----------+
 * | DI  (MOSI) | GPIO13  | GPIO23 | GPIO35   | GPIO11   | GPIO6    | GPIO19   | GPIO25   |
 * +------------+---------+--------+----------+----------+----------+----------+----------+
 * | SCL (SCK)  | GPIO14  | GPIO18 | GPIO36   | GPIO12   | GPIO4    | GPIO21   | GPIO10   |
 * +------------+---------+--------+----------+----------+----------+----------+----------+
 * | DO  (MISO) | GPIO12  | GPIO19 | GPIO37   | GPIO13   | GPIO5    | GPIO20   | GPIO11   |
 * '------------'---------'--------'----------'----------'----------'----------'----------'
 *
 * For more info see file README.md in this library or on URL:
 * https://github.com/espressif/arduino-esp32/tree/master/libraries/SD
 */

#include <FS.h>                         // File System library
#include <SPI.h>                        // SPI library
#include <SD.h>                         // SD_Card library

// Uncomment to use custom pins for SPI communication
#define REASSIGN_PINS

int SD_CS   =  10;                      // ESP32-S3 Default Pins
int SD_MOSI =  11;
int SD_SCK  =  12;
int SD_MISO =  13;

void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  Serial.printf("Listing Directory: %s\n", dirname);
  File root = fs.open(dirname);
  if(!root) {
    Serial.println("Failed to Open Directory!");
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
        listDir(fs, file.path(), levels - 1);
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
    Serial.println("Failed to Open file for Append!");
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
  if(fs.rename(path1, path2)) {
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
  static uint8_t buf[512];
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
    Serial.printf("%u bytes Read for %lu ms\n", flen, end);
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
  for(i=0; i < 2048; i++) {
    file.write(buf, 512);
  }
  end = millis() - start;
  Serial.printf("%u bytes Written for %lu ms\n", 2048 * 512, end);
  file.close();
}


void setup() {
  Serial.begin(15200);              // Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

#ifdef REASSIGN_PINS
  SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  if(!SD.begin(SD_CS)) {
#else
  if(!SD.begin()) {
#endif
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
  deleteFile(SD, "/foo.txt");
  renameFile(SD, "/hello.txt", "/foo.txt");
  readFile(SD, "/foo.txt");
  testFileIO(SD, "/test.txt");
  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf(" Used space: %lluMB\n", SD.usedBytes()  / (1024 * 1024));
}

void loop() {}

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
00:00:14.452 -> SD_Card Type: SDHC
00:00:14.452 -> SD_Card Size: 59645MB
00:00:14.452 -> Listing Directory: /
00:00:14.452 ->   DIR : System Volume Information
00:00:14.452 ->   FILE: .dbxignore  SIZE: 545
00:00:14.452 ->   FILE: .dropbox.external.fileid  SIZE: 26
00:00:14.452 -> Creating Dir: /mydir
00:00:14.643 -> Dir created.
00:00:14.643 -> Listing Directory: /
00:00:14.643 ->   DIR : mydir
00:00:14.643 ->   DIR : System Volume Information
00:00:14.643 ->   FILE: .dbxignore  SIZE: 545
00:00:14.643 ->   FILE: .dropbox.external.fileid  SIZE: 26
00:00:14.643 -> Removing Dir: /mydir
00:00:14.643 -> Dir removed.
00:00:14.643 -> Listing Directory: /
00:00:14.643 ->   DIR : System Volume Information
00:00:14.643 -> Listing Directory: /System Volume Information
00:00:14.807 ->   FILE: WPSettings.dat  SIZE: 12
00:00:14.807 ->   FILE: IndexerVolumeGuid  SIZE: 76
00:00:14.807 ->   FILE: .dbxignore  SIZE: 545
00:00:14.807 ->   FILE: .dropbox.external.fileid  SIZE: 26
00:00:14.807 -> Writing file: /hello.txt
00:00:14.807 -> File Written.
00:00:14.807 -> Appending to file: /hello.txt
00:00:14.807 -> Message Appended.
00:00:14.807 -> Reading file: /hello.txt
00:00:14.807 -> Read from file: Hello, World!
00:00:14.807 -> Deleting file: /foo.txt
00:00:14.807 -> Delete failed!
00:00:14.807 -> Renaming file /hello.txt to /foo.txt
00:00:14.807 -> File Renamed.
00:00:14.807 -> Reading file: /foo.txt
00:00:14.807 -> Read from file: Hello, World!
00:00:14.807 -> Failed to Open file for Reading!
00:00:17.236 -> 1048576 bytes Written for 2565 ms
00:00:17.274 -> Total space: 59629MB
00:00:17.274 ->  Used space: 1MB

--------------------------------------------------------------------
Output:
¯¯¯¯¯¯¯
Sketch uses 385950 bytes (12%) of program storage space.
Maximum is 3145728 bytes.
Global variables use 21908 bytes (6%) of dynamic memory,
            leaving 305772 bytes for local variables.
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c
...
Leaving...
Hard resetting with RTC WDT...
*******************************************************************/
