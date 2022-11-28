/* 
 * Written by Max Leon Guwa (OrangePurgatory; https://github.com/OrangePurgatory)
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


#include <Servo.h>

// defining pins for servo data send
int servoPin1 = 9;
int servoPin2 = 10;
int relay_pin = 12;
int led_pin = 13;

// defining variables
int in = 0;
int servoAngle = 0;

// defining both servos
Servo servo1;
Servo servo2;

void setup() {
  // defining bitrate of serial input
  Serial.begin(19200);
  pinMode(relay_pin, OUTPUT);
  bool active = false;
  while (!active) {
    while(Serial.available()) {
        char c = Serial.read();
        if (c == 'i') {
            Serial.write('i');
            active = true;
            digitalWrite(led_pin, LOW);
            break;
        } else {
          digitalWrite(led_pin, HIGH);
          break;
        }
    }
  }
}


void loop() {
  while (Serial.available()) { // while serial is sending data -
    char in = Serial.read(); // - read data received
    // depending on what data is being recieved, it should turn either of the servos to the stated angle
    // servo1 (fan speed)
    // exact angles still TBD
    Serial.println(in);
      if (in == 'c') {
        servo1.attach(servoPin1);
        delay(100);
        servo1.write(30);
        delay(1000);
        servo1.detach();
     } else if (in == 'd') {
        servo1.attach(servoPin1);
        delay(100);
        servo1.write(60);
        delay(1000);
        servo1.detach();
     } else if (in == 'e') {
        servo1.attach(servoPin1);
        delay(100);
        servo1.write(90);
        delay(1000);
        servo1.detach();
     } else if (in == 'f') {
        servo1.attach(servoPin1);
        delay(100);
        servo1.write(120);
        delay(1000);
        servo1.detach();
     // servo2 (off/on)
     // exact angles still TBD
     } else if (in == 'a') {
        servo2.attach(servoPin2);
        delay(100);
        servo2.write(0);
        delay(1000);
        servo2.detach();
     } else if (in == 'b') {
        servo2.attach(servoPin2);
        delay(100);
        servo2.write(90);
        delay(1000);
        servo2.detach();
     // relay (off/on)
     } else if (in = 'g') {
        digitalWrite(relay_pin, LOW);
     } else if (in = 'h') {
        digitalWrite(relay_pin, HIGH);
     }
  }
}