#include <cerebro.h>
/*
 Este es un ejemplo de lo que puedes hacer con cerebro
 Este ejemplo es un robot seguidor de linea, te sorprenderás
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
 
void setup() {
 //Sumamente importante inicializar los componentes de CEREBRO
  robot.CerebroInit();

}

void loop() {
 //Obtener los valores de los 2 sensores de linea
 /*
 Si el valor es 3 entonces los dos sensores se encuentran en linea blanca
 Si el valor es 1 entonces el sensor izquierdo se encuentra en linea negra
 Si el valor es 2 el sensor derecho se encuentra en linea negra
 Si el valor es 0 los dos sensores se encuentran en linea negra
 */
int direccion = robot.lineSensor();

// comenzamos con nuestro algoritmo 
// Primero necesitamos verificar en que estado se encuentra nuestro robot
switch(direccion){
  // Si los dos sensores se encuentran en linea blanca significa que nuestro robot debe de avanzar :)
  case 3: robot.moveTank(Forward,0); break;
  // Si el sensor izquierdo esta en linea negra el robot debe de girar a la derecha 
  case 1: robot.moveTank(Right,0); break;
   // Si el sensor derecho esta en linea negra el robot debe de girar a la izquierda
  case 2: robot.moveTank(Left,0); break;
  // Si los dos sensores se encuentran en linea negra significa que nuestro robot debe de detenerse :C
  case 0: robot.moveTank(Stop,0); break;
  
  }

}
