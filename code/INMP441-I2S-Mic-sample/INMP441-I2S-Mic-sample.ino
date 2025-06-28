/* INMP441-I2S-Mic-sample.ino           (Visual “Audio Waveforms”)
 * Requires an INMP441 I²S Microphone
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 * 1. Sample the sound from an INMP441 I²S Microphone, then
 * 2. Show the “Audio Waveforms” on the Arduino IDE Serial Plotter.
 *
 * Sound with ESP32 – I²S Protocol  
 * https://dronebotworkshop.com/esp32-i2s/
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
/* -----------------------------------------------------------------
 1. We start this sketch by including the ESP32 I²S driver.
 2. We then define the connections to our INMP441 I²S Microphone. If
    you wish you can rewire the microphone & change the code here.
 3. The ESP32 has two internal I²S processors. We will be using the
    first one, “I²S Port 0”. We also define the length of our input
    data buffer.
 4. Next, we have a function called “I2S_install()”, which sets up
    the I²S port parameters.
 5. A second function, “I2S_setPin()”, sets the physical connection
    to the I²S device, which in our case is our INMP441 Microphone.
 6. In setup(), we set up our Serial connection, as we will also be 
    using the ‘Serial Plotter’ to display our “Audio Waveforms”. We 
    then call our two functions to set up the I²S port, and then 
    start it with a third ‘built-in’ function, “i2s_start()”.
 7. Our loop() starts with a “false” Print statement, this just
    causes two constants to be printed to steady the reading on the
    ‘Serial Plotter’, which otherwise might dynamically change its’
    Y-axis scale.
 8. We then read data from the INMP441 Microphone and place it in
    our data buffer. If the data is good, we read it out and display
    the raw data in the Serial Monitor and the “Audio Waveforms” on 
    the Serial Plotter.

    Testing the INMP441 I²S Microphone:   (Visual “Audio Waveforms”)
    
    Hook everything up and load the sketch. 0pen the Serial Monitor
    AND the Serial Plotter. --Have a little fun, sing your favorite
    little song into the INMP441 Mic. The INMP441 is very sinsitive,
    you don’t have to sing very loud. Try sound at varing distances,
    or even try to be as quiet as possible & watch the Audio pickup.

    You should see a representation of the sounds (Audio Waveforms)
    in the Serial Plotter window, and the digital data output in the
    Serial Monitor, that the INMP441 Microphone is picking up. You 
    can adjust the “sensitivity” by altering the ‘rangeLimit’ 
    variable at the top of loop().

----------------------------------------------------------------- */
#include <driver/i2s.h>                 // Include the I²S driver

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
  Serial.begin(115200);                 // Initialize the Serial Monitor
  while(!Serial);                       // Wait for Serial Port to open
  Serial.println(" ");
  delay(1000);

  I2S_install();                        // Set up INMP441 I²S Mic
  I2S_setPin();
  i2s_start(I2S_PORT);
  delay(500);
}

void loop() {
  // False print statements will “lock the range” on Serial Plotter.
  // Change this ‘rangeLimit’ value to adjust the “sensitivity”.
  int rangeLimit = 3000;
  Serial.print(rangeLimit * -1);
  Serial.print(" ");
  Serial.print(rangeLimit);
  Serial.print(" ");

  // Get the I²S Data and place it in the Data buffer.
  size_t bytesIn   = 0;
  esp_err_t result = i2s_read(I2S_PORT, &sBuffer, bufferLen, 
                              &bytesIn, portMAX_DELAY);

  if(result == ESP_OK) {
    int16_t samplesRead = bytesIn / 8;
    if(samplesRead > 0) {
      float mean = 0;
      for(int16_t i=0; i < samplesRead; ++i) {
        mean += (sBuffer[i]);
      }
      mean /= samplesRead;             // Average the Data reading.
      Serial.println(mean);            // Print the raw data to the
    }                                  // Serial Monitor, and show 
  }                                    // the “Audio Waveforms” in
}                                      // the Serial Plotter window.

/*******************************************************************
Sketch uses 340830 bytes (16%) of program storage space. 
 aximum is 2097152 bytes.
Global variables use 21292 bytes (6%) of dynamic memory, 
            leaving 306388 bytes for local variables. 
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c

Leaving...
Hard resetting with RTC WDT...

--------------------------------------------------------------------
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
12:21:21.301 -> -3000 3000 16.00
12:21:21.301 -> -3000 3000 -2.87
12:21:21.301 -> -3000 3000 23.12
12:21:21.301 -> -3000 3000 -3.50
12:21:21.301 -> -3000 3000 -0.37
12:21:21.301 -> -3000 3000 15.63
12:21:21.301 -> -3000 3000 -9.88
12:21:21.301 -> -3000 3000 5.12
12:21:21.301 -> -3000 3000 16.25
12:21:21.301 -> -3000 3000 -19.37 ...

Watch the visual “Audio Waveforms” in the Serial Plotter window.
*******************************************************************/
