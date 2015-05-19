/**
 * Proyecto Lab4
 * Modulo Timer
 * Funciones para el manejo del timer A.
 *
 * Los comentarios que aparecen en este archivo se refieren
 * a la funcionalidad y la interface del modulo.
 * Nunca a su implementacion.
 *
 * Timer.h
 * Inicia el TimerA para interrumpir cada 250ms,
 * y llamar a un handler especificado.
 *
 * @author  Braulio R�os <braulioriosf@gmail.com>
 * @version 1.0
 * @date 30 Marzo 2015
 */

/**********************************************************
* Tipos definidos utilizados por el m�dulo
**********************************************************/
//Tipo para pasar puntero al handler
//typedef void (*timer_handler)(void);


 /**
  * Configura e inicia el timer A para interrumpir cada 250ms,
  * y llamar a la funci�n que se pasa como argumento.
  * Cuidado: Se habilitan las interrupciones sin importar el estado anterior.
  * @param void(*h)(void) funci�n que se llamar� cada 250ms.
  */
void start_timerA_250ms(void (*h)(void));
