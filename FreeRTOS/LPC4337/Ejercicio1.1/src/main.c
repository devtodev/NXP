/*  TP 1.1
 *  CURSO RTOS
 *  Activar un durante 500 ms cada 1 seg
 *  by cmiguens
 * */
#include <board.h>
#include <board_api.h>
#include <chip.h>
#include <FreeRTOS.h>
#include <lpc_types.h>
#include <task.h>
#include "main.h"

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
	while (1) {
			Board_LED_Toggle(LED3);
			vTaskDelay(500 / portTICK_RATE_MS);
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
