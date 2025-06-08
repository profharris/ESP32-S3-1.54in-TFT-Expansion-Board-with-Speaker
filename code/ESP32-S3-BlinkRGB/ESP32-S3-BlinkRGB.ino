/* ESP32-S3-BlinkRGB.ino
 * ESP32-S3-WROOM (CAM Module) | ESP32-S3-CAM | ESP32-S3-N16R8
 *
 * Demonstrate usage of the onboard RGB LED (NeoPixel) on most
 * ESP32-S3 Dev boards.
 * https://github.com/espressif/arduino-esp32/blob/114965010529c004ce914fea773095274ea2ce4d/libraries/ESP32/examples/GPIO/BlinkRGB/BlinkRGB.ino#L25-L37
 * 
 * Calls to digitalWrite(RGB_BUILTIN, HIGH)
 *   ...will use the hidden RGB driver.
 *
 * the older neopixelWrite() command has been replaced by:
 * rgbLedWrite(uint8_t Pin, uint8_t R, uint8_t G, uint8_t B)
 *
 * rgbLedWrite demonstrates controll of all 3 RGB color channels.
 * Example:  rgbLedWrite(RGB_BUILTIN, Red, Green, Blue)
 *
 *  NOTE: The ColorOrder is “RGB”, NOT BGR as in some ESP32s'.
 */

/*******************************************************************
Type-C USB Data cable is plugged into the Right-side USB-UART port.
                                          ¯¯¯¯¯¯¯¯¯¯ ¯¯¯¯¯¯¯¯
Arduino IDE > Tools                                  [CONFIGURATION]
                   Board: "ESP32S3 Dev Module"
         USB CDC On Boot: "Disabled"  * Sketch locks up if ENABLED *
           CPU Frequency: "240MHz (WiFi)"
         USB DFU On Boot: "Disabled"
              Flash Mode: "QIO 80MHz"
              Flash Size: "16MB 128Mb"  -or-
              Flash Size: "8MB 64Mb"   check your board!
USB Firmware MSC On Boot: "Disabled"
        Partition Scheme: "16M Flash (2MB APP/12.5MB FATFS)"  -or-
        Partition Scheme: "8MB with spiffs (3MB APP/1.5MB SPIFFS)"
                   PSRAM: "QSPI PSRAM"
             Upload Mode: "UART0/Hardware CDC"
            Upload Speed: "115200"
                USB Mode: "Hardware CDC and JTAG"
*******************************************************************/

//#define RGB_BUILTIN 48    // DO NOT REDEFINE RGB_BUILTIN
                            // If so, digitalWrite() will not work.
                             
#ifdef  RGB_BRIGHTNESS      // if RGB_BRIGHTNESS is defined...
#undef  RGB_BRIGHTNESS      // un-define it
#define RGB_BRIGHTNESS 10   // Change color brightness (max 255)
#endif

void setup() {
  Serial.begin(115200);             // Initialize Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  // No need to initialize the RGB LED!  
  rgbLedWrite(RGB_BUILTIN, 0,0,0);  // Make sure RGB NeoPixel is Off
}

void loop() {
  // Blink the RGB LED (White),
  // use the hidden RGB driver built into digitalWrite()
  Serial.println("Blink White!");
  digitalWrite(RGB_BUILTIN, HIGH);  // Turn On the RGB LED (White)
  delay(1000);
  digitalWrite(RGB_BUILTIN, LOW);   // Turn Off the RGB LED
  delay(1000);

  // Now let's Blink the Neopixel RGB LED in COLOR!
  Serial.print("Blink Red!... ");
  rgbLedWrite(RGB_BUILTIN,RGB_BRIGHTNESS,0,0);  // Red
  delay(1000);
  Serial.print("Blink Green!... ");
  rgbLedWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0);  // Green
  delay(1000);
  Serial.println("Blink Blue!\n");
  rgbLedWrite(RGB_BUILTIN,0,0,RGB_BRIGHTNESS);  // Blue
  delay(1000);
  rgbLedWrite(RGB_BUILTIN,0,0,0);               // OFF
  delay(1000);
}

/*******************************************************************
Sketch uses 323144 bytes (15%) of program storage space. 
  Maximum is 2097152 bytes.
Global variables use 20052 bytes (6%) of dynamic memory, 
  leaving 307628 bytes for local variables. Maximum is 327680 bytes.
esptool.py v4.8.1
Serial port COM6
Connecting.....
Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: cc:ba:97:05:10:8c
Uploading stub...
Running stub...
Stub running...
Configuring flash size...
Erasing flash (this may take a while)...
Chip erase completed successfully in 3.5 seconds.
Compressed 20160 bytes to 12987...
Writing at 0x00000000... (100 %)
Wrote 20160 bytes (12987 compressed) at 0x00000000 in 1.3 seconds 
  (effective 127.8 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 143...
Writing at 0x00008000... (100 %)
Wrote 3072 bytes (143 compressed) at 0x00008000 in 0.0 seconds 
  (effective 834.8 kbit/s)...
Hash of data verified.
Compressed 8192 bytes to 47...
Writing at 0x0000e000... (100 %)
Wrote 8192 bytes (47 compressed) at 0x0000e000 in 0.0 seconds 
  (effective 2149.3 kbit/s)...
Hash of data verified.
Compressed 323248 bytes to 173462...
Writing at 0x00010000... (9 %)
Writing at 0x0001c196... (18 %)
Writing at 0x000289b0... (27 %)
Writing at 0x0002e12e... (36 %)
Writing at 0x00033c74... (45 %)
Writing at 0x00039417... (54 %)
Writing at 0x0003ec21... (63 %)
Writing at 0x000448ab... (72 %)
Writing at 0x0004a18e... (81 %)
Writing at 0x000553ae... (90 %)
Writing at 0x0005b46a... (100 %)
Wrote 323248 bytes (173462 compressed) at 0x00010000 in 15.4 seconds 
  (effective 168.2 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
*******************************************************************/

/* -----------------------------------------------------------------
Serial Monitor:

17:16:58.393 -> ESP-ROM:esp32s3-20210327

Blink White!
Blink Red!... Blink Green!... Blink Blue!

Blink White!
Blink Red!... Blink Green!... Blink Blue!

Blink White!
Blink Red!... Blink Green!... Blink Blue!
...
----------------------------------------------------------------- */
