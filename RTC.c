/**
 * Proyecto Lab4
 * Modulo RTC
 * Funciones para el manejo de la hora.
 *
 * Los comentarios que aparecen en este archivo se refieren
 * a la implementación del módulo.
 *
 * RTC.c
 * @author  Braulio Ríos <braulioriosf@gmail.com>
 * @version 1.0
 * @date 30 Marzo 2015
 */

#include "RTC.h"

//----------------------------------------------------------
/** Estructura interna que almacena el valor actual del tiempo
 */
static reloj_t reloj;


//----------------------------------------------------------
/** Inicializa la estructura estática de tipo reloj_t que lleva la cuenta del tiempo
 */
void inicializar_reloj(unsigned char hora,  unsigned char minuto, unsigned char segundo, unsigned char centiseg){
	reloj.hora = hora;
	reloj.minuto = minuto;
	reloj.segundo = segundo;
	reloj.centiseg = centiseg;
}

//----------------------------------------------------------
/** Incrementa coherentemente cada campo de la estructura reloj_t
 */
void incrementar_250ms(){
	unsigned char centiseg = reloj.centiseg + 25;
	if(centiseg >= 100){
		unsigned char seg = reloj.segundo + 1;
		centiseg -= 100;
		if(seg >= 60){
			unsigned char min = reloj.minuto + 1;
			seg -= 60;
			if(min >= 60){
				unsigned char hora = reloj.hora + 1;
				min -= 60;
				if(hora >= 24){
					hora = 0;
				}
				reloj.hora = hora;
			}
			reloj.minuto = min;
		}
		reloj.segundo = seg;
	}
	reloj.centiseg = centiseg;
}

//----------------------------------------------------------
/** Devuelve una copia de la estructura interna reloj_t
 */
reloj_t tiempo_actual(){
	return reloj;
}
