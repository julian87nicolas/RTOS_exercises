/*  2 - Cree un programa usando FreeRtos que cumpla con las siguientes consignas:

Ejecutar la tarea Tarea1.
La Tarea1 debe leer el valor de la entrada GPIO_2 cada 500 ms,
indicando su estado por puerto serie. En caso de estar activa, crear la Tarea2.
La Tarea2 debe cambiar el estado del led amarillo, indicarlo por puerto serie y terminar.
  */

  /*

  LED_1 = amarillo
  LED_2 = rojo
  LED_3 = verde

  */
 /*==================[inclusions]=============================================*/
#include "sapi.h"
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "assert.h"



/*==================[external functions definition]==========================*/


int main(void)
{
  Board_Init();

  for(;;){
    Board_LED_Set(LED_1, Board_GPIO_GetStatus(BOARD_GPIO_1));
    //printf("Estado del LED_1 con Board_LED_GetStatus:%d\r\n", Board_LED_GetStatus(LED_1));
    //printf("Estado del LED_1 con gpioRead:%d\r\n", gpioRead(LED_1));
    //printf("Estado del LED_1 con Board_TEC_GetStatus:%d\r\n", Board_TEC_GetStatus(LED_1));
    printf("Estado del LED_1 con LED_1:%d\r\n",Board_LED_Test(LED_1));
  }
}

/*==================[end of file]============================================*/
