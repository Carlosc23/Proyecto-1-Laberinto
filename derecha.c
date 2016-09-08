/* Librerias necesarias para el funcionamiento del robot*/
#include "simpletools.h"                      
#include "abdrive.h"
#include "ping.h"

/*
Autores:
Carlos Calderon , 15219
Jennifer Barillas, 15307
Jorge Azmitia, 15202
Algoritmo de seguir a la pared derecha
*/

//Declaracipon de funciones
void rTurn();   //Vuelta a la derecha
void lTurn();   //Vuelta a la izquierda
void step(int num);    //Moverse una casilla hacia enfrente

//Declaracion de variables 
int distance;

int ultra=8;		//pin del sensor Ultrasonico PING

int main()     // Main function
{
  
  
  distance=ping_cm(ultra);  
  //Se inicializa el origen y se entra al laberinto
  if (distance>20){
     step(150);   //Entra al laberinto

  }    
 
  //Bucle infinito 
  while(1){
	  rTurn();                         //Gira a la derecha
	  distance=ping_cm(ultra);         //Mide la distancia hasta la pared mas cercana
	  
	  //Si la distancia es mayor a 20 no hay pared enfrente
	  //Por lo que avanza un paso largo
	  if (distance>20){
		  step(77);
	  }
	  //Si la distancia es menor a 20 hay pared enfrente
	  //Entonces gira a la izquierda hasta que ya no tenga una pared enfrente
	  //Y asi se asegura de siempre mantener una pared a su lado derecho
	  else{
		  while(distance<20){
			  lTurn();
			  distance=ping_cm(ultra);
		  }
		  step(50);						//Da un paso corto
	  }
  }

  

}

/* Funciones definidas */

//Vuelta a la derecha 90 grados
void rTurn(){
  drive_goto(26,-25); 
  pause(200);
}

//Vuelta a la izquierda 90 grados
void lTurn(){
  drive_goto(-25,26); 
  pause(200);
}

//Moverse una casilla hacia adelante lo indicado por el parametro
void step(int num){
	drive_goto(num,num);
	pause(100);
}
