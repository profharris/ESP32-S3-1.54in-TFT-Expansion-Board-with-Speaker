/* SPI_SD_Card-Test.ino
 * Requires an SPI microSD Card reader/writer
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 * SD_Card test
 *
 * This example shows how use the utility libraries on which the “SD”
 * library is based in order to get info about your SD card. Very 
 * useful for testing a card when you're not sure whether its working 
 * properly or not.
 *
 * Wiring:
 *
 *  | ESP32-S3 Dev Board | SPI microSD_Card pins  |
 *  |-------------------:|------------------------|
 *  |     3V3            | 1. 3V3  (Power)        |
 *  |     GPIO10         | 2. CS   (Chip Select)  |
 *  |     GPIO11         | 3. MISO (SPI SDO)      |
 *  |     GPIO12         | 4. MOSI (SPI SDI)      |
 *  |     GPIO13         | 5. CLK  (SPI Clock)    |
 *  |     GND            | 6. GND                 | 
 */
 
#include <SPI.h>        // Arduino SPI library
#include <SD.h>         // Arduino SD Card library

Sd2Card  card;
SdVolume volume;
SdFile   root;
File     myFile;

const int chipSelect = 10;

// List Files
void printDIR(File dir, int numTabs) {
  while(true) {
    File entry = dir.openNextFile();
    if(!entry) { // no more files
      break;
    }
    for(uint8_t i=0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if(entry.isDirectory()) {
      Serial.println("/");
      printDIR(entry, numTabs + 1);
    } else { // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void setup() {
  Serial.begin(15200);              // Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  Serial.print("\nInitializing SD_card...");

  if(!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    while(1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

  Serial.println();
  Serial.print("Card type:         ");
  switch(card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  if(!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.");
    Serial.println("Make sure you've formatted the card.");
    while (1);
  }

  Serial.print("Clusters:          "); 
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:  "); 
  Serial.println(volume.blocksPerCluster());
  Serial.print("Total Blocks:      "); 
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();   // Clusters are collections of Blocks
  volumesize *= volume.clusterCount();      // We'll have a lot of Clusters
  volumesize /= 2;                          // SD_card Blocks are always 512 bytes
  Serial.print("Volume size (Kb):  ");      //  (2 Blocks are 1KB)
  Serial.println(volumesize);
  Serial.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Gb):  ");
  Serial.println((float)volumesize / 1024.0);
  
  Serial.println("initialization done.");

  // Test for existing file "example.txt"
  if(SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }

  // Open a new file and immediately close it:
  Serial.println("Creating example.txt...");
  myFile = SD.open("example.txt", FILE_WRITE);
  myFile.close();

  // Check to see if the file exists:
  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }

  // Delete the file:
  Serial.println("Removing example.txt...");
  SD.remove("example.txt");
  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }

  // Directory listing of existing files
  Serial.println("\nFiles found on the SD_card (Name, Date and Size in bytes): ");
  root.openRoot(volume);

  // List all Files in the SD_Card with Date and Size
  root.ls(LS_R | LS_DATE | LS_SIZE);
  root.close();

  // List Files using printDIR() function
  Serial.println();
  root = SD.open("/");
  printDIR(root, 0);

  Serial.println("done!");
}

void loop() {
}
