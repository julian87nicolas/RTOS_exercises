/*  Copyright 2020 - FreeRTOS Kernel V10.0.1

 * este codigo NO esta en el libro de Sistemas Empotrados en tiempo real
 * pero el objetivo es intriducir a FreeRTOS usando solo una (o dos) tarea que
 * imprime por el puerto serie, e invocando al planificador
 *
 *  - xTaskCreate()
 *  - vTaskStartScheduler()
 *  - vTaskDelay(ticks)
 *
 *  */
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
  int state;
  state = Board_GPIO_GetStatus(BOARD_GPIO_0);
   for ( ;; ){
     if(state != Board_GPIO_GetStatus(BOARD_GPIO_0)){
       printf("\r\nValor de GPIO: %d", Board_GPIO_GetStatus(BOARD_GPIO_0));
       state = Board_GPIO_GetStatus(BOARD_GPIO_0);
     }
   }
}

static void vTarea2( void *pvParameters){
  for(;;){
    Board_LED_Toggle(5); //titila "LED 3" ( verde )
    vTaskDelay( 1000 / portTICK_RATE_MS);
    //printf("Estado del led verde: %d\n", Board_LED_GetStatus(5)));
    printf("\r\nTicks configurados del reloj: %d", portTICK_RATE_MS);
  }
}
/*==================[external functions definition]==========================*/

int main(void)
{
	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, (void*)pcTextoTarea1, tskIDLE_PRIORITY+1, NULL );
	xTaskCreate(vTarea2, (const char *)"Tarea2", TAM_PILA, (void*)pcTextoTarea2, tskIDLE_PRIORITY+2, NULL );

	vTaskStartScheduler(); /* y por último se arranca el planificador . */
    //Nunca llegara a ese lazo  .... espero
     for( ;; );
     return 0;
}

/*==================[end of file]============================================*/
