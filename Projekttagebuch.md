<!--Written by Max Leon Guwa (OrangePurgatory; https://github.com/OrangePurgatory)-->


<h1 align="center">Arduinogesteuerter Ventilator - Projekttagebuch</h1> 
<h3 align="center"> Ein Projekt von Max, Lois und Timo 11p </h3>
</br>


<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://user-images.githubusercontent.com/105984356/186677878-5eddbf06-304d-4ea7-90db-5ddba9e40dbf.png">
  <source media="(prefers-color-scheme: light)" srcset="https://user-images.githubusercontent.com/105984356/186676647-16dacef0-4117-4750-afc1-1d4d6409e6d3.png">
  <img alt="" src="">
</picture>

<h3 align="left">Stormarnschule Ahrensburg <br/> Informatik, Buhl <br/> Schuljahr 2022/23, 1. Halbjahr </br> </h3> </div>
<h3 align="left"> &#10132; <a href="https://github.com/LoMaTiInformatik/Smarthome_Ventilator/blob/main/README.md"> Projektseite</a> </h3> 
</br>



## Inhalt
<p><a href="#kapitell">1. Einleitung</a></p>
<p style="margin-bottom: 5px;">
<details style="margin: 0px !important;">
<summary>2. Stundenprotokolle</summary>
<ul>
  <li><a href="#stundenprotokoll-zum-22082022">Stundenprotokoll zum 22.08.2022</a></li>
  <li><a href="#stundenprotokoll-zum-25082022">Stundenprotokoll zum 25.08.2022</a></li>
  <li><a href="#stundenprotokoll-zum-29082022">Stundenprotokoll zum 29.08.2022</a></li>
  <li><a href="#stundenprotokoll-zum-05092022">Stundenprotokoll zum 05.09.2022</a></li>
  <li><a href="#stundenprotokoll-zum-08092022">Stundenprotokoll zum 08.09.2022</a></li>
  <li><a href="#stundenprotokoll-zum-12092022">Stundenprotokoll zum 12.09.2022</a></li>
  <li><a href="#stundenprotokoll-zum-19092022">Stundenprotokoll zum 19.09.2022</a></li>
  <li><a href="#stundenprotokoll-zum-22092022">Stundenprotokoll zum 22.09.2022</a></li>
  <li><a href="#stundenprotokoll-zum-26092022">Stundenprotokoll zum 26.09.2022</a></li>
  <li><a href="#stundenprotokoll-zum-06102022">Stundenprotokoll zum 06.10.2022</a></li>
  <li><a href="#stundenprotokoll-zum-24102022">Stundenprotokoll zum 24.10.2022</a></li>
  <li><a href="#stundenprotokoll-zum-03112022">Stundenprotokoll zum 03.11.2022</a></li>
  <li><a href="#stundenprotokoll-zum-07112022">Stundenprotokoll zum 07.11.2022</a></li>
  <li><a href="#stundenprotokoll-zum-17112022">Stundenprotokoll zum 17.11.2022</a></li>
  <li><a href="#stundenprotokoll-zum-21112022">Stundenprotokoll zum 21.11.2022</a></li>
  <li><a href="#stunden-darauffolgend-zusammengefasst">Stunden darrauffolgend zusammengefasst</a></li>
</ul></details></p>
<p style="margin-top: 5px;"><a href="#kapitel3">3. Ideen und To Do's</a></p>
<p><a href="#kapitel4">4. Materialien</a></p>
<p><a href="#kapitel5">5. Quellen</a></p>


<h2 id="kapitell">1. Einleitung</h2>
Hallo und herzlich Wilkommen zu unserem Projekttagebuch. Hier protokollieren wir unseren Arbeitsprozess, um später wieder zurückgucken zu können und sehen, was wir an welchem Tag genau gemacht haben. Einige Protokolle enthalten Beispielcodes, um unseren Arbeitsprozess zu visualisieren.

Den gesamten Code kann man jederzeit in diesem Repository im /src/ Ordner abrufen.
<details>
<summary>Links zu dem Code</summary>
<p><a href="https://github.com/LoMaTiInformatik/Smarthome_Ventilator/blob/main/src/server/serverhomebridge.ino">Code vom Server(Kommunikations-Arduino)</a></p>
<p><a href="https://github.com/LoMaTiInformatik/Smarthome_Ventilator/blob/main/src/controller/controller.ino">Code vom Controller(Steuernder-Arduino)</a></p>
</details>


<h2 id="kapitel2">2. Stundenprotokoll</a></h2></li>

### Stundenprotokoll zum 22.08.2022
Wir haben uns heute überlegt, wie und an welchem Projekt wir über die nächsten 3 Monate arbeiten wollen. Dies stellte sich als nicht sehr einfach dar, da wir die Sorgen hatten, dass wir nicht kommplett über die Zeit mit einigen Projektideen beschäftigen werden sein würden und früher als die angesetze Deadline fertig werden würden. Nack einigen Internetrecherchen und langem Überlegen (teilweise auch schon vor dem Unterricht), haben wir uns dazu entschlossen folgendes Projekt anzufangen:
- Ein Ventilator, der über ein externes Touchdisplay angeschaltet und bedient werden kann.
- (Weitere Details wurden noch nicht ausgearbeitet und müssen noch im Verlauf entschieden werden.) </br>

Außerdem haben wir diese Repository erstellt und eingerichtet.

### Stundenprotokoll zum 25.08.2022
Heute haben wir versucht ein Prototyp von unserem Vorhaben zu erstellen. Dies haben wir mithilfe von einem Motor und Arduino versucht. Erfolgreich waren wir jedoch nicht. Uns scheint es so, dass der Arduino nicht eine solche Stromstärke erreichen kann und sich einfach abschaltet. Allerdings benötigt dies weitere Inspektion. Unser Projekt sollte das Problem aber nicht beeinträchtigen, da der Ventilator nicht direckt über den Arduino laufen soll, sondern dierekt aus der Steckdose betrieben werden soll. </br>
Zusätzlich haben wir es geschafft eine LED mithilfe eines Regulators zu steuern. </br>

### Stundenprotokoll zum 29.08.2022
Die heutige Stunde hat ebenfalls damit angefangen, dass wir eine LED mithilfe eines Regulators gesteuert bekommen haben. Den selben Code haben wir dann nochmal mit dem Motor ausprobiert und es hat nicht funktioniert. Es stellte sich herraus, dass der Arduino nur 220 mA ausgeben kann und der Motor deutlich mehr als das benötigt. Nach dieser Erkenntniss, haben wir uns daran gemacht das WiFi Modul, das für eine kabellose Übertragung von Daten benötigt wird, zum laufen zu bekommen, mit Erfolg. Jedoch ist das Modul noch nicht vollständig funktionstüchtig, eine Datenübertragung ist allerdings möglich. 
<details>
  <summary>Code für das steueren einer LED</summary>
  
```c
#define LED 9
#define POTENT 1

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(POTENT, INPUT);

  Serial.begin(9600);
}

void loop() {
  analogWrite(LED, map(analogRead(POTENT), 0, 1023, 0, 255));
  Serial.println(analogRead(POTENT));
}
```
</details>


### Stundenprotokoll zum 05.09.2022
Vor der heutigen Stunde haben wir zu Hause einen Code für das WLAN Modul geschrieben. Diesen Code haben wir dann auf den Arduino gespielt und damit versucht das WLAN Modul zum laufen zu bekommen. In dem Prozess wurde allerdings das WLAN Modul beschädigt und ist nun inoperabel. Allerdings haben wir ein neues Modul gefunden und dieses hat dann wieder Antworten gesendet. Ein Paar weitere Tweaks am Code und das WLAN Modul hat funktioniert. </br>

### Stundenprotokoll zum 08.09.2022
Wir haben uns heute dazu entschieden die Idee des WLAN Moduls erstmal zu streichen. Die Entscheidung ist gefallen, da schon zum zweiten Mal ein WLAN Modul kaputt gegangen ist und es unmöglich für uns wurde diese für unser Projekt zu verwenden. 

### Stundenprotokoll zum 12.09.2022
Heute haben wir uns damit beschäftigt einen Code für einen Servo Motor zu schreiben (dieser ist unten zu finden). Parallel dazu hat Lois sein WLAN Modul von Zuhause mitgebracht, dass deutlich besser funktioniert, als die Module aus der Schule. Zu Hause hat Lois an dem Code weiter gearbeitet und in der Schule weiter Fehler behoben. Das Modul funktioniert in seiner Basis.

<details>
  <summary>Code für das einfache rotieren eines Servo Motors</summary>
  
```c
#include <Servo.h>
 
int servoPin = 9;
 
Servo servo;  
 
int servoAngle = 0;
 
void setup()
{
  Serial.begin(9600);  
  servo.attach(servoPin);
}
 
 
void loop()
{
   servo.write(0);
   delay(2000);
   servo.write(180);
   delay(2000);
}
```
  
</details>
  

  
### Stundenprotokoll zum 19.09.2022
Wir haben heute an einem Script gearbeitet, dass einen Servo Motor auf Knopfdruck drehen lässt. Das Script funktioniert von Grund auf, enthält allerdings Bugs, die den Servo Motor zum zittern bringt. Es muss in der nächsten Zeit daran gearbeitet werden, diese Bugs zu beheben. Der dazugehörige Code befindet sich unten angehängt. Währenddessen war Lois mit dem W-Lan Modul am Kämpfen. Dieses schickte keine vollstänge Antwort. Der Fehler war dann am Ende der Stunde behoben.
  

  <details>
  <summary>(Broken) Code für das Steuern eines Servo Motors auf Knopfdruck</summary>

```c
#include <Servo.h>

int buttonPin = 2; 
int servoPin = 9;
 
Servo servo;  

bool onAndOff = false;

int buttonState = 0;
int servoAngle = 0;
 
void setup()
{
  Serial.begin(9600);  
  servo.attach(servoPin);
  pinMode(buttonPin, INPUT);
}

void loop() {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
        if (onAndOff == false) {
            onAndOff = true;
            servo.write(180);     
        } else {
            onAndOff = false;
            servo.write(0);
        }
    }
}
```
</details>
    
  
### Stundenprotokoll zum 22.09.2022
Heute haben wir an weiter an dem Code von der letzten Stunde gearbeitet und versucht das Problem mit dem zittern zu beheben, mit Erfolg. Der voll funktionstüchtige Code, ohne Bugs, ist unten in der Summary zu finden. Wir haben es so gemacht, dass bei jedem Tastendruck, die Tastendrücke gezählt werden und bei jedem neuen Tastendruck, sich der Arduino in die andere Richtung dreht. Zeitgleich versuchte Lois einen Servo mit dem W-Lan Modul zu verknüpfen, welches sich wieder sträubte eine vollständige Antwort zu schicken. Das Problem lag an der "Servo.h" API, die aus irgendeinem unbekannten Grund das W-Lan Modul beeinträchtigt.

    
<details>
  <summary>(Broken) Code für das Steuren eines Servo Motors auf Knopfdruck</summary>

```c
#include <Servo.h>

int buttonPin = 2; 
int servoPin = 9;
 
Servo servo;  

int buttonState = 0;
int servoAngle = 0;
int lastButtonState = 0;
int buttonPushCounter = 0;
 
void setup()
{
  Serial.begin(9600);  
  servo.attach(servoPin);
  pinMode(buttonPin, INPUT);
  pinMode(servoPin, OUTPUT);
}

void loop() {
    buttonState = digitalRead(buttonPin);
      if (buttonState != lastButtonState) {
        if (buttonState == HIGH) {
          buttonPushCounter++;
          Serial.println("on");
          Serial.print("number of button pushes: ");
          Serial.println(buttonPushCounter);
          servo.write(180);     
       } else {
          Serial.println("off");
          servo.write(0);
      }
      delay(50);
    }
    lastButtonState = buttonState;
    
    if (buttonPushCounter % 2 == 0) {
      digitalWrite(servoPin, HIGH);
   } else {
      digitalWrite(servoPin, LOW);
  }
}
```
</details>
  
  
### Stundenprotokoll zum 26.09.2022
Heute haben wir herrausgefunden, dass der Code im Grunde genommen das macht was er soll, allerdings nur der untere Teil des Codes funktioniert. Der obere/mittlere Teil der im void loop steht, funktioniert kaum bis gar nicht. Also muss innerhalb der nächsten Stunden eine Lösung für das Problem gefunden werden.
  
  
### Stundenprotokoll zum 06.10.2022
Mithilfe der optimierung des Codes und der Vereinfachung, haben wir es geschafft, den Code nun vollständig zum laufen zu bekommen. Der nun vollständig funktioniernede Code ist unten in der Summary zu finden.

  
<details>
  <summary>(Fixed) Code für das Steuern eines Servo Motors auf Knopfdruck</summary>

```c
#include <Servo.h>

int buttonPin = 2; 
int servoPin = 9;
 
Servo servo;  

int buttonState = 0;
int servoAngle = 0;
int lastButtonState = 0;
int buttonPushCounter = 0;
 
void setup()
{
  Serial.begin(9600);  
  servo.attach(servoPin);
  pinMode(buttonPin, INPUT);
  pinMode(servoPin, OUTPUT);
}

void loop() {
    buttonState = digitalRead(buttonPin);
      if (buttonState != lastButtonState) {
        if (buttonState == HIGH) {
          buttonPushCounter++;
           if (buttonPushCounter % 2 == 0) {
            Serial.println("on");
            servo.write(180);
         } else {
            Serial.println("off");
            servo.write(0);
         }
         Serial.print("number of button pushes: ");
         Serial.println(buttonPushCounter);
      delay(50);
     }
    lastButtonState = buttonState;
  }
}
```
</details>
  
  
### Stundenprotokoll zum 24.10.2022
Wir haben einen Code für das steuern von zwei Servos über Serial geschieben, um die Daten vom Server zu verarbeiten.

  
<details>
  <summary>Code für steuern von zwei Servos über Serial</summary>
  
```c
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
```
</details>

  
### Stundenprotokoll zum 03.11.2022
Heute haben wir versucht den Code hinsichtlich der doppelten Auführung des Serial.read optimiert um die Funktionalität des Codes zu gewärleisten. 

  
### Stundenprotokoll zum 07.11.2022
Wir haben heute ein Relay und eine Error LED zum Controller hinzugefügt. Das Relay wird für die Steuerung von der Luftlenkplatte verwendet und die Error LED zeigt an, wenn etwas am Servo/Controller nicht korrekt funktioniert. Ebenfalls haben wir Homebridge in unser Projekt mit eingebunden. Da der Code des Servers(Der Kommunikations-Arduino), die letzten Paar Stunden nicht funktionierte, wechselten wir auf einen Arduino Mega2560. Jetzt funktioniert dieser Code wie er soll.

  
<details>
  <summary>Oberer Code mit Additionen</summary>

```c
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

void setup()
{
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
      if (in == 'c') {
        servo1.attach(servoPin1);
        servo1.write(30);
        servo1.detach();
     } else if (in == 'd') {
        servo1.attach(servoPin1);
        servo1.write(60);
        servo1.detach();
     } else if (in == 'e') {
        servo1.attach(servoPin1);
        servo1.write(90);
        servo1.detach();
     } else if (in == 'f') {
        servo1.attach(servoPin1);
        servo1.write(120);
        servo1.detach();
     // servo2 (on/off)
     // exact angles still TBD
     } else if (in == 'a') {
        servo2.attach(servoPin2);
        servo2.write(0);
        servo2.detach();
     } else if (in == 'b') {
        servo2.attach(servoPin2);
        servo2.write(90);
        servo2.detach();
     // relay (off/on)
     } else if (in = 'g') {
        digitalWrite(relay_pin, LOW);
     } else if (in = 'h') {
        digitalWrite(relay_pin, HIGH);
     }
  }
}
```
</details>

  
### Stundenprotokoll zum 17.11.2022
Wir versuchen in dieser Stunde den Code so zu reduzieren um den Code von einem Arduino Mega laufen zulassen. Dies hat allerdings nicht funktioniert und wir haben Troubleshooting am Code betrieben. Außerdem haben wir das Controller Script finalisiert, indem wir die Servos mit Relays ausgetauscht haben und das Script dementsprechend umgeschrieben haben. Der umgeschriebene Code ist unten zu finden.
  
  
### Stundenprotokoll zum 21.11.2022
Wir optimieren in dieser Stunde das Relay und führen unseren ersten echten Test des Codes durch.

  
<details>
  <summary>Oberer Code mit Additionen</summary>

```c
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
```
</details>

  
### Stunden darauffolgend zusammengefasst
In den darrauffolgenden Stunden haben wir kleinere Änderungen an beiden Codes gemacht, um die Funktionalität zu optimieren und diese auch sicherzustellen.

  
<details>
  <summary>Optimierter und fertiger Code zum steuern des Relays</summary>

```c
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
   Serial.begin(19200);
   // attaching relays
   pinMode(relaypin1, OUTPUT);
   delay(100);
   pinMode(relaypin2, OUTPUT);
   delay(100);
   pinMode(relaypin3, OUTPUT);
   delay(100);
   pinMode(relaypin4, OUTPUT);
   delay(100);
   pinMode(relaypin5, OUTPUT);
   delay(100);
   pinMode(relaypin6, OUTPUT);
   delay(100);
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
         digitalWrite(relaypin2, LOW);
         digitalWrite(relaypin3, LOW);
         digitalWrite(relaypin4, LOW);
         delay(500);
         digitalWrite(relaypin1, HIGH);
      }
      else if (in == 100)
      {
         digitalWrite(relaypin1, LOW);
         digitalWrite(relaypin3, LOW);
         digitalWrite(relaypin4, LOW);
         delay(500);
         digitalWrite(relaypin2, HIGH);
      }
      else if (in == 101)
      {
         digitalWrite(relaypin1, LOW);
         digitalWrite(relaypin2, LOW);
         digitalWrite(relaypin4, LOW);
         delay(500);
         digitalWrite(relaypin3, HIGH);
      }
      else if (in == 102)
      {
         digitalWrite(relaypin1, LOW);
         digitalWrite(relaypin2, LOW);
         digitalWrite(relaypin3, LOW);
         delay(500);
         digitalWrite(relaypin4, HIGH);
         // relay5 (fan off/on)
      }
      else if (in == 97)
      {
         digitalWrite(relaypin5, LOW);
      }
      else if (in == 98)
      {
         delay(100);
         digitalWrite(relaypin5, HIGH);
         // relay6 (swing off/on)
      }
      else if (in == 103)
      {
         digitalWrite(relaypin6, LOW);
      }
      else if (in == 104)
      {
         delay(100);
         digitalWrite(relaypin6, HIGH);
      }
   }
}
```
</details>


<h2 id="kapitel3">3. Ideen und To Do's</a></h2></li>

  
### Ideen

- Drehgeschwindichkeitsregler auseinander bauen und mit Servomotor kontrolierbar machen.
- Servo über zwei Arduinos steuern (einer für die Kommunikation und einer für die Steuerung des Servos an sich selbst).

### To Do:

- [X] WLAN Modul zum funktionieren bekommen
- [X] Servo Motor
- [X] Prototyp erstellen
- [X] Mit Homebridge verbinden
- [ ] In Ventilator einbauen


<h2 id="kapitel4">4. Materialien</a></h2>

- Arduino Mega
- Arduino Uno
- Servo Motor
- Ventilator
- WLAN Modul
- LED
- Kabel
- Relay Modul

<h2 id="kapitel5">5. Quellen</a></h2>
<p><a href="https://arduino.cc">Arduino</a></p>
<p><a href="https://developers.homebridge.io/#/">Homebridge API</a></p>
<p><a href="https://github.com/homebridge/homebridge-examples/tree/master/accessory-example-typescript">Homebridge Beispielplugin</a></p>
