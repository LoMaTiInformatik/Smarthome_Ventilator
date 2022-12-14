/*
 * Written by Max Leon Guwa (OrangePurgatory; https://github.com/OrangePurgatory)
 * Verification done, working
 *
 *
 *
 * Data:
 *
 * a(97): Turn off
 * b(98): Turn on
 * c(99): Speed 1
 * d(100): Speed 2
 * e(101): Speed 3
 * f(102): Speed 4
 * g(103): Swing off
 * h(104): Swing on
 * i(105): Initialisation key (DO NOT SEND!)
 *
 *
*/

// defining pins
const int relaypin1 = 7;
const int relaypin2 = 8;
const int relaypin3 = 9;
const int relaypin4 = 10;
const int relaypin5 = 11;
const int relaypin6 = 12;
const int ledpin = 13;

// defining variables
int in = 0;

void setup()
{
   // defining bitrate of serial input
   digitalWrite(relaypin1, HIGH);
   digitalWrite(relaypin2, HIGH);
   digitalWrite(relaypin3, HIGH);
   digitalWrite(relaypin4, HIGH);
   digitalWrite(relaypin5, HIGH);
   digitalWrite(relaypin6, HIGH);
   Serial.begin(19200);
   // attaching relays
   pinMode(relaypin1, OUTPUT);
   
   pinMode(relaypin2, OUTPUT);
   
   pinMode(relaypin3, OUTPUT);
   
   pinMode(relaypin4, OUTPUT);
   
   pinMode(relaypin5, OUTPUT);
   
   pinMode(relaypin6, OUTPUT);
   // initializing
   bool active = false;
   while (!active)
   {
      while (Serial.available())
      {
         char c = Serial.read();
         if (c == 'i')
         {
            Serial.write('i');
            active = true;
            digitalWrite(ledpin, LOW);
            break;
         }
         else
         {
            digitalWrite(ledpin, HIGH);
            break;
         }
      }
   }
}

void loop()
{
   while (Serial.available())
   {                           // while serial is sending data -
      int in = Serial.read(); // - read data received
      // relay1-4 (fan speed)
      Serial.println(in);
      if (in == 99)
      {
         digitalWrite(relaypin2, HIGH);
         digitalWrite(relaypin3, HIGH);
         digitalWrite(relaypin4, HIGH);
         delay(500);
         digitalWrite(relaypin1, LOW);
      }
      else if (in == 100)
      {
         digitalWrite(relaypin1, HIGH);
         digitalWrite(relaypin3, HIGH);
         digitalWrite(relaypin4, HIGH);
         delay(500);
         digitalWrite(relaypin2, LOW);
      }
      else if (in == 101)
      {
         digitalWrite(relaypin1, HIGH);
         digitalWrite(relaypin2, HIGH);
         digitalWrite(relaypin4, HIGH);
         delay(500);
         digitalWrite(relaypin3, LOW);
      }
      else if (in == 102)
      {
         digitalWrite(relaypin1, HIGH);
         digitalWrite(relaypin2, HIGH);
         digitalWrite(relaypin3, HIGH);
         delay(500);
         digitalWrite(relaypin4, LOW);
         // relay5 (fan off/on)
      }
      else if (in == 97)
      {
         digitalWrite(relaypin5, HIGH);
      }
      else if (in == 98)
      {
         delay(100);
         digitalWrite(relaypin5, LOW);
         // relay6 (swing off/on)
      }
      else if (in == 103)
      {
         digitalWrite(relaypin6, HIGH);
      }
      else if (in == 104)
      {
         delay(100);
         digitalWrite(relaypin6, LOW);
      }
   }
}