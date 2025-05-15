# ESP32-S3 1.54in TFT Expansion Board with Speaker (and MIC, and ???)
** WORK IN PROGRESS ** — Prof. Michael P. Harris

## Compatible Development boards:

ESP32-S3 N16R8 Development Board with Speaker and 1.54in TFT Display
Expansion Adapter Kit for DIY AI Type-C Wifi Module ESP32-S3
```
ESP32-S3-WROOM-1 “pin-compliant” Development boards:     Pins   CAM SD RGB LEDs
                                                                       LED
 1. Espressif ESP32-S3-DevKitC-1 (no camera, no SD card)  44            ✓  1+RGB
 2. YD-ESP32-S3 (ESP32-S3-WROOM-1 Dev) (DevKitC-1 clone)  44            ✓  3+RGB
 3. WaveShare ESP32-S3-DEV-KIT-N8R8    (DevKitC-1 clone)  44            ✓  1+RGB
 4. GOOUUU ESP32-S3-CAM     (DevKitC-1 clone + CAM + SD)  40     ✓  ✓  ✓  2+RGB
 5. ESP32-S3-WROOM CAM   (FREENOVE ESP32-S3-WROOM clone)  40     ✓  ✓  ✓  4+RGB
 6. FREENOVE ESP32-S3-WROOM (CAM)                         40     ✓  ✓  ✓  4+RGB
 7. FREENOVE ESP32-S3-WROOM Lite                          40     ✓  ✓  ✓  4+RGB
```

NOTES:

【1】 Espressif ESP-S3-DevKitC-1 — 44-pin (40-pin compatible) headers<br/>
    Header pins(dual on one side) support **both** Dev Board widths.

    (Almost {...extra pins top and bottom} the same pinout as the<br/>
    ESP32-S3-WROOM (CAM), and ESP32-S3-GOOUUU-CAM).
```
Xtensa® 32-bit   ESP32-S3-DevKitC-1         ESP32-S3-WROOM-1 N16R8
Dual-core LX7      _______________
 16MB Flash       |  ___   _   __¯|         NO CAMERA MODULE
  8MB PSRAM       | | | |_| |_|   |         NO SD-CARD
               .——| | |           |——.
         3V3  1|o:|               |:•|44 GND               Hardware
         3V3  2|o:|ESP32S3-WROOM-1|:•|43 G43 TX›           SPI2 HSPI
[RST]    ENT  3|o:|               |:•|42 G44 RX‹           —————————
A3       G4   4|o:| Œ Æ   N16R8   |:o|41 G1  A0            G10 SS
A4       G5   5|o:| .··. .   ____ |:o|40 G2  A1            G11 MOSI
A5       G6   6|o:| WiFi ß  |QRCD||:o|39 G42               G12 SCK
A6       G7   7|o:| °   F©  |____||:o|38 G41               G13 MISO
A14      G15  8|o:'———————————————':o|37 G40
A15      G16  9|o ·. ¨¨|¯¯¯¬        o|36 G39               Software
A16      G17 10|o ¯  ¨¨|   []   PWR ¤|35 G38               SPI -ALT-
A17      G18 11|o ¯  ¨¨|___-     ¤  o|34 G37 PSRAM         —————————
I²C SDA  G8  12|o RGB     ¬ ¬       o|33 G36 PSRAM         G42  SCLK
A2       G3  13|o [¤]48   ¨ ¨       o|32 G35 PSRAM         G41  MOSI
LOG      G46 14|o      ........ ·   o|31 G0  [BOOT]         -1  MISO
I²C SCL  G9  15|o ¨ ¨  |CP2102| ¨   o|30 G45                G0  RST
SPI SS   G10 16|o ¨¨   '''''''' ¨   o|29 G48 RGB LED       G45  DC
SPI MOSI G11 17|o BOOT .......  RST o|28 G47               G47  CS
SPI SCK  G12 18|o 【Ø】  '''~'''  【Ø】 o|27 G21               G21  BL*
SPI MISO G13 19|o                   ø|26 G20 A19 D-
A13      G14 20|o  _____ O T _____  ø|25 G19 A20 D+        I²C -ALT-
         5V0 21|o | USB |T T| USB | o|24 GND               —————————
         GND 22|o |  C  |G L|  C  | o|23 GND               1. *  GND
               '——'ESP32'———'UART0'——'                     2. *  3V3
                                         G48 RGB_BUILTIN,  3. G1 SDA
                                         LED_BUILTIN       4. G2 SCL

ESP32-S3 Pins: 0…18 GPIO, 19…20 D+/D-, 21 GPIO, 22…25 Do Not Exist,
26…32 QSPI ƒlash, 33…34 Missing, 35…42 GPIO, 43…44 TX/RX, 45…48 GPIO
    pins_arduino.h ~ ESP32-S3-DevKitC
```
【2】 MCU 44-pin header pins compatible with:
```
        44-pin ESP32-S3-WROOM-1 Development Boards:
            o ESP-S3-DevKitC-1
            o YD-ESP32-S3
            o ESP32-S3-WROOM-1 Dev
            o WaveShare ESP32-S3-DEV-KIT-N8R8

        40-pin ESP32-S3-WROOM-1 Development Boards
               (skip top & bottom extra pins)
            o ESP-S3-WROOM (CAM)
            o FREEVOVE ESP32-S3-WROOM
            o GOOUUU ESP32-S3-CAM
```
 【3】 LCD 1.54in 240×240 color IPS TFT (ST7789T3) header pins:
```
        TFT LCD   ESP32-S3
         8-Pin    Pin       Function/Description
        ———————   ————————  ——————————————————————————
        1. GND    GND       System Ground
        2. VCC    3V3       Positive Power (3.3V)
        3. SCL    G21       SPI Clock
        4. SDA    G47       SPI Data (MOSI)
        5. RES    G45       TFT Reset
        6. DC     G40       Data/Command Select
        7. CS     G41       SPI Chip Select
        8. BLK    G42       BackLight Control

        TFT LCD   ESP32-S3
        10-Pin    Pin       Function/Description
        ———————   ————————  ——————————————————————————
        1. GND    GND       System Ground
        2. RS     G40       Data/Command Select
        3. CS     G41       SPI Chip Select
        4. SCL    G21       SPI Clock
        5. SDA    G47       SPI Data (MOSI)
        6. RST    G45       TFT Reset
        7. VDD    3V3       Positive Power (3.3V)
        8. GND    GND       System Ground
        9. A      3V3       BackLight LED Anode (+)
       10. K      GND       BackLight LED Cathode (-)
```
【4】 22-pin single-row I/O Interface header: (½ the availiable pins)
```
                         .——Interface Pins absent from I/O header——.
                         | G4 INMP441   Mic   LCD TFT   G37* PSRAM |
    3V3   o  1.          | G5 INMP441   Mic   G42 BLK   G36* PSRAM |
    G1    o  2.          | G6 INMP441   Mic   G41 CS    G35* PSRAM |
    G2    o  3.          |                    G42 BLK              |
    G39   o  4.          | G7 MAX98357A Amp   G41 CS    G8  I²C SDA|
    G38   o  5.          |G15 MAX98357A Amp   G40 DC    G9  I²C SCL|
    G0    o  6.  BOOT    |G16 MAX98357A Amp   G45 RES   G42 BMA423 |
    G48   o  7.  RGB LED |                    G47 SDA       3-Axis |
    G20   o  8.  USB_D-  |G38 ???, G39 ???    G21 SCL       IRQ    |
    G19   o  9.  USB_D+  '—————————————————————————————————————————'
    G17   o 10.  ---------------------------------------------------
    G18   o 11.             {Pins  10..22 I/O header}
    G8    o 12.  I²C SDA    {match 10..22 MCU header}
    G11   o 17.  SPI MOSI
    G12   o 18.  SPI SCK
    G13   o 19.  SPI MISO
    G3    o 13.
    G46   o 14.
    G9    o 15.  I²C SCL
    G10   o 16.  SPI SS
    G14   o 20.
    5V0   o 21.
    GND   o 22.
```
【5】 Microphone “pass-through” hole & icon on top-side:
```
        o PDM Mic chip mounted on the bottom-side.
        o (guess) MEMS digital microphone (INMP441)
        o possible configuration:
            WS  Data Select         G4
            SCK Data Clock          G5
            SD  Data Out            G6
            VCC                     3V3 Vin
            GND Ground Short Connect L/R Left Right Channel
```
【6】 Large on-board Speaker on top: (guess — with amplifier)
```
        o (guess) I²S interface, possibly I²S MAX98357A Audio
        o possible MAX98357A Amplifier configuration:
            DIN Digital Signal      G7
            BCLK Bit Clock          G15
            LRC Left Right Clock    G16
            VCC                     3V3 Vin
            GND  GND Ground Short Connect
                 GAIN Gain and Channel

        o External Speaker interface
            Audio+  Connect to Speaker Positive (usually Red wire)
            Audio-  Connect to Speaker Negative
```
【7】 Additional peripheral chip mounted on the bottom side:
```
        o (guess) by inspection an I²C BMA423 3-Axis sensor.
        o possible configuration:
            I²C SDA     G8
            I²C SCL     G9
            IRQ         G14
```
———————————————————————————————————————————————————————————————————

LCD TFT Display Specifications:
```
LCD 1.54in 240×240 color IPS TFT 10-pin (ST7789T3)
  ◆          Brand Name: Maithoga
  ◆           Driver IC: ST7789T3
  ◆                Size: 1.54in color
  ◆    Number of Pixels: 240(RGB)×240
  ◆  Driver IC RAM Size: 240×16×240
  ◆      Display Colors: 262K
  ◆      Interface Pins: 10-Pin
  ◆      Data Interface: SPI interface
  ◆           Backlight: White LED Parallel
  ◆      Polarizer Mode: Normally Black, Transmissive
  ◆   Viewing Direction: ALL O’clock
  ◆      Contrast Ratio: 300
  ◆           Luminance: 180 cd/m2
  ◆       Input Voltage: 3V
  ◆          Dimensions: 31.52×33.72×1.96mm
  ◆         Active Area: 27.72×27.72mm
  ◆      Operating Temp: -20° ~ 70°
  ◆ Storage Temperature: -30° ~ 80°

  ◆ Display 10-pin SPI Interface:
        1. GND  (Ground)
        2. RS   (Data/Command)
        3. CS   (Chip Select)
        4. SCL  (SPI SCK)
        5. SDA  (SPI MOSI)
        6. RST  (Reset)
        7. VDD  (3V3)
        8. GND  (Ground)
        9. A    (LED Anode)
       10. K    (LED Cathode)
```
