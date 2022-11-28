/* 
 * Written by Max Leon Guwa (OrangePurgatory; https://github.com/OrangePurgatory)
 * Verification pending
 * 
 * 
 * Codes:
 * 
 * a: Off
 * b: On
 * c: Speed 1
 * d: Speed 2
 * e: Speed 3
 * f: Speed 4
 * g: Swing Off
 * h: Swing On
 * i: Initialize
 * 
*/

//defining pins
const int relaypin1 = 7;
const int relaypin2 = 8;
const int relaypin3 = 9;
const int relaypin4 = 10;
const int relaypin5 = 11;
const int relaypin6 = 12;
const int ledpin = 13;

// defining variables
int in = 0;


void setup() {
  // defining bitrate of serial input
  Serial.begin(19200);
  //attaching relays
  pinMode(relaypin1, OUTPUT);
  pinMode(relaypin2, OUTPUT);
  pinMode(relaypin3, OUTPUT);
  pinMode(relaypin4, OUTPUT);
  pinMode(relaypin5, OUTPUT);
  pinMode(relaypin6, OUTPUT);
  //initializing
  bool active = false;
  while (!active) {
    while(Serial.available()) {
        char c = Serial.read();
        if (c == 'i') {
            Serial.write('i');
            active = true;
            digitalWrite(ledpin, LOW);
            break;
        } else {
          digitalWrite(ledpin, HIGH);
          break;
        }
    }
  }
}


void loop() {
  while (Serial.available()) { // while serial is sending data -
    char in = Serial.read(); // - read data received
    // relay1-4 (fan speed)
    Serial.println(in);
      if (in == 'c') {
         digitalWrite(relaypin2, LOW);
         digitalWrite(relaypin3, LOW);
         digitalWrite(relaypin4, LOW);
         delay(100);
         digitalWrite(relaypin1, HIGH);
         } else if (in == 'd') {
            digitalWrite(relaypin1, LOW);
            digitalWrite(relaypin3, LOW);
            digitalWrite(relaypin4, LOW);
            delay(100);
            digitalWrite(relaypin2, HIGH);
         } else if (in == 'e') {
            digitalWrite(relaypin1, LOW);
            digitalWrite(relaypin2, LOW);
            digitalWrite(relaypin4, LOW);
            delay(100);
            digitalWrite(relaypin3, HIGH);
         } else if (in == 'f') {
            digitalWrite(relaypin1, LOW);
            digitalWrite(relaypin2, LOW);
            digitalWrite(relaypin3, LOW);
            delay(100);
            digitalWrite(relaypin4, HIGH);
     // relay5 (fan off/on)
         } else if (in == 'a') {
            digitalWrite(relaypin5, LOW);
         } else if (in == 'b') {
            delay(100);
            digitalWrite(relaypin5, HIGH);
     // relay6 (swing off/on)
         } else if (in = 'g') {
            digitalWrite(relaypin6, LOW);
         } else if (in = 'h') {
            delay(100);
            digitalWrite(relaypin6, HIGH);
     }
  }
}