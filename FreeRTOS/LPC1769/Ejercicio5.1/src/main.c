/*
===============================================================================
 Name        : main.c
 Author      : Carlos Miguens
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

// TODO: insert other include files here
/*Includes del FreeRTOS*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"

/*Includes de la C-API*/
#include "GPIO.h"
#include "lpc_176X_PinNames.h"
#include "lpc_176X_PeriphNames.h"


GPIO led;
GPIO pulsador;
long contarTicks = -1;
xQueueHandle cola;

void EINT3_IRQHandler(void)
{
	static signed portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;

	if(LPC_GPIOINT->IO0IntStatF & (1<<4))
	{
		contarTicks = 0;
	} else
	if (LPC_GPIOINT->IO0IntStatR & (1<<4)) {
		contarTicks = contarTicks / portTICK_RATE_MS;
		xQueueSendFromISR(cola,  &contarTicks, &xHigherPriorityTaskWoken);
		contarTicks = -1;
	}
	LPC_GPIOINT->IO0IntClr = 1<<4;

	// Si la tarea asociada tiene mayor prioridad que la que
	//se esta ejecutando
   if(xHigherPriorityTaskWoken == pdTRUE)
	   // se realiza un cambio de contexto manualmente
	   //(no se pasa por el scheduler).
	   vPortYieldFromISR ();
}

static void setupHardware(void)
{
	GPIO_Init(&led, SALIDA, ALTO, GPIO__0_22);

	/* Pulsador en P0.4, lo usamos por interrupcion */
	GPIO_Init(&pulsador, ENTRADA, BAJO, EABASE_SW3_REV_A);

	/* Configuro interrupcion de P0.4 */
	LPC_GPIOINT->IO0IntEnF |= 1 << 4;
	LPC_GPIOINT->IO0IntEnR |= 1 << 4;

	NVIC_EnableIRQ(EINT3_IRQn);

}

void taskLED(void * pvParameters)
{
	(void *)pvParameters;
	long tiempo = 0;
	while(1)
	{
		xQueueReceive(cola, &tiempo, portMAX_DELAY);

		Activar(&led);
		vTaskDelay(tiempo/portTICK_RATE_MS);
		Pasivar(&led);
	}
}

int main(void)
{
	
	// TODO: insert code here

	//Incialización del Hardware
	setupHardware();

	//Trace del RTOS
	//traceSTART();

	//Creacion del semaforo
	cola = xQueueCreate(10, sizeof(long));

	//Creación de las tareas
	xTaskCreate(	taskLED,
					(const signed char * const)"taskLED",
					configMINIMAL_STACK_SIZE,
					NULL,
					tskIDLE_PRIORITY+1,
					NULL );

	//Inicio el Scheduler
	vTaskStartScheduler();

	while(1);
}

void vApplicationTickHook ( void )
{
	contarTicks = (contarTicks >= 0)?contarTicks+1:-1;
}

void vApplicationIdleHook ( void )
{
	__ASM volatile ("wfi");
}



