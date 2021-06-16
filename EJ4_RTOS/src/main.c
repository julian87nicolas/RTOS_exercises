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

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

#define TAM_PILA 512

const char *task1 = "Tarea 1 en funcionamiento\r\n";
const char *task2 = "Tarea 2 en funcionamiento\r\n";

TickType_t xLastWakeTime;

static void vTarea(void *pvParameters){

  TickType_t xLastWakeTime;
  UBaseType_t prioridad;
  prioridad = uxTaskPriorityGet(NULL);
  xLastWakeTime = xTaskGetTickCount();

   for ( ;; ){
     printf((void*)pvParameters);
     printf("Prioridad: %d\r\n", prioridad);
     vTaskDelayUntil(&xLastWakeTime, 500 / portTICK_RATE_MS );
   }
}

void vApplicationIdleHook( void ){

    if( xLastWakeTime + ( 300 / portTICK_RATE_MS ) == xTaskGetTickCount()){
      xLastWakeTime = xTaskGetTickCount();
      printf("\r\n\r\nIDLE Hook en funcionamiento");
      Board_LED_Toggle(LED_BLUE);
      printf("\r\nEstado de LED cambiado a: %d\r\n\r\n", Board_LED_Test(LED_BLUE));
    }

}


int main(void){

  xTaskCreate(vTarea, (const char *)"Tarea1", TAM_PILA, (void*) task1, tskIDLE_PRIORITY+1, NULL );
  xTaskCreate(vTarea, (const char *)"Tarea2", TAM_PILA, (void*) task2, tskIDLE_PRIORITY+2, NULL );

  vTaskStartScheduler();

  for( ;; ){

     }
     return 0;
}

/*
  La tarea idle Hook no puede detenerse con delay, se ejecuta continuamente mientras no hay otra ninguna tarea en ejecucion,
  por eso para que imprima cada 300ms se uso el if que se ve en el codigo.

  Si la tarea1 fuera continua nunca se llegaria a tener tiempo ocioso entonces vApplicationIdleHook nunca se ejecutaría.

*/

/*----------------------------------------------------------------------------*/
