/*
4 - Cree un programa usando FreeRtos que cumpla con las siguientes consignas:

Ejecutar dos tareas, Tarea1 y Tarea2 de distinta prioridad y que sean implementadas con la misma función.
Ambas tareas deben indicar por puerto serie que están en ejecución y su prioridad, luego bloquearse por 500ms.
En el tiempo ocioso (Idle) aprovechar para cambiar el estado del led azul cada 300ms e indicarlo por puerto serie. (Implementar Idle Hook)
Justifique que sucede con los cambios de estado del led en caso que la tarea Tarea1 pase a ejecutarse de manera contínua.


*/
  /*

  LED_1 = amarillo
  LED_2 = rojo
  LED_3 = verde

  LED_BLUE
  LED_RED


  */
 /*==================[inclusions]=============================================*/

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

/*==================[macros and definitions]=================================*/

#define TAM_PILA 512

const char *pcTextoTarea1 = "\r\nTarea1 en funcionamiento";
const char *pcTextoTarea2 = "\r\nTarea2 en funcionamiento";
TickType_t xLastWakeTime;

static void vTarea(void *pvParameters){
  TickType_t xLastWakeTime, delay;

  int state0, state1, state2, state3;
  UBaseType_t prioridad;
  prioridad = uxTaskPriorityGet(NULL);
  xLastWakeTime = xTaskGetTickCount();

   for ( ;; ){
     //vTaskDelayUntil(&xLastWakeTime, 500 / portTICK_RATE_MS );
     printf((void*)pvParameters);
     printf("\r\nPrioridad: %d\r\n", prioridad);
     vTaskDelay(500 / portTICK_RATE_MS);
   }
}

void vApplicationIdleHook( void ){

    if( xLastWakeTime + 300 == xTaskGetTickCount()){
      xLastWakeTime = xTaskGetTickCount();
      printf("\r\nIdle Hook en funcionamiento");
      Board_LED_Toggle(LED_BLUE);
    }

}

/*--------------MAIN-----------------*/

int main(void){

  //Board_Init();


  xTaskCreate(vTarea, (const char *)"Tarea1", TAM_PILA, (void*)pcTextoTarea1, tskIDLE_PRIORITY+1, NULL );
  xTaskCreate(vTarea, (const char *)"Tarea2", TAM_PILA, (void*)pcTextoTarea2, tskIDLE_PRIORITY+2, NULL );

  //VER COMO SUAR IDLE HOOK

  vTaskStartScheduler();

  for( ;; ){

     }
     return 0;
}

/*
  La tarea idle Hook no puede detenerse con delay, se ejecuta continuamente mientras no hay otra ninguna tarea en ejecucion,
  por eso para que imprima cada 300ms se uso el if que se ve en el codigo.

*/

/*----------------------------------------------------------------------------*/
