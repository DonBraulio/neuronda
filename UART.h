/******************************************************************************
*
* Proyecto Laboratorio SisEm
* Modulo UART
*
* Este modulo implementa las funciones e interrupciones de la comunicacion serial
* en modo UART
*
* UART.h
* @version 1.0
* @date 12 Abril 2015
*
******************************************************************************/

/******************************************************************************
* Constantes del modulo
******************************************************************************/

/** Maximo largo del mensaje */
#define MAX_LENGHT 100

/******************************************************************************
* Funciones del modulo
******************************************************************************/

/** init_UART
* @brief: Inicializa el modulo UART
*/
void init_UART();

/** enviar_msg
* @brief: Envia una cadena de caracteres por serial
* @precond: El mensaje tiene un tamaño igual o menor a MAX_LENGTH
* @param unsigned char * msg: Cadena a enviar
*/
void enviar_msg(unsigned char * msg);

/** copiar_bufferRX
* @brief: Devuelve el mensaje almacenado en el buffer y lo limpia
* @param unsigned char * msg: Puntero a donde se devuelve el buffer
*/
void copiar_bufferRX(unsigned char * msg);

/** FLAG_RX_COMPLETO
* @brief: Pregunta si hay un mensaje completo en el buffer
* @return: FLAG de mensaje completo
*/
unsigned short int FLAG_RX_COMPLETO();

/** TXA0_ISR
* @brief: Interrupcion TX
*/
__interrupt void TXA0_ISR();

/** RXA0_ISR
* @brief: Interrupcion RX
* @precond: El bufferRX no va a estar lleno (los mensajes recibidos
*               tienen el tamaño igual o menor a MAX_LENGTH)
*/
__interrupt void RXA0_ISR();