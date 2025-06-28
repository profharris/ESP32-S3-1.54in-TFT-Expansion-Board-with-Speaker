/* MAX98357-I2S-stream-from-PROGMEM.ino
 * Requires a MAX98357A I²S Audio Amplifier/Speaker
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 *      Stream/Play an Audio file to the I²S bus from PROGMEM:
 *      https://forum.arduino.cc/t/arduino-and-esp32-i2s/501975/4
 *
 * Requires a music file in the same directory:  “soundsample.h”
 *
 * Wiring:
 * ¯¯¯¯¯¯¯
 * MAX98357A I²S Amp (7-pins)       ESP32-S3-WROOM-1
 * 1. VIN  (Power)              --> 3V3
 * 2. GND                       --> GND
 * 3. SD   (L/R Channel Select) --> Connect to 3V3 (0Ω = Left)
 * 4. GAIN                      --> Connect to GND (12dB Gain)
 * 5. DIN  (Serial Data In/Out) --> GPIO7
 * 6. BCLK (Bit Clock)          --> GPIO15
 * 7. LRC  (Left Right Clock)   --> GPIO16
 *
 * External Speaker interface: (⧾ ⧿)
 * Audio⧾  Connect to Speaker Positive (usually Red wire)
 * Audio⧿  Connect to Speaker Negative
 *
 * REF: // https://busyducks.com/comprehensive-example-code-demonstrating-using-arduino-flash-memory-via-progmem/
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
 
#include <pgmspace.h>           // Arduino PROGMEM library
#include "driver/i2s.h"         // Include newer ESP-IDF I²S library

#include "soundsample.h"        // 16-bit 16kHz wav audio sample (static)

int i2s_num = 0;                // I²S port number
i2s_config_t i2s_config = {     // I²S configuration
  .mode                 = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
  .sample_rate          = 16000, // 16-bit, 16kHz wav sample
  .bits_per_sample      = I2S_BITS_PER_SAMPLE_16BIT,
  .channel_format       = I2S_CHANNEL_FMT_RIGHT_LEFT,
  .communication_format = I2S_COMM_FORMAT_STAND_I2S,
  .intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1, // High IRQ priority
  .dma_buf_count        = 8,
  .dma_buf_len          = 64,
  .use_apll             = true   // use internal clock, better audio
};

i2s_pin_config_t pin_config = {
  .bck_io_num           = 15, // MAX98357A I²S BCLK pin
  .ws_io_num            = 16, // MAX98357A I²S LRC  pin
  .data_out_num         =  7, // MAX98357A I²S DOUT pin
  .data_in_num          = I2S_PIN_NO_CHANGE // Not used
};


// Main function to Play samples from PROGMEM
void playPROGMEMsample(const uint32_t *audioSample) {

  uint32_t sampleSize = sizeof(audioSample) * 4;
  uint32_t counter    = 0;

  // Initialize I²S with configurations above
  i2s_driver_install((i2s_port_t)i2s_num, &i2s_config, 0, NULL);
  i2s_set_pin((i2s_port_t)i2s_num, &pin_config);
  // Set sample rate of I²S to sample rate of audio file
  i2s_set_sample_rates((i2s_port_t)i2s_num, 16000);

  uint32_t readData;
  while(audioSample)  {
    readData = pgm_read_dword(&audioSample[counter++]);
    if(!readData) break; // NULL
    i2s_write_sample_nb(readData);         // Send sample to I²S bus
  }
  // Stop & uninstall I²S driver
  i2s_driver_uninstall((i2s_port_t)i2s_num);
}

size_t i2s_bytes_written = 0;
bool i2s_write_sample_nb(uint32_t sample) { // Send sample to I²S bus
  i2s_write((i2s_port_t)i2s_num, (const uint32_t *)&sample,
            sizeof(uint32_t), (size_t *)&i2s_bytes_written, 100);
  if(!i2s_bytes_written) 
      return false;
  else
      return true;
}


void setup() {
  Serial.begin(115200);             // Initialize the Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  Serial.println("Listen to the music sample in PROGMEM!");
  playPROGMEMsample(sample1);
}

void loop() {
    // Listen to the music...
}

/*******************************************************************
Output:
¯¯¯¯¯¯¯
Sketch uses 735826 bytes (23%) of program storage space. 
Maximum is 3145728 bytes.
Global variables use 21252 bytes (6%) of dynamic memory, 
            leaving 306428 bytes for local variables. 
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c
...
Leaving...
Hard resetting with RTC WDT...

--------------------------------------------------------------------
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
19:39:19.870 -> ESP-ROM:esp32s3-20210327

19:39:19.988 -> Listen to the music sample in PROGMEM!
*******************************************************************/
