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

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "assert.h"


/*==================[macros and definitions]=================================*/

#define TAM_PILA 150

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
const char *pcTextoTarea1 = "Tarea1 is running\r\n";
const char *pcTextoTarea2 = "Tarea2 is running\r\n";

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void vTarea2( void *pvParameters){
    printf("Estado de LED amarillo: %d\r\n", gpioRead(LED_1));
    vTaskDelay(100/portTICK_RATE_MS);
    for(;;){

    }
}

static void vTarea1(void *pvParameters){
   for ( ;; ){
     vTaskDelay(500 / portTICK_RATE_MS);
     printf("Estado de la entrada GPIO_2: %d\r\n", Board_GPIO_GetStatus(BOARD_GPIO_2));

      if (Board_GPIO_GetStatus(BOARD_GPIO_2)){
        xTaskCreate(vTarea2, (const char *)"Tarea2", TAM_PILA, (void*)pcTextoTarea2, tskIDLE_PRIORITY+1, NULL );
      }
     }
}



/*==================[external functions definition]==========================*/

int main(void)
{
  Board_Init();
	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, (void*)pcTextoTarea1, tskIDLE_PRIORITY+2, NULL );

	vTaskStartScheduler(); /* y por último se arranca el planificador . */
    //Nunca llegara a ese lazo  .... espero
     for( ;; );
     return 0;
}

/*==================[end of file]============================================*/
