/* MAX98357-I2S-stream-from-Flash.ino
 * Requires a MAX98357A I²S Audio Amplifier/Speaker
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 *      Stream a file from Flash Memory and send it to the I²S bus:
 *
 *      Uses Arduino AudioTools library
 *      https://github.com/pschatzmann/arduino-audio-tools
 *
 * Requires a music file in the same directory:  “StarWars30.h”
 *
 * Wiring:
 * ¯¯¯¯¯¯¯
 * MAX98357A I²S Amp (7-pins)       ESP32-S3-WROOM-1
 * 1. DIN  (Serial Data In/Out) --> GPIO7
 * 2. BCLK (Bit Clock)          --> GPIO15
 * 3. LRC  (Left Right Clock)   --> GPIO16
 * 4. GAIN                      --> Connect to GND (12 dB gain)
 * 5. SD   (L/R Channel Select) --> Connect to GND (select Left)
 * 6. GND                       --> GND
 * 7. VIN  (Power)              --> 3V3
 *
 * External Speaker interface: (+ —)
 * Audio+  Connect to Speaker Positive (usually Red wire)
 * Audio-  Connect to Speaker Negative
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
 
#include "AudioTools.h"             // Arduino Audio Tools library
// https://github.com/pschatzmann/arduino-audio-tools
// ~/Documents/Arduino/libraries\audio-tools\src\AudioToolsConfig.h
#include "StarWars30.h"
// https://github.com/pschatzmann/arduino-audio-tools/
//   blob/main/examples/examples-stream/streams-memory_raw-i2s/StarWars30.h

uint8_t  channels                   =     2;
uint16_t sample_rate                = 22050;
uint8_t  bits_per_sample            =    16;

uint8_t  pin_bck                    =    15;  // MAX98357A BCLK 
uint8_t  pin_ws                     =    16;  // MAX98357A WS/LRC
uint8_t  pin_data                   =     7;  // MAX98357A DIN/DOUT

// Make sure “StarWars30.h” is in the same directory as this sketch
MemoryStream music(StarWars30_raw, StarWars30_raw_len);
I2SStream i2s;                      // Output(Stream) to I²S
StreamCopy copier(i2s, music);      // Copy music to I²S bus

void setup(){
  Serial.begin(115200);             // Initialize the Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  auto config            = i2s.defaultConfig(TX_MODE);
  config.sample_rate     = sample_rate;
  config.channels        = channels;
  config.bits_per_sample = bits_per_sample;
  config.pin_bck         = pin_bck;  // MAX98357A Bit Clock
  config.pin_ws          = pin_ws;   // MAX98357A Left/Right Clock
  config.pin_data        = pin_data; // MAX98357A Serial Data In/Out
  i2s.begin(config);

  music.begin();
}

void loop() {
    copier.copy();
    // Listen to the “Star Wars” intro...
}

/*******************************************************************
Sketch uses 2239534 bytes (71%) of program storage space. 
  Maximum is 3145728 bytes.
Global variables use 45260 bytes (13%) of dynamic memory, 
leaving 282420 bytes for local variables. Maximum is 327680 bytes.

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
Flash will be erased from 0x00010000 to 0x00232fff...
Compressed 20208 bytes to 13058...
Writing at 0x00000000... (100 %)
Wrote 20208 bytes (13058 compressed) at 0x00000000 in 0.4 seconds 
  (effective 444.8 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 144...
Writing at 0x00008000... (100 %)
Wrote 3072 bytes (144 compressed) at 0x00008000 in 0.0 seconds 
  (effective 548.8 kbit/s)...
Hash of data verified.
Compressed 8192 bytes to 47...
Writing at 0x0000e000... (100 %)
Wrote 8192 bytes (47 compressed) at 0x0000e000 in 0.1 seconds 
  (effective 607.0 kbit/s)...
Hash of data verified.
Compressed 2239680 bytes to 1827216...
Writing at 0x00010000... (0 %)
Writing at 0x0001cdb2... (1 %)
Writing at 0x000284bf... (2 %)
Writing at 0x0002c67a... (3 %)
Writing at 0x00030928... (4 %)
Writing at 0x00034c8c... (5 %)
Writing at 0x00039171... (6 %)
Writing at 0x0003d59e... (7 %)
Writing at 0x00041bf7... (8 %)
Writing at 0x000461c6... (8 %)
Writing at 0x0004a721... (9 %)
Writing at 0x0004ec97... (10 %)
Writing at 0x0005312a... (11 %)
Writing at 0x000573d0... (12 %)
Writing at 0x0005b7b8... (13 %)
Writing at 0x0005fc97... (14 %)
Writing at 0x0006410d... (15 %)
Writing at 0x00068435... (16 %)
Writing at 0x0006c6e9... (16 %)
Writing at 0x00070984... (17 %)
Writing at 0x00074e97... (18 %)
Writing at 0x00079278... (19 %)
Writing at 0x0007d51d... (20 %)
Writing at 0x00081953... (21 %)
Writing at 0x00085cba... (22 %)
Writing at 0x00089f7a... (23 %)
Writing at 0x0008e314... (24 %)
Writing at 0x00092769... (25 %)
Writing at 0x00096a3d... (25 %)
Writing at 0x0009ada0... (26 %)
Writing at 0x0009f29b... (27 %)
Writing at 0x000a36ba... (28 %)
Writing at 0x000a7a02... (29 %)
Writing at 0x000abc82... (30 %)
Writing at 0x000aff53... (31 %)
Writing at 0x000b424b... (32 %)
Writing at 0x000b8614... (33 %)
Writing at 0x000bca17... (33 %)
Writing at 0x000c0ce5... (34 %)
Writing at 0x000c4f69... (35 %)
Writing at 0x000c9266... (36 %)
Writing at 0x000cd52d... (37 %)
Writing at 0x000d18b9... (38 %)
Writing at 0x000d5b0d... (39 %)
Writing at 0x000d9d21... (40 %)
Writing at 0x000ddf65... (41 %)
Writing at 0x000e2208... (41 %)
Writing at 0x000e6507... (42 %)
Writing at 0x000ea80a... (43 %)
Writing at 0x000eeaff... (44 %)
Writing at 0x000f2df5... (45 %)
Writing at 0x000f7166... (46 %)
Writing at 0x000fb3f3... (47 %)
Writing at 0x000ff687... (48 %)
Writing at 0x00103a20... (49 %)
Writing at 0x00107cbc... (50 %)
Writing at 0x0010bf33... (50 %)
Writing at 0x0011027a... (51 %)
Writing at 0x001144b4... (52 %)
Writing at 0x00118794... (53 %)
Writing at 0x0011cba7... (54 %)
Writing at 0x00120ebc... (55 %)
Writing at 0x00125128... (56 %)
Writing at 0x001294ea... (57 %)
Writing at 0x0012d7d6... (58 %)
Writing at 0x00131ac9... (58 %)
Writing at 0x00135dc9... (59 %)
Writing at 0x00139f66... (60 %)
Writing at 0x0013e0f2... (61 %)
Writing at 0x0014243e... (62 %)
Writing at 0x00146800... (63 %)
Writing at 0x0014ad59... (64 %)
Writing at 0x0014f240... (65 %)
Writing at 0x001536e2... (66 %)
Writing at 0x00157b9c... (66 %)
Writing at 0x0015c091... (67 %)
Writing at 0x001604e7... (68 %)
Writing at 0x0016489a... (69 %)
Writing at 0x0016c342... (70 %)
Writing at 0x0017a5c4... (71 %)
Writing at 0x00182a29... (72 %)
Writing at 0x001888c3... (73 %)
Writing at 0x0018e277... (74 %)
Writing at 0x00193b36... (75 %)
Writing at 0x0019942f... (75 %)
Writing at 0x0019f3b2... (76 %)
Writing at 0x001a45c6... (77 %)
Writing at 0x001a9817... (78 %)
Writing at 0x001aecbf... (79 %)
Writing at 0x001b437b... (80 %)
Writing at 0x001b98cd... (81 %)
Writing at 0x001bea3f... (82 %)
Writing at 0x001c3c9d... (83 %)
Writing at 0x001c9362... (83 %)
Writing at 0x001cee51... (84 %)
Writing at 0x001d42c0... (85 %)
Writing at 0x001d9af8... (86 %)
Writing at 0x001de890... (87 %)
Writing at 0x001e383a... (88 %)
Writing at 0x001e8bdf... (89 %)
Writing at 0x001edf46... (90 %)
Writing at 0x001f301e... (91 %)
Writing at 0x001f8158... (91 %)
Writing at 0x001fd815... (92 %)
Writing at 0x002035b4... (93 %)
Writing at 0x00208bf0... (94 %)
Writing at 0x00212c24... (95 %)
Writing at 0x002193bc... (96 %)
Writing at 0x0021e219... (97 %)
Writing at 0x00223d04... (98 %)
Writing at 0x002299e7... (99 %)
Writing at 0x0022faeb... (100 %)
Wrote 2239680 bytes (1827216 compressed) at 0x00010000 in 19.7 seconds 
  (effective 907.6 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting with RTC WDT...
*******************************************************************/
