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
    if(esp8266.find("+IPD,")) {
        int timeout = 3000;
        long int times = millis();

        String result = "";

        while((times+timeout) > millis()) {
            while(esp8266.available()) {
                char c = esp8266.read();

                result+=c;
            }
        }

        int connectionid = result.charAt(0) - 48;

        int start = result.indexOf("/?");
        int end = result.indexOf(" HTTP");

        if(start != -1 && end != -1) {
          String substr = result.substring((start + 2),end);
          Serial.println("Substr:" + substr);
          sendWebpage(connectionid);
          
        }

        Serial.println(connectionid);

        String closeCommand = "AT+CIPCLOSE=";

        closeCommand+=connectionid;
        closeCommand+="\r\n";

        sendData(closeCommand,1000,DEBUG);
    }
}

void sendWebpage(int conid) {
  /*String page = ("HTTP/1.1 200 OK\r\n"
  "Content-Type: text/plain\r\n"
  "Connection: Closed\r\n"
  "\r\n"
  "This is test!\r\n");*/
  String page = "HTTP/1.1 204 no content\r\n";

  int len = page.length() + 4;

  sendData("AT+CIPSEND=" + String(conid) + "," + String(len) + "\r\n", 100, DEBUG);

  sendData(page, 3000, DEBUG);
}

String sendData(String command, const int timeout, boolean debug) {
  String response = "";

  if(command.substring(0, 4) == "HTTP") {
    /*for(int i = 0; i == command.length(); i++) {
      String c = command.charAt(i);
      esp8266.print(c);
      delay(10);
    }*/
    esp8266.print(command);
  } else {
    esp8266.print(command);
  }

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