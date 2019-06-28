#include "WiFi.h"
#include <Ultrasonic.h>

const char* ssid = "CINGUESTS";
const char* password =  "acessocin";

//const char* ssid = "TP-LINK_BBAE38";
//const char* password =  "mdpg1996";

unsigned int distancia = 0;

#define INTERVALO_LEITURA 250 //(ms)
#define PIN_TRIGGER   23
#define PIN_ECHO      22

Ultrasonic ultrasonic(PIN_TRIGGER, PIN_ECHO);

void setup() {
  
  pinMode(2, OUTPUT);
  Serial.begin(115200);

  Serial.println("Bom dia");
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  digitalWrite(2,HIGH);
  
 
}
 
void loop() {
  verificarDistancia();
  delay(INTERVALO_LEITURA);
  }
  
/*
  VERIFICA A DISTANCIA ATUAL QUE O SENSOR ULTRASONIC ESTA LENDO
  E EM SEGUIDA, IMPRIME O VALOR NO DISPLAY, E ACENDE O LED CORRESPONDENTE
*/
void verificarDistancia()
{

    //recupera a distância atual lida pelo sensor
    distancia = getDistance();
    
  Serial.print("Distancia: ");
  Serial.println(distancia);
  
  
}

/*
  FAZ A LEITURA DA DISTANCIA ATUAL CALCULADA PELO SENSOR
*/
int getDistance()
{
    //faz a leitura das informacoes do sensor (em cm)
    int distanciaCM;
    long microsec = ultrasonic.timing();
    distanciaCM = ultrasonic.convert(microsec, Ultrasonic::CM);

    return distanciaCM;
}
