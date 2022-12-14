<!--Written by Max Leon Guwa (OrangePurgatory; https://github.com/OrangePurgatory)-->


<head>
<h1 align="center">Arduinogesteuerter Ventilator - Projektseite</h1> 
</head>
<h3 align="center"> Ein Projekt von Max, Lois und Timo 11p </h3>
</br>

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://user-images.githubusercontent.com/105984356/186677878-5eddbf06-304d-4ea7-90db-5ddba9e40dbf.png">
  <source media="(prefers-color-scheme: light)" srcset="https://user-images.githubusercontent.com/105984356/186676647-16dacef0-4117-4750-afc1-1d4d6409e6d3.png">
  <img alt="" src="">
</picture>


<h3 align="left">Stormarnschule Ahrensburg <br/> Informatik, Buhl <br/> Schuljahr 2022/23, 1. Halbjahr </br> </h3> </div>
<h3 align="left"> &#10132; <a href="https://github.com/LoMaTiInformatik/Smarthome_Ventilator/blob/main/Projekttagebuch.md"> Projekttagebuch</a> </h3> 
</br>


## Inhalt
<p><a href="#kapitell">1. Einleitung</a></p>
<p><a href="#kapitel2">2. Vorstellung der Projekts</a></p>
<p><a href="#kapitel3">3. Erklärung des Codes</a></p>
<p><a href="#controlcode">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Controller-Code</a></p>
<p><a href="#servercode">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Server-Code</a></p>
<p><a href="#hbcode">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Homebridge-Code</a></p>
<p><a href="#kapitel4">4. Entstehung des Projekts</a></p>
<p><a href="#kapitel5">5. Fazit</a></p>
<p><a href="#kapitel6">6. Quellen</a></p>
<p><a href="#kapitel7">7. Eigenständigkeitserklärung</a></p>
</br>


<h2 id="kapitell">1. Einleitung</h2>
Hallo und herzlich willkommen zu unserer Projektseite für unser Projekt. Hier erklären wir das Verfahren, unsere Ideen und erklären das Endprodukt.</br>
<a href="https://github.com/LoMaTiInformatik/Smarthome_Ventilator"> Hier</a> kommst du zu der GitHub Repository und <a href="https://github.com/LoMaTiInformatik/Smarthome_Ventilator/blob/main/Projekttagebuch.md"> hier</a> zur Protokollseite.
</br>


<h2 id="kapitel2">2. Vorstellung des Projekts</h2>
Smarthome wird immer beliebter in Haushalten. Dies ist auch leicht zu erklären. Smarthome erleichtert das Leben der Menschen um einiges. Es können Geräte aller Art, von allen möglichen Standorten auf der Welt gesteuert werden. Also kamen wir auf die Idee, einen Ventilator mit Arduino und Smarthome (Homebridge) steuerbar zu machen. Verwenden kann man dieses Konzept am besten an heißen Sommertagen, an denen man, wegen der starken Hitze kaum noch Kraft hat aufzustehen und von überall im selben Netzwerk, seinen Ventilator bedienen kann.</br></br>
Das Projekt funktioniert wie folgt:</br>
Der Ventilator ist an ein Relay angeschlossen, welches an den Controller-Arduino angeschlossen ist. Dieser Controller-Arduino ist nur dafür zuständing, das Relay zu steuern und die Daten von dem Server-Arduino, der mit dem Controller-Arduino verbunden ist, zu verarbeiten. Der Server-Arduino ist hingegen mit einem WLAN-Modul verbunden, welches die Daten von Homebridge empfängt, welches wiederrum die Daten von einem Handy erhält. Alles funktioniert nur, wenn sich alle Geräte im selben Netzwerk befinden.</br></br>
<details>
  <summary>Bilder zum Projekt</summary>
<!--Insert images and other details here-->
</details></br>
<details>
  <summary>Schaltplan</summary>
    <picture>
      <source media="(prefers-color-scheme: dark)" srcset="https://user-images.githubusercontent.com/105984356/207425594-ad6fc3ed-255a-4325-aa42-8d07242417c6.png">
      <source media="(prefers-color-scheme: light)" srcset="https://user-images.githubusercontent.com/105984356/207425594-ad6fc3ed-255a-4325-aa42-8d07242417c6.png">
      <img alt="" src="">
  </picture>
</details>
</br>


<h2 id="kapitel3">3. Erklärung des Codes</h2>
Der Code ist in zwei Teile, den Controller-Code und den Server-Code, aufgeteilt.</br>Hier werden wir auf Beide ausführlich eingehen.
</br>
<h3 id="controlcode">Controller-Code</h2>
Beim Controller Code wird kein hinzufügen einer Library benötigt, also wird am Anfang direkt damit angefangen die Pins für die Relays und die Error-LED zu setzen. Außerdem wird die Variable für das erhalten von Daten definiert.

```c
//defining pins
const int relaypin1 = 7;
const int relaypin2 = 8;
const int relaypin3 = 9;
const int relaypin4 = 10;
const int relaypin5 = 11;
const int relaypin6 = 12;
const int ledpin = 13;

//defining variables
int in = 0;
```
</br>

Dann wird im Setup erstmal die Baud-Rate gesetzt, die die Geschwindingkeit der Kommunikation festlegt. Diese ist auf 19200 gesetzt.

Danach folgt die Setzung der oben definierten Pins, auf Output, heißt die Pins werden Daten aussenden und nicht empfangen.

Daraufhin folgt die Inizialisierung des Codes (des Boards), die von dem Server-Arduino ausgeführt wird. Hierbei wird geprüft, ob beide Boards miteinander Kommunizieren können und Daten erhalten können. Wenn dies nicht der Fall sein sollte, wird die Error-LED aufleuchten.

```c
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
```
</br>

Nun kommt der eigentlich spannende Teil des Codes. Im Loop wird die ganze Zeit geprüft, ob von dem Server-Arduino Daten gesendet werden oder nicht (Serial.available()). Wenn Daten gesendet werden, soll der Arduino die Daten auslesen, die Variable "in" auf den ausgelesenen Buchstaben setzen und schließlich den gesetzten Buchstaben wieder zurücksenden.

Jetzt folgt ein langer "else if" Teil. Hier wird, sobald die oben genannten Punkte geschehen sind, geprüft welcher Buchstabe gesendet wurde und ob dieser mit einem bekannten Buchstaben übereinstimmt. Jeder Buchstabe hat seine eigene Bedeutung und wird einen bestimmten Teil vom Code ausführen.

Beispiel: Wenn der Controller-Arduino ein "c" von dem Server-Arduino erhält, soll er Relay 2, 3 und 4 ausschalten, 100 Millisekunden warten und das Relay 1 einschalten.

```c
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

</br>
<h3 id="servercode">Server-Code</h2>
Am Anfang des Codes wird zuerst die "SoftwareSerial.h" Bibliothek eingebunden. Dies ist eine vorinstallierte Bibliothek, die für die serielle Kommunikation, außerhalb der standard seriellen Schnitstellen, zuständig ist.

Anschließend werden zwei Instanzen von SoftwareSerial initialisiert. Die "esp8266" Instanz ist zuständig für die Kommunikation mit dem ESP8266-01S W-Lan Modul und die "controller" Instanz wird für die Kommunikation mit dem "Controller" Arduino verwendet.

Danach wird die serielle Kommunikationsgeschwindigkeit gesetzt und der Debug-Modus definiert.

```c
#include <SoftwareSerial.h>

SoftwareSerial esp8266(11, 10);
SoftwareSerial controller(51, 50);

#define serialCommunicationSpeed 9600

#define DEBUG true
```
</br>

Im Setup wird zuerst die Error-Led als Output definiert und auf LOW gesetzt. Danach werden die serielle Schnittstelle und die "esp8266" Instanz mit der vorher definierten seriellen Kommunikationsgeschwindigkeit gestartet. Sobald dies getan ist, wird überprüft, ob die "esp8266" Instanz läuft und direkt im Anschluss wird die "Controller" Instanz auf einer Baud-Rate von 19200 gestartet.</br>Der nächste Teil Code ist lediglich benötigt, um den "Controller" Arduino zu initialisieren und wenn all dies getan ist, wird das W-Lan Modul initialisiert.

```c
void setup()
{
  pinMode(errorled, OUTPUT);

  digitalWrite(errorled, LOW);

  Serial.begin(serialCommunicationSpeed);

  esp8266.begin(serialCommunicationSpeed);

  if (!esp8266) {
    handleErrors(3);
  }

  controller.begin(19200);

  bool active = false;

  long int mils = millis();

  int i = 0;

  controller.listen();

  controller.write(105);

  Serial.println("Initialising controller...");

  while (active == false) {
    if (i >= 5) {
      Serial.println("Error while initializing controller!");
      handleErrors(1);
    }
    while(controller.available()) {
      char chara = controller.read();
      if (chara == 'i') {
        active = true;
      }
    }
    if (millis() - mils > 1000 && !active) {
      i++;
      mils = millis();
      controller.write(105);
      Serial.println("Initialisation failed! Trying again:" + String(i));
    }
  }

  InitWifiModule();

  Serial.println("Ready");
}
```

</br>

<h4>Loop-Funktion</h4>

Am Anfang der Loop-Funktion wird geprüft, ob das W-Lan Modul ein "busy" ausgibt, falls dies der Fall ist gibt es einen Error. Danach wird nach einem "+IPD," gesucht, welches den Anfang einer Http-Anfrage ankündigt.

```c
void loop()
{
  if (esp8266.find("busy")) {
    handleErrors(4);
  }
  if (esp8266.find("+IPD,"))
  { // look for request start
```

</br>

Nun wird kurz überprüft, ob bereits eine Anfrage bearbeitet wird, sodass der Arduino nicht überladen wird. Falls dies nicht der Fall sein sollte, wird die gesamte Anfrage ausgelesen.

```c
if (!processing)
    {
      processing = true;
      int timeout = 500;
      long int lastmillis = millis();

      String result = "";

      while ((millis() - lastmillis) < timeout)
      { // save whole request
        while (esp8266.available())
        {
          const char c = esp8266.read();

          result += c;
        }
      }
```

</br>

Hier wird der Anfrage die Verbindungs-Id entnommen. Nun wird die gesammte Anfrage in die Funktion "processRequest" eingesetzt. Und das Ergebnis von dieser wird dann von der Funktion "sendResponse" übernommen. Sobald dies erfolgt ist, wird mit dem Befehl "AT+CIPCLOSE" die Verbindung geschlossen.

```c
int connectionid = result.charAt(0) - 48;

// Process request and send response
sendResponse(processRequest(result), connectionid);
// Close the connection

String closeCommand = "AT+CIPCLOSE=";

closeCommand += connectionid;
closeCommand += "\r\n";

sendData(closeCommand, 20, DEBUG);

```

</br>

<h4>processRequest-Funktion</h4>

Anfangs wird überprüft, ob es sich um eine "favicon.ico" bzw. eine "apple-touch-icon.png", also eine Anfrage für das Websiteicon, handelt. Es gibt noch weitere Anfragentypen, das wären "/getStatus", "/getInfo" und die "Action" Anfragen.</br>Mit der "/getStatus" Anfrage kann man den aktuellen Zustand des Ventilators erfragen.</br>Die "/getInfo" Anfrage wird zurzeit nicht verwendet, wurde aber dafür gedacht die Geräteinfos zu bekommen, wie z.B. den Namen, die Seriennummer, usw.</br>Die "Action" Anfrage wird im folgenden Kommentar näher erläutert.

```c
int processRequest(String result)
{

  // Check for favicon or status/info requests

  if (result.indexOf("/favicon.ico") != -1 || result.indexOf("/apple-touch-icon.png") != -1)
  {
    return 204;
  }
  if (result.indexOf("/getStatus") != -1)
  {
    answertype = 1;
    return 200;
  }
  if (result.indexOf("/getInfo") != -1)
  {
    answertype = 2;
    return 200;
  }
```

</br>

Die restlichen Kommentare zu der "processRequest" Funktion befassen sich mit der "Action" Anfrage.</br>Hier wird die Anfrage in ihre Einzelteile zerlegt.</br>Eine Anfrage sieht zum Beispiel so aus: "http://[IP-DES-ARDUINOS]/?act=power&arg1=1".</br>Diese Anfrage würde den Ventilator anschalten.</br>act: Die Aktion die ausgeführt werden soll.</br>arg1: Der Wert auf den die Einstellung gesetzt werden soll.</br>arg2 und arg3 werden zurzeit nicht verwendet.</br></br>Falls keine Aktion oder Wert definiert wurden, wird der HTTP Code 400, also "Invalid Request", geschickt.

```c
// Handle commands
  int act = result.indexOf("act=");
  String param = result.substring(act, result.indexOf(" HTTP"));
  int arg1 = param.indexOf("&arg1=");
  int arg2 = param.indexOf("&arg2=");
  int arg3 = param.indexOf("&arg3=");
  if (act == -1 || arg1 == -1)
  {
    errormsg = "{\"status\":\"Error\",\"body\":{\"errmsg\":\"Function: No action or value\"}}\r\n";
    errormsglen = 70;
    return 400;
  }
  String actstr = param.substring(4, arg1);
```
</br>

Dies ist ein Beispiel für eine "Action". Zuerst wird der Wert aus der URL zu einer Zahl verarbeitet, danach wird gecheckt, ob dieser Wert im zulässigen Bereicht liegt. (Hier ist es zum Beispiel im Bereich von 0 bis 1.) Falls der Wert außerhalb des zulässigen Bereichs liegt, wird ein HTTP Code 400 geschickt. Anderenfalls wird die gewünschte Aktion ausgeführt.

```c
if (actstr == "power" && arg1 != -1)
  {
    int arg1num = param.substring((arg1 + 6)).toInt();
    if (arg1num > 1 || arg1num < 0)
    {
      errormsg = "{\"status\":\"Error\",\"body\":{\"errmsg\":\"Power: Number out of range\"}}\r\n";
      errormsglen = 68;
      return 400;
    }
    powerval = arg1num;
    sendSettings(97, arg1num);
    return 200;
  }
```

</br>

<h4>sendRespone-Funktion</h4>

Vorerst wird überprüft welcher Status geschickt werden soll. Hier wird der Code 200 (HTTP OK) bearbeitet. Hierbei wird der HTTP-Header gesetzt, dieser definiert was die Antwort enthalten wird. Danach wird der "Content" oder "Body" gesetzt, darin ist alles Andere enthalten.

```c
void sendResponse(int code, int conid)
{
  String header = "";
  String content = "";
  int headlen = 0;
  int conlen = 0;
  if (code == 200)
  {
    header = ("HTTP/1.1 200 OK\r\n"
              "Content-Type: text/json\r\n"
              "Connection: Closed\r\n"
              "\r\n");

    headlen = header.length();

    // Set the status answer
    if (powerval == 0) {
      content = "{\\\"power\\\":" + String(powerval) + ",\\\"speed\\\":" + String(0) + ",\\\"swing\\\":" + String(swingval) + "}\r\n";
    } else {
      content = "{\\\"power\\\":" + String(powerval) + ",\\\"speed\\\":" + String(speedval) + ",\\\"swing\\\":" + String(swingval) + "}\r\n";
    }
```
</br>

Das hier ist die Antwort für den Code 400 (HTTP Bad Request). Da wird wieder der HTTP-Header gesetzt. Danach wird eine potentielle Errorbeschreibung eingesetzt.

```c
else if (code == 400)
  {
    header = ("HTTP/1.1 400 Bad Request\r\n"
              "Connection: Closed\r\n"
              "Content-Type: text/json\r\n"
              "\r\n");

    // Send error message

    bool errmsgexist = (errormsg != "");
    content = (errmsgexist) ? errormsg : defaulterrormsg;

    headlen = header.length();
    conlen = (errmsgexist) ? errormsg.length() : defaulterrormsglen;

    errormsg = "";
    errormsglen = 0;
  }
```

</br>

Am Ende der Funktion wird Header und Body versendet. Dabei wird die insgesamte Länge der Antwort gemessen und danach wird das W-Lan Modul mit einem "AT+CIPSEND" Befehl auf das Senden vorbereitet. Kurz drauf wird zuerst der Header und dann der Body gesendet.

```c
int len = headlen + conlen;

  Serial.println(len);

  esp8266.print("AT+CIPSEND=" + String(conid) + "," + String(len) + "\r\n");

  delay(100);

  esp8266.print(header);
  if (content)
  {
    esp8266.print(content);
  }
```

<h3 id="hbcode">Homebridge-Code</h3>

Der Homebridge-Code ist in TypeScript (verwandt mit JavaScript) geschrieben und verwendet die Homebridge API.
</br>
Im folgenden Code wird zunächst HAP (HomeKit Accessory Protocol) definiert, welches für die Kommunikation mit Homebridge verwendet wird.
</br>
Anschließend wird das Accessory, also das Gerät, "exportiert". Das heißt es wird Homebridge offenbart, damit es gesteuert werden kann.

```ts
let hap: HAP;

/*
 * Initializer function called when the plugin is loaded.
 */
export = (api: API) => {
  hap = api.hap;
  api.registerAccessory("Ventilator", VentilatorPl);
};
```
</br>

Hier wird die Klasse VentilatorPl definiert. Darin werden Variabeln gesetzt, die wichtig für die Verarbeitung der Daten sind.

```ts
class VentilatorPl implements AccessoryPlugin {

  private readonly log: Logging;
  private readonly name: string;
  private readonly ip: string;
  private status;
  private queue = {
    power: 0,
    speed: 0,
    swing: 0
  };
  private processrequest = false;

  private readonly ventilatorService: Service;
  private readonly informationService: Service;
  ```
</br>

<h2 id="kapitel4">4. Entstehung des Projekts</h2>
Anfangs war es schwer für uns eine Idee zu bekommen, was wir denn überhaupt für ein Projekt erstellen wollen. Nach ein paar Stunden Denk- und Überlegzeit, sind wird nach vielen einzelnen Ideen und Gedankengängen, zum Schluss gekommen einen Ventilator ferngesteuert zu machen. Allerdings stand zu dem Zeitpunkt noch nicht fest, dass wir den Ventilator mit Smarthome steuern werden. Es stand nur fest, dass wir dies durch eine eventuelle Webseite machen wollen. Im verlaufe des Projekts kamen wir dann aber auf diese Idee. Dies hat uns zwar mehr Arbeit zu Hause gekostet, lohnte sich dann aber letzendlich für uns und unser Projekt.

Da der Schwierigkeitsgrad nicht für alle Teilnehmer der Gruppe angemessen war, hatten wir uns dazu entschieden, arbeitsteilig zu arbeiten. Wärend einer den Code für den Controller geschrieben, sich mehr mit Arduino vertraut gemacht und sich um die Projektseite/-tagebuch gekümmert hat, hat der andere den anspruchsvolleren Code (Servo und Homebridge) beschäftigt. So hatte jeder immer etwas zu tun und etwas woran er arbeiten kann.
</br>


<h2 id="kapitel5">5. Fazit</h2>
Das Informatikprojekt zum Thema eines Ventilators, der mit Smart Home gesteuert werden kann, hat gezeigt, dass es möglich ist, ein solches Gerät zu entwickeln und in das Smart Home System zu integrieren. Durch die Verwendung von Sensoren und Steuerungselementen kann der Ventilator nicht nur ein- und ausgeschaltet werden, sondern auch die Geschwindigkeit und Richtung der Luftzirkulation angepasst werden. Die Integration in das Smart Home System ermöglicht es, den Ventilator über eine mobile App zu bedienen und so die Raumluftqualität zu verbessern. </br>
Insgesamt hat das Projekt gezeigt, dass es möglich ist, die Funktionalität von Haushaltsgeräten durch die Verwendung von Smart Home Technologien zu erweitern und so den Komfort und die Bequemlichkeit für den Nutzer zu verbessern.
</br>


<h2 id="kapitel6">6. Quellen</h2>
<p><a href="https://arduino.cc">Arduino</a></p>
<p><a href="https://developers.homebridge.io/#/">Homebridge API</a></p>
<p><a href="https://github.com/homebridge/homebridge-examples/tree/master/accessory-example-typescript">Homebridge Beispielplugin</a></p>
</br>


<h2 id="kapitell">7. Eigenständigkeitserklärung</h2>

<b>Eigenständigkeitserklärung</b></br>
Wir erklären, dass wir die vorliegende Arbeit selbstständig und ohne Benutzung anderer als den 
angegebenen Hilfsmittel angefertigt und alle Stellen, die wörtlich oder sinngemäß aus 
veröffentlichten oder unveröffentlichten Schriften entnommen wurden, als solche kenntlich 
gemacht haben.</br>
Diese Arbeit wurde nicht, auch nicht auszugsweise, bereits für eine andere Prüfung angefertigt.</p>
