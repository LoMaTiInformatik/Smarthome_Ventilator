int servopin = 6;

void setup() {
    pinMode(servopin, OUTPUT);

    Serial.begin(9600);
    Serial.println("Ready!");
}

void loop() {
    if(Serial.available()) {
        double test = Serial.parseFloat();
        Serial.println(test);
        servoset(test, 6);
    }
}

void servoset(int x, int pin){
  int val = x;
  digitalWrite(pin,HIGH);
  delay(val);
  digitalWrite(pin,LOW);
  delay(10);
  Serial.println(x);
  Serial.println(val);
  }