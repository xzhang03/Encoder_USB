# USB running encoder for Bruker microscope

## Parts list
1. PCB board (see folder for gerber file)
2. Edge SMA connector (CON-SMA-EDGE-S-ND, Digikey)
3. Adafruit Trinket M0 (Digikey)
4. Beam breaker (1855-1043-ND, Digikey)
5. Through-hole 300 ohm resistor (Amazon, Digikey)
6. Optional: SN74HC14PWR inverter (296-8234-1-ND, Digikey)
7. Optoinal: 0805 50 ohm resistor (Amazon, Digikey)

## Encoding scheme
The dataline is normally 1.65 V, this is the neutral position. Every 6 ms, the encoder will read out a step value from the previous reading. A 4-ms pulse will be used to reflect a non-zero step. The pulse is positive (>1.65 V) for forward steps and negative (<1.65 V) for backward steps. Voltage will be returned to 1.65V for 2 ms at the end of the step to complete the 6 ms pulse cycle. The voltage steps are below:

| Step value (quadrature) | Voltage (V) | DAC value (10 bit) | Lower threshold (V) | Upper threshold (V) |
| ----------------------- | ----------- | ------------------ | ------------------- | ------------------- |
| -1 					  | 0			| 0					 | -					| 0.205					|
| -2					  | 0.410		| 127				 | 0.205				| 0.617					|
| -3					  | 0.823		| 255				 | 0.617				| 1.029					|
| -4					  | 1.235		| 383				 | 1.029				| 1.442					|
| 0						  | 1.648		| 511				 | 1.442				| 1.855					|
| 4						  | 2.061		| 639				 | 1.855				| 2.263					|
| 3						  | 2.465		| 764				 | 2.263				| 2.676					|
| 2						  | 2.887		| 895				 | 2.676				| 3.094					|
| 1						  | 3.3			| 1023				 | 3.094				| -						|


Notes:
1. The max speed that this scheme can read is 4 steps forward or reverse per 6 ms. Speed faster than this is not expected.
2. Please note that the voltage steps are not linear to quadrature readings. This is to increase SNR for the most common step sizes: +1 or -1 quadrature reading.

## Decoder demo
See folder for MATLAB code

![Decoder_demo](https://github.com/xzhang03/Encoder_USB/blob/main/Encoder%20bruker/Decoding/demo.png)