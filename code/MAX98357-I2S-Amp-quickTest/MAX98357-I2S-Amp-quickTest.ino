/* MAX98357-I2S-Amp-quickTest.ino
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *      Quick Test: Send 440Hz Sine Waves to the MAX98357A/Speaker.
 *      https://www.kincony.com/forum/showthread.php?tid=6898
 *
——————————————————————————————————————————————————————————————————— ————————————
YD-ESP32-S3 (ESP32-S3-WROOM-1 Dev)  (44-Pin)    ESP32-S3 Dev Module   I²C QWIIC
                                                                    ————————————
Xtensa® 32-bit         ESP32-S3-DevKit-C-1  ESP32-S3-WROOM-1 N16R8  1   *   GND
dual-core LX7               YD-ESP32-S3                             2   *   3V3
240MHz,  512KB SRAM       _______________   NO CAMERA MODULE        3 GPIO8 SDA
8MB ƒlash, 2MB PSRAM     |  ___   _   __¯|  NO SD-CARD              4 GPIO9 SCL
WiFi 802.11 b/g/n        | | | |_| |_|   |  GPIO_ = Strapping Pins
BLE®5                 .——| ' '           |——.                       ————————————
               3V3   1|o:|ESP32S3-WROOM-1|:o|44 GND                 Hardware SPI
               3V3   2|o:|               |:¤|43 IO43 [U0TXD›   LED] microSD_Card
[RESET/RST   ] EN    3|o:| .··. . F© Œ Æ |:¤|42 IO44 [U0RXD‹   LED] ————————————
[I²S Mic WS  ] IO4   4|o:| WiFi ß   ____ |:o|41 IO1  [A0          ] GPIO10 CS
[I²S Mic SCK ] IO5   5|o:|         |QRCD||:o|40 IO2  [A1          ] GPIO11 MOSI
[I²S Mic SD  ] IO6   6|o:| ° N16R8 |____||:o|39 IO42 [SPI TFT BL  ] GPIO12 SCK
[I²S Amp DIN ] IO7   7|o:'———————————————':o|38 IO41 [SPI TFT CS  ] GPIO13 MISO
[I²S Amp BCLK] IO15  8|o:                 :o|37 IO40 [SPI TFT DC  ]
[I²S Amp LRC ] IO16  9|o  :: ‡‡‡    · RST  o|36 IO39 [   Volume UP] ————————————
[A16         ] IO17 10|o  ¨¨|¯¯¯¬   : [Ø]  o|35 IO38 [   Volume DN] 1.54in  TFT
[A17         ] IO18 11|o  ¨¨|LDO[]  : BOOT •|34 IO37 [PSRAM      •] 240×240 IPS
[A7  I²C SDA ] IO8  12|o  ¨¨|___- ¬¬  [Ø]  •|33 IO36 [PSRAM      •] ————————————
[A2          ] IO3_ 13|o  ·  ‡‡‡  ¨¨       •|32 IO35 [PSRAM      •] GPIO42 BL
[IN ONLY     ] IO46_14|o      RGB   P T R  o|31 IO0_ [BOOT      OK] GPIO41 CS
[A8  I²C SCL ] IO9  15|o  RGB CTRL  R X X  o|30 IO45_[SPI TFT RST ] GPIO40 DC
[A9  SPI CS  ] IO10 16|o  [¤]  ¥    ¤ ¤ ¤  ¤|29 IO48 [RGB WS2812¤ ] GPIO45 RST
[A10 SPI MOSI] IO11 17|o           ··· ___ o|28 IO47 [SPI TFT MOSI] GPIO47 MOSI
[A11 SPI SCK ] IO12 18|oIN-OUT ‡‡‡ :::|343|o|27 IO21 [SPI TFT SCLK] GPIO21 SCLK
[A12 SPI MISO] IO13 19|o ¥            |___|ø|26 IO20 [A19       D⧾]
[A13         ] IO14 20|o  _____ O T _____  ø|25 IO19 [A18       D⧿] ————————————
[      IN-OUT]  5V0 21|o | USB |T T| USB | o|24 GND                 INMP441 Mic
                GND 22|o |  C  |G L|  C  | o|23 GND                 ————————————
                      '——'ESP32'———'UART0'——'                       GPIO4  WS
                                                IO48 RGB_BUILTIN,   GPIO5  SCK
Red PWR LED, Green TX LED, Blue RX LED               LED_BUILTIN    GPIO6  SD

 1.  INMP441  I²S Microphone            3. 1.54in 240×240 TFT       ————————————
 2. MAX98357A I²S Audio Amp/Speaker     4. SPI microSD_Card          MAX98357A
                                                                      I²S Amp
ESP32-S3 Pins: 0…18 GPIO, 19…20 D+/D-, 21 GPIO, 22…25 Do Not Exist, ————————————
26…32 QSPI ƒlash, 33…34 N/A, 35…42 GPIO, 43…44 TX/RX, 45…48 GPIO.   GPIO7  DIN
 pins_arduino.h ~ ESP32-S3-DevKitC-1                                GPIO15 BCLK
——————————————————————————————————————————————————————————————————— GPIO16 LRC
 *
 * Requires a MAX98357A I²S Audio Amplifier/Speaker
 *
 * NOTE¹:  You will NOT hear the 440Hz Sine Wave tone until
 * ¯¯¯¯¯¯  you open the Serial Monitor!
 *
 * NOTE²:  To stop the 440Hz Sine Wave tone, unplug the USB Data
 * ¯¯¯¯¯¯  cable, --or better yet, press and hold the [BOOT] button,
 *         press then release the [RESET] button, now release the
 *         [BOOT] button... This puts your ESP32-S3 into “Bootloader
 *         Mode”, waiting to be flashed with new firmware.
 *
 * NOTE³:  DO NOT use the old ‘<I2S.h>’ library with an ESP32-S3.
 * ¯¯¯¯¯¯  On the ESP32-S3, equivalent functionality for I²S
 *         communication is provided by the Espressif ESP-IDF I²S
 *         library: “<driver/i2s.h>”. NOTE the Uppercase/lowercase
 *         difference, this is important.
 *
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
 * MAX98357 I²S Audio Amp           ESP32-S3-WROOM-1
 * 1. VIN  (Power)              --> 3V3
 * 2. GND                       --> GND
 * 3. SD   (L/R Channel Select) --> Connect to 3V3 (select Right)
 * 4. GAIN                      --> Connect to GND (12 dB Gain)
 * 5. DIN  (Serial Data In/Out) --> GPIO7
 * 6. BCLK (Bit Clock)          --> GPIO15
 * 7. LRC  (Left Right Clock)   --> GPIO16
 *
 *    External Speaker Interface: (⧾ ⧿)
 *    Audio⧾  Connect to Speaker Positive (usually Red wire)
 *    Audio⧿  Connect to Speaker Negative
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
              Flash Size: "8MB 64Mb"     ...check your board!
USB Firmware MSC On Boot: "Disabled"
        Partition Scheme: "16M Flash (2MB APP/12.5MB FATFS)"  【or】
        Partition Scheme: "8MB with spiffs (3MB APP/1.5MB SPIFFS)"
                   PSRAM: "OPI PSRAM"
             Upload Mode: "UART0/Hardware CDC"
            Upload Speed: "115200"
                USB Mode: "Hardware CDC and JTAG"
*******************************************************************/

#include <Arduino.h>            // Include required libraries
#include <driver/i2s.h>         // Include newer ESP-IDF I²S library
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
    .ws_io_num    = I2S_LRC,            // Word Select|Left Right Clock
    .data_out_num = I2S_DOUT,           // Serial Data line, Data Out
    .data_in_num  = I2S_PIN_NO_CHANGE   // not used
  };
  i2s_set_pin(I2S_PORT, &pin_config);
}

void setup() {
  Serial.begin(115200);             // Initialize the Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  // NOTE:  You will not hear the 440Hz Sine Wave tone until
  // ¯¯¯¯¯  you open the Serial Monitor!

  Serial.println("Send 440Hz Sine Waves to the MAX98357A Amplifier/Speaker");

  i2s_install();                    // Set up I²S for Transmit only
  i2s_setpin();                     // Set up MAX98357A Audio Amp
  i2s_start(I2S_PORT);
  Serial.println("MAX98357A I²S driver installed.\n");
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

  // SPECIAL NOTE: To stop the 440Hz Sine Wave tone, unplug the USB
  // ¯¯¯¯¯¯¯¯¯¯¯¯¯ Data cable, --or better yet-, press and hold the
  //               [BOOT] button, press then release the [RESET]
  //               button, now release the [BOOT] button...
  //               This puts your ESP32-S3 into “Bootloader Mode”,
  //               waiting to be flashed with new firmware.

  //i2s_stop(I2S_PORT);             // Stop the MAX98357A I²S driver
}

/*******************************************************************
Sketch uses 344038 bytes (16%) of program storage space.
Maximum is 2097152 bytes.
Global variables use 21164 bytes (6%) of dynamic memory,
            leaving 306516 bytes for local variables. 
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
01:31:08.758 -> Send 440Hz Sine Waves to the MAX98357A Amplifier/Speaker
01:31:08.758 -> MAX98357A I²S driver installed.

*******************************************************************/
