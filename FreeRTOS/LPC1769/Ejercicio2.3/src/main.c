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
GPIO ledAzul;
GPIO pulsador;
portTickType contadorTiempoOprimido = -1;
volatile portTickType tiempoOprimido;
xSemaphoreHandle sem;

static void setupHardware(void)
{
	GPIO_Init(&ledRojo, SALIDA, ALTO, GPIO__0_22);
	GPIO_Init(&ledVerde, SALIDA, ALTO, EABASE_LED_ROJO);  //GPIO2_BOOT2
	GPIO_Init(&ledAzul, SALIDA, ALTO, EABASE_LED_AZUL);
	GPIO_Init(&pulsador, ENTRADA, BAJO, EABASE_SW3_REV_A);
}

void taskLed(void *pvParameters)
{
	xSemaphoreHandle * semaforo = (xSemaphoreHandle *)pvParameters;

	while(1)
	{

		if(xSemaphoreTake(*semaforo, 1000/portTICK_RATE_MS) != pdFALSE)
		{
			Activar(&ledVerde);
			vTaskDelay(100/portTICK_RATE_MS);
			Pasivar(&ledVerde);
		}
		else
		{
			Activar(&ledRojo);
			vTaskDelay(100/portTICK_RATE_MS);
			Pasivar(&ledRojo);
		}
	}
}


void taskPulsador(void * pvParameters)
{
	uint8_t state = NO_OPRIMIDO;
	xSemaphoreHandle * semaforo = (xSemaphoreHandle *)pvParameters;

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
					state = NO_OPRIMIDO;
					xSemaphoreGive(*semaforo);
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

	//Trace del RTOS
	//traceSTART();

	//Creación del semáforo
	vSemaphoreCreateBinary(sem);


	//Creación de las tareas
	xTaskCreate(taskPulsador,
			(const signed char * const)"taskPulsador",
			3*configMINIMAL_STACK_SIZE,
			&sem,
			tskIDLE_PRIORITY+1,
			NULL);

	xTaskCreate(taskLed,
			(const signed char * const)"taskLed",
			3*configMINIMAL_STACK_SIZE,
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

void vApplicationIdleHook ( void ) //Cuando Idle entra en bajo consumo
{
	__ASM volatile ("wfi");
}


