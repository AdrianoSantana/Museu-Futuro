#include "WiFi.h"

const char* ssid = "CINGUESTS";
const char* password = "acessocin";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Conectando ao wifi");  
  }
  Serial.print("Meu ip: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
