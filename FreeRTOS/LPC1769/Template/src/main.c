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

#define TIEMPO_DE_DIAGNOSTICO_ms 2000

GPIO led;
GPIO led2;

int tiempo_de_diagnostico;

static void setupHardware(void)
{
	GPIO_Init(&led, SALIDA, ALTO, GPIO__0_22);
	GPIO_Init(&led2, SALIDA, ALTO, GPIO__0_23);
}

void taskLed(void * pvParameters)
{
	GPIO * gpio = (GPIO *)pvParameters;

	while(1)
	{
		Activar(gpio);
		vTaskDelay(500/portTICK_RATE_MS);
		Pasivar(gpio);
		vTaskDelay(500/portTICK_RATE_MS);
	}
}

void taskPrintf(void * pvParameters)
{

	vPrintString("Comienza el diagnostico\n");
	//Loop infinito
	while(1)
	{
		//IMPORTANTE:
		//Este loop pretende simular un conjunto de funciones que
		//insumen un tiempo para realizar el diagnostico del equipo
		//Pero NO es aceptable tener al micro dentro de esta tarea
		//haciendo nada, esto es solo un ejemplo.
		if(!tiempo_de_diagnostico)
		{
			vPrintString("Termina el diagnostico\n");
			vTaskDelay(TIEMPO_DE_DIAGNOSTICO_ms/portTICK_RATE_MS);
			tiempo_de_diagnostico = TIEMPO_DE_DIAGNOSTICO_ms;
			vPrintString("Comienza el diagnostico\n");
		}

	}

}

int main(void) {
	
	// TODO: insert code here

	//Incialización del Hardware
	setupHardware();

	//Trace del RTOS
	//traceSTART();

	//Creación de las tareas
	xTaskCreate(	taskLed,
					(const signed char * const)"taskLed",
					configMINIMAL_STACK_SIZE,
					&led,
					tskIDLE_PRIORITY+2,
					NULL );

	xTaskCreate(	taskLed,
					(const signed char * const)"taskLed2",
					configMINIMAL_STACK_SIZE,
					&led2,
					tskIDLE_PRIORITY+2,
					NULL );


	xTaskCreate(	taskPrintf,
					(const signed char * const)"taskPrintf",
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
	if(tiempo_de_diagnostico)
		tiempo_de_diagnostico--;
}

void vApplicationIdleHook ( void )
{
	__ASM volatile ("wfi");
}



