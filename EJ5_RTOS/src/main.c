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

const char *pcTextoTarea1 = "Tarea1 is running\r\n";
const char *pcTextoTarea2 = "Tarea2 is running\r\n";


QueueHandle_t cola_msj;


static void vTarea1(void *pvParameters){
  int tiempo, prendio;
  BaseType_t Escr;
  prendio = *(int*)pvParameters;

  tiempo = prendio / portTICK_RATE_MS;

   for ( ;; ){

    Escr = xQueueSend(cola_msj, &tiempo, 150 / portTICK_RATE_MS);
    vTaskDelay(100 / portTICK_RATE_MS);

   }
}


static void vTarea3 (void *pvParameters){

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
    vTaskDelay( 500 / portTICK_RATE_MS );

  }
}

int main(void)
{
  int prendio1 = 900;
  int prendio2 = 250;

  cola_msj = xQueueCreate(TAM_COLA, TAM_MSJ);

	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, (void*)prendio1, tskIDLE_PRIORITY+1, NULL );
  xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, (void*)prendio2, tskIDLE_PRIORITY+1, NULL );
  xTaskCreate(vTarea3, (const char *)"Tarea2", TAM_PILA, (void*)pcTextoTarea2, tskIDLE_PRIORITY+3, NULL );

	vTaskStartScheduler();

     for( ;; );
     return 0;
}
