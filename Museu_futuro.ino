//////////////////////////////// Bibliotecas ////////////////////////////
#include <Stepper.h>
#include <IOXhop_FirebaseStream.h>
#include <IOXhop_FirebaseESP32.h>
#include "WiFi.h"
#include <dht.h>

/////////////////////////////////////////////////////////////////////
//////////////////////// Defines /////////////////////////////////////
#define ldr_pino 32
#define host "https://museufuturo.firebaseio.com"
#define senha "4NtPhemYTw8T22wyB928yq2rMIinSOwuG9WJn5St"
#define presenca 34
#define LM35 35
#define umidade 33
#define dht_dpin 23
#define atuador 26

dht DHT;
/////////////////////////////////////////////////////////////////////
//////////////////////////// Globais ///////////////////////////////
const char* ssid = "CINGUESTS";
const char* password = "acessocin";
int ldr_valor = 0;
bool presenca_valor;
float temperatura = 0;
////////////////////////////////////////////////////////////////////

void setup() {
  pinMode(ldr_pino,INPUT);
  pinMode(presenca,INPUT);
  pinMode(LM35,INPUT);
  pinMode(atuador,OUTPUT);
  
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
  
  ldr_valor = analogRead(ldr_pino);
  if(ldr_valor <= 1000)
    digitalWrite(atuador,HIGH);
  else
    digitalWrite(atuador,LOW);
    
  Serial.print("Valor LDR :");
  Serial.println(ldr_valor);

  temperatura = ((float(analogRead(LM35))*5/(4095))/0.01)/2;
  temperatura = temperatura - 9;
  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  DHT.read11(dht_dpin);
  Serial.print("Umidade = ");
  Serial.print(DHT.humidity);
  Serial.println(" %  ");

  presenca_valor = digitalRead(presenca);
  if(presenca_valor == HIGH)
    Serial.println("Detectado");
  else
    Serial.println("Não detectado");
    
  
   Firebase.setInt("Sensor_Luz",ldr_valor);
   Firebase.setInt("umidade",DHT.humidity);
   Firebase.setFloat("Temperatura",temperatura);
   Firebase.setBool("Deteccao",presenca_valor);
  
  delay(1000);
 
  


}
