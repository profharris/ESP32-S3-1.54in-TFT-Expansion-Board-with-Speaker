
# MAX98357A I²S Amp

## Product specifications:

1. Output power: 4h 3.2W, 10pc THD, 8h 1.8W, 10pc THD, with 5V power supply
2. PSRR: 77 decibels, typical @1 KHZ
3. Sampling rate of I²S ranges from 8kHz to 96kHz
4. You don't need MCLK
5. Five pin optional gain: 3db, 6db, 9db, 12db, 15db
6. Excellent click and pop suppression
7. Hot shutdown protection

The MAX98357A I²S Amplifier takes standard I²S digital audio input and
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
