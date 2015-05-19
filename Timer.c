#include "io430g2553.h"
#include "Timer.h"


static void (*handler)(void);

 /** start_timerA_250ms(handler): Inicia timeout cada 250ms.
  * Deshabilita el Watchdog Timer.
  * Configura el Basic Clock System (ver User Guide)
  * Habilita interrupciones y prende oscilador de cristal.
  * Configura el Timer A para interrumpir cada 250ms.
  * Fija el handler a ser llamado por la ISR (parametro).
  */
void start_timerA_250ms(void (*h)(void)){
  //--------Handler a ejecutar cada 250ms--
  handler = h;
  
  //---------parar WatchDog Timer (?)---------
  WDTCTL = WDTPW | WDTHOLD;
  
  //---------Basic Clock System Control---------
  BCSCTL1 |= DIVA_0; //sin divisor para ACLK
  BCSCTL3 |= XCAP_3; //12.5pF (tipico)
  
  
  //---------Habilito interrupciones y prendo el oscilador---------
  unsigned short register_SR = __get_SR_register();
  register_SR |= GIE;
  register_SR &= ~OSCOFF;
  __bis_SR_register(register_SR);
  
  //---------Configuracion del Timer A----------------
  //Limite del contador
  TA0CCR0 = 1024;  //250ms (aclk = 32768Hz, div = 8)
  
  //CTL del timer A: Clear, Clock Source aclk, Count Mode UP, divider /8
  TA0CTL = TACLR | TASSEL0 | MC0 | ID0 | ID1; //crystal clock
  
  //CTL del contador: Puede interrumpir
  TA0CCTL0 = CCIE;
  
}

  
 /**
  * ISR para el timer A: llama a la función que se le pasó como
  * argumento en start_timerA_250ms(funcion)
  */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void timerA_handler( void ){
  handler();
}
