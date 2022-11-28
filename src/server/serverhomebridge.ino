/*
 *
 * Driver for a fan to be used with smarthome(homebridge)
 * Written by Lois Gilly (https://github.com/luigicrafter)
 *
 *
 * Wiring
 *
 * ESP8266:
 *
 * - TX: 10
 * - RX: 11
 * - EN: 3.3V
 * - 3.3V: 3.3V
 * - GND: GND
 *
 * Controller Arduino:
 *
 * - TX(0): 50
 * - RX(1): 51
 * - GND: GND
 *
 * Settings
 *
 * DeviceName: Name to be shown in Homebridge
 * SerialNumber: SerialNumber for communication
 * SSID: SSID of your wifi network
 * Password: Password of your wifi network
 * AcessPointMode: Should the device make it's own network or should it connect to one
 * AlwaysReAuth: (Only if AccessPointMode is false) Always reconnects to wifi (Will result in longer load times)
 *
 */

String DeviceName = "Fan001";
String SerialNumber = "Fan001";
String SSID = "";
String Password = "";
bool AccessPointMode = false;
bool AlwaysReAuth = false;

// DO NOT EDIT! (Unless you know what you are doing)

// Test parameters (DO NOT USE)

bool testModecon = true; // Disables connection to controller

#include <SoftwareSerial.h>

SoftwareSerial esp8266(10, 11);
SoftwareSerial controller(51, 50);

#define serialCommunicationSpeed 9600

#define DEBUG true

/*
 *
 * Setup values
 *
 */

// Answers (Not really used anymore)
String answerstatus = "{\"power\":\"0\",\"speed\":\"0\",\"swing\":\"0\"}\r\n";
String answergdi = "{\"status\":\"OK\",\"body\":{\"name\":\"" + DeviceName + "\",\"sn\":\"" + SerialNumber + "\",\"functions\":{\"power\":{\"min\":0,\"max\":1},\"speed\":{\"min\":1,\"max\":4},\"swing\":{\"min\":0,\"max\":1}}}}\r\n";
String errormsg = "";
String defaulterrormsg = "{\"status\":\"Error\",\"body\":{\"errmsg\":\"An unknown error occurred.\"}}";
int answertype = 0;
int answerstatuslen = 0;
int answergdilen = answergdi.length();
int errormsglen = 0;
int defaulterrormsglen = 66;

// Error handling & Stress handling
int errorled = 6;
bool processing = false;

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

  if (!esp8266)
  {
    handleErrors(3);
  }

  controller.begin(19200);

  bool active = false;

  long int mils = millis();

  int i = 0;

  if (testModecon == false)
  {
    controller.listen();

    controller.write(105);

    Serial.println("Initialising controller...");

    while (active == false)
    {
      if (i >= 5)
      {
        Serial.println("Error while initializing controller!");
        handleErrors(1);
      }
      while (controller.available())
      {
        char chara = controller.read();
        if (chara == 'i')
        {
          active = true;
        }
      }
      if (millis() - mils > 1000 && !active)
      {
        i++;
        mils = millis();
        controller.write(105);
        Serial.println("Initialisation failed! Trying again:" + String(i));
      }
    }
  }
  else
  {
    Serial.println("Controller skipped. Test Mode enabled!");
  }

  InitWifiModule();

  Serial.println("Ready");
}

void loop()
{
  if (esp8266.find("busy"))
  {
    handleErrors(4);
  }
  if (esp8266.find("+IPD,"))
  { // look for request start
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
      // Not used for now
      /*answerstatus = "{\"status\":\"OK\",\"body\":{\"power\":\"" + String(powerval) + "\",\"speed\":\"" + String(speedval) + "\",\"swing\":\"" + String(swingval) + "\"}}\r\n";
      answerstatuslen = answerstatus.length();*/
      delay(500);
      processing = false;
    }
    else
    {
      Serial.println("Already processing!");
    }
  }
}

// Process recieved request

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

  // Check possible actions

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
  else if (actstr == "speed" && arg1 != -1)
  {
    int arg1num = param.substring((arg1 + 6)).toInt();
    if (arg1num == 0)
    {
      powerval = 0;
      sendSettings(97, 0);
      return 200;
    }
    if (arg1num > 4 || arg1num < 1)
    {
      errormsg = "{\"status\":\"Error\",\"body\":{\"errmsg\":\"Speed: Number out of range\"}}\r\n";
      errormsglen = 68;
      return 400;
    }
    if (powerval == 0)
    {
      powerval = 1;
      sendSettings(97, 1);
    }
    speedval = arg1num;
    sendSettings(98, arg1num);
    return 200;
  }
  else if (actstr == "swing" && arg1 != -1)
  {
    int arg1num = param.substring((arg1 + 6)).toInt();
    if (arg1num > 1 || arg1num < 0)
    {
      errormsg = "{\"status\":\"Error\",\"body\":{\"errmsg\":\"Swing: Number out of range\"}}\r\n";
      errormsglen = 68;
      return 400;
    }
    swingval = arg1num;
    sendSettings(103, arg1num);
    return 200;
  }
  errormsg = "{\"status\":\"Error\",\"body\":{\"errmsg\":\"Act: Unknown value\"}}\r\n";
  errormsglen = 60;
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
              "Content-Type: text/json\r\n"
              "Connection: Closed\r\n"
              "\r\n");

    headlen = header.length();

    // Set the status answer
    if (powerval == 0)
    {
      content = "{\\\"power\\\":" + String(powerval) + ",\\\"speed\\\":" + String(0) + ",\\\"swing\\\":" + String(swingval) + "}\r\n";
    }
    else
    {
      content = "{\\\"power\\\":" + String(powerval) + ",\\\"speed\\\":" + String(speedval) + ",\\\"swing\\\":" + String(swingval) + "}\r\n";
    }
    // Check answer type (Not used)
    /*
    switch (answertype)
    {
      //#TODO: Send status with set commands #21 & deprecate
    case 0:
      content = "{\"status\":\"OK\"}\r\n";
      //conlen = content.length();
      break;
    case 1:
      // Send Device Status
      content = answerstatus;
      //conlen = answerstatuslen;
      break;
    case 2:
      // Send Device Info
      content = answergdi;
      //conlen = answergdilen;
      break;
    default:
      content = "{\"status\":\"Error\",\"body\":{\"errmsg\":\"Answer not defined\"}}\r\n";
      break;
    }
    */
    conlen = content.length();

    answertype = 0;
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

  long int times = millis();

  while ((times + timeout) > millis())
  {
    while (esp8266.available())
    {
      char c = esp8266.read();

      response += c;
    }
  }
  if (response.indexOf("busy") != -1)
  {
    handleErrors(4);
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
  if (testModecon == false)
  {
    int num = action + value;
    controller.write(num);
  }
  else
  {
    Serial.println("Test mode enabled! Sent byte: " + String(action + value));
  }
}

void handleErrors(int errorid)
{
  digitalWrite(errorled, HIGH);
  Serial.println("Encountered Error: " + String(errorid));
  while (true)
  {
    /*
     *
     * Error Ids
     *
     * 1: Failed to initialize controller
     * 2: Could not connect to wifi
     * 3: Failed to initialize esp8266 Serial
     * 4: Got "busy". Resetting
     *
     */
    if (errorid == 1)
    {
      digitalWrite(errorled, LOW);
      delay(500);
      digitalWrite(errorled, HIGH);
      delay(2000);
    }
    else if (errorid == 2)
    {
      digitalWrite(errorled, LOW);
      delay(500);
      digitalWrite(errorled, HIGH);
      delay(500);
      digitalWrite(errorled, LOW);
      delay(500);
      digitalWrite(errorled, HIGH);
      delay(2000);
    }
    else if (errorid == 3)
    {
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
    else if (errorid == 4)
    {
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
      // resetFunc();
    }
  }
}

void InitWifiModule()
{
  esp8266.listen();
  sendData("AT+RST\r\n", 2000, DEBUG);

  if (AccessPointMode == true)
  {
    sendData("AT+CWMODE=2\r\n", 500, DEBUG);
    sendData("AT+CWSAP=\"" + SSID + "\",\"" + Password + "\",3,3\r\n", 500, DEBUG);
  }
  else
  {
    String log = sendData("AT+CWMODE=1\r\n", 1000, DEBUG);
    if (log.indexOf("WIFI CONNECTED") == -1)
    {
      sendData("AT+CWJAP=\"" + SSID + "\",\"" + Password + "\"\r\n", 7000, DEBUG);
    }
    else if (log.indexOf("WIFI CONNECTED") != -1 && AlwaysReAuth)
    {
      sendData("AT+CWJAP=\"" + SSID + "\",\"" + Password + "\"\r\n", 9000, DEBUG);
    }
    if (log.indexOf("WIFI GOT IP") == -1 && !AlwaysReAuth)
    {
      delay(2000);
    }
  }
  String info = sendData("AT+CIFSR\r\n", 500, DEBUG);

  if (AccessPointMode == false)
  {
    if (info.indexOf("+CIFSR:STAIP") == -1)
    {
      handleErrors(2);
    }
  }

  // delay(1000);
  sendData("AT+CIPMUX=1\r\n", 500, DEBUG);

  // delay(1000);
  sendData("AT+CIPSERVER=1,80\r\n", 500, DEBUG);
}

void (*resetFunc)(void) = 0;
