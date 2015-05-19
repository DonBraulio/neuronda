/*
 * Soluci?n del Laboratorio 5 version 2014
 * 
 * por Javier Schandy - IIE - FING - UdelaR <jschandy@fing.edu.uy>
 *
 * temperatura.c
 *
 */

#include <io430g2553.h>
#include "temperatura.h"

static int temp;
static int tempCelsius;
static int* flag;

//////////////////////////////////////////////////////////////////////
 //                         Funciones                                //
 //////////////////////////////////////////////////////////////////////

void pinSet(){
  P1DIR = 0xFF;                             // All P1.x outputs
  P1OUT = 0;                                // All P1.x reset
  P2DIR = 0xFF;                             // All P2.x outputs
  P2OUT = 0;                                // All P2.x reset
  P3DIR = 0xFF;                             // All P3.x outputs
  P3OUT = 0;                                // All P3.x reset  
}

void tempInit(){
  ADC10CTL1 = INCH_10 + ADC10DIV_3;         // Temp Sensor ADC10CLK/4
  ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE;
  __delay_cycles(1000);                     // Esperar que se estabilice la Ref del ADC  
}

void runTemp(){
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
}

void setTemp_flag(int* flag_main){
  flag = flag_main;
}

int getTemp(){
  tempCelsius = ((temp - 673) * 423) / 1024;  // Hago la conversi?n a ?C
  return tempCelsius;
}

 //////////////////////////////////////////////////////////////////////
 //         Rutinas de atenci?n a interrupciones                     //
 //////////////////////////////////////////////////////////////////////  

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
  *flag = 1;
  temp = ADC10MEM;
}