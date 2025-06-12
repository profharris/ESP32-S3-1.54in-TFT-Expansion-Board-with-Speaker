/* MAX98357-I2S-Amp-quickTest.ino
 * https://www.kincony.com/forum/showthread.php?tid=6898
 *
 * Requires a MAX98357A I²S Audio Amplifier/Speaker.
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 * DO NOT use the old I²S I2S.h library:   #include <I2S.h>
 *
 * ESP32-S3 replacement I²S I2S.h driver:  #include <driver/i2s.h>
 *
 * On the ESP32-S3, equivalent functionality for I²S communication
 * is provided by the Espressif ESP-IDF I²S driver: “<driver/i2s.h>”
 *
 * This is the new standard way to interface with the I²S peripherals
 * on the ESP32-S3.
 *
 * In summary, when working with I²S on the ESP32-S3, you will use the
 * ESP-IDF I²S driver, “<driver/i2s.h>” and its associated functions
 * rather than the standalone I2S.h header file. You can refer to the
 * Espressif ESP-IDF documentation for detailed information & examples.
 *
 * https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/peripherals/i2s.html
 *
 * Inter-IC Sound (I²S)
 * ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
 * I2S (Inter-IC Sound) is a synchronous serial communication protocol
 * usually used for transmitting audio data between two digital audio
 * devices. Used to communicate ‘PCM Audio Data’ between integrated
 * circuits in an electronic device.
 *
 * ESP32-S3 contains two I²S peripheral(s). These peripherals can be
 * configured to input and output sample data via the I²S driver.
 *
 * An I²S bus that communicates in “Standard” and “TDM mode”,
 * consists of the following lines:
 *
 *     MCLK: Master Clock line. It is an ‘optional’ signal depending
 *           on the slave side, mainly used for offering a reference
 *           clock to the I²S slave device.
 *     BCLK: Bit clock line. Every tick of the BCLK stands for one
 *           data bit on Data pin. The ‘slot’ bit width configured
 *           in “i2s_std_slot_config_t::slot_bit_width” is equal to
 *           the number of BCLK ticks, which means there will be:
 *           8/16/24/32 BCLK ticks in one ‘slot’.
 *  LRCK/WS: Left/Right Clock -or Word Select Clock. For non-PDM
 *           mode, its frequency is equal to the “sample rate”,
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
#define I2S_BLCK     15         // bck        "
#define I2S_LRC      16         // ws         "

#define I2S_PORT I2S_NUM_0      // I²S Port/Processor number

const int sampleRate  = 44100;  // Sample Rate and wave parameters
const float Frequency = 440.0;  // sine wave Frequency (A4 note)
const int Amplitude   = 3000;   // Amplitude of the sine wave

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
  Serial.println("Generating sine wave on the MAX98357A amplifier");

  i2s_install();                    // Set up I²S for TX
  i2s_setpin();                     // Set up MAX98357A
  i2s_start(I2S_PORT);
  Serial.println("MAX98357A I²S driver installed.");
  delay(500);
}

void loop() { // Quick Test: Send a 440Hz sine wave to the MAX98357A
  int16_t buffer[64];               // Buffer to hold the Audio data

  // Generate the 440Hz sine wave and write it to the I²S buffer
  for(int i=0; i < 64; i++) {
    float sample = sinf(2.0f * M_PI * Frequency * i / sampleRate);
    buffer[i] = (int16_t)(sample * Amplitude);
  }

  // Send the sine wave in the buffer to the MAX98357A I²S amplifier
  size_t bytesWritten;
  i2s_write(I2S_PORT, &buffer, sizeof(buffer), &bytesWritten, portMAX_DELAY);

  //i2s_stop(I2S_PORT);             // Stop the MAX98357A I²S driver
}
