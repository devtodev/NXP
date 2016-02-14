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
		VALIDAR,
		OPRIMIDO
};

GPIO led;
GPIO pulsador;
portTickType contadorTiempoOprimido = -1;
volatile portTickType tiempoOprimido;
xSemaphoreHandle sem;
xQueueHandle cola;

static void setupHardware(void)
{
	GPIO_Init(&led, SALIDA, ALTO, GPIO__0_22);
	GPIO_Init(&pulsador, ENTRADA, BAJO, GPIO__0_18);
}

void taskLedPeriodic(void *pvParameters)
{

	while(1)
	{
		xSemaphoreTake(sem, portMAX_DELAY);

		portTickType ticks = xTaskGetTickCount();

		Activar(&led);
		vTaskDelayUntil(&ticks, 500/portTICK_RATE_MS);
		Pasivar(&led);
		vTaskDelayUntil(&ticks, 500/portTICK_RATE_MS);

		xSemaphoreGive(sem);
	}
}


void taskPulsador(void * pvParameters)
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
					tiempoOprimido = contadorTiempoOprimido;
					xQueueSend(*  cola, tiempoOprimido, portMAX_DELAY);
					state = NO_OPRIMIDO;
				}
				break;
			default:
				break;
		}
	}
}

void taskLedTimer(void *pvParameters)
{
	xQueueHandle *cola= (xQueueHandle*) pvParameters;
	int time=0;
	while(1)
	{
		xSemaphoreTake(cola, portMAX_DELAY);
		xQueueReceive(*cola, &time, portMAX_DELAY);

		portTickType ticks = xTaskGetTickCount();

		Activar(&led);
		vTaskDelayUntil(&ticks, time/portTICK_RATE_MS);
		Pasivar(&led);
		vTaskDelayUntil(&ticks, time/portTICK_RATE_MS);

		xSemaphoreGive(sem);
	}
}

int main(void)
{
	//Incialización del Hardware
	setupHardware();

	//Trace del RTOS
	//traceSTART();

	//Creación del semáforo
	sem = xSemaphoreCreateMutex();
	cola= xQueueCreate(3,sizeof(portTickType));

	//Creación de las tareas
	xTaskCreate(taskPulsador,
			(const signed char * const)"taskPulsador",
			configMINIMAL_STACK_SIZE,
			&sem,
			tskIDLE_PRIORITY+1,
			NULL);

	xTaskCreate(taskLedPeriodic,
			(const signed char * const)"taskLed",
			configMINIMAL_STACK_SIZE,
			&sem,
			tskIDLE_PRIORITY+1,
			NULL);

	xTaskCreate(taskLedTimer,
			(const signed char * const)"taskLed",
			configMINIMAL_STACK_SIZE,
			&sem,
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



