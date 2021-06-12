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
TaskHandle_t idTarea1, idTarea2;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/


static void vTarea2( void *pvParameters){ //La Tarea2 se declara antes para que no haya error en la compilacion.
  UBaseType_t uxPriority2;
  uxPriority2 = uxTaskPriorityGet( NULL );   //Almacena la prioridad de la tarea actual en la variable uxPriority2
  for(;;){
  //Board_LED_Set(LED_1, 1);
    Board_LED_Toggle(LED_1);
    printf("Estado de LED amarillo: %b\r\n", gpioRead(LED_1));  //Lo muestra en puerto serie
    vTaskDelay(10/portTICK_RATE_MS);
    vTaskPrioritySet( NULL, uxPriority2-2 );     //Disminuye la prioridad de la tarea actual para que en el proximo tick se ejecute la tarea1
    //TaskEndTrace();
    //vTaskDelete(vTarea2); //Delay para permitir activar o descativar individualmente el led
  }
}


static void vTarea1(void *pvParameters){
  bool status, t = 0;
  UBaseType_t uxPriority1;
  uxPriority1 = uxTaskPriorityGet( NULL );
  for ( ;; ){
     vTaskDelay(500 / portTICK_RATE_MS);
     status = Board_GPIO_GetStatus(BOARD_GPIO_2);           //Lee la entrada GPIO_2
     printf("Estado de la entrada GPIO_2: %d\r\n", status); //La imprime en puerto serie
     if (status){
       if(t==0){
         t=1;
         xTaskCreate(vTarea2, (const char *)"Tarea2", TAM_PILA, (void*)pcTextoTarea2, uxPriority1 + 1, &idTarea2 );  //Arranca la tarea con prioridad mayor a tarea1 asi aranca de inmediato
        }
        else{
          vTaskPrioritySet( &idTarea2 ,  uxPriority1+1 );
        }
      }
    }
}



/*==================[external functions definition]==========================*/


int main(void)
{
  Board_Init();

  xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, (void*)pcTextoTarea1, tskIDLE_PRIORITY+2, &idTarea1 ); //Arranca la tarea dos con prioridad 2 + la mínima

	vTaskStartScheduler(); //Arranca el planificador

  for( ;; );
     return 0;
}

/*==================[end of file]============================================*/
