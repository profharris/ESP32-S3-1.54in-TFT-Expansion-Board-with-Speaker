# ESP32-S3 1.54in TFT Expansion Board with Speaker
## _(with I²S INMP441 Microphone, & I²S MAX98357A Audio Amplifier)_

***A WORK IN PROGRESS*** &nbsp; &nbsp; Prof. Michael P. Harris &nbsp; &nbsp; *06/07/2025*<br/>
[GitHub Pages](https://pages.github.com/)<br/>
<br/>

> ***AI Chatbot*** compatible!&nbsp;
> https://docs.keyestudio.com/projects/ESP32S3_LCD154/en/latest/LCD154/LCD154.html <br/>
> Ask anything, get answers on the go! This project can be a portable,
> low-power AI assistant that works in real-time using just a single
> ESP32-S3, a mic, and a speaker. It can listens to your voice, processes
> your questions through Google’s Gemini AI API, and responds with an
> answer via tech-to-speech.

ESP32-S3 1.54in TFT Expansion Board with Speaker
![ESP32-S3 1.54in TFT Expansion Board with Speaker](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%201.54in%20TFT%20Expansion%20Board%20with%20Speaker-1.jpg)


## Compatible Development boards:&nbsp; &nbsp; _(8 and counting...)_

ESP32-S3 N16R8 Development Board with Speaker and 1.54in TFT Display<br/>
&nbsp; &nbsp; &nbsp; Expansion Adapter Kit for DIY AI Type-C Wifi Module ESP32-S3

```
ESP32-S3-WROOM-1 “pin-compliant” Development boards:     Pins   CAM SD RGB LEDs
                                                                       LED
 1. Espressif ESP32-S3-DevKitC-1 (no camera, no SD card)  44            ✓  1+RGB
 2. YD-ESP32-S3 (ESP32-S3-WROOM-1 Dev) (DevKitC-1 clone)  44            ✓  3+RGB
 3. WeAct Studio ESP32-S3-A/B Core     (DevKitC-1 clone)  44            ✓  1+RGB
 4. WaveShare ESP32-S3-DEV-KIT-N8R8    (DevKitC-1 clone)  44            ✓  1+RGB

 5. GOOUUU ESP32-S3-CAM     (DevKitC-1 clone + CAM + SD)  40     ✓  ✓  ✓  2+RGB
 6. ESP32-S3-WROOM CAM   (FREENOVE ESP32-S3-WROOM clone)  40     ✓  ✓  ✓  4+RGB
 7. FREENOVE ESP32-S3-WROOM (CAM)                         40     ✓  ✓  ✓  4+RGB
 8. FREENOVE ESP32-S3-WROOM-Lite (no camera)              40            ✓  4+RGB
```
> [1. Espressif ESP32-S3-DevKitC-1](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/1.%20ESP32-S3-DevKitC-1%20(44-pins).jpg)<br/>
> [2. YD-ESP32-S3 (ESP32-S3-WROOM-1 Dev)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/2.%20YD-ESP32-S3%20(ESP32-S3-DevKitC-1%20clone)%20(44-pins).jpg)<br/>
> [3. WeAct Studio ESP32-S3-A/B Core](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/3.%20WeAct%20Studio%20ESP32-S3-AB%20Core%20(44-pins).jpg)<br/>
> [4. WaveShare ESP32-S3-DEV-KIT-N8R8](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/4.%20WaveShare%20ESP32-S3-DEV-Kit-N8R8%20(44-pins).jpg)<br/>
><br/>
> [5. GOOUUU ESP32-S3-CAM](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/5.%20GOOUUU%20ESP32-S3-CAM%20(40-pins).jpg)<br/>
> [6. ESP32-S3-WROOM (CAM)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/6.%20ESP32-S3-WROOM%20(CAM)%20(40-pins).jpg)<br/>
> [7. FREENOVE ESP32-S3-WROOM (CAM)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/7.%20FREENOVE%20ESP32-S3-WROOM%20(CAM)%20(40-pins).jpg)<br/>
> [8. FREENOVE ESP32-S3-WROOM-Lite](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/8.%20FREENOVE%20ESP32-S3-WROOM-Lite%20(40-pins).jpg)


## NOTES: ##

### Quick Wiring Guide:

 1. Wiring between ESP32-S3-WROOM-1 Development Board and the &nbsp; ***ST7789 1.54” 240×240 TFT Display:***

 | ESP32-S3 Dev Board | ST7789 1.54” 240×240 TFT   |
 |-------------------:|----------------------------|
 |     GND            | 1. GND                     |
 |     3V3            | 2. VDD (Power)             |
 |     GPIO21         | 3. SCL SPI Clock    (SCLK) |
 |     GPIO47         | 4. SDA SPI Data     (MOSI) |
 |     GPIO45         | 5. RES TFT Reset     (RST) |
 |     GPIO40         | 6. RS  Data/Command   (DC) |
 |     GPIO41         | 7. CS  Chip Select    (CS) |
 |     GPIO42         | 8. BLK BackLight      (BL) |

 > [LCD 1.54in 240RGB×240 IPS TFT (ST7789) Wiring Diagram](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/LCD%201.54in%20240RGB×240%20IPS%20TFT%20(ST7789)%20Wiring%20Diagram.png)
<br/>

 2. Wiring between ESP32-S3-WROOM-1 Development Board and the &nbsp; ***I²S INMP441 Microphone:***

| ESP32-S3 Dev Board  | I²S INMP441 Microphone    |
|--------------------:|---------------------------|
|     GND  (LOW=Left) | 1. L/R Left/Right Channel |
|     GPIO4           | 2. WS  Data Select        |
|     GPIO5           | 3. SCK Data Clock         |
|     GPIO6           | 4. SD  Data Out           |
|     3V3             | 5. VDD (Power)            |
|     GND             | 6. GND                    |

The `L/R pin` &nbsp;(Left/Right) Channel Selection works as follows:<br/>
   > LEFT &nbsp;– connect L/R to GND.<br/>
   > RIGHT – connect L/R to VDD.

> [INMP441 I²S MEMS Mic Wiring Diagram](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/INMP441%20I%C2%B2S%20MEMS%20Mic%20Wiring%20Diagram.png)
<br/>

 3. Wiring between ESP32-S3-WROOM-1 Development Board and the &nbsp; ***I²S MAX98357A Amplifier/Speaker:***

| ESP32-S3 Dev Board | I²S MAX98357A Amplifier/Speaker |
|-------------------:|---------------------------------|
|    3V3             | 1. VIN                          |
|    GND             | 2. GND                          |
|    VIN (0Ω = Left) | 3. SD (L/R Channel Select)      |
|    GND (12dB Gain) | 4. GAIN (Signal Amp)            |
|    GPIO7           | 5. DIN  Digital Signal In       |
|    GPIO15          | 6. BCLK Bit Clock               |
|    GPIO16          | 7. LRC  Left Right Clock        |
|                    |                                 |
|    Audio +         | Speaker Positive  (+)           |
|    Audio -         | Speaker Negative  (-)           |

> [MAX98357A I²S Amp Wiring Diagram](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/MAX98357A%20I²S%20Amp%20Wiring%20Diagram.png)
<br/>

 4. _(Optional)_&nbsp; Wiring between ESP32-S3-WROOM-1 Development Board and the &nbsp; ***SPI microSD_Card:***

| ESP32-S3 Dev Board | SPI microSD_Card pins  |
|-------------------:|------------------------|
|     3V3            | 1. 3V3  (Power)        |
|     GPIO10         | 2. CS   <br/>(Chip Select)  |
|     GPIO11         | 3. MOSI <br/>(SPI SDI)      |
|     GPIO12         | 4. CLK  <br/>(SPI Clock)    |
|     GPIO13         | 5. MISO <br/>(SPI SDO)      |
|     GND            | 6. GND                 |

> **NOTE¹:**&nbsp; Micro SD Card (size: less than 2G), Micro SDHC Card (size: less than 32G).
<br/>

 5. _(Optional)_&nbsp; Wiring between ESP32-S3-WROOM-1 Development Board and an I²C interface & OLED Display:<br/>
    (STEMMA-Qt/Qwiic I²C interface)

| ESP32-S3 Dev Board | I²C 0.96" 128×64 OLED  | Qwiic Wire Color |
|-------------------:|------------------------|------------------|
|     GND            | 1. GND                 | Black            |
|     3V3            | 2. VDD (Power)         | Red              |
|     GPIO8          | 4. SDA I²C Data  (SDA) | Blue             |
|     GPIO9          | 3. SCL I²C Clock (SCL) | Yellow           |

> **NOTE²:**&nbsp; There are hundreds of STEMMA-Qt/Qwiic I²C sensors availiable.<br/>
> [Introducing Qwiic / Stemma-Qt](https://learn.adafruit.com/introducing-adafruit-stemma-qt)<br/>
> [Adafruit Stemma-QT/Qwiic I²C sensors & devices](https://www.adafruit.com/category/1018)<br/>
> [SparkFun Stemma-QT/Qwiic I²C sensors & devices](https://www.sparkfun.com/catalogsearch/result/?q=Qwiic)
<br/>

 6. _(Optional)_&nbsp; Wiring between ESP32-S3-WROOM-1 Development Board and additional Buttons:<br/>
    _(Most ESP32-S3 Dev Boards have two Button on-board,&nbsp; **RESET** and **BOOT**)_

| ESP32-S3 Dev Board | Buttons                                       |
|-------------------:|-----------------------------------------------|
|     GPIO0          | **BOOT Button**. Can also be used as a<br/>“Wake/Interrupt” button. (connected to GND) |
|     GPIO39         | **Volume Up**. (shorts to GND), Short press<br/>Increases volume, Long press for Max volume. |
|     GPIO38         | **Volume Dn**. (shorts to GND), Short press<br/>Reduces volume, Long press Mutes.            |

> **NOTE³:**&nbsp; The [WeAct Studio ESP32-S3-A/B Core](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/3.%20WeAct%20Studio%20ESP32-S3-AB%20Core%20(44-pins).jpg)
> Dev Board already has a third button, at GPIO45 _(TFT Reset)_.
>
> [Expansion Board with Speaker - Buttons Wiring Diagram](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%20Expansion%20Board%20with%20Speaker%20Buttons%20Wiring%20Diagram.png)
<hr><br/>

### 【1】 Espressif ESP-S3-DevKitC-1 — &nbsp;44-pin &nbsp;_(40-pin compatible)_&nbsp; ***Header pins***

**Header pins** _(dual on one side)_&nbsp; supports **both** ESP32-S3 Development Board widths…<br/>
<br/>
Almost _{...extra pins top and bottom}_ the same pinout as the<br/>
ESP32-S3-WROOM (CAM), &nbsp;and&nbsp; ESP32-S3-GOOUUU-CAM, etc.

![ESP32-S3 1.54in TFT Expansion Board with Speaker - header pins](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%201.54in%20TFT%20Expansion%20Board%20with%20Speaker-1.2.jpg)

```
               ESP32-S3 1.54in TFT Expansion Board with Speaker
Xtensa® 32-bit         ESP32-S3-DevKitC-1     ESP32-S3-WROOM-1 N16R8
Dual-core LX7               (44-pins)
Dual-core LX7            _______________
 16MB Flash             |  ___   _   __¯|         NO CAMERA MODULE
  8MB PSRAM             | | | |_| |_|   |         NO SD-CARD
 512K SRAM           .——| | |           |——.
               3V3  1|o:|   Espressif   |:•|44 GND                Hardware
               3V3  2|o:|ESP32S3-WROOM-1|:•|43 G43 TX›            SPI2 HSPI
[RST]          ENT  3|o:|               |:•|42 G44 RX‹            —————————
A3  (Mic WS)   G4   4|o:| Œ Æ   N16R8   |:o|41 G1  A0             G10 SS/CS
A4  (Mic SCK)  G5   5|o:| .··. .   ____ |:o|40 G2  A1             G11 MOSI
A5  (Mic SD)   G6   6|o:| WiFi ß  |QRCD||:o|39 G42     (TFT BL)   G12 SCK
A6  (Amp DIN)  G7   7|o:| °   F©  |____||:o|38 G41     (TFT CS)   G13 MISO
A14 (Amp BCLK) G15  8|o:'———————————————':o|37 G40     (TFT DC)
A15 (Amp LRC)  G16  9|o ·. ¨¨|¯¯¯¬        o|36 G39                Software
A16            G17 10|o ¯  ¨¨|LDO[]   PWR o|35 G38                SPI -ALT-
A17            G18 11|o ¯  ¨¨|___-     ¤  o|34 G37 PSRAM          —————————
I²C SDA        G8  12|o RGB     ¬ ¬       o|33 G36 PSRAM           -1  MISO
A2             G3  13|o ‹¤›IO48 ¨ ¨       o|32 G35 PSRAM          G42  BL
LOG            G46 14|o      ........ ·   o|31 G0  [BOOT]         G41  CS
I²C SCL        G9  15|o ¨ ¨  |CP2102| ¨   o|30 G45     (TFT RST)  G40  DC
SPI SS/CS      G10 16|o ¨¨   '''''''' ¨   ¤|29 G48 RGB LED        G45  RST
SPI MOSI       G11 17|o BOOT .......  RST o|28 G47    (TFT MOSI)  G47  MOSI
SPI SCK        G12 18|o ‹•›  '''''''  ‹•› o|27 G21    (TFT SCLK)  G21  SCLK
SPI MISO       G13 19|o                   ø|26 G20 A19 USB_D-
A13            G14 20|o  _____ O T _____  ø|25 G19 A20 USB_D+     I²C -ALT-
               5V0 21|o | USB |T T| USB | o|24 GND                —————————
               GND 22|o |  C  |G L|  C  | o|23 GND                1. *  GND
                     '——'ESP32'———'UART0'——'                      2. *  3V3
  INMP441 I²S Mic                              G48 RGB_BUILTIN,   3. G1 SDA
MAX98357A I²S Audio Amp                            LED_BUILTIN    4. G2 SCL
```
#### ESP32-S3 Pins Summary:
0…18 GPIO,&nbsp; 19…20 D+/D-,&nbsp; 21 GPIO,&nbsp;
22…25 Do Not Exist,&nbsp; 26…32 QSPI ƒlash,&nbsp; 33…34 Missing,&nbsp;
35…42 GPIO,&nbsp; 43…44 TX/RX,&nbsp; 45…48 GPIO<br/>
&nbsp; &nbsp; _pins_arduino.h_ ***~*** **ESP32-S3-DevKitC-1**
<hr><br/>

### 【2】 The 44-pin &nbsp;_(40-pin compatible)_&nbsp; MCU headers are pin-compatible with:
```
        44-pin “ESP32-S3-WROOM-1” Development Boards:
            o Espressif ESP-S3-DevKitC-1
            o VCC-GND Studio YD-ESP32-S3 (ESP32-S3-WROOM-1 Dev)
            o WaveShare ESP32-S3-DEV-KIT-N8R8
            o WeAct Studio ESP32-S3-A/B Core

        40-pin “ESP32-S3-WROOM-1” Development Boards
              (skip top & bottom extra pins)
            o GOOUUU ESP32-S3-CAM
            o ESP-S3-WROOM (CAM)
            o FREEVOVE ESP32-S3-WROOM (CAM)
            o FREEVOVE ESP32-S3-WROOM-Lite
```
<hr><br/>

![ESP32-S3 1.54in TFT Expansion Board with Speaker-5.2](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%201.54in%20TFT%20Expansion%20Board%20with%20Speaker-5.2.jpg)
<br/><br/>

### 【3】 LCD 1.54in 240×240 color IPS TFT (ST7789V2) &nbsp; ***verified***

The TFT Display is identified by:&nbsp; (1) “1.54 TFT Display” in the
title and &nbsp;(2) the picture of the _10-pin ribbon connection_ for the
display on the back of the Expansion Adapter.&nbsp; The TFT Display is
a:&nbsp; 1.54in LCD Module,&nbsp; IPS color 240×240 TFT,&nbsp;
with a 10Pin plug-in strip,&nbsp; and ST7789V2 Driver.

![LCD 1.54in 240×240 color IPS TFT (ST7789V2)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/LCD%201.54in%20240%C3%97240%20color%20IPS%20TFT%2010-pin%20(ST7789T3).jpg)<br/>
![ESP32-S3 1.54in TFT Expansion Board with Speaker-2.1](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%201.54in%20TFT%20Expansion%20Board%20with%20Speaker-2.1.jpg)

```
Configuration:

        TFT LCD   ESP32-S3
        10-Pin    Pin       Function/Description
        ———————   ————————  ——————————————————————————
        1. GND    GND       System Ground   (GND)
        2. RS/DC  GPIO40    Data/Command    (DC)
        3. CS     GPIO41    TFT Chip Select (CS)
        4. SCL    GPIO21    SPI Clock       (SCK)
        5. SDA    GPIO47    SPI Data        (MOSI)
        6. RST    GPIO45    TFT Reset       (RST)
        7. VDD    3V3       Positive Power  (3.3V)
        8. GND    GND       System Ground   (GND)
        9. A      3V3       BackLight LED Anode   (+)
       10. K      GPIO42    BackLight LED Cathode (-) (BL)

        TFT LCD   ESP32-S3
         8-Pin    Pin       Function/Description
        ———————   ————————  ——————————————————————————
        1. GND    GND       System Ground   (GND)
        2. VDD    3V3       Positive Power  (3.3V)
        3. SCL    GPIO21    SPI Clock       (SCK)
        4. SDA    GPIO47    SPI Data        (MOSI)
        5. RES    GPIO45    TFT Reset       (RST)
        6. RS/DC  GPIO40    Data/Command    (DC)
        7. CS     GPIO41    TFT Chip Select (CS)
        8. BLK    GPIO42    BackLight       (BL)
```

#### LCD 1.54in 240×240 color Display Specifications:
```
LCD 1.54in 240×240 color IPS TFT 10-pin (ST7789V2)
  ◆          Brand Name: Maithoga
  ◆           Driver IC: ST7789V2
  ◆                Size: 1.54in color
  ◆    Number of Pixels: 240(RGB)×240
  ◆  Driver IC RAM Size: 240×16×240 (16-Bit RGB565 Color)
  ◆      Display Colors: 262K
  ◆      Interface Pins: 10-Pin
  ◆      Data Interface: SPI 4-pin interface
  ◆           Backlight: White LED Parallel
  ◆      Polarizer Mode: Normally Black, Transmissive
  ◆   Viewing Direction: ALL O’clock
  ◆      Contrast Ratio: 300:1
  ◆           Luminance: 180 cd/m2
  ◆       Input Voltage: 3V
  ◆          Dimensions: 31.52×33.72×1.96mm
  ◆         Active Area: 27.72×27.72mm
  ◆      Operating Temp: -20° ~ 70°
  ◆ Storage Temperature: -30° ~ 80°
```

LCD 1.54in 240×240 color IPS TFT (ST7789V2) sample program at the end.
<hr><br/>

### 【4】 22-pin single-row I/O Interface header: &nbsp;_(½ the availiable pins)_

![ESP32-S3 1.54in TFT Expansion Board with Speaker-4.1](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%201.54in%20TFT%20Expansion%20Board%20with%20Speaker-4.1.jpg)
<br/>
```
                                .——Interface Pins absent from the I/O header——.
                                | G4 INMP441   I²S Mic   LCD TFT   G43  TX›   |
    3V3   o  1.                 | G5 INMP441   I²S Mic   ———————   G44  RX‹   |
    G1    o  2.                 | G6 INMP441   I²S Mic   G42 BLK              |
    G2    o  3.                 |                        G41 CS    G37* PSRAM |
    G39   o  4.  (Volume ▲)     | G7 MAX98357A I²S Amp   G40 RS/DC G36* PSRAM |
    G38   o  5.  (Volume ▼)     |G15 MAX98357A I²S Amp   G45 RST   G35* PSRAM |
    G0    o  6.  [BOOT]         |G16 MAX98357A I²S Amp   G47 SDA              |
    G48   o  7.  RGB LED        |                        G21 SCL              |
    G20   o  8.  USB D⧿         '—————————————————————————————————————————————'
    G19   o  9.  USB D⧾                 {Pins  10..22 I/O header}
    G17   o 10.  --------------------------------------------------------------
    G18   o 11.                         {match 10..22 MCU header}
    G8    o 12.  I²C SDA
    G3    o 13.      ‘JTAG’
    G46   o 14.      ‘LOG’
    G9    o 15.  I²C SCL
    G10   o 16.  SPI SS/CS      (optional) SPI microSD_Card Reader
    G11   o 17.  SPI MOSI           "           "
    G12   o 18.  SPI SCK            "           "
    G13   o 19.  SPI MISO           "           "
    G14   o 20.
    5V0   o 21.
    GND   o 22.
```
<hr><br/>

### 【5】 INMP441 &nbsp;I²S Microphone:&nbsp; “pass-through” hole & icon on the top-side:

![MEMS digital microphone (INMP441)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/INMP441%20I%C2%B2S%20Mic.jpg)

### INMP441 &nbsp;I²S MEMS PDM Digital Microphone &nbsp; ***verified***

 1. I²S Mic chip mounted on the bottom-side of the Expansion Board.
 2. I²S MEMS PDM Digital Microphone ( **INMP441** )
 3. 6-Pin configuration:

  | ESP32-S3 Dev Board  | I²S INMP441 Microphone    |
  |--------------------:|---------------------------|
  |     GND  (LOW=Left) | 1. L/R Left/Right Channel |
  |     GPIO4           | 2. WS  Data Select        |
  |     GPIO5           | 3. SCK Data Clock         |
  |     GPIO6           | 4. SD  Data Out           |
  |     3V3             | 5. VDD (Power)            |
  |     GND             | 6. GND                    |
<br/>

### INMP441 I²S Mic Interface definition:

1. L/R:&nbsp; Left/Right Channel selection.
>   When set to LOW, the microphone outputs a signal on the Left
>   channel of the I²S frame.  When set to HIGH, the microphone
>   outputs signals on the Right channel of the I²S frame.
2.  WS:&nbsp; Serial data Word Selection for the I²S interface.
3. SCK:&nbsp; Serial data Clock for the I²S interface.
4.  SD:&nbsp; &nbsp; Serial Data output of the I²S interface.
5. VDD:&nbsp; Input Power, 1.8V to 3.3V.
6. GND:&nbsp; Power Ground

### INMP441 I²S Microphone Introduction:

***I²S*** is a protocol for transferring Digital Audio.&nbsp; The audio quality
can range from telephone-grade to ultra-high fidelity,&nbsp; and you can have
one or two channels.

The I²S **INMP441** is a high performance, low power, digital output,&nbsp;
_“omnidirectional”_ **MEMS microphone** with a _‘bottom port’_.&nbsp; The complete
INMP441 solution consists of a **MEMS** Sensor,&nbsp; Signal Conditioning,&nbsp;
an **ADC** Analog to Digital converter,&nbsp; Anti-Aliasing Filter,&nbsp; Power
Management,&nbsp; and industry standard 24-bit **I²S** interface.

The I²S interface allows the INMP441 to be directly connected to
digital processors such as DSPs and microcontrollers without the
need for an _Audio Codec_ for use in the system.

The I²S INMP441 has a high SNR _“Signal-to-Noise Ratio”_&nbsp; and is an excellent
choice for ‘near field’ applications.&nbsp; The I²S INMP441 has a flat wideband
‘frequency response’ that results in high definition of natural sound.

### INMP441 I²S Mic Features:

1. Digital I²S interface with high precision 24-bit data
2. High SNR Signal-To-Noise ratio: 61 dBA
3. High Sensitivity: 26 dBFS
4. Stable Frequency Response from 60 Hz to 15 kHz
5. Low power consumption, low current consumption: 1.4 mA
6. High PSR (Power Supply Rejection): -75 dBFS
<hr><br/>

## INMP441 I²S Microphone sample program:

**Download:**&nbsp; [INMP441-I2S-Mic-sample.ino &nbsp; (Visual “Audio Waveforms”)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/code/INMP441-I2S-Mic-sample/INMP441-I2S-Mic-sample.ino)
```C++
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
 1. We start this sketch by including the ESP32-S3 I²S driver.
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

#define I2S_PORT I2S_NUM_0              // Use I²S Port/Processor 0

#define bufferLen 64                    // Input buffer length
int16_t sBuffer[bufferLen];             // I²S Serial Input buffer

void I2S_install() {                    // I²S Port/Processor config
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

/* -----------------------------------------------------------------
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
----------------------------------------------------------------- */
```
<br/>

### What is the difference between an “**Omnidirectional**” microphone and a “**Unidirectional**” microphone?

First of all,&nbsp; understand that _sound divergence_ is all-round us.&nbsp; One
person speaks and divergence in the air.&nbsp; As for how far it can pass,&nbsp;
that depends on many factors.

1. **Directional microphone:**&nbsp; the ‘general pickup radius’ is very small,&nbsp;
    30cm is a big one...&nbsp; single use,&nbsp; put it on the mouth,&nbsp; the sound quality
    is very good,&nbsp; because it is not _“picked up”_ again.<br/><br/>

    The Mic shape is generally a goose neck, a rod, or a curved rod to your mouth
    directly,&nbsp; just listen to your voice.&nbsp; With a single-point microphone,&nbsp;
    the _‘Sensitivity’_ is limited to a certain range.<br/><br/>

    If the _‘Sensitivity’_ is too high,&nbsp; it causes sharp whistling,&nbsp; etc., involving
    many other devices.&nbsp; As for why not make a big pickup radius,&nbsp; there is a
    reason we’ll discuss later.

2. **Omnidirectional microphone:**&nbsp; the ‘general pickup radius’ is very large,&nbsp;
    one meter, two meters, three meters, five meters, compared with ten centimeters.&nbsp;
    This _‘sensitivity level’_ is very different.&nbsp; It is not just _“picking up”_ a persons’
    voice,&nbsp; but multiple people,&nbsp; five, six, seven, eight, or more.<br/><br/>

    Omnidirectional microphones are highly _‘Sensitive’_.&nbsp; The omnidirectional microphone
    ‘pickup radius’ is large,&nbsp; and it will pick up more ambient noise,&nbsp; so the sound
    quality is not as good as the single-point microphone,&nbsp; unless you do very good
    _‘noise reduction’_.<br/><br/>

    There is definitely a difference between ‘collective’ use and ‘single-person’ service.&nbsp;
    But omnidirectional Mics have one benefit,&nbsp; the wiring is simple.&nbsp; It is not one-to-one.&nbsp;
    They are Suitable for small meetings,&nbsp; ad-hoc meetings,&nbsp; some remote discussions,&nbsp; and
    remote operations.

3.  A single-point Directional Mic generally supports _‘local amplification’_.&nbsp; Omnidirectional
    microphones generally do not support _‘local amplification’_.&nbsp; It should be noted that because
    of the _high sensitivity_,&nbsp; local amplification whistling is very scary,&nbsp; and the
    current technology can be difficult to deal with.

_to be continued..._
<hr><br/>

### 【6】 Large _on-board_ cavity Speaker on top:<br/> &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; _(with an I²S MAX98357A Audio Amplifier on the bottom)_

![MAX98357A I²S Audio Amplifier/Speaker](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/MAX98357A%20I%C2%B2S%20Amp.jpg)

### MAX98357A I²S Audio Amplifier/Speaker &nbsp; ***verified***

So, there’s no DAC on the ESP32-S3.&nbsp; You would think this would be a bit of a downer
if you want to get Audio out and use an Audio Amplifier like the **MAX98357A**.

But it’s actually surprisingly easy to output ***Pulse Density Modulated*** Audio using
‘Sigma Delta Modulation’ on the ESP32-S3 and the **MAX98357A** Audio Amplifier
recovers the Audio signal by low pass filtering it with an RC filter.

The **MAX98357A** is a digital Audio Amplifier that also uses the **I²S** interface to receive
Audio data.&nbsp; It can be used in various applications,&nbsp; such as speakers,&nbsp;
walkie-talkies,&nbsp; and voice recognition devices.&nbsp; The **MAX98357A** can also be
used to play music files directly from an SD_card.

 1. &nbsp;I²S 3W Audio Amp ( **MAX98357A** )
 2. &nbsp;7-Pin \+ 2,&nbsp; I²S MAX98357A Audio Amplifier/Speaker configuration:

| ESP32-S3 Dev Board | MAX98357A I²S Audio Amplifier/Speaker         |
|-------------------:|-----------------------------------------------|
|     GPIO7          | 1. DIN  &nbsp;Digital Signal In               |
|     GPIO15         | 2. BCLK &nbsp;Bit Clock                       |
|     GPIO16         | 3. LRC  &nbsp;Left Right Clock                |
|     GND &nbsp;(12dB Gain) | 4. GAIN &nbsp;(Signal Amp)             |
|     VDD &nbsp;(0Ω=Left)   | 5. SD &nbsp;&nbsp;(L/R Channel Select) |
|     GND            | 6. GND                                        |
|     3V3            | 7. VIN                                        |
|                    |                                               |
|     Audio ⧾        | Speaker Positive  &nbsp;(⧾)                   |
|     Audio ⧿        | Speaker Negative  &nbsp;(⧿)                   |

### MAX98357A I²S Audio Amp specifications:

**I²S** _(not to be confused with **I²C**)_, is the digital Sound Protocol used
to deliver Audio data on a circuit board.&nbsp; Many high-end chips and processors
manage all Audio in a digital _I²S_ format.&nbsp; Then, in order to input or output
data,&nbsp; 3 or 4 pins _(Data Input, Data Output, Bit Clock, and Left/Right
Channel Selection)_ are used.&nbsp; Usually, for Audio devices,&nbsp; there is
a built-in ***DAC chip*** that takes I²S and converts it into an Analog signal
that can directly drive the speaker or headset.

The ***MAX98357A I²S Audio Amplifier*** takes standard I²S digital audio input and
not only decodes it into an ‘Analog signal’,&nbsp; but also amplifies it directly
to a speaker.&nbsp; Perfect for adding compact amplified sound.&nbsp; It takes 2
sources &nbsp;_(I²SDAC and AMP)_&nbsp; and combines them into one.

 1. **Class D Amplifier:**&nbsp; The **MAX98357A** is a Class D amplifier,&nbsp;
    which means it’s efficient and suitable for battery-powered projects.
 2. **Output Power:**&nbsp; 4Ω speakers 3.2W, 10% THD _(Total Harmonic Distortion)_;<br/>
    8Ω speakers 1.8W, 10% THD _(Total Harmonic Distortion)_, with a 5V power supply
 3. **I²S Sampling Rate:**&nbsp; 8kHz to 96kHz
 4. **PSRR _(Power Supply Rejection Ratio)_:**&nbsp; 77 decibels, typical @1 KHZ
 5. **Audio Amp “Gain”:** five pin settable options;&nbsp; 3dB, 6dB, 9dB, 12dB, and 15dB.
 6. You don’t need a **MCLK _(Master Clock)_** timing signal.
 7. Excellent **_click and pop_ suppression**.
 8. Automatic built-in thermal **Hot shutdown**.

The **I²S MAX98357A** is an inexpensive, small, ‘mono’ Audio Amplifier that is
surprisingly powerful.&nbsp; It is capable of delivering **‘3.2 Watts’** of power
to a _‘4 Ohm impedance’_ speaker at 5 volts power _(10% THD)_.&nbsp; Inside the
microchip is a ‘D-level’ Amplifier,&nbsp; capable of operating between 2.7V and
5.5Vdc.&nbsp; Because the Amp is _class D_,&nbsp; it is highly efficient and
perfect for portable and battery-powered projects.&nbsp;
It has built-in _thermal protection_ and _overcurrent protection_.

The Audio input is **I²S standard**,&nbsp; and it can use 3.3V or 5V logic data.&nbsp;
The outputs are _“bridged”_ &nbsp;-this means that they are directly connected
to the output (Speaker),&nbsp; rather than grounded.&nbsp; The Audio output is a
_‘Pulse-Width Modulation,&nbsp; ~300kHz square-wave’_,&nbsp; which is then
“averaged out” by the speaker coil &nbsp-no high frequency distortion is heard.&nbsp;

***What all of this means that you can not connect the output to another Audio Amplifier,&nbsp;
the I²S MAX98357A should drive the Speakers directly.***

The I²S **MAX98357A** Audio Amplifier has a signal _‘Gain’_ pin that can be
manipulated to change the signal Amp Gain.&nbsp; By default,&nbsp; the
**MAX98357A** Audio Amplifier will give you a Gain of ****‘9dB’***.&nbsp;
The _‘Gain’_ pin can be confifured for&nbsp; 3dB, 6dB, 9dB, 12dB, or 15dB
by directly connecting a _pull-up resistor_ or _pull-down resistor_
or other wiring.

   | MAX98357A Amp Gain | Gain pin configuration/wiring       |
   |-------------------:|-------------------------------------|
   |      3 dB          | Connect to VIN via a 100kΩ resistor |
   |      6 dB          | Directly connect to VIN             |
   |      9 dB          | Unconnected (floating)              |
   |     12 dB          | Directly connect to GND             |
   |     15 dB          | Connect to GND via a 100kΩ resistor |

The _‘Shutdown/Mode’_ pin of the I²S **MAX98357A** Audio Amplifier&nbsp; can be used
to put the Amp into a “shutdown state”&nbsp; _-or_&nbsp; to set which I²S Audio channel
( _Left_ &nbsp;-or _Right_ &nbsp;-or a _LR mix_)&nbsp; is connected to the Speaker.

By default,&nbsp; the **MAX98357A** Audio Amplifier will output a _(L+R)/2_
Stereo mix to a _mono_ output to the Speaker.&nbsp; By adding a resistor,&nbsp;
you can change it to output just the _Left_ or _Right_ Speaker output.&nbsp;
By adding a second inexpensive,&nbsp; I²S **MAX98357A** Audio Amplifier,&nbsp;
set one to _Left_,&nbsp; set the other to _Right_,&nbsp; you can get true
Stereo sound.

   | MAX98357A Audio channel | SD pin configuration  |
   |------------------------:|-----------------------|
   |  No output              | 0 VDC, connect to GND |
   |  Stereo Average         | 0.16 - 0.77 VDC       |
   |  Right  Channel         | 0.77 - 1.4  VDC       |
   |  Left   Channel         | 1.4 VDC or Higher     |
<hr><br/>

## MAX98357A I²S Audio Amp/Speaker sample programs:

**Download:**&nbsp; [MAX98357-I2S-Amp-quickTest.ino &nbsp; (440Hz sine wave)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/code/MAX98357-I2S-Amp-quickTest/MAX98357-I2S-Amp-quickTest.ino)
```C++
/* MAX98357-I2S-Amp-quickTest.ino
 *      Quick Test: Send 440Hz Sine Waves to the MAX98357A/Speaker.
 *      https://www.kincony.com/forum/showthread.php?tid=6898
 *
 * Requires a MAX98357A I²S Audio Amplifier/Speaker
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
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
 * 1. DIN  (Serial Data In/Out) --> GPIO7
 * 2. BCLK (Bit Clock)          --> GPIO15
 * 3. LRC  (Left Right Clock)   --> GPIO16
 * 4. GAIN                      --> Connect to GND (12 dB Gain)
 * 5. SD   (L/R Channel Select) --> Connect to GND (select Left)
 * 6. GND                       --> GND
 * 7. VIN  (Power)              --> 3V3
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
    .ws_io_num    = I2S_LRC,            // Word Select|Left/Right Channel
    .data_out_num = I2S_DOUT,           // Serial Data line, Data Out
    .data_in_num  = I2S_PIN_NO_CHANGE
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

  // SPECIAL NOTE: To stop the 440Hz Sine Wave tone, unplug the USB
  // ¯¯¯¯¯¯¯¯¯¯¯¯¯ Data cable, --or better yet-, press and hold the
  //               [BOOT] button, press then release the [RESET]
  //               button, now release the [BOOT] button...
  //               This puts your ESP32-S3 into “Bootloader Mode”,
  //               waiting to be flashed with new firmware.

  //i2s_stop(I2S_PORT);             // Stop the MAX98357A I²S driver
}

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
01:31:08.758 -> Send 440Hz Sine Waves to the MAX98357A Amplifier/Speaker
01:31:08.758 -> MAX98357A I²S driver installed.

*******************************************************************/
```
<br/>

**Download:**&nbsp; [MAX98357-I2S-Amp-SD-Music-Player.ino &nbsp; (I²S Music Player)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/code/MAX98357-I2S-Amp-SD-Music-Player/MAX98357-I2S-Amp-SD-Music-Player.ino)
```C++
/* MAX98357-I2S-Amp-SD-Music-Player.ino     (MP3 Music Player)
 * Requires a MAX98357A I²S Audio Amplifier/Speaker.
 * Requires an SPI microSD Card reader/writer to hold the MP3 files.
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 * The MAX98357A (3 Watt Audio Amplifier with DAC), connectes three
 * lines (DOUT, BLCK, and LRC) to the I²S bus. The I²S output frequency
 * is always 48kHz regardless of the input source, so Bluetooth
 * devices can also be connected without any problems. To get stereo,
 * two MAX98357A are necessary. Using “AudioI2S” you can play MP3s,
 * Icy-streams, GoogleTTS, OpenAIspeech, and more.
 *
 * This sketch is a simple ESP32-S3 microSD_Card I²S MP3 Music Player:
 *
 * Play your MP3 files directly from one of two types of microSD Cards:
 *      1. Micro SD_Card   (size up to 2GB)
 *      2. Micro SDHC_Card (size up to 32G)
 *
 *  Uses a MAX98357A I²S Amplifier.
 *  Uses the ESP32-audioI2S Library:
 *      https://github.com/schreibfaul1/ESP32-audioI2S
 *
 * Using the MAX98357A I²S Audio Amplifier and Speaker:
 *
 *   The sound source will be an .mp3 file that is stored on your
 *   microSD_Card.  This is an extremely basic MP3 player, for
 *   practical use you would need to code a system for navigating
 *   the microSD_Card, to play more than one selection.  This sketch
 *   is just to illustrate how to use the MAX98357A I²S Audio Amplifier,
 *   as well as a library that makes working with I²S Audio apps a
 *   bit easier.
 *
 * Project Wiring:
 * ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
 * MAX98357A I²S Amp                ESP32-S3-WROOM-1
 * 1. DIN  (Digital Signal In)  --> GPIO7
 * 2. BCLK (Bit Clock)          --> GPIO15
 * 3. LRC  (Left Right Clock)   --> GPIO16
 * 4. GAIN                      --> Connect to GND (12dB Gain)
 * 5. SD   (L/R Channel Select) --> Connect to VIN (0Ω = Left)
 * 6. GND                       --> GND
 * 7. VIN  (Power)              --> 3V3
 *
 *    External Speaker interface: (⧾ ⧿)
 *
 *    Audio⧾  Connect to Speaker Positive (usually a Red wire)
 *    Audio⧿  Connect to Speaker Negative
 *
 * microSD Card                     ESP32-S3-WROOM-1
 * 1. 3V3  (Power)              --> 3V3
 * 2. CS   (Chip Select)        --> GPIO10
 * 3. MOSI (SPI SDI)            --> GPIO11
 * 4. CLK  (SPI Clock)          --> GPIO12
 * 5. MISO (SPI SDO)            --> GPIO13
 * 6. GND                       --> GND
 *
 * Sound with ESP32 – I²S Protocol
 * https://dronebotworkshop.com/esp32-i2s/
 */

/*******************************************************************
Type-C USB Data cable. Plug into the Left-side ESP32-S3 USB-OTG port
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

#include "Arduino.h"                // Include required libraries
#include "Audio.h"                  // ESP32-audioI2S library
#include "SD.h"                     // SD_Card and µSD_Card library
#include "FS.h"
                                    // microSD_Card pins
#define SD_CS         10            // microSD_Card Chip Select
#define SPI_MOSI      11            // SPI Data In  (SDI)
#define SPI_SCK       12            // SPI Clock    (CLK)
#define SPI_MISO      13            // SPI Data Out (SDO)

                                    // MAX98357 I²S Amp pins
#define I2S_DOUT       7            // MAX98357 I²S Amp pins (DIN)
#define I2S_BCLK      15            //      "
#define I2S_LRC       16            //      "

Audio audio;                        // ESP32-audioI2S Audio object

void setup() {
  Serial.begin(115200);             // Initialize Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  pinMode(SD_CS,      OUTPUT);      // Set microSD_Card CS as OUTPUT
  digitalWrite(SD_CS, HIGH);        // Disable (Active LOW)

  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI); // Initialize the SPI bus

  if(!SD.begin(SD_CS)) {            // Start the microSD_Card
    Serial.println("Error accessing microSD_Card!");
    while(true);
  }

  // Setup the MAX98357 I²S Amplifier & Volume control
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(5);                   // Set Volume

  // Open your .mp3 music file from the microSD_Card
  audio.connecttoFS(SD,"/MYMUSIC.mp3"); // Change to name of chosen
}                                       // .mp3 file on microSD_Card

void loop() {
  audio.loop();                         // Play the .mp3 file in a loop
}
```
<hr><br/>

## LCD 1.54in 240×240 color IPS TFT (ST7789V2) sample program:

**Download:**&nbsp; [GFX_ST7789_colorGraphicsDemo.ino &nbsp; (a dozen GFX graphics demos)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/code/GFX_ST7789_colorGraphicsDemo/GFX_ST7789_colorGraphicsDemo.ino)
```C++
// GFX_ST7789_colorGraphicsDemo.ino  (a dozen GFX graphics demos)
//
// ESP32-S3 1.54in TFT Expansion Board with Speaker
// LCD 1.54in 240×240 color IPS TFT (ST7789V2)
// Prof. Michael P. Harris

/* This demo works with several “pin-compliant” Ðevelopment boards:
 *  1. Espressif ESP32-S3-DevKitC-1 (no camera, no SD card)
 *  2. YD-ESP32-S3 (ESP32-S3-WROOM-1 Dev) (DevKitC-1 clone)
 *  3. WeAct Studio ESP32-S3-A/B Core     (DevKitC-1 clone)
 *  4. WaveShare ESP32-S3-DEV-KIT-N8R8    (DevKitC-1 clone)
 *  5. GOOUUU ESP32-S3-CAM     (DevKitC-1 clone + CAM + SD)
 *  6. ESP32-S3-WROOM CAM   (FREENOVE ESP32-S3-WROOM clone)
 *  7. FREENOVE ESP32-S3-WROOM (CAM)
 *  8. FREENOVE ESP32-S3-WROOM-Lite (no camera)
 */

/*  TFT LCD 1.54in 240×240 color SPI IPS (ST7789V2)     [WIRING]
 *
 *  Pins: TFT LCD             Pins: ESP32-S3-WROOM-1
 *  1. GND  GND               GND
 *  2. VCC  3V3               3V3
 *  3. SCL  SPI Clock         GPIO21  TFT_SCLK
 *  4. SDA  SPI Data (MOSI)   GPIO47  TFT_MOSI
 *  5. RES  TFT Reset         GPIO45  TFT_RST
 *  6. RS   Data/Command      GPIO40  TFT_DC
 *  7. CS   Chip Select       GPIO41  TFT_CS
 *  8. BLK  BackLight         GPIO42  TFT_BL
 *
 *     -1   SPI MISO (N/C)
 */

/**************************************************************************
               ESP32-S3 1.54in TFT Expansion Board with Speaker
Xtensa® 32-bit         ESP32-S3-DevKitC-1     ESP32-S3-WROOM-1 N16R8
Dual-core LX7               (44-pins)
Dual-core LX7            _______________
 16MB Flash             |  ___   _   __¯|         NO CAMERA MODULE
  8MB PSRAM             | | | |_| |_|   |         NO SD-CARD
 512K SRAM           .——| | |           |——.
               3V3  1|o:|   Espressif   |:•|44 GND                Hardware
               3V3  2|o:|ESP32S3-WROOM-1|:•|43 G43 TX›            SPI2 HSPI
[RST]          ENT  3|o:|               |:•|42 G44 RX‹            —————————
A3  (Mic WS)   G4   4|o:| Œ Æ   N16R8   |:o|41 G1  A0             G10 SS/CS
A4  (Mic SCK)  G5   5|o:| .··. .   ____ |:o|40 G2  A1             G11 MOSI
A5  (Mic SD)   G6   6|o:| WiFi ß  |QRCD||:o|39 G42     (TFT BL)   G12 SCK
A6  (Amp DIN)  G7   7|o:| °   F©  |____||:o|38 G41     (TFT CS)   G13 MISO
A14 (Amp BCLK) G15  8|o:'———————————————':o|37 G40     (TFT DC)
A15 (Amp LRC)  G16  9|o ·. ¨¨|¯¯¯¬        o|36 G39                Software
A16            G17 10|o ¯  ¨¨|LDO[]   PWR o|35 G38                SPI -ALT-
A17            G18 11|o ¯  ¨¨|___-     ¤  o|34 G37 PSRAM          —————————
I²C SDA        G8  12|o RGB     ¬ ¬       o|33 G36 PSRAM           -1  MISO
A2             G3  13|o ‹¤›IO48 ¨ ¨       o|32 G35 PSRAM          G42  BL
LOG            G46 14|o      ........ ·   o|31 G0  [BOOT]         G41  CS
I²C SCL        G9  15|o ¨ ¨  |CP2102| ¨   o|30 G45     (TFT RST)  G40  DC
SPI SS/CS      G10 16|o ¨¨   '''''''' ¨   ¤|29 G48 RGB LED        G45  RST
SPI MOSI       G11 17|o BOOT .......  RST o|28 G47    (TFT MOSI)  G47  MOSI
SPI SCK        G12 18|o ‹•›  '''''''  ‹•› o|27 G21    (TFT SCLK)  G21  SCLK
SPI MISO       G13 19|o                   ø|26 G20 A19 USB_D-
A13            G14 20|o  _____ O T _____  ø|25 G19 A20 USB_D+     I²C -ALT-
               5V0 21|o | USB |T T| USB | o|24 GND                —————————
               GND 22|o |  C  |G L|  C  | o|23 GND                1. *  GND
                     '——'ESP32'———'UART0'——'                      2. *  3V3
  INMP441 I²S Mic                              G48 RGB_BUILTIN,   3. G1 SDA
MAX98357A I²S Audio Amp                            LED_BUILTIN    4. G2 SCL

**************************************************************************/

/*******************************************************************
Arduino IDE > Tools                                  [CONFIGURATION]
                       Board: "ESP32S3 Dev Module"
             USB CDC On Boot: "Disabled"    *** Sketch locks up if ENABLED ***
               CPU Frequency: "240MHz (WiFi)"
             USB DFU On Boot: "Disabled"
                  Flash Mode: "QIO 80MHz"
                  Flash Size: "16MB 128Mb"
    USB Firmware MSC On Boot: "Disabled"
              Partion Scheme: "16M Flash (2MB APP/12.5MB FATFS)"
                       PSRAM: "OPI PSRAM"
                Upload Speed: "115200"
*******************************************************************/

/*******************************************************************
When you have Tools > USB CDC On Boot > Disabled
    selected from the Arduino IDE menus, calling Serial.println etc.
    in your sketch will cause the serial communication to be done
    via that socket's Serial Port labled "USB-TTL" or "UART":

When you have Tools > USB CDC On Boot > Enabled
    selected from the Arduino IDE menus, serial communication will
    instead be done via the ESP32-S3 internal Serial Port, the USB
    socket labeled "USB-OTG":
 ******************************************************************/

#include <Adafruit_GFX.h>    // Adafruit Core GFX Graphics library
#include <Adafruit_ST7789.h> // Hardware specific library for ST7789
#include <SPI.h>

/* Some ready-made 16-bit ('565') Color settings:
#define ST77XX_BLACK    0x0000
#define ST77XX_WHITE    0xFFFF
#define ST77XX_RED      0xF800
#define ST77XX_GREEN    0x07E0
#define ST77XX_BLUE     0x001F
#define ST77XX_CYAN     0x07FF
#define ST77XX_MAGENTA  0xF81F
#define ST77XX_YELLOW   0xFFE0
#define ST77XX_ORANGE   0xFC00
*/

// Define the 240×240 ST7789V2 TFT LCD display size
#define TFT_WIDTH   240     // TFT LCD Width  in pixels
#define TFT_HEIGHT  240     // TFT LCD Height in pixels

// OPTION 2: Lets you interface your display using ANY 2 or 3 Pins,
// tradeoff being that performance is not as fast as hardware SPI.
// SPI Pins declared for the TFT display (Right-side ESP32-S3-WROOM)
#define TFT_BL       42     // BackLight
#define TFT_CS       41     // SPI Chip Select
#define TFT_DC       40     // SPI Data/Command
#define TFT_RST      45     // SPI Reset
#define TFT_MOSI     47     // SPI Data  (SDA)
#define TFT_SCLK     21     // SPI Clock (SCL)

Adafruit_ST7789 tft=Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI,
                                    TFT_SCLK, TFT_RST);

float pi = 3.1415926;

void setup(void) {
  Serial.begin(115200);             // Initialize Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  rgbLedWrite(RGB_BUILTIN, 0,0,0);  // Make sure RGB NeoPixel is Off

  tft.init(TFT_HEIGHT, TFT_WIDTH);  // Init ST7789V2 240×320 TFT LCD
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  Serial.println(F("\n...ST7789V2 Screen Initialized"));

  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library,
  // you can override it here. Note that the speed allowable depends
  // on the chip and quality of wiring, if you go too fast, you may
  // end up with a Black/Blank screen some times, or all the time.
  // tft.setSPISpeed(40000000);

  tft.setRotation(3);               // Rotation(0..3) 0°,90°,180°,270°
  Serial.println(F("Hello! a dozen ST7789 GFX color Graphics Demos:"));

  uint16_t time = millis();
  time = millis() - time;
  Serial.print(F("Start time: ")); Serial.println(time, DEC);
  delay(1000);


  // Demo 1. Two large blocks of text in two sizes
  tft.setTextSize(1);               // TextSize (1..3) 1=5×8 pixels
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  testDrawText("Lorem ipsum dolor sit amet, consectetur adipiscing "
               "elit. Curabitur adipiscing ante sed nibh tincidunt "
               "feugiat. Maecenas enim massa, fringilla sed malesuada "
               "et, malesuada sit amet turpis. Sed porttitor neque ut "
               "ante pretium vitae malesuada nunc bibendum. Nullam "
               "aliquet ultrices massa eu hendrerit. Ut sed nisi "
               "lorem. In vestibulum purus a tortor imperdiet posuere.",
               ST77XX_WHITE); delay(1000);

  tft.setTextSize(2);               // TextSize (1..3) 2=10×16 pixels
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  testDrawText("Lorem ipsum dolor sit amet, consectetur adipiscing "
               "elit. Curabitur adipiscing ante sed nibh tincidunt "
               "feugiat. Maecenas enim massa, fringilla sed malesuada "
               "et, malesuada sit amet turpis. Sed porttitor neque ut "
               "ante pretium vitae malesuada nunc bibendum. Nullam "
               "aliquet ultrices massa eu hendrerit. Ut sed nisi "
               "lorem. In vestibulum purus a tortor imperdiet posuere.",
               ST77XX_CYAN); delay(2000);


  // Demo 2. A single Pixel centered on the display
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  tft.drawPixel(tft.width()/2,tft.height()/2, ST77XX_GREEN);
  delay(1000);

  // Demo 3. Draw Lines (in 8 colors)
  testDrawLines(ST77XX_WHITE, ST77XX_RED, ST77XX_GREEN, ST77XX_BLUE,
                ST77XX_CYAN, ST77XX_MAGENTA, ST77XX_YELLOW,
                ST77XX_ORANGE); delay(1000);

  // Demo 4. Draw Optimized Lines
  testFastLines(ST77XX_RED, ST77XX_BLUE); delay(1000);

  // Demo 5. Draw Rectangles
  testDrawRects(ST77XX_ORANGE); delay(1000);

  // Demo 6. Draw Filled Rectangles
  testFillRects(ST77XX_YELLOW, ST77XX_MAGENTA); delay(1000);

  // Demo 8. Draw Filled Circles
  testFillCircles(10, ST77XX_BLUE); delay(1000);

  // Demo 7. Draw Circles
  testDrawCircles(10, ST77XX_WHITE); delay(1000);

  // Demo 9. Draw Round Rectangles
  testRoundRects(); delay(1000);

  // Demo 10. Draw Triangles
  testTriangles(); delay(1000);

  // Demo 11. Draw sample Media Buttons (for a Touchscreen)
  mediaButtons(); delay(1000);

  // Demo 12. TFT Print Test function!
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  tftPrintTest(); delay(3000);

  time = millis()/1000;
  Serial.print(F("  End time: ")); Serial.println(time, DEC);

  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.println("\nThis Sketch has been");
  tft.println("running for:\n");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.\n"); delay(1500);

  Serial.println("Done.\n"); delay(2000);
}


void loop() {
  tft.invertDisplay(true);
  delay(1000);
  tft.invertDisplay(false);
  delay(1000);
}


void testDrawText(char *text, uint16_t color) {
  tft.setCursor(0,0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testDrawLines(uint16_t color1, uint16_t color2,
                   uint16_t color3, uint16_t color4,
                   uint16_t color5, uint16_t color6,
                   uint16_t color7, uint16_t color8) {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0,0, x,tft.height()-1, color1);
    delay(0);
  }
  for(int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0,0, tft.width()-1,y, color2);
    delay(0);
  }
  delay(500);
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1,0, x,tft.height()-1, color3);
    delay(0);
  }
  for(int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1,0, 0,y, color4);
    delay(0);
  }
  delay(500);
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0,tft.height()-1, x,0, color5);
    delay(0);
  }
  for(int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0,tft.height()-1, tft.width()-1,y, color6);
    delay(0);
  }
  delay(500);
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1,tft.height()-1, x,0, color7);
    delay(0);
  }
  for(int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1,tft.height()-1, 0,y, color8);
    delay(0);
  }
  delay(500);
}

void testFastLines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0,y, tft.width(), color1);
  }
  for(int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x,0, tft.height(), color2);
  }
}

void testDrawRects(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2-x/2,tft.height()/2-x/2, x,x, color);
  }
}

void testFillRects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2-x/2,tft.height()/2-x/2, x,x, color1);
    tft.drawRect(tft.width()/2-x/2,tft.height()/2-x/2, x,x, color2);
  }
}

void testDrawCircles(uint8_t radius, uint16_t color) {
  for(int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for(int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x,y, radius, color);
    }
  }
}

void testFillCircles(uint8_t radius, uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  for(int16_t x=radius; x < tft.width(); x+=radius*2) {
    for(int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x,y, radius, color);
    }
  }
}

void testTriangles() {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  uint16_t color = 0xF800;          // ST77XX_RED
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0; t <= 15; t++) {
    tft.drawTriangle(w,y, y,x, z,x, color);
    x-=4;
    y+=4;
    z-=4;
    color += 255;                   // change color
  }
}

void testRoundRects() {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  uint16_t color = 127;
  int i;
  int t;
  for(t=0; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(i=0; i <= 16; i+=1) {
      tft.drawRoundRect(x,y, w,h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1024;
    }
    color+=128;
  }
}

void mediaButtons() {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  // Play Button
  tft.fillRoundRect(25,10, 78,60, 8, ST77XX_WHITE);
  tft.fillTriangle( 42,20, 42,60, 90,40, ST77XX_RED);
  delay(1000);
  // Pause Button
  tft.fillRoundRect(25,90, 78,60, 8, ST77XX_WHITE);
  tft.fillRoundRect(39,98, 20,45, 5, ST77XX_GREEN);
  tft.fillRoundRect(69,98, 20,45, 5, ST77XX_GREEN);
  delay(1000);
  // Play Button color1
  tft.fillTriangle(42,20, 42,60, 90,40, ST77XX_BLUE);
  delay(1000);
  // Pause Button color
  tft.fillRoundRect(39,98, 20,45, 5, ST77XX_RED);
  tft.fillRoundRect(69,98, 20,45, 5, ST77XX_RED);
  // Play Button color2
  tft.fillTriangle(42,20, 42,60, 90,40, ST77XX_GREEN);
  delay(1000);
}

void tftPrintTest() {
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  tft.setTextWrap(false);
  tft.setCursor(0,30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hello, World!");
  tft.println(" ");
  tft.setTextColor(ST77XX_ORANGE);
  tft.setTextSize(2);
  tft.println("Hello, World!");
  tft.println(" ");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello, World!");
  tft.println(" ");
  tft.setTextColor(ST77XX_BLUE);
  tft.print(1234.567);
  delay(4500);
  tft.setCursor(0,0);
  tft.fillScreen(ST77XX_BLACK);     // clear the screen
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.println("Hello, World!");
  tft.println(" ");
  tft.setTextSize(3);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(pi, 6);
  tft.println("\n Want Pi?");
  delay(1500);
  tft.setTextSize(1);
  tft.print(8675309, HEX);      // print 8,675,309 out in HEX!
  tft.println("\n Printing in HEX!");
  tft.println(" ");
}

/*******************************************************************
Adafruit_GFX Graphics library -=- Quick Function Summary:
Parameters are assumed to be ‘int16_t’ unless otherwise specified.

Default Argument List:
    x,y         primary screen coordinates
    x1,y1       secondary screen coordinates
    x2,y2       tertiary screen coordinates
    w,h         Width and Height (also used for Length)
    r           circle or rounded entity radius
    color, bg   16-bit 565Color color for fgColor or bgColor
    ch          unsigned char ch (ASCII character)
    s           uint8_t pixel ratio multiplier, e.g. 2 = 2:1

Adafruit_GFX(w, h);                 // Constructor
// Assumes setRotation() is 0.

width(void), height(void)           // return w,h -current rotation

setCursor(x,y)                      // coords need not be visable
getCursorX(void);
getCursorY(void);

setRotation(r);                     // 0-3 Cardinal 0°,90°,180°,270°
getRotation(void);                  // 0-3 Cardinal 0°,90°,180°,270°

invertDisplay(bool i);              // True or False

setFont(const GFXfont *f = NULL)

setTextSize(s);                     // ratio multiplier to default
setTextWrap(bool w)                 // True or False

drawPixel(x,y, color);
getPixel(x,y);

drawChar(x,y, ch, color[, bg][, size]);
drawLine(x,y, x1,y1, color);
drawFastVLine(x,y, h, color);
drawFastHLine(x,y, w, color);
drawRect(x,y, w,h, color);
drawRoundRect(x,y, w,h, r, color);
drawCircle(x,y, r, color);
drawTriangle(x,y, x1,y1, x2,y2, color);

fillScreen(color);
fillRect(x,y, w,h, color);
fillRoundRect(x,y, w,h, r, color);
fillCircle(x,y, r, color);
fillTriangle(x,y, x1,y1, x2,y2, color);

drawBitmap(x,y, uint8_t [*]bitmap[], w,h, color[, bg]);
drawRGBBitmap((x,y, uint8_t [*]bitmap[], w,h);

byteSwap(void);
*******************************************************************/
```
<hr>
