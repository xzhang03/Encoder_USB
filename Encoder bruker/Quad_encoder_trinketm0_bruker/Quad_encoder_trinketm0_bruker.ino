// Make sure encoder library is 1.4.3 or later
#define debug false
#define debugstream false

// Turn off neopixel
#include <Adafruit_DotStar.h>
#include <SPI.h>
#define NUMPIXELS 1 // Number of LEDs in strip
#define DATAPIN 7
#define CLOCKPIN 8
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);

#include <Encoder.h>
Encoder myEnc(2, 3); // Switch order to alter direction

// Pins
const byte ledpin = 13;
const byte trigpin = 0;

// Analog out cycle cycle
unsigned long tcycle = 4000; // us, how often analog writes are sent
unsigned long twidth = 2000; // us, how long each analog write is

// Analog voltages (10 bit dac)
// Range: 4 steps forward or backward per cycle. Most of time it should be 1 step, so vsteps are largest in these situations
// indices     =     { 0,   1,   2,   3,   4,   5,   6,   7,    8}
// Step counts =     {-1,  -2,  -3,  -4,   0,   4,   3,   2,    1}
uint16_t vsteps[9] = { 0, 127, 255, 383, 511, 639, 764, 895, 1023};
int8_t vind;
uint8_t max_step = 4;

// Encoder
long pos;

// time variables
unsigned long tnow, t0;

// Bool variables
bool led = false;
bool stepdone = false;

// Serial 
byte m, n;
bool debugflag1;

void setup() {
  Serial.begin(115200);
  myEnc.write(0);

  // Turn off dot star
  strip.begin(); // Initialize pins for output
  strip.setPixelColor(0, 0x000000); // black
  strip.show();  // Turn all LEDs off ASAP

  pinMode(ledpin, OUTPUT);
  pinMode(trigpin, INPUT); // Reserved for the future
  digitalWrite(ledpin, led);

  // Timers
  tnow = micros();
  t0 = micros();

}

void loop() {
  // Time
  tnow = micros();

  // New cycle
  if (((tnow - t0) > tcycle) && !stepdone){
    // Update time
    t0 = tnow;

    // Read
    pos = myEnc.read();

    // Debug 
    #if debug
      if (Serial.available() > 1) {
        // Read
        m = Serial.read();
        n = Serial.read();
        m = m - '0';

        // Manually input pos for testing
        if ((m > 0) && (m < 10)){
          // m   =  1,  2,  3,  4, 5, 6, 7, 8, 9
          // pos = -4, -3, -2, -1, 0, 1, 2, 3, 4
          pos = m - 5;
        }

        Serial.print(m);
        Serial.print(" ");
        Serial.print(n);
        Serial.print(": ");
        Serial.print(pos);

        debugflag1 = true;
      }
    #endif

    // Decide what to write
    // V index
    if (pos == 0){
      // No step
      vind = 4;

      // Update LED to off
      led = false;
    }
    else if (pos > 0){
      // Forward
      vind = 9 - pos;

      // LED indicator on
      led = true;
    }
    else if (pos < 0){
      // Backward
      vind = -(pos + 1);

      // LED indicator on
      led = true;
    }

    // Write
    analogWrite(A0, vsteps[vind]);

    #if debug
      if (debugflag1){
        Serial.print(" ");
        Serial.print(vind);
        Serial.print(" ");
        Serial.println(vsteps[vind]);
        debugflag1 = false;
      }
    #endif
    
    // Update
    stepdone = true;
    myEnc.write(0);

    // led
    digitalWrite(ledpin, led);
    
    // Serial debug
    #if debugstream
      Serial.println(pos);
    #endif
  }
  else if (((tnow - t0) > twidth) && stepdone){
    // Turn off the step
    analogWrite(A0, vsteps[4]);
    stepdone = false;
  }
}
