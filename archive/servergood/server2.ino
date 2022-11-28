#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial esp8266(3,2);
//Servo servo;

#define serialCommunicationSpeed 9600

#define DEBUG true

int lamp = 6;

//int angle = 0;

int bright = 0;

bool status = false;

String ssid = "Test";

String pw = "Test12345";

void setup() {
  pinMode(lamp,OUTPUT);

  analogWrite(lamp, 0);

  //servo.attach(8);

  Serial.begin(serialCommunicationSpeed);

  esp8266.begin(serialCommunicationSpeed);

  InitWifiModule();

  Serial.println("Ready");

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

        /*if(result.indexOf("+IPD,") != -1) {
          Serial.println("Yes second");
          String secondresult = result.substring((result.indexOf("+IPD,")+4));
          result = result.substring(0, result.indexOf("+IPD,"));
          int connectionid2 = secondresult.charAt(0) - 48;
          sendResponse(processRequest(secondresult), connectionid2);

          delay(500);
          String closeCommand2 = "AT+CIPCLOSE=";
          closeCommand2+=connectionid2;
          closeCommand2+="\r\n";

          sendData(closeCommand2, 20, DEBUG);
        }*/

        /*int start = result.indexOf("/?act");
        int end = result.indexOf(" HTTP");
        bool favi = (result.indexOf("favicon.ico") != -1);
        bool isact = (result.indexOf("act=") != -1);          // check if request is valid

        Serial.println("Start:" + String(start));
        Serial.println("End:" + String(end));*/

        /*if(start != -1 && end != -1 && favi != true && isact == true) {
          String substr = result.substring((start + 2),end);
          Serial.println("Substr:" + substr);*/
        sendResponse(processRequest(result), connectionid);
        /*} else if(favi == true) {
          sendResponse(204, connectionid);
        } else {
          sendResponse(400, connectionid);
        }*/

        delay(500);

        String closeCommand = "AT+CIPCLOSE=";

        closeCommand+=connectionid;
        closeCommand+="\r\n";

        sendData(closeCommand,20,DEBUG);
    }
}

int processRequest(String result) {
  Serial.print(result);
  if(result.indexOf("favicon.ico") != -1) {
    return 204;
  }
  int act = result.indexOf("act=");
  String param = result.substring(act, result.indexOf(" HTTP"));
  int arg1 = param.indexOf("&arg1=");
  int arg2 = param.indexOf("&arg2=");
  int arg3 = param.indexOf("&arg3=");
  if(act == -1 || arg1 == -1) {
    Serial.println("No act/arg");
    return 400;
  }
  String actstr = param.substring(4, arg1);
  if(actstr == "toggle" && arg1 != -1) {
    int arg1num = param.substring((arg1 + 6)).toInt();
    if(arg1num == 0) {
      analogWrite(lamp, 0);
      status = false;
      return 200;
    } else if(arg1num == 1) {
      if(bright == 0) {
        bright = 255;
      }
      analogWrite(lamp, bright);
      status = true;
      return 200;
    }
  } else if(actstr == "bright" && arg1 != -1) {
    int arg1num = param.substring((arg1 + 6)).toInt();
    Serial.println(param.substring(arg1 + 6));
    Serial.println(arg1num);
    if(arg1num <= 100 && arg1num >= 0) {
      bright = map(arg1num, 0, 100, 0, 255);
      analogWrite(lamp, bright);
      if(arg1num == 0) {
        status = false;
      } else {
        status = true;
      }
      return 200;
    }
  } else if(actstr == "turn" && arg1 != -1) {
    int arg1num = param.substring((arg1 + 6)).toInt();
    Serial.println("Turn: " + String(arg1num));
    if(arg1num <= 180 && arg1num >= 0) {
      //angle = arg1num;
      //servo.write(arg1num);
      return 200;
    }
  }
  Serial.println("Wrong act!");
  return 400;
}

void sendResponse(int code, int conid) {    //Respond #1
  String header = "";
  String content[] = {};
  String statusstr = ((status)? "On":"Off");
  if(code == 200) {
    header = ("HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Connection: Closed\r\n"
    "\r\n");

    content[0] = ("Status: " + statusstr + "\r\n");
    content[1] = ("Brightness: " + String(bright) + "\r\n");
    
    /*content = ("Status: " + statusstr + "\r\n"
    "Brightness: " + String(bright) + "\r\n");*/
  } else if(code == 204) {
    header = ("HTTP/1.1 204 No Content\r\n"
    "Connection: Closed\r\n"
    "\r\n");
  } else if(code == 400) {
    header = ("HTTP/1.1 400 Bad Request\r\n"
    "Connection: Closed\r\n"
    "Content-Type: text/plain\r\n"
    "\r\n"
    "Invalid request!\r\n");
  } else if(code == 404) {
    header = ("HTTP/1.1 404 Not Found\r\n"
    "Connection: Closed\r\n"
    "Content-Type: text/plain\r\n"
    "\r\n"
    "Not Found!\r\n");
  }

  int csize = (sizeof(content) - 1);

  Serial.println("Page begin: ");

  Serial.println(header);

  for (int i = 0; i >= csize; i++) {
    Serial.println(content[i]);
  }

  Serial.println("Page end");

  int len = 0;
  len+=header.length();
  for (int i = 0; i >= csize; i++) {
    len+=content[i].length();
  }

  Serial.println(len);

  //sendData("AT+CIPSEND=" + String(conid) + "," + String(len) + "\r\n", 100, DEBUG);

  esp8266.print("AT+CIPSEND=" + String(conid) + "," + String(len) + "\r\n");

  delay(200);

  esp8266.print(header);
  if(csize != -1) {
    for (int i = 0; i >= csize; i++) {
      esp8266.print(content[i]);
    }
  }
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

  String settingscommand = ("AT+CWSAP=\""+ssid+"\",\""+pw+"\",3,3\r\n");

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
