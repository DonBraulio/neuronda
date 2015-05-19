#include "cola_f.h"

/******************************************************************************
*
* Proyecto Laboratorio SisEm
* Modulo cola de funciones
*
* Este modulo implementa la cola de funciones
*
* cola_f.c
* @version 1.0
* @date 18 Abril 2015
*
******************************************************************************/

/******************************************************************************
* variables del modulo (restringidas 
******************************************************************************/

/*Cola de funciones*/
static void (*funciones[MAX_LENGTH])();
/*apunta a primer funcion*/
static int primer_funcion = 0;
/*apunta a la posicion donde esta la ultima funcion*/
static int ultima_funcion = -1;

/******************************************************************************
* funciones de modulo
******************************************************************************/



/** cola_llena 
Se detecta cola llena cuando el ultimo elemento está justo antes del primero.
Salvo en el caso donde ultima_funcion = -1 (y primer_funcion = 0),
que se setea explícitamente cuando la cola queda vacía.
*/
char cola_llena(){
  //descarto el caso cola vacía
  if (ultima_funcion == -1) return 0;
  //calculo elemento siguiente al ultimo de la cola circular
  char siguiente_ultima = ultima_funcion + 1;
  if (siguiente_ultima == MAX_LENGTH) siguiente_ultima = 0;
  //si el siguiente al ultimo es el primero, la cola esta llena
  return siguiente_ultima == primer_funcion;
}

/** cola_vacia 
Debe asegurarse que en desencolar_funcion() se lleva ultima_funcion a -1 cuando
se extrae el último elemento.
*/
char cola_vacia(){
  return (ultima_funcion == -1);
}

/** desencolar_funcion 
Si al desencolar una funcion, se cumple la condicion para cola_llena(),
debido a que el último elemento está justo antes del primero, quiere decir
que en realidad la cola acaba de quedar vacía, por lo que se setea
manualmente ultima_funcion = -1, primer_funcion = 0.
*/
f_pointer_t desencolar_funcion(){
  if(cola_vacia()){
    //retorna null pointer
    return (f_pointer_t)0;
  }
  /** Se asigna al puntero funcion la primer funcion disponible */
  f_pointer_t funcion = funciones[primer_funcion];
  
  /* Cola circular */
  if(++primer_funcion == MAX_LENGTH){
    primer_funcion = 0;
  }
  //las condiciones cola_llena y cola_vacía son iguales, se distinguen
  //poniendo el indice de ultima_funcion = -1 cuando está vacía.
  if(cola_llena()){//en realidad está vacía, acabamos de sacar el último
    primer_funcion = 0;
    ultima_funcion = -1;
  }
  return funcion;
}

/** encolar_funcion */
char encolar_funcion(void (*funcion)(void)){
  if(cola_llena())
    return 0;
  
  /* Cola circular */
  if(++ultima_funcion == MAX_LENGTH){
    ultima_funcion = 0;
  }
  /* Se guarda la funcion apuntada por el parametro */
  funciones[ultima_funcion] = funcion;
  return 1;
}