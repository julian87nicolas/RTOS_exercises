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

#define TAM_PILA 150

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
const char *pcTextoTarea1 = "Tarea1\r\n";
const char *pcTextoTarea2 = "Tarea2\r\n";

static void vTarea1(void *pvParameters){
  int state0, state1, state2, state3;
  UBaseType_t prioridad;
  prioridad = uxTaskPriorityGet(NULL);
   for ( ;; ){
     printf("\r\nTarea Nº%d en ejecucion\n", &pvParameters);
     printf("\r\nPrioridad de la tarea: %d", prioridad);

     vTaskDelay(500/ portTICK_RATE_MS);
   }
}

void vApplicationIdleHook(void){
  Board_LED_Toggle(LED_BLUE);
  vTaskDelay(300/ portTICK_RATE_MS);
}

/*--------------MAIN-----------------*/

int main(void){

  char t1[10], t2[10];
  t1 = "Tarea1"
  t2 = "Tarea2"
  Board_Init();


  xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, (void*)pcTextoTarea1, tskIDLE_PRIORITY+2, NULL );
  xTaskCreate(vTarea1, (const char *)"Tarea2", TAM_PILA, (void*)pcTextoTarea1, tskIDLE_PRIORITY+1, &idTarea2 );

  //VER COMO SUAR IDLE HOOK

  vTaskStartScheduler();

     for( ;; );
     return 0;
}



/*----------------------------------------------------------------------------*/
