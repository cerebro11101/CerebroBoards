#include <cerebro.h>
/*
 Este es un ejemplo de lo que puedes hacer con cerebro
 Este ejemplo es un robot seguidor de luz, te sorprenderás
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

void setup(){
  //Sumamente importante inicializar los componentes de CEREBRO
  robot.CerebroInit();
  }

void loop(){
//Obtener los valores del LDR1 utilizando como parametro la letra "l" 
//la cual hace referencia al sensor left(izquierdo)
int LDRIzquierdo = robot.lightSensor('l');
//lo mismo con el otro sensor solo que cambiaremos "l" -> "r"
int LDRDerecho = robot.lightSensor('r');

/*comenzamos con nuestro algoritmo :)
si el valor del LDRI y LDRD son mayores a 500 significa
que los dos sensores tienen mucha luz entonces moveremos a nuestro
robot hacia adelante por 0 segundos ,
Los 0 segundos se pone para que sea una acción que siempre se realize y 
no tome ningun tiempo realizar la acción de mover adelante
*/
if(LDRIzquierdo >= 500 && LDRDerecho >= 500){
    robot.moveTank(Forward,0);
    //encedemos un led de cualquier color de tu agrado
    robot.RGBcolor(Magenta,0);
  }
/*
si el valor del LDRI y LDRD son menores a 500 significa
que los dos sensores tienen poca luz entonces detendremos a nuestro
robot,
Los 0 segundos se pone para que sea una acción que siempre se realize y 
no tome ningun tiempo realizar la acción de mover adelante
*/
if(LDRIzquierdo < 500 && LDRDerecho < 500){
    robot.moveTank(Stop,0);
    //encedemos un led de cualquier color de tu agrado
    robot.RGBcolor(Red,0);
  }

/*
si el valor del LDRI es menor a 500 y  LDRD es mayor a 500 significa
que el sensor I tiene menos luz que el D entonces el robot se muee
hacia la derecha,
Los 0 segundos se pone para que sea una acción que siempre se realize y 
no tome ningun tiempo realizar la acción de mover adelante
*/
if(LDRIzquierdo < 500 && LDRDerecho >= 500){
    robot.moveTank(Right,0);
    //encedemos un led de cualquier color de tu agrado
    robot.RGBcolor(Blue,0);
  }
/*
si el valor del LDRI es mayor a 500 y  LDRD es menor a 500 significa
que el sensor D tiene menos luz que el I entonces el robot se muee
hacia la izquierda,
Los 0 segundos se pone para que sea una acción que siempre se realize y 
no tome ningun tiempo realizar la acción de mover adelante
*/
if(LDRIzquierdo >= 500 && LDRDerecho < 500){
    robot.moveTank(Left,0);
    //encedemos un led de cualquier color de tu agrado
    robot.RGBcolor(Green,0);
  }
  }
