
/**
 * Proyecto Lab4
 * Modulo RTC
 * Funciones para el manejo de la hora.
 *
 * Los comentarios que aparecen en este archivo se refieren
 * a la funcionalidad y la interface del modulo.
 * Nunca a su implementacion.
 *
 * RTC.h
 * Se mantiene una estructura con precisión de centisegundos, segundos, minutos y horas.
 * La cuenta de horas reinicia en 24.
 *
 * @author  Braulio Ríos <braulioriosf@gmail.com>
 * @version 1.0
 * @date 30 Marzo 2015
 */

/**********************************************************
* Tipos definidos utilizados por el módulo
**********************************************************/

//---------------------------------------------------------
/** Estructura que guarda la cuenta del tiempo en horas, minutos, segundos y centisegundos */
typedef struct{
	unsigned char hora;
	unsigned char minuto;
	unsigned char segundo;
	unsigned char centiseg;
} reloj_t;


/**********************************************************
* Funciones del modulo
**********************************************************/
 
 /**
  * Devuelve el tiempo actual almacenado
  * @return reloj_t Copia de la estructura que almacena el tiempo actual en el módulo.
  */
reloj_t tiempo_actual();


 /**
  * Inicializa el tiempo almacenado en el módulo.
  * Los valores fuera de rango son ignorados.
  * @param unsigned char hora: Valores mayores a 23 serán ignorados
  * @param unsigned char minuto: Valores mayores a 59 serán ignorados
  * @param unsigned char segundo: Valores mayores a 59 serán ignorados
  * @param unsigned char centiseg: Valores mayores a 99 serán ignorados
  */
void inicializar_reloj(unsigned char hora, unsigned char minuto, unsigned char segundo, unsigned char centiseg);

/**
  * Incrementa el contador de tiempo del módulo en 250ms.
  * Suma en el contador de centisegundos, segundos, minutos o horas según sea necesario.
  * Si el contador de hora llega a 24, se reinicia la cuenta a 0.
  */
void incrementar_250ms();
