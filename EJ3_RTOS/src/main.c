/* 3 - Cree un programa usando FreeRtos que cumpla con las siguientes consignas:

Ejecutar dos tareas, Tarea1 y Tarea2.
*La Tarea1, de mayor prioridad, debe ejecutar una espera activa (busy-waiting)
indicando a través del puerto serie el valor de las entradas GPIO_0 a GPIO_3
en formato binario (nibble).
*Periódicamente debe aumentar la prioridad de la Tarea2, para que esta pueda ejecutarse.
*La Tarea2 debe cambiar el estado del led verde, indicarlo por puerto serie y
disminuir su propia prioridad para detener su ejecución.
  */

  /*

  LED_1 = amarillo
  LED_2 = rojo
  LED_3 = verde

  */
 /*==================[inclusions]=============================================*/

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

/*==================[macros and definitions]=================================*/

#define TAM_PILA 150

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
const char *pcTextoTarea1 = "Tarea1 is running\r\n";
const char *pcTextoTarea2 = "Tarea2 is running\r\n";

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void vTarea1(void *pvParameters){
  int state0, state1, state2, state3;
  //uint8 state0, state1, state2, state3;
  //nibble state0, state1, state2, state3;
   for ( ;; ){
     vTaskDelay(500 / portTICK_RATE_MS);
     state0 = Board_GPIO_GetStatus(BOARD_GPIO_0);
     state1 = Board_GPIO_GetStatus(BOARD_GPIO_1);
     state2 = Board_GPIO_GetStatus(BOARD_GPIO_2);
     state3 = Board_GPIO_GetStatus(BOARD_GPIO_3);
     printf("\r\nEstado de la entrada GPIO_0 GPIO_1 GPIO_2 GPIO_3:\r\n");
     printf("\r\n%d, %d, %d, %d", state0, state1, state2, state3);
     uxTaskPriority(tarea2);
     }
}

static void vTarea2( void *pvParameters){
    Board_LED_Toggle(LED_3);  //Verde
    printf("Estado de LED amarillo cambiado a: %d\r\n", gpioRead(LED_3) );
    vTaskPrioritySet(tarea2, tskIDLE_PRIORITY+1);

}
/*==================[external functions definition]==========================*/

int main(void)
{
  TaskHandle_t *tarea2;
  Board_Init();
  xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, (void*)pcTextoTarea1, tskIDLE_PRIORITY+2, NULL );
  xTaskCreate(vTarea2, (const char *)"Tarea1", TAM_PILA, (void*)pcTextoTarea1, tskIDLE_PRIORITY+1, tarea2 );

	vTaskStartScheduler(); /* y por último se arranca el planificador . */
    //Nunca llegara a ese lazo  .... espero
     for( ;; );
     return 0;
}

/*==================[end of file]============================================*/
