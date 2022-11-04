#include <Servo.h>

// defining pins for servo data send
int servoPin1 = 9;
int servoPin2 = 10;

// defining variables
int in = 0;
int servoAngle = 0;

// defining both servos
Servo servo1;
Servo servo2;

void setup()
{
  // defining bitrate of serial input
  Serial.begin(19200);
  bool active = false;
  while (!active) {
    while(Serial.available()) {
        char c = Serial.read();
        if (c == 'i') {
            Serial.write('i');
            active = true;
            break;
        }
    }
  }
}

/*
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

void loop() {
  while (Serial.available()) { // while serial is sending data -
    char in = Serial.read(); // - read data received
    // depending on what data is being recieved, it should turn either of the servos to the stated angle
    // servo1 (fan speed)
    // exact angles still TBD
    Serial.println(in);
    // attaching servos
    servo1.attach(servoPin1);
    servo2.attach(servoPin2);
      if (in == 'c') {
        servo1.write(30);
     } else if (in == 'd') {
        servo1.write(60);
     } else if (in == 'e') {
        servo1.write(90);
     } else if (in == 'f') {
        servo1.write(120);
     // servo2 (on/off)
     // exact angles still TBD
     } else if (in == 'a') {
        servo2.write(0);
     } else if (in == 'b') {
        servo2.write(90);
    }
  }
}