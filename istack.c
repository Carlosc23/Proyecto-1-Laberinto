/*
  Maze solver 1 mano izquierda 
Jorge Azmitia 15202
Carlos Calderon 15219
Jennifer Barillas 15307
*/
/* Librerias necesarias para el funcionamiento del robot*/

#include "simpletools.h"                      
#include "abdrive.h"
#include "ping.h"
#include <stdio.h>
#include <stdlib.h>
/*definiendo tamaño maximo*/
#define STACK_SIZE 100
#define EMPTY (-1)
//funciones de guardado de pasos 
void push(char ch);		
char pop();				
int isEmpty();			
int isFull();			
char elements[ STACK_SIZE];
int top = EMPTY;

void push( char ch)
{
	elements[ ++top] = ch;
}

char pop()
{
	return elements[ top--];
}

int isEmpty()
{
	return top == EMPTY;
}

int isFull()
{
	return top == STACK_SIZE - 1;
}

//Declaracipon de funciones
void rTurn();   //Vuelta a la derecha
void lTurn();   //Vuelta a la izquierda
void step(int num);    //Moverse una casilla hacia enfrente
void mostrar();

//Declaracion de variables
int distance;
int ultra=8;		//pin del sensor Ultrasonico PING
int i;
int main()     // Main function
{
  distance=ping_cm(ultra);  //se mide la distancia hacia la pared 
  //Se inicializa el origen y se entra al laberinto
  if (distance>20){
     step(150);   //Entra al laberinto
  }    
  //Bucle infinito 
  while(1){
	  lTurn();   
	  //Gira a la izquierda
	  distance=ping_cm(ultra);         //Mide la distancia hasta la pared mas cercana
	  
	  //Si la distancia es mayor a 20 no hay pared enfrente
	  //Por lo que avanza 
	  if (distance>20){
		  step(77);
		  push("I"); 
		  push("A"); 

	  }
	  //Si la distancia es menor a 20 hay pared enfrente
	  //Entonces gira a la derecha hasta que ya no tenga una pared enfrente
	  //Y asi se asegura de siempre mantener una pared a su lado izquierdo
	  else{
		  while(distance<20){
			  rTurn();
			  distance=ping_cm(ultra);
			  push("D"); 
		  }
		  step(50);						//Avanza
		  push("A");
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

//mostrar los pasos realizados para salir del laberinto 
void mostrar(){
  printf("\nLos pasos para Salir son:\n");
		for (i=top; i>=0; i--)  {
            if (elements[i]=='A'){
              printf("\tAdelante\n");
            }
            if (elements[i]=='D'){
              printf("\tDerecha\n");
            }
            if (elements[i]=='I'){
              printf("\tIquierda\n");
            }       
			} 
}  