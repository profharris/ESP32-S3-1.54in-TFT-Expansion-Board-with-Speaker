# ESP32-S3 1.54in TFT Expansion Board with Speaker <br/>_(and Microphone, & Audio Amplifier)_

***A WORK IN PROGRESS*** &nbsp;—&nbsp; Prof. Michael P. Harris

ESP32-S3 1.54in TFT Expansion Board with Speaker
![ESP32-S3 1.54in TFT Expansion Board with Speaker](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%201.54in%20TFT%20Expansion%20Board%20with%20Speaker.jpg)


## Compatible Development boards:&nbsp; &nbsp; _(8 and counting...)_

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

### Quick Wiring Guide:

1. Wiring between ESP32-S3-WROOM-1 Development Board and the &nbsp; ST7789 1.54" 240×240 Display:

| ESP32-S3 Dev Board | SPI 1.54" 240×240 TFT  |
|-------------------:|------------------------|
|     GPIO21         | SCL  SPI Clock  (SCLK) |
|     GPIO47         | SDA  SPI Data   (MOSI) |
|     GPIO45         | RES  TFT Reset   (RST) |
|     GPIO40         | DC   Data/Command (DC) |
|     GPIO41         | CS   Chip Select  (CS) |
|     GPIO42         | BL   BackLight    (BL) |

2. Wiring between ESP32-S3-WROOM-1 Development Board and the &nbsp; I²S INMP441 Microphone:

| ESP32-S3 Dev Board | I²S INMP441 Mic        |
|-------------------:|------------------------|
|     GPIO4          | WS   Data Select       |
|     GPIO5          | SCK  Data Clock        |
|     GPIO6          | SD   Data Output       |
|     GND (LOW=Left) | L/R  (Left/Right)      |

3. Wiring between ESP32-S3-WROOM-1 Development Board and the &nbsp; I²S MAX98357A Amplifier:

| ESP32-S3 Dev Board | I²S MAX98357A Amp      |
|-------------------:|------------------------|
|     GPIO7          | DIN   Digital Signal   |
|     GPIO15         | BCLK  Bit Clock        |
|     GPIO16         | LRC   Left Right Clock |
|     GND (LOW=Left) | SD    Channel Select   |
|     GND (9dB Gain) | GAIN                   |
|                    |                        |
|     Audio +        | Speaker Positive  (+)  |
|     Audio -        | Speaker Negative  (-)  |
<hr>

### 【1】 Espressif ESP-S3-DevKitC-1 — &nbsp;44-pin &nbsp;_(40-pin compatible)_&nbsp; header pins

Header pins _(dual on one side)_ supports **both** ESP32-S3 Development Board widths…<br/>
<br/>
Almost _{...extra pins top and bottom}_ the same pinout as the<br/>
ESP32-S3-WROOM (CAM), &nbsp;and&nbsp; ESP32-S3-GOOUUU-CAM.

![ESP32-S3 1.54in TFT Expansion Board with Speaker - header pins](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%201.54in%20TFT%20Expansion%20Board%20with%20Speaker-1.2.jpg)

```
Xtensa® 32-bit      ESP32-S3-DevKitC-1        ESP32-S3-WROOM-1 N16R8
Dual-core LX7            (44-pins)
Dual-core LX7         _______________
 16MB Flash          |  ___   _   __¯|         NO CAMERA MODULE
  8MB PSRAM          | | | |_| |_|   |         NO SD-CARD
 512K SRAM        .——| | |           |——.
            3V3  1|o:|               |:•|44 GND               Hardware
            3V3  2|o:|ESP32S3-WROOM-1|:•|43 G43 TX›           SPI2 HSPI
[RST]       ENT  3|o:|               |:•|42 G44 RX‹           —————————
A3   (WS)   G4   4|o:| Œ Æ   N16R8   |:o|41 G1  A0            G10 SS
A4   (SCK)  G5   5|o:| .··. .   ____ |:o|40 G2  A1            G11 MOSI
A5   (SD)   G6   6|o:| WiFi ß  |QRCD||:o|39 G42     (BL)      G12 SCK
A6   (DIN)  G7   7|o:| °   F©  |____||:o|38 G41     (CS)      G13 MISO
A14  (BCLK) G15  8|o:'———————————————':o|37 G40     (DC)
A15  (LRC)  G16  9|o ·. ¨¨|¯¯¯¬        o|36 G39               Software
A16         G17 10|o ¯  ¨¨|LDO[]   PWR o|35 G38               SPI -ALT-
A17         G18 11|o ¯  ¨¨|___-     ¤  o|34 G37 PSRAM         —————————
I²C SDA     G8  12|o RGB     ¬ ¬       o|33 G36 PSRAM          -1  MISO
A2          G3  13|o ‹¤›IO48 ¨ ¨       o|32 G35 PSRAM         G42  BL
LOG         G46 14|o      ........ ·   o|31 G0  [BOOT]        G41  CS
I²C SCL     G9  15|o ¨ ¨  |CP2102| ¨   o|30 G45     (RST)     G40  DC
SPI SS/CS   G10 16|o ¨¨   '''''''' ¨   ¤|29 G48 RGB LED       G45  RST
SPI MOSI    G11 17|o BOOT .......  RST o|28 G47     (MOSI)    G47  MOSI
SPI SCK     G12 18|o ‹•›  '''''''  ‹•› o|27 G21     (SCLK)    G21  SCK
SPI MISO    G13 19|o                   ø|26 G20 A19 D-
A13         G14 20|o  _____ O T _____  ø|25 G19 A20 D+        I²C -ALT-
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
<hr>

![ESP32-S3 1.54in TFT Expansion Board with Speaker-5.2](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%201.54in%20TFT%20Expansion%20Board%20with%20Speaker-5.2.jpg)

### 【3】 LCD 1.54in 240×240 color IPS TFT (ST7789T3)

The TFT Display was identified by:&nbsp; (1) “1.54 Inch TFT Display” in the
title and &nbsp;(2) the picture of the _10-pin ribbon connection_ for the
display on the back of the Expansion Adapter.&nbsp; The TFT Display appears
to be:&nbsp; a 1.54in LCD Module,&nbsp; IPS color 240×240 TFT,&nbsp;
with a 10Pin plug-in strip,&nbsp; and ST7789V2 Driver.

![LCD 1.54in 240×240 color IPS TFT (ST7789T3)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/LCD%201.54in%20240%C3%97240%20color%20IPS%20TFT%2010-pin%20(ST7789T3).jpg)<br/>
![ESP32-S3 1.54in TFT Expansion Board with Speaker-2.1](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%201.54in%20TFT%20Expansion%20Board%20with%20Speaker-2.1.jpg)

```
Configuration:

        TFT LCD   ESP32-S3
        10-Pin    Pin       Function/Description
        ———————   ————————  ——————————————————————————
        1. GND    GND       System Ground   (GND)
        2. RS     G40       Data/Command    (DC)
        3. CS     G41       SPI Chip Select (CS)
        4. SCL    G21       SPI Clock       (SCK)
        5. SDA    G47       SPI Data        (MOSI)
        6. RST    G45       TFT Reset       (RST)
        7. VDD    3V3       Positive Power  (3.3V)
        8. GND    GND       System Ground   (GND)
        9. A      3V3       BackLight LED Anode   (+)
       10. K      G42       BackLight LED Cathode (-) (BL)

        TFT LCD   ESP32-S3
         8-Pin    Pin       Function/Description
        ———————   ————————  ——————————————————————————
        8. BLK    G42       BackLight Control
        7. CS     G41       SPI Chip Select
        6. RS/DC  G40       Data/Command Select
        5. RES    G45       TFT Reset
        4. SDA    G47       SPI Data (MOSI)
        3. SCL    G21       SPI Clock (SCK)
        2. VDD    3V3       Positive Power (3.3V)
        1. GND    GND       System Ground
```

## 1.54in 240×240 color LCD Display Specifications:
```
LCD 1.54in 240×240 color IPS TFT 10-pin (ST7789T3)
  ◆          Brand Name: Maithoga
  ◆           Driver IC: ST7789T3
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
<hr>

### 【4】 22-pin single-row I/O Interface header: &nbsp;_(½ the availiable pins)_
![ESP32-S3 1.54in TFT Expansion Board with Speaker-4.1](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/ESP32-S3%201.54in%20TFT%20Expansion%20Board%20with%20Speaker-4.1.jpg)

```
                                .——Interface Pins absent from the I/O header——.
                                | G4 INMP441   I²S Mic   LCD TFT   G43  TX›   |
    3V3   o  1.                 | G5 INMP441   I²S Mic   ———————   G44  RX‹   |
    G1    o  2.                 | G6 INMP441   I²S Mic   G42 BLK              |
    G2    o  3.                 |                        G41 CS    G37* PSRAM |
    G39   o  4.                 | G7 MAX98357A I²S Amp   G40 RS/DC G36* PSRAM |
    G38   o  5.                 |G15 MAX98357A I²S Amp   G45 RST   G35* PSRAM |
    G0    o  6.  [BOOT]         |G16 MAX98357A I²S Amp   G47 SDA              |
    G48   o  7.  RGB LED        |                        G21 SCL              |
    G20   o  8.  USB D-         '—————————————————————————————————————————————'
    G19   o  9.  USB D+                 {Pins  10..22 I/O header}
    G17   o 10.  --------------------------------------------------------------
    G18   o 11.                         {match 10..22 MCU header}
    G8    o 12.  I²C SDA
    G3    o 13.      ‘JTAG’
    G46   o 14.      ‘LOG’
    G9    o 15.  I²C SCL
    G10   o 16.  SPI SS/CS
    G11   o 17.  SPI MOSI
    G12   o 18.  SPI SCK
    G13   o 19.  SPI MISO
    G14   o 20.
    5V0   o 21.
    GND   o 22.
```
<hr>

### 【5】 INMP441 &nbsp;I²S Microphone:&nbsp; “pass-through” hole & icon on the top-side:
![MEMS digital microphone (INMP441)](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/INMP441%20I%C2%B2S%20Mic.jpg)

```
        o I²S Mic chip mounted on the bottom-side of the Expansion Board.
        o (_guess_) I²S MEMS PDM Digital Microphone ( **INMP441** )
        o 6-Pins:   Possible configuration:
            L/R Left/Right Channel | Connect to GND (Left)
            WS  Data Select        | G4
            SCK Data Clock         | G5
            SD  Data Out           | G6
            VDD                    | 3V3
            GND                    | Ground
```

## INMP441 &nbsp;I²S MEMS PDM Digital Microphone

### INMP441 I²S Microphone Introduction:

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

### INMP441 I²S Mic Interface definition:

1. GND:&nbsp; Power Ground
2. VDD:&nbsp; Input Power, 1.8V to 3.3V.
3.  SD:&nbsp; Serial Data output of the I²S interface.
4. SCK:&nbsp; Serial data Clock for the I²S interface.
5.  WS:&nbsp; Serial data Word Selection for the I²S interface.
6. L/R:&nbsp; Left/Right Channel selection.
>   When set to LOW, the microphone outputs a signal on the Left
>   channel of the I²S frame.  When set to HIGH, the microphone
>   outputs signals on the Right channel of the I²S frame.

### Connect to your INMP441 I²S Microphone:
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
<hr>

### INMP441 I²S Microphone sample program:

#### INMP441-I2S-Mic-sample.ino
```C++
/* INMP441-I2S-Mic-sample.ino
 * Requires an INMP441 I²S Microphone
 *
 * 1. Sample the sound from an INMP441 I²S Microphone.
 * 2. Display the “Audio Waveforms” on the Arduino IDE Serial Plotter.
 *
 * https://dronebotworkshop.com/esp32-i2s/
 */

/* -----------------------------------------------------------------
 1. We start by including the ESP32 I²S driver.
 2. We then define the connections to our INMP441 I²S Microphone. If
    you wish you can rewire the microphone & change the code here.
 3. The ESP32 has two internal I²S processors. We will be using the
    first one, “I²S Port 0”. We also define the length of our input
    data buffer.
 4. Next, we have a function called “I2S_install()”, which sets up
    the I²S port parameters.
 5. A second function, “I2S_setPin()”, sets the physical connection
    to the I²S device, which in our case is our INMP441 Microphone.
 6. In setup(), we set up our Serial connection, as we will be using
    the ‘Serial Plotter’ to display our “Audio Waveforms”.  We then
    call our two functions to set up the I²S port, and then start it
    with a third ‘built-in’ function, “i2s_start()”.
 7. Our loop() starts with a “false” Print statement, this just
    causes two constants to be printed to steady the reading on the
    ‘Serial Plotter’, which otherwise will dynamically change its’
    Y-axis scale.
 8. We then read data from the INMP441 Microphone and place it in
    our data buffer. If the data is good, we read it out and display
    the “Audio Waveforms” on the Serial Plotter.

    Testing the INMP441 I²S Microphone:
    
    Hook everything up, load the sketch and open the Serial Plotter. 
    You should see a representation of the sound (Audio Waveforms)
    that the INMP441 Microphone is getting. You can adjust the 
    “sensitivity” by altering the ‘rangeLimit’ variable in the Loop.

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
  // False print statements to “lock range” on Serial Plotter display
  // Change the ‘rangeLimit’ value to adjust “sensitivity”.
  int rangeLimit = 3000;
  Serial.print(rangeLimit * -1);
  Serial.print(" ");
  Serial.print(rangeLimit);
  Serial.print(" ");

  // Get I²S Data and place in the Data buffer.
  size_t bytesIn   = 0;
  esp_err_t result = i2s_read(I2S_PORT, &sBuffer, bufferLen, &bytesIn, portMAX_DELAY);

  if(result == ESP_OK) {
    int16_t samplesRead = bytesIn / 8;
    if(samplesRead > 0) {
      float mean = 0;
      for(int16_t i=0; i < samplesRead; ++i) {
        mean += (sBuffer[i]);
      }
      mean /= samplesRead;              // Average the Data reading.
      Serial.println(mean);             // Print the “Audio Waveforms”
    }                                   //   to the Serial Plotter.
  }
}
```

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
<hr>

### 【6】 Large on-board cavity Speaker on top:<br/> _(with an I²S MAX98357A Audio Amplifier on the bottom)_
![MAX98357A I²S Audio Amplifier](https://github.com/profharris/ESP32-S3-1.54in-TFT-Expansion-Board-with-Speaker/blob/main/images/MAX98357A%20I%C2%B2S%20Amp.jpg)

```
        o (_guess_) I²S interface, possibly I²S 3W ( **MAX98357A** ) Audio Amp
        o 7-Pins:&nbsp; possible I²S MAX98357A Amplifier configuration:
            LRC Left Right Clock    | G16
            BCLK Bit Clock          | G15
            DIN Digital Signal In   | G7
            GAIN                    | Connect to GND (9 dB Gain)
            SD (L/R Channel Select) | Connect to GND (select Left)
            GND                     | Ground
            Vin                     | 3V3


        o External Speaker interface: (+ —)
            Audio+  Connect to Speaker Positive (usually Red wire)
            Audio-  Connect to Speaker Negative
```
## MAX98357A I²S Audio Amplifier

### MAX98357A I²S Amp specifications:

 1. Output Power:&nbsp; 4Ω speakers 3.2W, 10% THD _(Total Harmonic Distortion)_;<br/>
    8Ω speakers 1.8W, 10% THD _(Total Harmonic Distortion)_, with a 5V power supply
 2. PSRR _(Power Supply Rejection Ratio)_:&nbsp; 77 decibels, typical @1 KHZ
 3. I²S Sampling Rate:&nbsp; 8kHz to 96kHz
 4. Five pin optional “Gain”: 3db, 6db, 9db, 12db, 15db
 5. You don’t need a MCLK _(Master Clock signal)_ timing signal
 6. Excellent _click and pop_ suppression
 7. Hot shutdown protection

The ***MAX98357A I²S Amplifier*** takes standard I²S digital audio input and
not only decodes it into an ‘Analog signal’,&nbsp; but also amplifies it directly
to a speaker.&nbsp; Perfect for adding compact amplified sound.&nbsp; It takes 2
sources &nbsp;_(I²SDAC and AMP)_&nbsp; and combines them into one.

**I²S** _(not to be confused with **I²C**)_, in the digital Sound Protocol used
to deliver Audio data on a circuit board.&nbsp; Many high-end chips and processors
manage all Audio in a digital _I²S_ format.&nbsp; Then, in order to input or output
data,&nbsp; 3 or 4 pins _(Data Input, Data Output, Bit Clock, and Left/Right
Channel Selection)_ are used.&nbsp; Usually, for Audio devices,&nbsp; there is a
***DAC chip*** that takes I²S and converts it into an Analog signal that can
drive the speakers or headset.

The **I²S MAX98357A** is small ‘mono’ amplifier that is surprisingly powerful.&nbsp;
It is capable of delivering ‘3.2 Watts’ of power to a ‘4 Ohm’ impedance speaker
_(5 volts power, 10%THD)_.&nbsp; Inside the microchip is a ‘D-level’ controller
capable of operating between 2.7V and 5.5Vdc.&nbsp; Because the AMP is _class D_,&nbsp;
it is highly efficient and perfect for portable and battery-powered projects.&nbsp;
It has built-in _thermal protection_ and _overcurrent protection_.

The audio input is **I²S standard** and can use 3.3V or 5V logic data.&nbsp;
The outputs are “bridged” &nbsp;- this means that they are directly connected
to the output,&nbsp; rather than grounded.&nbsp; The output is a _‘~300kHz
square-wave, Pulse-Width Modulation’_,&nbsp; which is then “averaged out”
by the speaker coil &nbsp;- no high frequencies are heard.&nbsp;

***What all of this means that you can not connect the output to another amplifier,&nbsp;
the I²S MAX98357A should drive the speakers directly.***

There is a _‘Gain’_ pin that can be manipulated to change the signal gain.&nbsp;
By default,&nbsp; the amplifier will give you a Gain of _‘9 dB’_.&nbsp;
Gain pins can be set to 3db, 6db, 9db, 12db, or 15db by directly
connecting a pull-up resistor or pull-down resistor or wiring.

The _‘Shutdown/Mode’_ pins can be used to put the chip in the “shutdown state”&nbsp;
or to set which I²S audio channel is connected to the speaker through the pipeline.&nbsp;
By default,&nbsp; the amplifier will output a _(L+R) /2_ stereo mix to _mono_ output.&nbsp;
By adding a resistor,&nbsp; you can change it to output just to the Left or Right.
<hr>

### MAX98357A I²S Amp sample program:

#### MAX98357-I2S-Amp-SD-Music-Player.ino
```C++
/* MAX98357-I2S-Amp-SD-Music-Player.ino
 *
 * ESP32-S3 microSD_Card I²S Music Player:
 *  Play MP3 files from a microSD_Card
 *  Uses a MAX98357 I²S Amplifier
 *  Uses the ESP32-audioI2S Library:
 *      https://github.com/schreibfaul1/ESP32-audioI2S
 *
 * Using the MAX98357 I²S Amplifier:
 *   The sound source will be an MP3 file that is stored on a
 *   microSD_Card.  This is an extremely basic MP3 player, for
 *   practical use you would need to make a system for navigating
 *   the microSD_Card to play more than one selection.  This sketch
 *   is just to illustrate how to use the MAX98357 I²S Amplifier,
 *   as well as a library that makes working with I²S audio
 *   applications a bit easier.
 *
 * Wiring:
 *
 * MAX98357 I²S Amp                 ESP32-S3-WROOM-1
 * 1. LRC  (Left Right Clock)   --> GPIO16
 * 2. BCLK (Bit Clock)          --> GPIO15
 * 3. DIN  (Digital Signal In)  --> GPIO7
 * 4. GAIN                      --> Connect to GND (9 dB gain)
 * 5. SD   (L/R Channel Select) --> Connect to GND (select Left)
 * 6. GND                       --> GND
 * 7. VIN  (Power)              --> 3V3
 *
 * External Speaker interface: (+ —)
 * Audio+  Connect to Speaker Positive (usually Red wire)
 * Audio-  Connect to Speaker Negative
 *
 * microSD Card                     ESP32-S3-WROOM-1
 * 1. 3V3  (Power)              --> 3V3
 * 2. CS   (Chip Select)        --> GPIO10
 * 3. MOSI (SPI SDI)            --> GPIO11
 * 4. CLK  (SPI Clock)          --> GPIO12
 * 5. MISO (SPI SDO)            --> GPIO13
 * 6. GND                       --> GND
 *
 * https://dronebotworkshop.com/esp32-i2s/
 */

#include "Arduino.h"                // Include required libraries
#include "Audio.h"
#include "SD.h"
#include "FS.h"
                                    // microSD_Card pins
#define SD_CS         10            // microSD_Card Chip Select
#define SPI_MOSI      11            // SPI Data In  (DI)
#define SPI_SCK       12            // SPI Clock    (CLK)
#define SPI_MISO      13            // SPI Data Out (DO)

                                    // MAX98357 I²S Amp pins
#define I2S_DOUT       7            // MAX98357 I²S Amp (DIN)
#define I2S_BCLK      15            //      "
#define I2S_LRC       16            //      "

Audio audio;                        // ESP32-audioI2S Audio object

void setup() {
  Serial.begin(115200);             // Initialize Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  pinMode(SD_CS,      OUTPUT);      // Set microSD_Card CS as OUTPUT
  digitalWrite(SD_CS, HIGH);        // Disable (Active LOW)

  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI); // Initialize the SPI bus

  if(!SD.begin(SD_CS)) {                // Start the microSD_Card
    Serial.println("Error accessing microSD_Card!");
    while(true);
  }

  // Setup MAX98357 I²S Amplifier & Volume control
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(5);                   // Set the Volume

  // Open .mp3 music file on microSD_Card
  audio.connecttoFS(SD,"/MYMUSIC.mp3"); // Change to name of chosen
}                                       // .mp3 file on microSD_Card

void loop() {
  audio.loop();
}
```

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
