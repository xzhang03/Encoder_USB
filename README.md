# Encoder_USB
 USB-based quad encoder

Two equavalent versions that use Adafruit Trinket M0 and Seeeduino Xiao respectively. Seeeduino Xiao RP2040 would also work.

Uploading tip: The M0 processer that both boards use sometimes needs to be forced into bootloading mode before Arduino IDE can upload the binaries. To do so in Trinket M0, double tap the reset button after plugging the USB. To do so in Seeeduino Xiao, use a wire to short the two reset pins twice (mimicking a double button push) next to the USB-C socket after plugging in the USB. These steps archieve the same purpose.

Current limiting resistor (R1) range: at least 150-350 Ohm if not wider.

Trinket M0: https://learn.adafruit.com/adafruit-trinket-m0-circuitpython-arduino/pinouts

![Schematic](https://github.com/xzhang03/Encoder_USB/blob/main/Trinket%20variant/Schematic_IR%20rotary%20encoder%20trinket%20v1_2022-12-29.png)

Seeeduino Xiao: https://wiki.seeedstudio.com/Seeeduino-XIAO/

![Schematic](https://github.com/xzhang03/Encoder_USB/blob/main/Xiao%20variant/Schematic_IR%20rotary%20encoder%20xiao%20v1_2022-12-18.png)

Trinket M0 for Bruker scope:

![Schematic](https://github.com/xzhang03/Encoder_USB/blob/main/Encoder%20bruker/PCB/Schematic_IR%20rotary%20encoder%20bruker%20trinket_2024-11-13.png)
