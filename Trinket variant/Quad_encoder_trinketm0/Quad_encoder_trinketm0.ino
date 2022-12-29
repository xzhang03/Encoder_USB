// Make sure encoder library is 1.4.3 or later

#define debug false

// Turn off neopixel
#include <Adafruit_DotStar.h>
#include <SPI.h>
#define NUMPIXELS 1 // Number of LEDs in strip
#define DATAPIN 7
#define CLOCKPIN 8
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);

#include <Encoder.h>
Encoder myEnc(2, 3);

const byte ledpin = 13;
bool led = false;

void setup() {
  Serial.begin(115200);
//  Serial1.begin(1000000);
  myEnc.write(0);

  // Turn off dot star
  strip.begin(); // Initialize pins for output
  strip.setPixelColor(0, 0x000000); // black
  strip.show();  // Turn all LEDs off ASAP

  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, led);
}

void loop() {
  long pos;
  byte *b,m;

  b = (byte *) &pos;  
  pos = myEnc.read();

  if (Serial.available()) {
    m = Serial.read();

    // Adjust for arduino serial encoding
    #if debug
      m = m - '0';
    #endif

    #if !debug 
      // Normal version
      if(m>0) {
        myEnc.write(0);    // zero the position
        pos = 0;
      }
      else {
        Serial.write((byte *) &pos,4);
      }
    #else
      // Debug version
      Serial.print(m);
      Serial.print(" ");
      Serial.println(pos);
    #endif 

    // toggle led
    led = !led;
    digitalWrite(ledpin, led);
  }

//  if(Serial1.available()) {
//    Serial1.read();
//    Serial1.write((byte *) & pos,4);
//  }
  
}
