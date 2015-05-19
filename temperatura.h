/**
 * Solución del Laboratorio 5 version 2015
 * 
 * @author Javier Schandy - IIE - FING - UdelaR <jschandy@fing.edu.uy>
 * @version 1.0
 * @date 6 de Abril de 2015
 *
 * temperatura.h
 *
 */

/**********************************************************
* Funciones del modulo
**********************************************************/

/**
 * Inicializa todos los pines del MCU como salidas y en 0
 */
void pinSet();

/**
 * Inicializa el ADC, lo configura en modo "sensar temperatura" y espera que estabilice la Ref0
 */
void tempInit();

/**
 * Configura la bandera que indica que hay una medida pronta
 * @param int* flag_main: bandera a encender cuando haya una medida de temperatura lista
 */
void setTemp_flag(int* flag_main);

/**
 * Lanza una lectura de temperatura
 */
void runTemp();

/**
 * Adquisición de temperatura
 * @return int última temperatura medida
 */
int getTemp();
