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
  /*if(esp8266.available()) {
    Serial.print(esp8266.read());
  }*/
  if(esp8266.find("+IPD,")) {
    Serial.println("Yes");
    delay(10);

    //int trash = esp8266.read();
    int connectionid = esp8266.read() - 48;

    while(esp8266.available()) {
    if(esp8266.find("act=")) {
      Serial.println("Act!");
      
    }

    if(esp8266.find("&lum=")) {
      Serial.println("Lum!");
      int lum = -1;
      delay(10);
      String lumstr = "";
      for(int i = 0; i <= 3; i++) {
        int num = esp8266.read() - 48;
        if(num >= 0 && num <= 9) {
          lumstr += String(num);
        }
      }
      if(lumstr != "") {
        lum = lumstr.toInt();
      }
      Serial.println("Lum:" + String(lum));
    }

    /*int lum = (esp8266.read()-48)*100;
    lum += (esp8266.read()-48)*10;
    lum += (esp8266.read()-48);

    if(lum <= 100) {
      int val = map(lum, 0, 100, 0, 255);

      analogWrite(lamp, val);
      
    }*/
    }
    Serial.println(connectionid);

    String closeCommand = "AT+CIPCLOSE=";

    closeCommand+=connectionid;
    closeCommand+="\r\n";

    sendData(closeCommand,1000,DEBUG);
 
  }
}

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
