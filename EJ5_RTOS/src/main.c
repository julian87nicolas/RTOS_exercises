/*  5 - Cree un programa usando FreeRtos que cumpla con las siguientes consignas:

Ejecutar las tareas Tarea1, Tarea2 y Tarea3 con los niveles de prioridad apropiados.
Las tareas Tarea1 y Tarea2 deben enviar por cola de mensaje a la Tarea3 el tiempo en milisegundos que debe estar
encendido el led amarillo e indicarlo por puerto serie.
La Tarea3 debe leer esos tiempos de la cola a medida que llegan y controlar el led en cuestión.
Siempre, el tiempo apagado del led es de 500ms. También debe indicar por puerto serie sus acciones.
Indique que pasa en caso de que el timeout de la escritura en la cola de mensajes sea de 300ms.

*/

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


#define TAM_PILA 512
#define TAM_COLA 20
#define TAM_MSJ 16


QueueHandle_t cola_msj;


static void vTareaEnvia(void *pvParameters){
  int TiempoON, LedON;
  BaseType_t Escr;
  LedON = (int)pvParameters;   //Aparece un warning acá. Cuidado

  TiempoON = LedON / portTICK_RATE_MS;

   for ( ;; ){

    Escr = xQueueSend(cola_msj, &TiempoON, 150 / portTICK_RATE_MS);
    vTaskDelay(1);  // Delay de 1 tick para asegurar el cambio de tarea.

   }
}


static void vTareaRecibe (void *pvParameters){

  int buff;
  BaseType_t Lect;


  for(;;){

    Lect = xQueueReceive( cola_msj, &buff, 150/portTICK_RATE_MS);
    if( Lect ){
      Board_LED_Set(LED_1, 1);
      printf("\r\n LED encendido por %d ms.\r\n", buff * portTICK_RATE_MS);
      vTaskDelay(buff);

    }
    else{
      printf("\r\n No se pudo leer la cola.");
    }

    Board_LED_Set(LED_1, 0);
    printf("\r\n LED apagado.\r\n");
    vTaskDelay( 500 / portTICK_RATE_MS );

  }
}


int main(void)
{
  int LedTarea1 = 900;
  int LedTarea2 = 250;

  cola_msj = xQueueCreate(TAM_COLA, TAM_MSJ);

	xTaskCreate(vTareaEnvia, (const char *)"Tarea1", TAM_PILA, (void*)LedTarea1, tskIDLE_PRIORITY+1, NULL );
  xTaskCreate(vTareaEnvia, (const char *)"Tarea1", TAM_PILA, (void*)LedTarea2, tskIDLE_PRIORITY+1, NULL );
  xTaskCreate(vTareaRecibe, (const char *)"Tarea2", TAM_PILA, NULL, tskIDLE_PRIORITY+3, NULL );

	vTaskStartScheduler();

     for( ;; );
     return 0;
}
