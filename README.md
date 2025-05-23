# ESP32-S3 1.54in TFT Expansion Board with Speaker <br/>_(and Microphone, & Audio Amplifier)_

***A WORK IN PROGRESS*** &nbsp;—&nbsp; Prof. Michael P. Harris

ESP32-S3 1.54in TFT Expansion Board with Speaker
![ESP32-S3 1.54in TFT Expansion Board with Speaker](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%201.54in%20TFT%20Expansion%20Board%20with%20Speaker.jpg)


## Compatible Development boards:

ESP32-S3 N16R8 Development Board with Speaker and 1.54in TFT Display<br/>
&nbsp; &nbsp; &nbsp; Expansion Adapter Kit for DIY AI Type-C Wifi Module ESP32-S3

```
ESP32-S3-WROOM-1 “pin-compliant” Development boards:     Pins   CAM SD RGB LEDs
                                                                       LED
 1. Espressif ESP32-S3-DevKitC-1 (no camera, no SD card)  44            ✓  1+RGB
 2. YD-ESP32-S3 (ESP32-S3-WROOM-1 Dev) (DevKitC-1 clone)  44            ✓  3+RGB
 3. WaveShare ESP32-S3-DEV-KIT-N8R8    (DevKitC-1 clone)  44            ✓  1+RGB
 4. GOOUUU ESP32-S3-CAM     (DevKitC-1 clone + CAM + SD)  40     ✓  ✓  ✓  2+RGB
 5. ESP32-S3-WROOM CAM   (FREENOVE ESP32-S3-WROOM clone)  40     ✓  ✓  ✓  4+RGB
 6. FREENOVE ESP32-S3-WROOM (CAM)                         40     ✓  ✓  ✓  4+RGB
 7. FREENOVE ESP32-S3-WROOM-Lite (no camera)              40            ✓  4+RGB
 8. WeAct Studio ESP32-S3-A/B Core Board                  44            ✓  1+RGB
```
> [1. Espressif ESP32-S3-DevKitC-1](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/1.%20ESP32-S3-DevKitC-1.jpg)<br/>
> [2. YD-ESP32-S3 (ESP32-S3-WROOM-1 Dev)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/2.%20YD-ESP32-S3%20(ESP32-S3-DevKitC-1%20clone).jpg)<br/>
> [3. WaveShare ESP32-S3-DEV-KIT-N8R8](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/3.%20WaveShare%20ESP32-S3-DEV-Kit-N8R8.jpg)<br/>
> [4. GOOUUU ESP32-S3-CAM](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/4.%20GOOUUU%20ESP32-S3-CAM.jpg)<br/>
> [5. ESP32-S3-WROOM (CAM)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/5.%20ESP32-S3-WROOM%20(CAM%20Module).jpg)<br/>
> [6. FREENOVE ESP32-S3-WROOM (CAM)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/6.%20FREENOVE%20ESP32-S3-WROOM%20(CAM).jpg)<br/>
> [7. FREENOVE ESP32-S3-WROOM-Lite](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/7.%20FREENOVE%20ESP32-S3-WROOM-Lite.jpg)<br/>
> [8. WeAct Studio ESP32-S3-A/B Core Board](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/8.%20WeAct%20Studio%20ESP32-S3-AB.jpg)


## NOTES: ##
<hr>

### 【1】 Espressif ESP-S3-DevKitC-1 — &nbsp;44-pin _(40-pin compatible)_ header pins

Header pins _(dual on one side)_ supports **both** ESP32-S3 Development Board widths…<br/>
<br/>
Almost _{...extra pins top and bottom}_ the same pinout as the<br/>
ESP32-S3-WROOM (CAM), &nbsp;and&nbsp; ESP32-S3-GOOUUU-CAM.

![ESP32-S3 1.54in TFT Expansion Board with Speaker - header pins](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%201.54in%20TFT%20Expansion%20Board%20with%20Speaker-1.1.jpg)

```
Xtensa® 32-bit   ESP32-S3-DevKitC-1         ESP32-S3-WROOM-1 N16R8
Dual-core LX7         (44-pins)
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
A16      G17 10|o ¯  ¨¨|LDO[]   PWR ¤|35 G38               SPI -ALT-
A17      G18 11|o ¯  ¨¨|___-     ¤  o|34 G37 PSRAM         —————————
I²C SDA  G8  12|o RGB     ¬ ¬       o|33 G36 PSRAM         G42  SCLK
A2       G3  13|o ‹¤›48   ¨ ¨       o|32 G35 PSRAM         G41  MOSI
LOG      G46 14|o      ........ ·   o|31 G0  [BOOT]         -1  MISO
I²C SCL  G9  15|o ¨ ¨  |CP2102| ¨   o|30 G45                G0  RST
SPI SS   G10 16|o ¨¨   '''''''' ¨   o|29 G48 RGB LED       G45  DC
SPI MOSI G11 17|o BOOT .......  RST o|28 G47               G47  CS
SPI SCK  G12 18|o ‹•›  '''''''  ‹•› o|27 G21               G21  BL*
SPI MISO G13 19|o                   ø|26 G20 A19 D-
A13      G14 20|o  _____ O T _____  ø|25 G19 A20 D+        I²C -ALT-
         5V0 21|o | USB |T T| USB | o|24 GND               —————————
         GND 22|o |  C  |G L|  C  | o|23 GND               1. *  GND
               '——'ESP32'———'UART0'——'                     2. *  3V3
                                         G48 RGB_BUILTIN,  3. G1 SDA
                                         LED_BUILTIN       4. G2 SCL
```
### ESP32-S3 Pins Summary:
0…18 GPIO,&nbsp; 19…20 D+/D-,&nbsp; 21 GPIO,&nbsp;
22…25 Do Not Exist,&nbsp; 26…32 QSPI ƒlash,&nbsp; 33…34 Missing,&nbsp;
35…42 GPIO,&nbsp; 43…44 TX/RX,&nbsp; 45…48 GPIO<br/>
&nbsp; &nbsp; _pins_arduino.h_ ***~*** **ESP32-S3-DevKitC-1**
<hr>

### 【2】 The 44-pin MCU headers are pin-compatible with:
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
<hr>

![ESP32-S3 1.54in TFT Expansion Board with Speaker-5.2](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%201.54in%20TFT%20Expansion%20Board%20with%20Speaker-5.2.jpg)

### 【3】 LCD 1.54in 240×240 color IPS TFT (ST7789T3)

The TFT Display was identified by (1) "1.54 Inch TFT Display" in the
title and (2) the picture of the _10-pin ribbon connection_ for the
display on the back of the Expansion Adapter. The TFT Display is a:
1.54in TFT LCD Module, IPS color 240×240, 10Pin Plug-in strip,
ST7789V2 Driver.

![LCD 1.54in 240×240 color IPS TFT (ST7789T3)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/LCD%201.54in%20240%C3%97240%20color%20IPS%20TFT%2010-pin%20(ST7789T3).jpg)<br/>
![ESP32-S3 1.54in TFT Expansion Board with Speaker-2.1](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%201.54in%20TFT%20Expansion%20Board%20with%20Speaker-2.1.jpg)

```
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
```
<hr>

### 【4】 22-pin single-row I/O Interface header: (½ the availiable pins)
![ESP32-S3 1.54in TFT Expansion Board with Speaker-4.1](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%201.54in%20TFT%20Expansion%20Board%20with%20Speaker-4.1.jpg)

```
                            .——Interface Pins absent from I/O header——.
                            | G4 INMP441   Mic   LCD TFT   G43  TX›   |
    3V3   o  1.             | G5 INMP441   Mic   ———————   G44  RX‹   |
    G1    o  2.             | G6 INMP441   Mic   G42 BLK              |
    G2    o  3.             |                    G41 CS    G37* PSRAM |
    G39   o  4.             | G7 MAX98357A Amp   G40 RS/DC G36* PSRAM |
    G38   o  5.             |G15 MAX98357A Amp   G45 RST   G35* PSRAM |
    G0    o  6.  [BOOT]     |G16 MAX98357A Amp   G47 SDA              |
    G48   o  7.  RGB LED    |                    G21 SCL              |
    G20   o  8.  USB_D-     '—————————————————————————————————————————'
    G19   o  9.  USB_D+             {Pins  10..22 I/O header}
    G17   o 10.  ------------------------------------------------------
    G18   o 11.                     {match 10..22 MCU header}
    G8    o 12.  I²C SDA
    G3    o 13.
    G46   o 14.
    G9    o 15.  I²C SCL
    G10   o 16.  SPI SS
    G11   o 17.  SPI MOSI
    G12   o 18.  SPI SCK
    G13   o 19.  SPI MISO
    G14   o 20.
    5V0   o 21.
    GND   o 22.
```
<hr>

### 【5】 INMP441 Microphone “pass-through” hole & icon on top-side:
![MEMS digital microphone (INMP441)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/INMP441%20I%C2%B2S%20Mic.jpg)

```
        o PDM Mic chip mounted on the bottom-side.
        o (_guess_) MEMS digital microphone (INMP441)
        o 6-Pins: possible configuration:
            L/R Left/Right Channel  Short Connect to GND
            WS  Data Select         G4
            SCK Data Clock          G5
            SD  Data Out            G6
            VDD                     3V3
            GND                     Ground
```
## INMP441 I²S Mic

### INMP441 I²S Mic introduction:

The INMP441 is a high performance, low power, digital output,
“omnidirectional” MEMS microphone with ‘bottom port’. The complete
INMP441 solution consists of a MEMS sensor, signal conditioning,
analog to digital converter, anti-aliasing filter, power management
and industry standard 24-bit I²S interface.

The I²S interface allows the INMP441 to be directly connected to
digital processors such as DSPs and microcontrollers without the
need for an audio codec for use in the system.

The INMP441 has a high “signal-to-noise ratio” and is an excellent
choice for near field applications. The INMP441 has a flat wideband
frequency response that results in high definition of natural sound.

### INMP441 I²S Mic Features:

1. Digital I²S interface with high precision 24-bit data
2. High signal to noise ratio is 61 dBA
3. High sensitivity - 26 dBFS
4. Stable frequency response from 60 Hz to 15 kHz
5. Low power consumption: low current consumption 1.4 mA
6. High PSR: -75 dBFS

### INMP441 I²S Mic Interface definition:

1. GND: power ground
2. VDD: Input power, 1.8V to 3.3V.
3.  SD: Serial Data output of the I²S interface.
4. SCK: Serial data clock for I²S interface.
5.  WS: Serial data word selection for I²S interface.
6. L/R: Left/Right channel selection.
>   When set to LOW, the microphone outputs a signal on the Left
>   channel of the I²S frame.  When set to HIGH, the microphone
>   outputs signals on the Right channel of the I²S frame.

This product provides tutorials for using ESP32 modules with I²S functionality:

### Connect to your INMP441:
```
    INMP441     ESP32-S3        ESP32-S2
    ———————     ————————        ————————
      SCK        GPIO4           GPIO14
      SD         GPIO5           GPIO32
      WS         GPIO6           GPIO15
      L/R        GND (Left)      GND (Left)
      GND        GND             GND
      VDD        3V3             3V3
```

### What is the difference between an “**Omnidirectional**” microphone and a “**Unidirectional**” microphone?

First of all, understand that the sound divergence is all-round. One
person speaks and divergence in the air. As for how far it can pass,
it depends on many factors.

1. **Directional microphone**, the general pickup radius is very small,
    30cm is a big one... single use, put it on the mouth, the sound quality
    is very good, because it is not picked up again.<br/><br/>

    The shape is generally a goose neck, a rod, a curved rod, to your mouth,
    directly, just listen to your voice. With a single-point microphone,
    the ‘sensitivity’ is limited to a certain range.<br/><br/>

    If ‘Sensitivity’ is too high, it causes sharp whistling, etc., involving
    many other devices. As for why not make a big pickup radius, there is a
    reason we’ll discuss later.

2. **Omnidirectional microphone**, the general pickup radius is very large,
    one meter, two meters, three meters five meters, compared with ten centimeters,
    this ‘sensitivity’ level is very different. It is not just picking a persons’
    voice, but multiple people, five six, seven eight or even ten.<br/><br/>

    Omnidirectional microphones are highly sensitive. The omnidirectional microphone
    pickup radius is too large, and it will pick up more ambient noise, so the sound
    quality is not as good as the single-point microphone, unless you do very good
    ‘noise reduction’.<br/><br/>

    There is definitely a difference between collective use and single-person service.
    But omnidirectional has a benefit, the wiring is simple, not one to one. Suitable
    for small meetings, ad hoc meetings, some remote discussions, and  remote operations.

3. Single-point Mics generally supports local amplification, Omnidirectional microphones
    generally do not support local amplification. It should be noted that because of
    such high sensitivity, the local amplification whistling is very scary, and the
    current technology is difficult to deal with.

_to be continued..._
<hr>

### 【6】 Large on-board Speaker on top:<br/> _(with MAX98357A amplifier on bottom)_
![MAX98357A I²S Audio Amplifier](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/MAX98357A%20I%C2%B2S%20Amp.jpg)

```
        o (_guess_) I²S interface, possibly I²S 3W MAX98357A Audio Amp
        o 7-Pins: possible MAX98357A Amplifier configuration:
            LRC Left Right Clock    G16
            BCLK Bit Clock          G15
            DIN Digital Signal      G7
            GAIN                    Short Connect to GND
            SD (Channel)            Short Connect to GND
            GND                     Ground
            Vin                     3V3


        o External Speaker interface: (+ —)
            Audio+  Connect to Speaker Positive (usually Red wire)
            Audio-  Connect to Speaker Negative
```
## MAX98357A I²S Amp

### MAX98357A I²S Amp specifications:

1. Output power: 4h 3.2W, 10pc THD, 8h 1.8W, 10pc THD, with 5V power supply
2. PSRR: 77 decibels, typical @1 KHZ
3. Sampling rate of I²S ranges from 8kHz to 96kHz
4. You don't need MCLK
5. Five pin optional gain: 3db, 6db, 9db, 12db, 15db
6. Excellent click and pop suppression
7. Hot shutdown protection

The ***MAX98357A I²S Amplifier*** takes standard I²S digital audio input and
not only decodes it into an ‘Analog signal’,&nbsp; but also amplifies it directly
to a speaker.&nbsp; Perfect for adding compact amplified sound.&nbsp; It takes 2
sources &nbsp;_(I²SDAC and AMP)_&nbsp; and combines them into one.

**I²S** _(not to be confused with **I²C**)_, in the digital Sound Protocol used
to deliver Audio data on a circuit board.&nbsp; Many high-end chips and processors
manage all Audio in a digital I²S format.&nbsp; Then, in order to input or output
data,&nbsp; 3 or 4 pins _(Data Input, Data Output, Bit Clock, and Left/Right
Channel Selection)_ are used.&nbsp; Usually, for Audio devices,&nbsp; there is a
***DAC chip*** that takes I²S and converts it into an Analog signal that can
drive the speakers or headset.

The MAX98357A is small ‘mono’ amplifier that is surprisingly powerful. It
is capable of delivering ‘3.2 Watts’ of power to a ‘4 Ohm’ impedance
speaker _(5 volts power 10%THD)_.&nbsp; Inside the microchip is a ‘D-level’
controller capable of operating between 2.7V and 5.5Vdc.&nbsp; Because the
AMP is class D,&nbsp; it is highly efficient and perfect for portable
and battery-powered projects.&nbsp; It has built-in thermal protection
and overcurrent protection.

The audio input is I²S standard and can use 3.3V or 5V logic data.&nbsp;
The outputs are “bridged” &nbsp;- this means that they are directly connected
to the output, rather than grounded.&nbsp; The output is a ‘~300kHz
square-wave, Pulse-Width Modulation’,&nbsp; which is then “averaged out”
by the speaker coil &nbsp;- no high frequencies are heard.&nbsp;

***What all of this means that you can’t connect the output to another amplifier,&nbsp; 
the MAX98357A should drive the speakers directly.***

There is a ‘Gain’ pin that can be manipulated to change the gain.&nbsp;
By default,&nbsp; the amplifier will give you a gain of ‘9 dB’.&nbsp;
Gain pins can be set to 3db, 6db, 9db, 12db, or 15db by directly
connecting a pull-up resistor or pull-down resistor or wiring.

The ‘Shutdown/Mode’ pins can be used to put the chip in the “shutdown state”
or to set which I²S audio channel is connected to the speaker through the pipeline.&nbsp;
By default,&nbsp; the amplifier will output _(L+R) /2_ stereo mix to mono output.&nbsp;
By adding a resistor,&nbsp; you can change it to output just to the Left or Right.
<hr>

<!---
### 【7】 Additional peripheral chip mounted on the bottom side:
```
        o (_guess_) by inspection an I²C BMA423 3-Axis sensor.
        o possible configuration:
            I²C SDA     G8
            I²C SCL     G9
            IRQ         G14
```
<hr> -->

———————————————————————————————————————————————————
## LCD TFT Display Specifications:
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
        9. A    (BackLight LED Anode   +)
       10. K    (BackLight LED Cathode —)
```
<hr>
