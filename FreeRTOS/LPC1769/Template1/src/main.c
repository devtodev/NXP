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

static void setupHardware(void)
{
	GPIO_Init(&ledRojo, SALIDA, ALTO, GPIO__0_22);
}

void taskLed(void *pvParameters)
{
	long time = 500;

	while(1)
	{
		Activar(&ledRojo);

		vTaskDelay(time);

		Pasivar(&ledRojo);

		vTaskDelay(time);

	}
}


int main(void)
{
	//Incialización del Hardware
	setupHardware();
	//Trace del RTOS
	//traceSTART();

	xTaskCreate(taskLed,
			(const signed char * const)"taskLed",
			configMINIMAL_STACK_SIZE,
			NULL,
			tskIDLE_PRIORITY+1,
			NULL);

	//Inicio el Scheduler
	vTaskStartScheduler();

	while(1);
}

void vApplicationTickHook ( void )
{
}

void vApplicationIdleHook ( void )
{
	__ASM volatile ("wfi");
}


