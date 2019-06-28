#include <IOXhop_FirebaseStream.h>
#include <IOXhop_FirebaseESP32.h>

#include "WiFi.h"

const char* ssid = "CINGUESTS";
const char* password = "acessocin";

#define host "https://testando-b3a27.firebaseio.com/"
#define senha "utBiLBFodrpTtJKXFvkJpNnFt7P5lsRRDFcEJuKO"

#define ldr  35
#define led_a 13
#define led_amarelo 21

int ldr_valor = 0;
String valor_lido;

void setup() {
  pinMode(ldr,INPUT);
  pinMode(led_amarelo,OUTPUT);
  pinMode(led_a,OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Conectando ao wifi"); 
  }
  Serial.print("Meu ip: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(host,senha);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  ldr_valor = analogRead(ldr);
  Serial.print("Valor ldr:");
  Serial.println(ldr_valor);
  Firebase.setInt("Sensor_Luz",ldr_valor);
  valor_lido = Firebase.getString("Led_Azul");
  Serial.println(valor_lido);
  if(ldr_valor > 800){
    digitalWrite(led_amarelo,HIGH);
    
     
  }
  else{
  digitalWrite(led_amarelo,LOW);
  }
  if(valor_lido == "HIGH")
    digitalWrite(led_a,HIGH);
  else
    digitalWrite(led_a,LOW);

}
