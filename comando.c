/******************************************************************************
*
* Proyecto Laboratorio SisEm
* Modulo comando
*
* Este modulo implementa el procesado de comandos recibidos por la UART
*
* comando.c
* @version 1.0
* @date 18 Abril 2015
*
******************************************************************************/

#include "UART.h"
#include "temperatura.c"
#include "RTC.h"
#include "intrinsics.h"
#include <stdio.h>

/** procesar_comando */
void procesar_comando(){
  
  /* Deshabilita interrupciones mientras copia el mensaje del buffer */
  __disable_interrupt();
  copiar_bufferRX(msg);
  __enable_interrupt();
      
  /* Procesa comandos
  * WP: Setea ticks entre lecturas de temperatura
  * RP: Imprime ticks entre lecturas de temperatura
  * RT: Imprime ultima temperatura leida
  * WH: Setea hora del reloj
  * RH: Imprime hora del reloj
  */
  if(msg[0] == 'W' && msg[1] == 'P'){
    wp = ( (msg[3]-'0')*10 + msg[4]-'0');
  } else if(msg[0] == 'R' && msg[1] == 'P'){
    sprintf(msg, "%d\r", wp);
    /*Envia mensaje por la UART*/
    enviar_msg(msg);
  } else if(msg[0] == 'R' && msg[1] == 'T'){
    temp = getTemp();
    sprintf(msg, "%d\r", temp);
    /*Envia mensaje por la UART*/
    enviar_msg(msg);        
  } else if (msg[0] == 'W' && msg[1] == 'H'){
    unsigned char hora;
    unsigned char min;
    unsigned char seg;
        
    hora = (msg[3]-'0')*10 + msg[4]-'0';
    min = (msg[6]-'0')*10 + msg[7]-'0';
    seg = (msg[9]-'0')*10 + msg[10]-'0';
    
    /*Deshabilita interrupciones mientras setea el reloj*/
    __disable_interrupt();
    inicializar_reloj(hora,min,seg,0);
    __enable_interrupt();
  } else if (msg[0] == 'R' && msg[1] == 'H'){
      
    /*Deshabilita interrupciones mientras lee el reloj*/
    __disable_interrupt();
    reloj = tiempo_actual();
    __enable_interrupt();
    
    /*Envia mensaje por la UART*/
    sprintf(msg, "%02d:%02d:%02d\r", reloj.hora, reloj.minuto, reloj.segundo);
    enviar_msg(msg);
  }
 
}
