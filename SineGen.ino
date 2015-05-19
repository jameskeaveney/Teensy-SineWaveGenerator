/*
  Sine/Square Wave Generator
  JK
  
  Teensy 3.1 (https://www.pjrc.com/teensy/teensy31.html, Farnell order code SC13539, £16.99 ex VAT)
  
  Generates a Sine Wave with specified frequency at 12-bit resolution of DAC output
  Cycles through values in the Waveforms.h lookup file, which are created from 
  a python script and copied in manually
  
  The Teensy is used in preference to the Arduino DUE because the DAC output range
  is the full 0 to 3V3 range, rather than 1/6 to 5/6 of the range. It's also a fair
  bit cheaper, the clock speed is higher (overclocked), and it has a much smaller 
  physical footprint. Buy one, they're great!
  
  ** Original purpose - custom lock-in amplifier reference oscillator signal for use with
     a Faraday-filter laser system being developed in Durham University's Atomic and 
     Molecular Physics group
  
*/

// include lookup table of sine values from waveforms.h
#include "Waveforms.h"

// Pin 13 has the LED on Teensy 3.1 - will use this pin also as the square wave TTL output
int ledpin = 13;

volatile int i = 0;

// the setup routine runs once when you press reset:
IntervalTimer timer0;
FASTRUN void setup() {
  analogWriteResolution(12);
  pinMode(A14,OUTPUT);
  analogWrite(A14,0);
  pinMode(ledpin, OUTPUT);

  timer0.begin(timer0_callback, 1.25);  
}

FASTRUN void timer0_callback() {
  analogWrite(A14, waveformsTable[i]);  // write the selected waveform on DAC

  if (i<256) {
    digitalWrite(ledpin, HIGH);
  }
  else {
    digitalWrite(ledpin, LOW);
  }
  i++;
  if (i==512)
    i=0;
  //delayMicroseconds(samplerate); // to slow it down a bit if required
}

void loop() {
  
}
