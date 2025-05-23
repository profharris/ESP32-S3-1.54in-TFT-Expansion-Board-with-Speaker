# INMP441 I²S Mic

## Product introduction:

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

## Product Features:

1. Digital I²S interface with high precision 24-bit data
2. High signal to noise ratio is 61 dBA
3. High sensitivity - 26 dBFS
4. Stable frequency response from 60 Hz to 15 kHz
5. Low power consumption: low current consumption 1.4 mA
6. High PSR: -75 dBFS

## Interface definition:

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

## Connect to your INMP441:
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

## What is the difference between an “**Omnidirectional**” microphone and a “**Unidirectional**” microphone?

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
