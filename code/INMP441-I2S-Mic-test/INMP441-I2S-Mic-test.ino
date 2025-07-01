/* INMP441-I2S-Mic-test.ino
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 * Requires an INMP441 or ICS-43434 I²S Microphone
 */

#include <driver/i2s.h>

// Either wire your I²S microphone to these same pins
// or change these to match your wiring.
#define I2S_MIC_LEFT_RIGHT_CLOCK GPIO_NUM_4     // I²S Microphone WS / LRC
#define I2S_MIC_SERIAL_CLOCK     GPIO_NUM_5     // I²S Microphone SCK
#define I2S_MIC_SERIAL_DATA      GPIO_NUM_6     // I²S Microphone SD

// Most I²S Microphones default to Left channel,
// but you may need to tie the L/R pin LOW.
#define I2S_MIC_CHANNEL I2S_CHANNEL_FMT_ONLY_LEFT

// You shouldn't need to change these settings
#define SAMPLE_BUFFER_SIZE 512
#define SAMPLE_RATE        8000

int32_t raw_samples[SAMPLE_BUFFER_SIZE];

// You shouldn't need to change these settings
i2s_config_t i2s_config   = {
    .mode                 = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate          = SAMPLE_RATE,
    .bits_per_sample      = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format       = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count        = 4,
    .dma_buf_len          = 1024,
    .use_apll             = false,
    .tx_desc_auto_clear   = false,
    .fixed_mclk           = 0};

// You shouldn't need to change these settings
i2s_pin_config_t i2s_mic_pins = {
    .bck_io_num   = I2S_MIC_SERIAL_CLOCK,
    .ws_io_num    = I2S_MIC_LEFT_RIGHT_CLOCK,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num  = I2S_MIC_SERIAL_DATA};

void setup() {
  Serial.begin(115200);             // Initialize the Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  // Start up the I²S Microphone peripheral
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &i2s_mic_pins);
}

void loop() {
  // Read from the I²S Microphone device
  size_t bytes_read = 0;
  i2s_read(I2S_NUM_0, raw_samples, sizeof(int32_t) * SAMPLE_BUFFER_SIZE,
           &bytes_read, portMAX_DELAY);
  int samples_read = bytes_read / sizeof(int32_t);
  // Dump the samples out to the Serial Monitor & Serial Plotter.
  for(int i=0; i < samples_read; i++) {
    Serial.printf("%ld\n", raw_samples[i]);
  }
}

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
00:40:39.147 -> ESP-ROM:esp32s3-20210327
00:40:39.147 ->
00:40:39.147 -> 3620352
00:40:39.147 -> 3965440
00:40:39.147 -> 4045312
00:40:39.147 -> 3952128
...

--------------------------------------------------------------------
Output:
¯¯¯¯¯¯¯
Sketch uses 340134 bytes (10%) of program storage space. 
Maximum is 3145728 bytes.
Global variables use 23292 bytes (7%) of dynamic memory, 
            leaving 304388 bytes for local variables. 
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c

Leaving...
Hard resetting with RTC WDT...

*******************************************************************/
