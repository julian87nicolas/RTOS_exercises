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
#define TAM_COLA 2
#define TAM_MSJ 16

const char *pcTextoTarea1 = "Tarea1 is running\r\n";
const char *pcTextoTarea2 = "Tarea2 is running\r\n";


QueueHandle_t cola_msj;


static void vTarea1(void *pvParameters){
  int tiempo;
  BaseType_t Escr;

  printf("Tarea1, primer inicio\r\n");
  tiempo = 1000 / portTICK_RATE_MS;

   for ( ;; ){

    Escr = xQueueSend(cola_msj, &tiempo, 150 / portTICK_RATE_MS);
    if(Escr) printf("\r\nESCRITURA 1 EXTIOSA\r\n");

   }
}

static void vTarea2( void *pvParameters){
  int tiempo;
  BaseType_t Escr;
  printf("Tarea2, primer inicio\r\n");
  tiempo = 250 / portTICK_RATE_MS;

  for ( ;; ){

    Escr = xQueueSend(cola_msj, &tiempo, 150 / portTICK_RATE_MS);
    if(Escr) printf("\r\nESCRITURA 2 EXTIOSA\r\n");

    }
}

static void vTarea3 (void *pvParameters){

  int buff;
  BaseType_t Lect;


  for(;;){
    Board_LED_Set(LED_1, 0);
    vTaskDelay( 500 / portTICK_RATE_MS );

    Lect = xQueueReceive( cola_msj, &buff, 150/portTICK_RATE_MS);

    if( Lect ){
      Board_LED_Set(LED_1, 1);
      printf("\r\n LED encendido por %d ms.\r\n", buff);
      vTaskDelay(buff);

    }
    else{
      printf("\r\n No se pudo leer la cola.");
    }
  }
}

int main(void)
{

  InitSerie();

  cola_msj = xQueueCreate(TAM_COLA, TAM_MSJ);


	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, (void*)pcTextoTarea1, tskIDLE_PRIORITY+1, NULL );
  xTaskCreate(vTarea2, (const char *)"Tarea2", TAM_PILA, (void*)pcTextoTarea2, tskIDLE_PRIORITY+1, NULL );
  xTaskCreate(vTarea3, (const char *)"Tarea2", TAM_PILA, (void*)pcTextoTarea2, tskIDLE_PRIORITY+2, NULL );

	vTaskStartScheduler();

     for( ;; );
     return 0;
}
