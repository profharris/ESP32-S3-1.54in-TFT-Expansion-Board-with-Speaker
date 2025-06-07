/* INMP441-I2S-Mic-sample.ino
 * Requires INMP441 I²S microphone
 *
 * 1. Sample the sound from an INMP441 I²S Microphone.
 * 2. Display the sound on the Arduino IDE Serial Plotter.
 *
 * https://dronebotworkshop.com/esp32-i2s/
 */

#include <driver/i2s.h>                 // Include I²S driver

#define I2S_WS     4                    // Pins: INMP441 I²S Mic
#define I2S_SCK    5
#define I2S_SD     6

#define I2S_PORT I2S_NUM_0              // Use I²S Processor 0

#define bufferLen 64                    // Input buffer length
int16_t sBuffer[bufferLen];             // I²S Serial Input buffer

void I2S_install() {                    // I²S Processor config
  const i2s_config_t I2S_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate          = 44100,
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

void I2S_setPin() {                     // Set I²S pin configuration
  const i2s_pin_config_t pin_config = {
    .bck_io_num   = I2S_SCK,
    .ws_io_num    = I2S_WS,
    .data_out_num = -1,
    .data_in_num  = I2S_SD
  };

  i2s_set_pin(I2S_PORT, &pin_config);
}

void setup() {
  Serial.begin(115200);                 // Initialize Serial Monitor
  while(!Serial);                       // Wait for Serial Port to open
  Serial.println(" ");
  delay(1000);

  I2S_install();                        // Set up INMP441 I²S Mic
  I2S_setPin();
  i2s_start(I2S_PORT);
  delay(500);
}

void loop() {
  // False print statements to "lock range" on Serial Plotter display
  // Change the rangeLimit value to adjust "sensitivity"
  int rangeLimit = 3000;
  Serial.print(rangeLimit * -1);
  Serial.print(" ");
  Serial.print(rangeLimit);
  Serial.print(" ");

  // Get I²S Data and place in the Data buffer
  size_t bytesIn   = 0;
  esp_err_t result = i2s_read(I2S_PORT, &sBuffer, bufferLen, &bytesIn, portMAX_DELAY);

  if(result == ESP_OK) {
    int16_t samplesRead = bytesIn / 8;
    if(samplesRead > 0) {
      float mean = 0;
      for(int16_t i=0; i < samplesRead; ++i) {
        mean += (sBuffer[i]);
      }
      mean /= samplesRead;              // Average the Data reading
      Serial.println(mean);             // Print to Serial Plotter
    }
  }
}
