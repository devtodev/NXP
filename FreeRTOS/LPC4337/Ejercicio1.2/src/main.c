/*  TP 1.2
 *  CURSO RTOS
 *  Hacer una onda cuadrada de período de 1s, con ciclos de actividad incrementandose 100ms, 200ms, 300ms...
 *  by cmiguens
 * */

#include "main.h"

#include <board_api.h>
#include <chip.h>
#include <FreeRTOS.h>
#include <lpc_types.h>
#include <stdint.h>
#include <task.h>

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
	uint32_t delayVariable = 100;
	uint32_t periodo = 1000;
	while (1) {
		ticks = xTaskGetTickCount();
		delayVariable = (delayVariable < 900)? delayVariable + 100: 100;
		Board_LED_Set(LED3, 1);
		vTaskDelayUntil(&ticks, delayVariable/portTICK_RATE_MS);
		Board_LED_Set(LED3, 0);
		vTaskDelayUntil(&ticks, (periodo-delayVariable)/portTICK_RATE_MS);
	}
}

int main(void) {
	setupHardware();
	xTaskCreate(taskBlink, "taskBlink", configMINIMAL_STACK_SIZE, 0, tskIDLE_PRIORITY+1, 0);

	vTaskStartScheduler();

	while (TRUE);

	return 0;
}

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
