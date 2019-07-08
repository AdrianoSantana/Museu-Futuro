#include <Stepper.h> 
 
const int stepsPerRevolution = 500; 
  
//Inicializa a biblioteca utilizando as portas de 8 a 11 para 
//ligacao ao motor 
Stepper myStepper(stepsPerRevolution, 8,10,9,11); 
  
void setup() 
{ 
 //Determina a velocidade inicial do motor 
 myStepper.setSpeed(60);
} 
  
void loop() 
{  
 //Gira o motor no sentido horario, aumentando a
 //velocidade gradativamente
 for (int i = 10; i<=60; i=i+10)
 {
 myStepper.setSpeed(i);
 myStepper.step(40*i);
 }
 delay(2000); 
}
