# Encoder_USB
 USB-based quad encoder

Two equavalent versions that use Adafruit Trinket M0 and Seeeduino Xiao respectively. Seeeduino Xiao RP2040 would also work.

Uploading tip: The M0 processer that both boards use sometimes needs to be forced into bootloading mode before Arduino IDE can upload the binaries. To do so in Trinket M0, double tap the reset button after plugging the USB. To do so in Seeeduino Xiao, use a wire to short the two reset pins twice (mimicking a double button push) next to the USB-C socket after plugging in the USB. These steps archieve the same purpose.

Trinket M0: https://learn.adafruit.com/adafruit-trinket-m0-circuitpython-arduino/pinouts

Seeeduino Xiao: https://wiki.seeedstudio.com/Seeeduino-XIAO/
