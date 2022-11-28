const char* test[7] = {"<html>\r\n", "<head>\r\n", "</head>\r\n", "<body>\r\n", "<p>Test</p>\r\n", "</body>\r\n", "</html>\r\n"};

void setup() {
    Serial.begin(9600);
    for(int i = 0; i >= 6, i++;) {
        //Serial.println(String(i) + String(test[i]));
        Serial.println("No");
    }
}
void loop() {

}