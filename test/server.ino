#include <SoftwareSerial.h>

SoftwareSerial esp8266(3,2);

#define serialCommunicationSpeed 9600

#define DEBUG true

int lamp = 11;

String ssid = "Test";

String pw = "Test12345";

void setup() {
  pinMode(lamp,OUTPUT);

  analogWrite(lamp, 0);

  Serial.begin(serialCommunicationSpeed);

  esp8266.begin(serialCommunicationSpeed);

  InitWifiModule();

}

void loop() {
    if(esp8266.find("+IPD,")) {       //look for request start
        int timeout = 500;
        long int times = millis();

        String result = "";

        while((times+timeout) > millis()) {   //save whole request
            while(esp8266.available()) {
                char c = esp8266.read();

                result+=c;
            }
        }

        int connectionid = result.charAt(0) - 48;

        int start = result.indexOf("/?act");
        int end = result.indexOf(" HTTP");
        bool favi = (result.indexOf("favicon.ico") != -1);
        bool isact = (result.indexOf("act=") != -1);          // check if request is valid

        Serial.println("Start:" + String(start));
        Serial.println("End:" + String(end));

        if(start != -1 && end != -1 && favi != true && isact == true) {
          String substr = result.substring((start + 2),end);
          Serial.println("Substr:" + substr);
          sendResponse(200, connectionid);
        } else if(favi == true) {
          sendResponse(204, connectionid);
        } else {
          sendResponse(400, connectionid);
        }

        delay(200);
        Serial.println(connectionid);

        String closeCommand = "AT+CIPCLOSE=";

        closeCommand+=connectionid;
        closeCommand+="\r\n";

        sendData(closeCommand,20,DEBUG);
    }
}

void sendResponse(int code, int conid) {    //Respond #1
  String page = "";
  if(code == 200) {
    page = ("HTTP/1.1 200 OK\r\n"
    "Content-Type: text/plain\r\n"
    "Connection: Closed\r\n"
    "\r\n"
    "This is test!\r\n");
  } else if(code == 204) {
    page = ("HTTP/1.1 204 No Content\r\n"
    "Connection: Closed\r\n"
    "\r\n");
  } else if(code == 400) {
    page = ("HTTP/1.1 400 Bad Request\r\n"
    "Connection: Closed\r\n"
    "Content-Type: text/plain\r\n"
    "\r\n"
    "Invalid request!\r\n");
  } else if(code == 404) {
    page = ("HTTP/1.1 404 Not Found\r\n"
    "Connection: Closed\r\n"
    "Content-Type: text/plain\r\n"
    "\r\n"
    "Not Found!\r\n");
  }

  int len = page.length();

  sendData("AT+CIPSEND=" + String(conid) + "," + String(len) + "\r\n", 100, DEBUG);

  delay(200);

  esp8266.print(page);
}

/*
void send200(int conid) {
  String page = ("HTTP/1.1 200 OK\r\n"
  "Content-Type: text/plain\r\n"
  "Connection: Closed\r\n"
  "\r\n"
  "This is test!\r\n");

  int len = page.length();

  sendData("AT+CIPSEND=" + String(conid) + "," + String(len) + "\r\n", 100, DEBUG);

  delay(200);

  esp8266.print(page);
}

void send204(int conid) {
  String page = ("HTTP/1.1 204 No Content\r\n"
  "Connection: Closed\r\n"
  "\r\n");

  int len = page.length();

  sendData("AT+CIPSEND=" + String(conid) + "," + String(len) + "\r\n", 100, DEBUG);

  delay(200);

  esp8266.print(page);
}

void send400(int conid) {
  String page = ("HTTP/1.1 400 Bad Request\r\n"
  "Connection: Closed\r\n"
  "Content-Type: text/plain\r\n"
  "\r\n"
  "Invalid request!\r\n");

  int len = page.length();

  sendData("AT+CIPSEND=" + String(conid) + "," + String(len) + "\r\n", 100, DEBUG);

  delay(200);

  esp8266.print(page);
}
*/

String sendData(String command, const int timeout, boolean debug) {
  String response = "";

  esp8266.print(command);

  long int times = millis();

  while((times+timeout) > millis()) {
    while(esp8266.available()) {
      char c = esp8266.read();

      response+=c;
    }
  }
  if(debug) {
    Serial.println(response);
  }
  return response;
}

void InitWifiModule() {
  sendData("AT+RST\r\n", 2000, DEBUG);

  sendData("AT+SYSSTORE=0\r\n", 1000, DEBUG);

  String settingscommand = ("AT+CWSAP='"+ssid+"','"+pw+"',3,3\r\n");

  Serial.println(settingscommand);

  sendData("AT+CWMODE=2\r\n", 1500, DEBUG);

  sendData(settingscommand, 1500, DEBUG);
  //delay(1000);
  sendData("AT+CIFSR\r\n", 1500, DEBUG);

  //delay(1000);
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG);

  //delay(1000);
  sendData("AT+CIPSERVER=1,80\r\n", 1500, DEBUG);
}