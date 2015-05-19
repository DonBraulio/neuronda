/******************************************************************************
*
* Proyecto Laboratorio SisEm
* Modulo UART
*
* Este modulo implementa las funciones e interrupciones de la comunicacion serial
* en modo UART
*
* UART.c
* @version 1.0
* @date 12 Abril 2015
*
******************************************************************************/

#include "io430g2553.h"
#include "UART.h"
#include "cola_f.h"

/******************************************************************************
* Variables del modulo (restringidas)
******************************************************************************/

/** Buffer del mensaje a transmitir */
static unsigned char mensajeTX[MAX_LENGHT];
/** Buffer del mensaje leido */
static unsigned char mensajeRX[MAX_LENGHT];
/** Contador para el buffer TX */
static unsigned short int iTX = 0;
/** Contador para el buffer RX */
static unsigned short int iRX = 0;
/** Bandera que indica si hay un mensaje completo leido*/
static unsigned short int RX_COMPLETO = 0;
/** Bandera que indica si el TX esta en uso */
static unsigned short int TX_USE = 0;

/******************************************************************************
* funciones de modulo 
******************************************************************************/

/** init_UART */
void init_UART(){
  /*Se selecciona ACLK como reloj, el resto de las configuraciones
    son las de default*/
  UCA0CTL1_bit.UCSSEL0 = 1;
  UCA0CTL1_bit.UCSSEL1 = 0;
  
  IE2 = 0XFF;
  
  /*Baudios*/
  UCA0BR0 = 27;
  UCA0BR1 = 0;
  
  UCA0CTL1_bit.UCSWRST = 0;
  
    /*se debe inicializar con las interrupciones TX deshabilitadas
    y las RX habilitadas*/
  IE2_bit.UCA0RXIE = 1;
  IE2_bit.UCA0TXIE = 0;
}

/** enviar_msg */
void enviar_msg(unsigned char * msg){
  /** Si todavía se esta enviando un mensaje se espera a que termine */
  while(TX_USE == 1);
  
  /** Se indica que el TX esta en uso y se reinicia el contador del buffer
      TX */
  TX_USE = 1;
  iTX = 0;
  
  /** Se copia el mensaje en el buffer */
  while(*(msg + iTX) != '\r'){
    mensajeTX[iTX] = *(msg+iTX);
    iTX++;
  }
  mensajeTX[iTX] = '\r';
  
  /** Se envia el primer caracter y se habilitan las interrupciones */
  UCA0TXBUF = mensajeTX[0];
  iTX = 0;
  IE2_bit.UCA0TXIE = 1;
  IE2_bit.UCA0RXIE =1;
}

/** copiar_bufferRX */
void copiar_bufferRX(unsigned char * msg){
  /** Copia el buffer (se asume que tiene a lo sumo un mensaje completo) */
  int i = 0;
  while(mensajeRX[i] != '\r'){
    *(msg + i) = mensajeRX[i];
    i++;
  }
  *(msg + i) = mensajeRX[i];
  RX_COMPLETO = 0; /**Apaga el FLAG de mensaje completo */
}

/** FLAG_RX_COMPLETO */
unsigned short int FLAG_RX_COMPLETO(){
  return RX_COMPLETO; /**Retorna el FLAG*/
}

/** TXA0_ISR */
#pragma vector = USCIAB0TX_VECTOR
__interrupt void TXA0_ISR(){
  /**Envia el caracter siguiente del buffer, si se llega al final del mensaje
  entonces se apagan las interrupciones */
  iTX++;
  UCA0TXBUF = mensajeTX[iTX];
  if(mensajeTX[iTX] == '\r'){
    TX_USE = 0;
    IE2_bit.UCA0TXIE = 0;
  }
}

/** RXA0_ISR */
#pragma vector = USCIAB0RX_VECTOR
__interrupt void RXA0_ISR(){
  /** Se almacena el caracter entrante en el buffer, cuando se llega
  al final, el proximo mensaje se sobreescribira. */
  mensajeRX[iRX] = UCA0RXBUF;
  if(mensajeRX[iRX] == '\r'){
    iRX = 0;
    RX_COMPLETO = 1;
  } else{
    iRX++;
  }
}