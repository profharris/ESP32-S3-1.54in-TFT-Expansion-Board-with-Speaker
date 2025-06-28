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
            leaving 282420 bytes for local variables. 
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c
...
Leaving...
Hard resetting with RTC WDT...
*******************************************************************/
