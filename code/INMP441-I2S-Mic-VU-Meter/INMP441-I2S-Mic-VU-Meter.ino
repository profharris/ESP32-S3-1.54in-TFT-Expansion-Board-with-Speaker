/* INMP441-I2S-Mic-VU-Meter.ino
 * VU Meter Demo
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 * Requires an INMP441 I²S Microphone
 *
 * Often times you don't want the actual Audio Data but the overall
 * “sound pressure level”. This example will take a bunch of samples,
 * normalize the data to be around 0, then give you the maximum difference
 * between the waveforms for a VU-Meter ‘volume graph’.
 *
 * This example reads audio data from an Invensense's INMP441 I²S Mic, and
 * prints out the ‘Peek-to-Peek’ normalized samples to the Serial console.
 * The Serial Plotter built into the Arduino IDE can be used to plot the
 * normalized audio data.
 * (Tools -> Serial Plotter)
 *
 * Wiring:
 * ¯¯¯¯¯¯¯
 *   | ESP32-S3 Dev Board  | I²S INMP441 Microphone    |
 *   |--------------------:|---------------------------|
 *   |     GND             | 1. GND                    |
 *   |     3V3             | 2. VDD (Power)            |
 *   |     GPIO4           | 3. WS  Word/Data Select   |
 *   |     GPIO5           | 4. SCK Serial Data Clock  |
 *   |     GPIO6           | 5. SD  Serial Data Out    |
 *
 * originally created 17 November 2016, by Sandeep Mistry
 * https://learn.adafruit.com/adafruit-i2s-mems-microphone-breakout/arduino-wiring-and-test
 * ported to ESP32-S3 1.54in TFT Expansion Board with Speaker
 * by Prof. Michael P. Harris
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
              Flash Size: "16MB 128Mb"  【or】
              Flash Size: "8MB 64Mb"    ...check your board!
USB Firmware MSC On Boot: "Disabled"
        Partition Scheme: "16M Flash (2MB APP/12.5MB FATFS)"  【or】
        Partition Scheme: "8MB with spiffs (3MB APP/1.5MB SPIFFS)"
                   PSRAM: "OPI PSRAM"
             Upload Mode: "UART0/Hardware CDC"
            Upload Speed: "115200"
                USB Mode: "Hardware CDC and JTAG"
*******************************************************************/
#include <driver/i2s.h>             // Include the new I²S driver

#define I2S_WS     4                // Pins: INMP441 I²S Mic
#define I2S_SCK    5                //          "
#define I2S_SD     6                //          "

#define I2S_PORT I2S_NUM_0          // Use I²S Processor 0

#define bufferLen 512               // Input buffer length
int16_t samples[bufferLen];         // I²S Serial sample buffer

// Config I²S for 32kHz with 16-bits per sample
void I2S_install() {                // Set I²S Processor config
  const i2s_config_t I2S_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate          = 32768,
    .bits_per_sample      = i2s_bits_per_sample_t(16),
    .channel_format       = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags     = 0,
    .dma_buf_count        = 8,
    .dma_buf_len          = bufferLen,
    .use_apll             = false
  };
  i2s_driver_install(I2S_PORT, &I2S_config, 0, NULL);
}

void I2S_setPin() {                 // Set I²S Pin configuration
  const i2s_pin_config_t pin_config = {
    .bck_io_num   = I2S_SCK,
    .ws_io_num    = I2S_WS,
    .data_out_num = -1,
    .data_in_num  = I2S_SD
  };
  i2s_set_pin(I2S_PORT, &pin_config);
}

void setup() {
  Serial.begin(115200);             // Initialize the Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  Serial.println("INMP441 I²S Mic - VU-Meter");
  Serial.println("To see the ‘Peek-to-Peek’ VU-Meter, open the Serial Plotter");
  Serial.println("(Tools -> Serial Plotter)");
  delay(1000);

  I2S_install();                    // I²S driver install
  I2S_setPin();                     // I²S set pins
  i2s_start(I2S_PORT);              // Initialize INMP441 I²S Mic
  delay(500);
  
  // False print statements will “lock the range” on Serial Plotter.
  // Change this ‘rangeLimit’ value to adjust the “sensitivity”.
  int rangeLimit = 31072;   // int16_t max
  Serial.print(rangeLimit * -1);
  Serial.print(" ");
  Serial.print(rangeLimit);
  Serial.print(" ");
}


void loop() {
  // Read a bunch of Audio samples:
  // int16_t samples[bufferLen];

  // Get the I²S Data and place it in the Data buffer.
  size_t bytesIn   = 0;
  esp_err_t result = i2s_read(I2S_PORT, &samples, bufferLen,
                              &bytesIn, portMAX_DELAY);

  if(result == ESP_OK) {
    int16_t samplesRead = bytesIn / 2; // 16-bits/sample
    float meanVal = 0;
    // From the audio samples, get the ‘mean’ (average)
    if(samplesRead > 0) {
      for(int16_t i=0; i < samplesRead; ++i) {
        meanVal += (samples[i]);
      }
      meanVal /= samplesRead;
      //Serial.println(mean);
    }
    // Subtract the ‘mean’ from all samples to ‘normalized’ the dataset
    for(int16_t  i=0; i < samplesRead; i++) {
      samples[i] -= meanVal;
      //Serial.println(samples[i]);
    }
    // Find the 'Peak-to-Peak' minSample & maxSample,
    int16_t minSample, maxSample;
    minSample =  31072;   // int16_t max
    maxSample = -31072;   // int16_t min
    for(int16_t  i=0; i < samplesRead; i++) {
      minSample = min(minSample, samples[i]);
      maxSample = max(maxSample, samples[i]);
    }
    Serial.print(maxSample);
    Serial.print(" ");
    Serial.print(maxSample - minSample);
    Serial.print(" ");
    Serial.println(minSample);
  }
}

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
22:57:32.687 -> ESP-ROM:esp32s3-20210327
22:57:32.687 -> INMP441 I²S Mic - VU-Meter
22:57:32.687 -> To see the ‘Peek-to-Peek’ VU-Meter, open the Serial Plotter
22:57:32.687 -> (Tools -> Serial Plotter)
22:57:33.367 -> 22 51 -29
22:57:33.367 -> 23 53 -30
22:57:33.367 -> 25 55 -30
22:57:33.367 -> 22 56 -34
...

--------------------------------------------------------------------
Output:
¯¯¯¯¯¯¯
Sketch uses 340666 bytes (10%) of program storage space.
Maximum is 3145728 bytes.
Global variables use 21420 bytes (6%) of dynamic memory,
            leaving 306260 bytes for local variables.
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c

Leaving...
Hard resetting with RTC WDT...
*******************************************************************/
