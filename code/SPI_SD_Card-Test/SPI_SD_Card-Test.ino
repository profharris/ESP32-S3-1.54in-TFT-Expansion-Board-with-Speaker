/* SPI_SD_Card-Test.ino
 * Requires an SPI microSD_Card reader/writer
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 * Test Reads and Writes to a SD_Card using the “SD” library.
 * https://github.com/arduino-libraries/SD/blob/a3866205cf9af4eea3e10dcdc5ac2c713f293337/src/SD.h
 * https://docs.arduino.cc/libraries/sd/
 *
 * SD class sub-commands:
 *  begin()         https://docs.arduino.cc/libraries/sd/#SD%20class
 *  exists()            "
 *  mkdir()             "
 *  open()              "
 *  remove()            "
 *  rmdir()             "
 *
 * SD File class sub-commands:
 *  name()            https://www.arduino.cc/reference/en/libraries/sd/name
 *  available()       https://www.arduino.cc/reference/en/libraries/sd/available
 *  close()           https://www.arduino.cc/reference/en/libraries/sd/close
 *  flush()           https://www.arduino.cc/reference/en/libraries/sd/flush
 *  peek()            https://www.arduino.cc/reference/en/libraries/sd/peek
 *  position()        https://www.arduino.cc/reference/en/libraries/sd/position
 *  print()           https://www.arduino.cc/reference/en/libraries/sd/print
 *  println()         https://www.arduino.cc/reference/en/libraries/sd/println
 *  seek()            https://www.arduino.cc/reference/en/libraries/sd/seek
 *  size()            https://www.arduino.cc/reference/en/libraries/sd/size
 *  read()            https://www.arduino.cc/reference/en/libraries/sd/read
 *  write()           https://www.arduino.cc/reference/en/libraries/sd/write
 *  isDirectory()     https://www.arduino.cc/reference/en/libraries/sd/isdirectory
 *  openNextFile()    https://www.arduino.cc/reference/en/libraries/sd/opennextfile
 *  rewindDirectory() https://www.arduino.cc/reference/en/libraries/sd/rewinddirectory
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
 *
 * This example code is in the public domain
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-write-variable-to-sd-card
 *     Reference: https://forum.arduino.cc/t/what-does-file-myfile-actually-do/1295474/5
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

#define SD_CS   10                  // SPI microSD_Card Pins
#define SD_MOSI 11                  // ESP32-S3 Default Pins
#define SD_SCK  12
#define SD_MISO 13

// Path & Filename on SD_Card used for testing (8.3 short names required)
String filename = "/TestFile.txt";
// File object to represent file on SD_Card
File   myFile;
                                    // --Test Data--
int    myInt = -40;                 // Celsius = Fahrenheit
float  myFloat = 12.7;              // Milimeters = 1 Inch
String myString = "Hello, World!";
char   myCharArray[] = "Prof. Michael P. Harris CNE, CCNA, CCAI";
byte   myByteArray[] = {'0','1','2','3','4','5','6','7','8','9'};

void setup() {
  Serial.begin(15200);              // Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  // Initialize SPI bus and deactivate SD_Card Chip Select
  SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  pinMode(SD_CS,      OUTPUT);      // SPI SD_Card Chip Select
  digitalWrite(SD_CS, HIGH);        // Active LOW!

  if(!SD.begin(SD_CS)) {            // SPI SD_Card Chip Select
    Serial.println(F("SD_CARD FAILED, OR NOT PRESENT!"));
    while(1); // Don't do anything more:
  }

  Serial.println(F("SD_CARD INITIALIZED."));
  Serial.println(F("--------------------"));
  SD.remove(filename);
  // Delete the old file, if it exist...
  // NOTE: Remember the SD library uses short 8.3 names for files.

  Serial.println("Open SD_Card file for Writing:");
  myFile = SD.open(filename, FILE_WRITE);

  if(myFile) {
    Serial.print("SD_CARD: Writing to ");
    Serial.println(filename);
    Serial.println("This is a test file:");
    myFile.println("This is a test file:");
    Serial.println(myInt);
    myFile.println(myInt);          // Write Int variable to SD_Card
    Serial.println(myFloat);
    myFile.println(myFloat);        // Write Float variable to SD_Card
    Serial.println(myString);
    myFile.println(myString);       // Write String variable to SD_Card
    Serial.println(myCharArray);
    myFile.println(myCharArray);    // Write Char Array to SD_Card
    Serial.write(myByteArray, 10);
    myFile.write(myByteArray, 10);  // Write Byte Array to SD_Card
    Serial.println("");
    myFile.println("");             // Write a blank line to SD_Card

    for(int i=0; i < 10; i++) {
      Serial.write(myByteArray[i]);
      myFile.write(myByteArray[i]); // Write Byte Array elements to SD_Card
      if(i < 9) {
        Serial.print(",");
        myFile.print(",");          // Write a comma, to SD_Card
      }
    }
    Serial.println("\n");
    myFile.println("\n");           // Write a blank line to SD_Card
    myFile.close();                 // Close the SD_Card file
  } else {
    Serial.print(F("SD_Card: Error opening "));
    Serial.print(filename);
    Serial.println(F(" to Write!"));
  }

  Serial.println("Open SD_Card file for Reading:");
  myFile = SD.open(filename, FILE_READ);
  if(myFile) {
    Serial.print("SD_CARD: Reading from ");
    Serial.println(filename);
    while(myFile.available()) {
      Serial.write(myFile.read());  // Read characters one by one,
    }                               // Print to the Serial Monitor.
    Serial.println("\n");           // Print a blank line
    myFile.close();                 // Close the SD_Card file
  } else {
    Serial.print(F("SD_Card: Error Opening "));
    Serial.print(filename);
    Serial.println(F(" to Read!"));
  }
}

void loop() {
  // Nothing happens after setup() finishes.
}

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
18:40:58.598 -> ESP-ROM:esp32s3-20210327

19:37:41.909 -> SD_CARD INITIALIZED.
19:37:41.909 -> --------------------
19:37:41.909 -> Open SD_Card file for Writing:
19:37:41.909 -> SD_CARD: Writing to /TestFile.txt
19:37:41.909 -> This is a test file:
19:37:41.909 -> -40
19:37:41.909 -> 12.70
19:37:41.909 -> Hello, World!
19:37:41.909 -> Prof. Michael P. Harris CNE, CCNA, CCAI
19:37:41.909 -> 0123456789
19:37:41.909 -> 0,1,2,3,4,5,6,7,8,9
19:37:41.909 ->
19:37:41.909 -> Open SD_Card file for Reading:
19:37:41.909 -> SD_CARD: Reading from /TestFile.txt
19:37:41.909 -> This is a test file:
19:37:41.909 -> -40
19:37:41.909 -> 12.70
19:37:41.909 -> Hello, World!
19:37:41.909 -> Prof. Michael P. Harris CNE, CCNA, CCAI
19:37:41.909 -> 0123456789
19:37:41.909 -> 0,1,2,3,4,5,6,7,8,9
19:37:41.909 ->

--------------------------------------------------------------------
Output:
¯¯¯¯¯¯¯
Sketch uses 383286 bytes (12%) of program storage space.
Maximum is 3145728 bytes.
Global variables use 21484 bytes (6%) of dynamic memory,
            leaving 306196 bytes for local variables.
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c

Leaving...
Hard resetting with RTC WDT...
*******************************************************************/
