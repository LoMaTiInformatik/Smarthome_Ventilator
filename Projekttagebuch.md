<h1 align="center">Arduinogesteuerter Ventilator - Projekttagebuch</h1> 
<h3 align="center"> Ein Projekt von Max, Lois und Timo 11p </h3>
</br>


<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://user-images.githubusercontent.com/105984356/186677878-5eddbf06-304d-4ea7-90db-5ddba9e40dbf.png">
  <source media="(prefers-color-scheme: light)" srcset="https://user-images.githubusercontent.com/105984356/186676647-16dacef0-4117-4750-afc1-1d4d6409e6d3.png">
  <img alt="" src="">
</picture>

<h3 align="left">Stormarnschule Ahrensburg <br/> Informatik, Buhl <br/> Schuljahr 2022/23, 1. Halbjahr </br> </h3> </div>
<h3 align="left"> &#10132; <a href="https://github.com/OrangePurgatory/SSIU.Ventilatorsteuerung/blob/main/Projektseite.md"> Projektseite</a> </h3> 
</br>



## Inhalt
<ul>
<li><a href="#kapitell">1. Einleitung</a></li>
<li style="margin-bottom: 5px;">
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
</ul></details></li>
<li style="margin-top: 5px;"><a href="#kapitel3">3. Ideen und To Do's</a></li>
<li><a href="#kapitel4">4. Materialien</a></li>
<li><a href="#kapitel5">5. Quellen</a></li>
</ul>


<h2 id="kapitell">1. Einleitung</h2>
Hallo und herzlich Wilkommen zu unserem Projekttagebuch. Hier protokollieren wir unseren Arbeitsprozess, um später wieder zurückgucken zu können und sehen, was wir an welchem Tag genau gemacht haben. Einige Protokolle enthalten Beispielcodes, um unseren Arbeitsprozess zu visualisieren. Test


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
  
```
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


### Stundenprotokoll 05.09.2022
Vor der heutigen Stunde haben wir zu Hause einen Code für das WLAN Modul geschrieben. Diesen Code haben wir dann auf den Arduino gespielt und damit versucht das WLAN Modul zum laufen zu bekommen. In dem Prozess wurde allerdings das WLAN Modul beschädigt und ist nun inoperabel. Allerdings haben wir ein neues Modul gefunden und dieses hat dann wieder Antworten gesendet. Ein Paar weitere Tweaks am Code und das WLAN Modul hat funktioniert. </br>

### Stundenprotokoll 08.09.2022
Wir haben uns heute dazu entschieden die Idee des WLAN Moduls erstmal zu streichen. Die Entscheidung ist gefallen, da schon zum zweiten Mal ein WLAN Mudul kaputt gegangen ist und es unmöglich für uns wurde diese für unser Projekt zu verwenden. 

### Stundenprotokoll 12.09.2022
Heute haben wir uns damit beschäftigt einen Code für einen Servo Motor zu schreiben (dieser ist unten zu finden). Parallel dazu hat Lois sein WLAN Modul von Zuhause mitgebracht, dass deutlich besser funktioniert, als die Module aus der Schule. Zu Hause hat Lois an dem Code weiter gearbeitet und in der Schule weiter Fehler behoben. Das Modul funktioniert in seiner Basis.

<details>
  <summary>Code für das einfache rotieren eines Servo Motors</summary>
  
```
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
  

### Stundenprotokoll 19.09.2022
Wir haben heute an einem Script gearbeitet, dass einen Servo Motor auf Knopfdruck drehen lässt. Das Script funktioniert von Grund auf, enthält allerdings Bugs, die den Servo Motor zum zittern bringt. Es muss in der nächsten Zeit daran gearbeitet werden, diese Bugs zu beheben. Der dazugehörige Code befindet sich unten angehängt. Währenddessen war Lois mit dem W-Lan Modul am Kämpfen. Dieses schickte keine vollstänge Antwort. Der Fehler war dann am Ende der Stunde behoben.
  
<details>
  <summary>(Broken) Code für das Steuern eines Servo Motors auf Knopfdruck</summary>

```
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
  
### Stundenprotokoll 22.09.2022
Heute haben wir an weiter an dem Code von der letzten Stunde gearbeitet und versucht das Problem mit dem zittern zu beheben, mit Erfolg. Der voll funktionstüchtige Code, ohne Bugs, ist unten in der Summary zu finden. Wir haben es so gemacht, dass bei jedem Tastendruck, die Tastendrücke gezählt werden und bei jedem neuen Tastendruck, sich der Arduino in die andere Richtung dreht. Zeitgleich versuchte Lois einen Servo mit dem W-Lan Modul zu verknüpfen, welches sich wieder sträubte eine vollständige Antwort zu schicken. Das Problem lag an der "Servo.h" API, die aus irgendeinem unbekannten Grund das W-Lan Modul beeinträchtigt.

<details>
  <summary>(Broken) Code für das Steuren eines Servo Motors auf Knopfdruck</summary>

```
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
  
### Stundenprotokoll 26.09.2022
Heute haben wir herrausgefunden, dass der Code im Grunde genommen das macht was er soll, allerdings nur der untere Teil des Codes funktioniert. Der obere/mittlere Teil der im void loop steht, funktioniert kaum bis gar nicht. Also muss innerhalb der nächsten Stunden eine Lösung für das Problem gefunden werden.
  
### Stundenprotololl 06.10.2022
Mithilfe der optimierung des Codes und der Vereinfachung, haben wir es geschafft, den Code nun vollständig zum laufen zu bekommen. Der nun vollständig funktioniernede Code ist unten in der Summary zu finden.

<details>
  <summary>(Fixed) Code für das Steuern eines Servo Motors auf Knopfdruck</summary>

```
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
  
### Stundenprotokoll 24.10.2022

<details>
  <summary>bobm</summary>
  
```
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
  Serial.begin(9600);
  // attaching servos to pins
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo1.write(servoAngle);
  servo2.write(servoAngle);
}

void loop() {
  while (Serial.available()) { // while serial is sending data -
    int in = Serial.read(); // - read data received
    in -= 48; // get rid of that enter key
    // depending on what data is being recieved, it should turn either of the servos to the stated angle
    // servo1 (fan speed)
    // exact angles still TBD
    Serial.println(in);
     if (in == 0) {
        servo1.write(0);
     } else if (in == 1) {
        servo1.write(30);
     } else if (in == 2) {
        servo1.write(60);
     } else if (in == 3) {
        servo1.write(90);
     } else if (in == 4) {
        servo1.write(120);
    }
  }
  // servo2 (on/off)
  // exact angles still TBD
   while (Serial.available()) {
    int in = Serial.read();
    in -= 48;
    Serial.println(in);
     if (in == 8) {
        servo2.write(0);
     } else if (in == 9) {
        servo2.write(90);
     }
  }
}
```
</details>


<h2 id="kapitel3">3. Ideen und To Do's</a></h2></li>

### Ideen

- Stärkeregler auseinander bauen und mit Servomotor kontrolierbar machen
- Servo über zwei Arduinos steuern (einer für die Kommunikation und einer für die Steuerung des Servos an sich selbst)

### To Do:

- [X] WLAN Modul zum funktionieren bekommen
- [X] Servo Motor
- [ ] Prototyp erstellen


<h2 id="kapitel4">4. Materialien</a></h2>

- Adruino Uno
- Servo Motor
- Ventilator
- WLAN Modul
- Knopf
- Kabel

<h2 id="kapitel5">5. Quellen</a></h2>
https://arduino.cc
