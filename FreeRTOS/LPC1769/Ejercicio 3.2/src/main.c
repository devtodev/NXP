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

enum debounceStates {
		NO_OPRIMIDO,
		ANTIRREBOTE,
		OPRIMIDO
};

GPIO ledRojo;
GPIO ledVerde;
GPIO pulsador;
long contadorTiempoOprimido = -1;
xQueueHandle queue;

static void setupHardware(void)
{
	GPIO_Init(&ledRojo, SALIDA, ALTO, GPIO__0_22);
	GPIO_Init(&ledVerde, SALIDA, ALTO, GPIO__1_10);
	GPIO_Init(&pulsador, ENTRADA, BAJO, EABASE_SW3_REV_A);
}

void taskLed(void *pvParameters)
{
	xQueueHandle *cola = (xQueueHandle*)pvParameters;
	long time = 500, freq = 1000, timeoff;

	while(1)
	{
		xQueueReceive(* cola, &time, 0);

		Activar(&ledRojo);

		vTaskDelay(time);
		timeoff = (freq - time < 0)?0:freq - time;
		if (timeoff > 0)
		{
			Pasivar(&ledRojo);
			vTaskDelay(timeoff);
		}
	}
}


void taskGeneradora(void * pvParameters)
{
	uint8_t state = NO_OPRIMIDO;
	xQueueHandle * cola = (xQueueHandle*)pvParameters;

	while(1)
	{
				switch(state)
				{
					case NO_OPRIMIDO:
						if(isActivo(&pulsador))
						{
							contadorTiempoOprimido = 0;
							state = ANTIRREBOTE;
							vTaskDelay(20/portTICK_RATE_MS);
						}
						else
						{
							contadorTiempoOprimido = -1;
							vTaskDelay(100/portTICK_RATE_MS);
						}
						break;
					case ANTIRREBOTE:
						if(isActivo(&pulsador))
						{
							state = OPRIMIDO;
						}
						else
						{
							state = NO_OPRIMIDO;
						}
						break;
					case OPRIMIDO:
						if(!isActivo(&pulsador))
						{
							xQueueSend(*  cola, &contadorTiempoOprimido, portMAX_DELAY);
							state = NO_OPRIMIDO;
						}
						break;
					default:
						break;
				}

	}
}

int main(void)
{
	//Incialización del Hardware
	setupHardware();
	contadorTiempoOprimido = -1;
	//Trace del RTOS
	//traceSTART();

	//Creación del semáforo
	queue = xQueueCreate(10, sizeof(long));

	//Creación de las tareas
	xTaskCreate(taskGeneradora,
			(const signed char * const)"taskGeneradora",
			configMINIMAL_STACK_SIZE,
			&queue,
			tskIDLE_PRIORITY+1,
			NULL);

	xTaskCreate(taskLed,
			(const signed char * const)"taskLed",
			configMINIMAL_STACK_SIZE,
			&queue,
			tskIDLE_PRIORITY+1,
			NULL);

	//Inicio el Scheduler
	vTaskStartScheduler();

	while(1);
}

void vApplicationTickHook ( void )
{
	if(contadorTiempoOprimido >= 0)
		contadorTiempoOprimido++;
}

void vApplicationIdleHook ( void )
{
	__ASM volatile ("wfi");
}


