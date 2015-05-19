/******************************************************************************
*
* Proyecto Laboratorio SisEm
* Modulo main
*
*
* main.c
* @version 1.0
* @date 18 Abril 2015
*
******************************************************************************/

#include "RTC.h"
#include "intrinsics.h"
#include "io430g2553.h"
#include "UART.h"
#include "temperatura.h"
#include <stdio.h>
#include "Timer.h"
#include "cola_f.h"


static int num = 0;
static void (*funcion)();

static int numInterrupts = 0;
static int tempFlag;
static int temp;
static unsigned char NEW_TICK = 0;
static unsigned char msg[MAX_LENGHT];
char newTempMeas = 0;
reloj_t reloj;

static unsigned int wp = 4;

void tick();
void procesar_tick();
void sumar();
void procesar_comando();

/**
 * main
 * Prueba de la implementacion de la cola de funciones, se conservan
 * las instrucciones de inicializacion de los distintos modulos
 * ya que seran necesarias en el proximo laboratorio. 
 */
void main(){
  
  /*Inicializacion de los distintos modulos */
  
  __enable_interrupt();
  init_UART();
  start_timerA_250ms(tick);
  /* Apaga el WATCHDOG y configura el ACLK  a 32 kHz*/
  WDTCTL = WDTPW + WDTHOLD;
  BCSCTL1_bit.XTS = 0;          //Utiliza LFXTS en baja frecuencia
  BCSCTL3_bit.LFXT1S0=0;        //Selecciona crystal interno de 32 kHz
  BCSCTL3_bit.LFXT1S1=0;
  /*Configura el puerto 1.1 como RX y el 1.2 como TX*/
  P1SEL |= BIT1 + BIT2 ;
  P1SEL2 |= BIT1 + BIT2 ;
  
  tempInit();
  setTemp_flag(&tempFlag);
  
  //bucle principal
  while(1){
    if(FLAG_RX_COMPLETO()){
      procesar_comando();
    }
    if(NEW_TICK){
      procesar_tick();
    }
  }
  
}

/**tick(): El módulo Timer llama a esta función cada 250ms desde la ISR*/
void tick(){
  NEW_TICK=1;
  incrementar_250ms();
}

/** procesar_tick() */
void procesar_tick(){
        NEW_TICK = 0;
        numInterrupts++;
        if(numInterrupts == wp){
          numInterrupts = 0;
          runTemp();
          while(!tempFlag);
          temp = getTemp();
          sprintf(msg, "%d\r", temp);
          enviar_msg(msg);  
        }
}

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

  