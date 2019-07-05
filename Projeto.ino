//////////////////////////////// Bibliotecas ////////////////////////////
#include <Stepper.h>
#include <IOXhop_FirebaseStream.h>
#include <IOXhop_FirebaseESP32.h>
#include "WiFi.h"
#include <dht.h>

/////////////////////////////////////////////////////////////////////
//////////////////////// Defines /////////////////////////////////////
#define ldr_pino  15
#define host "https://museufuturo.firebaseio.com"
#define senha "4NtPhemYTw8T22wyB928yq2rMIinSOwuG9WJn5St"
#define presenca 34
#define LM35 32
#define umidade 33
#define dht_dpin 33

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
 Serial.print("Valor ldr:");
 Serial.println(ldr_valor);
 Firebase.setInt("Sensor_Luz",ldr_valor);
 
 presenca_valor = digitalRead(presenca);
 
 temperatura = ((float(analogRead(LM35))*5/(4095))/0.01)/2;
 temperatura = temperatura - 9;
 Firebase.setFloat("Temperatura",temperatura);
 Serial.print("Temperatura: ");
 Serial.println(temperatura);
 

  DHT.read11(dht_dpin); //Lê as informações do sensor
  Serial.print("Umidade = ");
  Serial.print(DHT.humidity);
  Serial.println(" %  ");
  Firebase.setInt("umidade",DHT.humidity);
 
 
 if(presenca_valor == HIGH){
    Serial.println("Detectado");
    Firebase.setString("Deteccao","Detectado");
 }
 else{
  Serial.println("Nao Detectado");
  Firebase.setString("Deteccao","Não Detectado");
 }
    

 
  


}
