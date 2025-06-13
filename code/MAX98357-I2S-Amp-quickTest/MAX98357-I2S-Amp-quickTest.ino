/* MAX98357-I2S-Amp-quickTest.ino
 *      Quick Test: Send 440Hz Sine Waves to the MAX98357A/Speaker.
 *      https://www.kincony.com/forum/showthread.php?tid=6898
 *
 * Requires a MAX98357A I²S Audio Amplifier/Speaker.
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 * DO NOT use the old I²S I2S.h library with an ESP32-S3: ‘<I2S.h>’
 * ¯¯¯¯¯¯
 * On the ESP32-S3, equivalent functionality for I²S communication
 * is provided by the Espressif ESP-IDF I²S driver: “<driver/i2s.h>”
 * NOTE the Uppercase/lowercase difference, this is important.
 * ¯¯¯¯
 * This is a new standard way to interface with the I²S peripherals
 * on the ESP32-S3. When working with I²S on the ESP32-S3, you can
 * use the new ESP-IDF I²S driver, <driver/i2s.h> and its associated
 * functions rather than the standalone I2S.h header file. You can
 * refer to Espressif ESP-IDF documentation for detailed information
 * and examples here:
 *
 * https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/peripherals/i2s.html
 *
 * Inter-IC Sound (I²S)
 * ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
 * I²S (Inter-IC Sound) is a synchronous serial bus communication
 * protocol, usually used for transmitting Audio data between two
 * Digital Audio devices. I²S is used to communicate ‘PCM Audio Data’
 * between integrated circuits in an electronic device.
 *
 * The ESP32-S3 contains two I²S Peripherals. These peripherals can
 * be configured to input and output sample data via the I²S driver.
 *
 * An I²S bus that communicates in “Standard” and “TDM mode”,
 * consists of the following lines:
 *
 *     MCLK: Master Clock line. It is an ‘optional’ signal depending
 *           on the slave side. It is mainly used for offering a
 *           reference clock to the I²S slave device.
 *     BCLK: Bit Clock line. Every tick of the BCLK stands for one
 *           data bit on Data pin. The ‘slot’ bit width configured
 *           in “i2s_std_slot_config_t::slot_bit_width” is equal to
 *           the number of BCLK ticks, which means there will be:
 *           8/16/24/32 BCLK ticks in one ‘slot’.
 *   LRC/WS: Left/Right Clock -or Word Select Clock. For non-PDM
 *           mode, its’ frequency is equal to the “sample Rate”,
 *           e.g. the number of sampled data in one second per slot.
 * DIN/DOUT: Serial Data Input/Output line. Data will loopback
 *           internally if DIN and DOUT are set to the same GPIO.
 *
 * An I²S bus that communicates in “PDM” mode,
 * consists of the following lines:
 *
 *      CLK: PDM Clock line.
 * DIN/DOUT: Serial Data Input/Output line.
 *
 * Wiring:
 * ¯¯¯¯¯¯¯
 * MAX98357 I²S Amp                 ESP32-S3-WROOM-1
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
 *
 * NOTE: You will not hear the 440Hz Sine Wave tone until
 * ¯¯¯¯¯ you open the “Serial Monitor”!
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

#include <Arduino.h>            // Include required libraries
#include <driver/i2s.h>         // Include newer ESP-IDF I²S driver
#include <math.h>
                                // MAX98357A I²S Audio Amp pins
#define I2S_DOUT      7         // data_out   "
#define I2S_BCLK     15         // bck        "
#define I2S_LRC      16         // ws         "

#define I2S_PORT I2S_NUM_0      // I²S Port/Peripheral number

const int sampleRate  = 44100;  // Sample Rate and Wave parameters
const float Frequency = 440.0;  // Sine Wave Frequency (A4 note)
const int Amplitude   = 3000;   // Amplitude of the Sine Wave

void i2s_install() {            // Setup I²S Port config for TX only
  const i2s_config_t i2s_config = {
    .mode                 = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate          = sampleRate,
    .bits_per_sample      = i2s_bits_per_sample_t(16),
    .channel_format       = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags     = 0,
    .dma_buf_count        = 8,
    .dma_buf_len          = 64,
    .use_apll             = false
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
}

void i2s_setpin() {   // I²S pin configuration for Output (Audio Amp)
  const i2s_pin_config_t pin_config = { // MAX98357A I²S pins
    .bck_io_num   = I2S_BCLK,           // Bit Clock line
    .ws_io_num    = I2S_LRC,            // Word Select|Left/Right Channel
    .data_out_num = I2S_DOUT,           // Serial Data line, Data Out
    .data_in_num  = I2S_PIN_NO_CHANGE
  };

  i2s_set_pin(I2S_PORT, &pin_config);
}

void setup() {
  Serial.begin(115200);             // Initialize the Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open
  
  // NOTE: You will not hear the 440Hz Sine Wave tone until
  //       you open the Serial Monitor!
  
  Serial.println("Send 440Hz Sine Waves to the MAX98357A Amplifier/Speaker");

  i2s_install();                    // Set up I²S for Transmit only
  i2s_setpin();                     // Set up MAX98357A Audio Amp
  i2s_start(I2S_PORT);
  Serial.println("MAX98357A I²S driver installed.");
  delay(500);
}

void loop() {
  int16_t buffer[64];               // Buffer to hold the Audio data

  // Generate a 440Hz Sine Wave and write it to the I²S buffer
  for(int i=0; i < 64; i++) {
    float sample = sinf(2.0f * M_PI * Frequency * i / sampleRate);
    buffer[i] = (int16_t)(sample * Amplitude);
  }

  // Send the Sine Wave in the buffer to the MAX98357A I²S Audio Amplifier
  size_t bytesWritten;
  i2s_write(I2S_PORT, &buffer, sizeof(buffer), &bytesWritten, portMAX_DELAY);

  //i2s_stop(I2S_PORT);             // Stop the MAX98357A I²S driver
}

/*******************************************************************
Sketch uses 344038 bytes (16%) of program storage space. 
  Maximum is 2097152 bytes.
Global variables use 21164 bytes (6%) of dynamic memory, 
  leaving 306516 bytes for local variables. Maximum is 327680 bytes.
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
Flash will be erased from 0x00010000 to 0x00064fff...
Compressed 20208 bytes to 13058...
Writing at 0x00000000... (100 %)
Wrote 20208 bytes (13058 compressed) at 0x00000000 in 0.4 seconds (effective 458.7 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 143...
Writing at 0x00008000... (100 %)
Wrote 3072 bytes (143 compressed) at 0x00008000 in 0.1 seconds (effective 460.0 kbit/s)...
Hash of data verified.
Compressed 8192 bytes to 47...
Writing at 0x0000e000... (100 %)
Wrote 8192 bytes (47 compressed) at 0x0000e000 in 0.1 seconds (effective 624.4 kbit/s)...
Hash of data verified.
Compressed 344176 bytes to 186452...
Writing at 0x00010000... (8 %)
Writing at 0x0001c405... (16 %)
Writing at 0x000295c3... (25 %)
Writing at 0x0002efcd... (33 %)
Writing at 0x00034994... (41 %)
Writing at 0x0003a11b... (50 %)
Writing at 0x0003f90d... (58 %)
Writing at 0x00045469... (66 %)
Writing at 0x0004b1d5... (75 %)
Writing at 0x000549fc... (83 %)
Writing at 0x0005b9a3... (91 %)
Writing at 0x0006199a... (100 %)
Wrote 344176 bytes (186452 compressed) at 0x00010000 in 3.1 seconds (effective 875.6 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting with RTC WDT...

--------------------------------------------------------------------
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
01:31:08.758 -> Send 440Hz Sine Waves to the MAX98357A Amplifier/Speaker
01:31:08.758 -> MAX98357A I²S driver installed.

*******************************************************************/
