/*  TP 1.3
 *  CURSO RTOS
 *  Medir usando el vApplicationTickHook() el tiempo de pulsación de un botón,
 *  aplicándole al mismo antirebote. Luego destellar un led durante el tiempo medido.
 *  by cmiguens
 * */

#include "main.h"

#include <board_api.h>
#include <chip.h>
#include <FreeRTOS.h>
#include <lpc_types.h>
#include <stdint.h>
#include <task.h>

#include "../../freertos_lpc43xx/src/FreeRTOSCommonHooks.h"

#define RED  							0
#define GREEN 							1
#define BLUE 							2
#define LED1			                3
#define LED2 			                4
#define LED3			                5
#define SW1								0
#define SW2								1
#define SW3								2
#define SW4								3

enum debounceStates {
		NO_OPRIMIDO,
		ANTIRREBOTE,
		VALIDAR,
		OPRIMIDO
};
volatile portTickType tiempoOprimido;

static void setupHardware(void) {
#if defined (__USE_LPCOPEN)
#if !defined(NO_BOARD_LIB)
	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();
	// Set up and initialize all required blocks and
	// functions related to the board hardware
	Board_Init();

#endif
#endif

}

static void taskBlink(void * p) {
	portTickType ticks;
	tiempoOprimido = 100;
	uint32_t apagado = 1000;
	while (1) {
		ticks = xTaskGetTickCount();
		Board_LED_Set(LED3, 1);
		vTaskDelayUntil(&ticks, tiempoOprimido/portTICK_RATE_MS);
		Board_LED_Set(LED3, 0);
		vTaskDelay(apagado/portTICK_RATE_MS);
	}
}


void taskPulsador(void * pvParameters)
{
	uint8_t state = NO_OPRIMIDO;

	while(1)
	{
		switch(state)
		{
			case NO_OPRIMIDO:
				if(Buttons_GetStatus(SW4) == 1)
				{
					setTickCounter(0);
					state = ANTIRREBOTE;
					vTaskDelay(20/portTICK_RATE_MS);
				}
				else
				{
					vTaskDelay(100/portTICK_RATE_MS);
				}
				break;
			case ANTIRREBOTE:
				if(Buttons_GetStatus(SW4) == 1)
				{
					state = OPRIMIDO;
				}
				else
				{
					state = NO_OPRIMIDO;
				}
				break;
			case OPRIMIDO:
				if(Buttons_GetStatus(SW4) != 1)
				{
					tiempoOprimido = getTickCounter();
					state = NO_OPRIMIDO;
				}
				break;
			default:
				break;
		}
	}
}

int main(void) {
	setupHardware();
	xTaskCreate(taskBlink, "taskBlink", configMINIMAL_STACK_SIZE, 0, tskIDLE_PRIORITY+1, 0);
	xTaskCreate(taskPulsador,"taskPulsador",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+1, 0);

	vTaskStartScheduler();

	while (TRUE);

	return 0;
}
/*
void vApplicationTickHook ( void )
{
	if(contadorTiempoOprimido >= 0)
		contadorTiempoOprimido++;
}*/

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
