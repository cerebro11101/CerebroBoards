#include <cerebro.h>
/*
 Este es un ejemplo de lo que puedes hacer con cerebro
 Este ejemplo es un robot detector de obstaculos, te sorprenderás
 de lo sencillo que es utilizar nuestra librería para que 
 puedas crear todo lo que venga a tu imaginación

 Creador : Epsilon
 Correo : epsilon11101@gmail.com
 Organización: Cerebro Industries
 git: https://github.com/cerebro11101
 Wiki:https://github.com/cerebro11101/cerebro/wiki
 */

//Primer paso: Crear una instancia de cerebro
Cerebro robot;
//definir una distancia limite de detección de obstaculos en mi caso 10 cm
#define limite_d  10


void setup() {
 //Sumamente importante inicializar los componentes de CEREBRO
  robot.CerebroInit();

}

void loop() {
  //obtener el valor de la distancia del sensor ultrasónico
int distancia = robot.getDistance();

  //Comparar si la distancia actual es menor a nuestro limite de distancia
  //ademas poner una restricción de que la distancia debe de ser siempre positiva y mayor que 0
  // ya que cuando las distancias son menores a 2 cm el sensor marca distancias negativas ten en cuenta esto para 
  //todos tus proyectos!
if(distancia <= limite_d && distancia > 0) {
    robot.moveTank(Stop,100);
    robot.moveTank(Forward,500);
    robot.moveTank(Right,500);
  }
  //si no hay obstaculos cerebro sigue hacia adelante :)
else{
    robot.moveTank(Backward,0);
  }

}
