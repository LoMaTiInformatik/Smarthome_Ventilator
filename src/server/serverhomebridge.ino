/*
  * 
  * Wiring
  * 
  * ESP8266:
  * 
  * - TX: 2
  * - RX: 3
  * - EN: 3.3V
  * - 3.3V: 3.3V
  * - GND: GND
  * 
  * Controller Arduino:
  * 
  * - TX(0): 4
  * - RX(1): 5
  * - GND: GND
  * 
  * Settings
  * 
  * DeviceName: Name to be shown in Homebridge
  * SerialNumber: SerialNumber for communication
  * SSID: SSID of your wifi network
  * Password: Password of your wifi network
  * AcessPointMode: Should the device make it's own network or should it connect to one
  * 
*/

String DeviceName = "Fan001";
String SerialNumber = "SNFan001";
String SSID = "Test";
String Password = "Test12345";
bool AccessPointMode = true;

// DO NOT EDIT! (Unless you know what you are doing)

#include <SoftwareSerial.h>

SoftwareSerial esp8266(3, 2);
//SoftwareSerial controller(5, 4);

#define serialCommunicationSpeed 9600

#define DEBUG true

/*
 *
 * Setup values
 *
 */

// Answers
String answerstatus = "";
String answergdi = "{\"name\":\""+ DeviceName +"\",\"sn\":\"" + SerialNumber + "\",\"functions\":{\"power\":{\"min\":0,\"max\":1},\"speed\":{\"min\":1,\"max\":4},\"swing\":{\"min\":0,\"max\":1}}}";
String errormsg = "";
String defaulterrormsg = "An unknown error occurred.";
int answertype = 0;
int answerstatuslen = 0;
int answergdilen = answergdi.length();
int errormsglen = 0;
int defaulterrormsglen = 27;

// Error handling
int errorled = 6;

// Settings
int powerval = 0;
int speedval = 1;
int swingval = 0;

void setup()
{
  pinMode(errorled, OUTPUT);

  digitalWrite(errorled, LOW);

  Serial.begin(serialCommunicationSpeed);

  esp8266.begin(serialCommunicationSpeed);

  /*if (!esp8266) {
    handleErrors(3);
  }*/

  /*controller.begin(serialCommunicationSpeed);

  controller.print("i");

  bool active = true;

  long int mils = millis();

  while (active == false) {
    while(controller.available()) {
      char chara = controller.read();
      if (chara == 'i') {
        active = true;
      }
    }
    if (millis() - mils > 5000) {
      Serial.println("Error while initializing controller!");
    }
  }*/

  InitWifiModule();

  Serial.println("Ready");
}

void loop()
{
  if (esp8266.find("+IPD,"))
  { // look for request start
    int timeout = 500 + millis();

    String result = "";

    while (millis() < timeout)
    { // save whole request
      while (esp8266.available())
      {
        const char c = esp8266.read();

        result += c;
      }
    }

    Serial.println(result);

    // Get connection id

    int connectionid = result.charAt(0) - 48;
    
    // Process request and send response

    sendResponse(processRequest(result), connectionid);

    delay(500);

    // Close the connection

    String closeCommand = "AT+CIPCLOSE=";

    closeCommand += connectionid;
    closeCommand += "\r\n";

    sendData(closeCommand, 20, DEBUG);
    
    // Do less important work when there is no request
    answerstatus = "{\"power\":\"" + String(powerval) + "\",\"speed\":\"" + String(speedval) + "\",\"swing\":\"" + String(swingval) + "\"}";
    answerstatuslen = answerstatus.length();
  }
}

// Process recieved request

int processRequest(String result)
{

  // Check for favicon or status/info requests

  if (result.indexOf("/favicon.ico") != -1)
  {
    return 204;
  }
  if (result.indexOf("/getStatus") != -1) {
    answertype = 1;
    return 200;
  }
  if (result.indexOf("/getInfo") != -1) {
    answertype = 2;
    return 200;
  }
  // Handle commands
  int act = result.indexOf("act=");
  String param = result.substring(act, result.indexOf(" HTTP"));
  int arg1 = param.indexOf("&arg1=");
  int arg2 = param.indexOf("&arg2=");
  int arg3 = param.indexOf("&arg3=");
  if (act == -1 || arg1 == -1)
  {
    errormsg = "Function: No action or value\r\n";
    errormsglen = 29;
    return 400;
  }
  String actstr = param.substring(4, arg1);

  // Check possible actions

  if (actstr == "power" && arg1 != -1)
  {
    int arg1num = param.substring((arg1 + 6)).toInt();
    if (arg1num > 1 || arg1num < 0) {
      errormsg = "Power: Number out of range\r\n";
      errormsglen = 27;
      return 400;
    }
    sendSettings(97, arg1num);
    return 200;
  }
  else if (actstr == "speed" && arg1 != -1)
  {
    int arg1num = param.substring((arg1 + 6)).toInt();
    if (arg1num > 4 || arg1num < 1) {
      errormsg = "Speed: Number out of range\r\n";
      errormsglen = 27;
      return 400;
    }
    sendSettings(98, arg1num);
    return 200;
  }
  else if (actstr == "swing" && arg1 != -1)
  {
    int arg1num = param.substring((arg1 + 6)).toInt();
    if (arg1num > 1 || arg1num < 0) {
      errormsg = "Swing: Number out of range\r\n";
      errormsglen = 27;
      return 400;
    }
    sendSettings(103, arg1num);
    return 200;
  }
  errormsg = "Act: Unknown value\r\n";
  errormsglen = 19;
  return 400;
}

// Send response

void sendResponse(int code, int conid)
{
  String header = "";
  String content = "";
  int headlen = 0;
  int conlen = 0;
  if (code == 200)
  {
    header = ("HTTP/1.1 200 OK\r\n"
              "Content-Type: text/plain\r\n"
              "Connection: Closed\r\n"
              "\r\n");

    headlen = header.length();

    if (answertype == 1) {
      // Send Device Status
      content = answerstatus;
      conlen = answerstatuslen;
    } else if(answertype == 2) {
      // Send Device Info
      content = answergdi;
      conlen = answergdilen;
    }
  }
  else if (code == 204)
  {
    header = ("HTTP/1.1 204 No Content\r\n"
              "Connection: Closed\r\n"
              "\r\n");

    headlen = header.length();
  }
  else if (code == 400)
  {
    header = ("HTTP/1.1 400 Bad Request\r\n"
              "Connection: Closed\r\n"
              "Content-Type: text/plain\r\n"
              "\r\n");

    // Send error message

    bool errmsgexist = (errormsg != "");
    content = (errmsgexist) ? errormsg : defaulterrormsg;

    headlen = 75;
    conlen = (errmsgexist) ? errormsglen : defaulterrormsglen;

    errormsg = "";
    errormsglen = 0;
  }
  else if (code == 404)
  {
    header = ("HTTP/1.1 404 Not Found\r\n"
              "Connection: Closed\r\n"
              "Content-Type: text/plain\r\n"
              "\r\n"
              "Not Found!\r\n");

    headlen = header.length();
  }

  Serial.println("Page begin: ");

  Serial.println(header);

  Serial.println(content);

  Serial.println("Page end");

  int len = headlen + conlen;

  Serial.println(len);

  esp8266.print("AT+CIPSEND=" + String(conid) + "," + String(len) + "\r\n");

  delay(200);

  esp8266.print(header);
  if (content)
  {
    esp8266.print(content);
  }
}

String sendData(String command, const int timeout, boolean debug)
{
  String response = "";

  esp8266.print(command);

  int times = millis();

  while ((times + timeout) > millis())
  {
    while (esp8266.available())
    {
      char c = esp8266.read();

      response += c;
    }
  }
  if (debug)
  {
    Serial.println(response);
  }
  return response;
}

void sendSettings(int action, int value)
{
  /*
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
  */

  // #2 Send instructions to controller
  int num = action+value;
  //controller.write(num);
}

void handleErrors(int errorid) {
  digitalWrite(errorled, HIGH);
  while(true) {
    /*
    * 
    * Error Ids
    * 
    * 1: Failed to initialize controller
    * 2: Could not connect to wifi
    * 3: Failed to initialize esp8266 Serial
    * 
    */
    if (errorid == 1) {
      digitalWrite(errorled, LOW);
      delay(500);
      digitalWrite(errorled, HIGH);
      delay(500);
      digitalWrite(errorled, LOW);
      delay(500);
      digitalWrite(errorled, HIGH);
      delay(2000);
    } else if (errorid == 2) {
      digitalWrite(errorled, LOW);
      delay(500);
      digitalWrite(errorled, HIGH);
      delay(500);
      digitalWrite(errorled, LOW);
      delay(500);
      digitalWrite(errorled, HIGH);
      delay(500);
      digitalWrite(errorled, LOW);
      delay(500);
      digitalWrite(errorled, HIGH);
      delay(2000);
    } else if (errorid == 3) {
      digitalWrite(errorled, LOW);
      delay(500);
      digitalWrite(errorled, HIGH);
      delay(500);
      digitalWrite(errorled, LOW);
      delay(500);
      digitalWrite(errorled, HIGH);
      delay(500);
      digitalWrite(errorled, LOW);
      delay(500);
      digitalWrite(errorled, HIGH);
      delay(500);
      digitalWrite(errorled, LOW);
      delay(500);
      digitalWrite(errorled, HIGH);
      delay(2000);
    }
  }
}

void InitWifiModule()
{
  sendData("AT+RST\r\n", 2000, DEBUG);

  String settingscommand = "";

  if (AccessPointMode == true) {
    settingscommand = ("AT+CWSAP=\"" + SSID + "\",\"" + Password + "\",3,3\r\n");
    sendData("AT+CWMODE=2\r\n", 1000, DEBUG);
  } else {
    settingscommand = ("AT+CWJAP=\"" + SSID + "\",\"" + Password + "\"\r\n");
    sendData("AT+CWMODE=1\r\n", 1000, DEBUG);
  }

  sendData(settingscommand, 1000, DEBUG);
  // delay(1000);
  sendData("AT+CIFSR\r\n", 1000, DEBUG);

  if (AccessPointMode == false) {
    if (sendData("AT+CWSTATE?\r\n", 1000, DEBUG).substring(10,10).toInt() != 2) {
      handleErrors(2);
    }
  }

  // delay(1000);
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG);

  // delay(1000);
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);
}
