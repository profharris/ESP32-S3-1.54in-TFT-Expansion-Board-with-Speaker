/******************************************************************
 * Filename    : YD-ESP32-S3_Blink.ino                            *
 * Description : Make the Green TX_LED and Blue RX_LED Blink.     *
 *                                                                *
 *       Board : ESP32S3 Dev Module                               *
 ******************************************************************/

/*******************************************************************
ESP32-S3-WROOM-1 Dev (YD-ESP32-S3)                ESP32S3 Dev Module
    Same pinout as ESP32-S3-DevKitC-1, except 1-pin space wider.
    Almost (with extra pins top & bottom) the same pinout as the
    ESP32-S3-WROOM (CAM Module), and ESP32-S3-CAM.

Xtensa® 32-bit           YD-ESP32-S3     ESP32-S3-WROOM-1 N8R2
dual-core LX7          _______________
240MHz, 512KB SRAM    |  ___   _   __¯|      NO CAMERA MODULE
8MB ƒlash, 2MB PSRAM  | | | |_| |_|   |      NO SD-CARD
WiFi/BLE®5         .——| | |           |——.
             3V3  1|o:|               |:o|44 GND
             3V3  2|o:|ESP32S3-WROOM-1|:o|43 GPIO43 TX›[U0TXD  ]
[RESET  ] EN/RST  3|o:| Œ Æ   N8R2    |:o|42 GPIO44 RX‹[U0RXD  ]
[A3   T4] GPIO4   4|o:| .··. .   ____ |:o|41 GPIO1  SDA[A0   T1]
[A4   T5] GPIO5   5|o:| WiFi ß  |QRCD||:o|40 GPIO2  SCL[A1   T2]
[A5   T6] GPIO6   6|o:| F©      |____||:o|39 GPIO42    [   MTMS]
[A6   T7] GPIO7   7|o:'———————————————':o|38 GPIO41    [   MTDI]
[A14    ] GPIO15  8|o:                 :o|37 GPIO40    [   MTDO]
[A15    ] GPIO16  9|o  :: ‡‡‡    · RST  o|36 GPIO39    [   MTCK]
[A16    ] GPIO17 10|o  ¨¨|¯¯¯¬   : [Ø]  o|35 GPIO38    [       ]
[A17    ] GPIO18 11|o  ¨¨|LDO[]  : BOOT •|34 GPIO37    [PSRAM •]
[A7  SDA] GPIO8  12|o  ¨¨|___- ¬¬  [Ø]  •|33 GPIO36    [PSRAM •]
[A2   T3] GPIO3_ 13|o  ·  ‡‡‡  ¨¨P      •|32 GPIO35    [PSRAM •]
[IN ONLY] GPIO46_14|o      RGB   w T R  o|31 GPIO0_    [BOOT   ]
[A8  SCL] GPIO9  15|o  RGB CTRL  R X X  o|30 GPIO45_   [   VSPI]
[A9  T10] GPIO10 16|o +[¤]  ¥    ¤ ¤ ¤  ¤|29 GPIO48 RGB[WS2812*]
[A10 T11] GPIO11 17|o           ··· ___ o|28 GPIO47    [       ]
[A11 T12] GPIO12 18|oIN-OUT ‡‡‡ :::|343|o|27 GPIO21    [       ]
[A12 T13] GPIO13 19|o ¥            |___|ø|26 GPIO20    [A19  D+]
[A13 T14] GPIO14 20|o .......O T....... ø|25 GPIO19    [A18  D—]
[ IN-OUT]    5V0 21|o | USB |T T| USB | o|24 GND
             GND 22|o |  C  |G L|  C  | o|23 GND
                   '——'ESP32'———'UART0'——'
                                             GPIO48 RGB_BUILTIN,
Red PWR LED, Green TX LED, Blue RX LED              LED_BUILTIN

ESP32-S3 Pins: 0…18 GPIO, 19…20 D+/D-, 21 GPIO, 22…25 Do Not Exist,
26…32 QSPI ƒlash, 33…34 N/A, 35…42 GPIO, 43…44 TX/RX, 45…48 GPIO.
    pins_arduino.h ~ ESP32-S3-DevKitC
*******************************************************************/

/*******************************************************************
Type-C USB cable plugged into the right-side TTL/UART port.

Arduino IDE > Tools                                  [CONFIGURATION]
                   Board: "ESP32S3 Dev Module"
         USB CDC On Boot: "Disabled"  * Sketch locks up if ENABLED *
           CPU Frequency: "240MHz (WiFi)"
         USB DFU On Boot: "Disabled"
              Flash Mode: "QIO 80MHz"
              Flash Size: "8MB 64Mb"
USB Firmware MSC On Boot: "Disabled"
          Partion Scheme: "8MB with spiff (3MB APP/1.5MB SPIFFS)"
                   PSRAM: "OPI PSRAM"
*******************************************************************/

// The YD-ESP32-S3 (ESP32-S3-WROOM-1 Dev) and its’ clones, have
// four LEDs, instead of five like the ESP32-S3-WROOM (CAM).
// There is no GPIO2 LED_BUILTIN. The RGB NeoPixel (GPIO48) is
// both LED_BUILTIN & RGB_BUILTIN.
//
// So, For this ‘Blink’ sketch, we will Blink the Green TX_LED
// and Blue RX_LED.

// Power LED                        // Red   LED    (left)
#define TX_LED         43           // Green LED    (middle)
#define RX_LED         44           // Blue  LED    (right)
//#define RGB_BUILTIN  48           // RGB NeoPixel (far left)

void setup(void) {
  Serial.begin(15200);              // Serial Monitor
  while(!Serial);                   // wait for Serial Port to open

  // The TX_LED & RX_LED are wired inverted, so HIGH = Off
  pinMode(TX_LED,      OUTPUT);     // initialize the Green TX_LED
  pinMode(RX_LED,      OUTPUT);     // initialize the Blue  RX_LED
  digitalWrite(TX_LED, HIGH);       // turn the TX_LED Off(inverted)
  digitalWrite(RX_LED, HIGH);       // turn the RX_LED Off(inverted)
//neopixelWrite(RGB_BUILTIN,0,0,0); // turn the RGB_BUILTIN Off
  delay(500);                       // wait 1/2 second

  Serial.println(F("YD-ESP32-S3 (ESP32-S3-WROOM-1 Dev)"));
  Serial.println(F("Blink the Green TX_LED and Blue RX_LED"));
}

void loop() {
  Serial.println(F("Blink!"));
  digitalWrite(TX_LED, LOW);        // turn the TX LED On(inverted)
  digitalWrite(RX_LED, LOW);        // turn the RX LED On(inverted)
  delay(500);                       // wait 1/2 second
  digitalWrite(TX_LED, HIGH);       // turn the TX LED Off(inverted)
  digitalWrite(RX_LED, HIGH);       // turn the RX LED Off(inverted)
  delay(500);                       // wait 1/2 second
}

/*******************************************************************
NOTE: We are initializing GPIO43 TX_LED and GPIO44 RX_LED pinMode()
¯¯¯¯¯ as ‘OUTPUT’; and sending HIGH and LOW values to the LEDs
      attached to the TX & RX GPIOs. The Serial Monitor, which also
      uses these GPIOs still functions! Chech out the Serial Monitor
      to see the message “Blink!” every 1/2 second cycle...

      BUT, whilethe Green TX_LED Blinks normally, the Blue RX_LED
      blinks dimly. This due to the RX Pin being inherently INPUT.
      BTW, if we attempt to Blink these LEDs alternatingly...

  digitalWrite(TX_LED, LOW);        // turn the TX LED On(inverted)
  digitalWrite(RX_LED, HIGH);       // turn the RX LED Off(inverted)
  delay(500);                       // wait 1/2 second
  digitalWrite(TX_LED, HIGH);       // turn the TX LED Off(inverted)
  digitalWrite(RX_LED, LOW);        // turn the RX LED On(inverted)
  delay(500);

      then the Blue RX_LED dimly stays lit, and does not Blink.

      Does this mean we can incorporate the the Green TX_LED into
      our sketches, without interfearing with the UART output to
      the Serial Monitor?
*******************************************************************/

/*******************************************************************
Sketch uses 329966 bytes (25%) of program storage space.
Maximum is 1310720 bytes.
Global variables use 21020 bytes (6%) of dynamic memory,
            leaving 306660 bytes for local variables. 
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c
...
Leaving...
Hard resetting via RTS pin...

————————————————————————————————————————————————————————————————————
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
ESP-ROM:esp32s3-20210327

YD-ESP32-S3 (ESP32-S3-WROOM-1 Dev)
Blink the Green TX_LED and Blue RX_LED
Blink!
Blink!
Blink!
...
*******************************************************************/
