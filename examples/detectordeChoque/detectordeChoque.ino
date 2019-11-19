#include <cerebro.h>
/*
 Este es un ejemplo de lo que puedes hacer con cerebro
 Este ejemplo es un robot detector de choque, te sorprenderás
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

 //Obtener los valores de los 2 sensores de choque
 /*
 Si el valor es 3 entonces los dos sensores se encuentran presionados
 Si el valor es 1 entonces el sensor izquierdo se encuentra presionado
 Si el valor es 2 el sensor derecho se encuentra presionado
 Si el valor es 0 los dos sensores no estan presionados
 */
int direccion = robot.ButtonState();

// comenzamos con nuestro algoritmo 
// Primero necesitamos verificar en que estado se encuentra nuestro robot
switch(direccion){
  // Si los dos sensores no estan presionados significa que nuestro robot debe de avanzar :)
  case 3: robot.moveTank(Forward,0); break;
  // Si el sensor izquierdo esta presionado el robotse detiene,retrocede y gira a la derecha
  case 1: robot.moveTank(Stop,200); robot.moveTank(Backward,500); robot.moveTank(Left,500); break;
  // Si el sensor derecho esta presionado el robotse detiene,retrocede y gira a la izquierda
  case 2: robot.moveTank(Stop,200); robot.moveTank(Backward,500); robot.moveTank(Right,500); break;
  // Si los dos sensores  estan presionados significa que nuestro robot debe de detener,girar atras y girar a la izquierda:)
  case 0: robot.moveTank(Stop,200); robot.moveTank(Backward,500); robot.moveTank(Right,500); break;
  
  }
}
