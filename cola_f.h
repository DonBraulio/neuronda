/******************************************************************************
*
* Proyecto Laboratorio SisEm
* Modulo cola de funciones
*
* Este modulo implementa la cola de funciones.
* Se implemente como una cola circular
*
* cola_f.h
* @version 1.0
* @date 18 Abril 2015
*
******************************************************************************/

/** Maximo de funciones que se pueden encolar */
#define MAX_LENGTH 5 

/** Tipo de dato Puntero a funcion**/
typedef void (*f_pointer_t)(void);

/******************************************************************************
* funciones de modulo
******************************************************************************/

/** cola_llena
* @brief: pregunta si la cola esta llena
* @return: 1 si esta llena, 0 en caso contrario
*/
char cola_llena();

/** cola_vacia
* @brief: pregunta si la cola esta vacia
* @return: 1 si esta vacia, 0 en caso contrario
*/
char cola_vacia();

/** desencolar_funcion
* NOTA: Si la cola está vacía, devuelve null pointer.
* @brief: Desencola una funcion
* @precond: La cola no esta vacia (o devuelve null pointer)
* @return f_pointer_t: Puntero a la función desencolada o null pointer
*/
f_pointer_t desencolar_funcion();

/** encolar_funcion
* @brief: Encola una funcion
* @param f_pointer_t: Puntero a la funcion a encolar
* @return 0 si la cola estaba llena (se ignora la llamada),
          1 si había espacio y la función se pudo encolar.
*/
char encolar_funcion(void (*funcion)(void));