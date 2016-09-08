x/*
  Maze solver 1 mano izquierda 
Jorge Azmitia 15202
Carlos Calderon 15219
Jennifer Barillas 15307
*/
#include "simpletools.h"                      
#include "abdrive.h"
#include "ping.h"
#include <stdio.h>
#include <stdlib.h>

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

//Funciones para laberinto
void der();   //vuelta derecha
void izq();   //Vuelta izquierda
void avanzar(int num);    //avanzar
void mostrar();
//variables
int distancia;
int pin=8;		//pin del sensor Ultrasonico PING
int i;



int main()                                   
{
  
  	  distancia=ping_cm(pin);         //Mide la distancia a la pared 
  
  
  //Se inicializa el origen y se entra al laberinto
if(distancia>10)
{
  avanzar(150);   //si la distancia es mayor a 10 cm avanza 
  push("A"); //sube que un char de que avanza al stack
}  
  while(1){
	  izq();                         //Gira a la izquierda
     push("I");                     // sube a stack char de izquierda
  	  distancia=ping_cm(pin);         //Mide la distancia a la pared 
	  //si hay mas de 25 cm entre el robot y la pared, avanza
	  if (distancia>25){
       avanzar(50);
        push("A");
	  }
	 //si la distancia es menor que 25 cm 
	  else{
     //mientras la distancia sea menor a 25 gira a la derecha hasta tener via libre
		  while(distance<25){
   			 der();
           push("D");
    			 distance=ping_cm(ultra);
		  }
		  avanzar(50);						//cuando ya tiene via libre avanza
       push("A");
	  }
  }
}


//vuelta a la derecha 
void der(){
  drive_goto(26,-26); 
  pause(200);
}

//vuelta a la izquierda 
void izq(){
  drive_goto(-26,26); 
  pause(200);
}

//Moverse una casilla hacia adelante lo indicado por el parametro
void avanzar(int num){
	drive_goto(num,num);
	pause(200);
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