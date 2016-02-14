/*
 * TimerService.c
 *
 *  Created on: 11/05/2012
 *      Author: alejandro
 */

#include "FreeRTOS.h"
#include "queue.h"

#include "FrameworkEventos.h"

extern portTickType ContarTicksVueltas;
extern portTickType ContarTicksSalud;

void 		vApplicationTickHook 		( void ){
	int modulo;
	Modulo_t * pModulo;
	portBASE_TYPE cambiarCtx = pdFALSE;

	ContarTicksVueltas = ContarTicksVueltas + 1;
	ContarTicksSalud = ContarTicksSalud + 1;

	for (modulo = 0; modulo < ultimoModulo; ++modulo) {
		pModulo = &modulos[modulo];
		if(pModulo->timeout_tick != TIMER_DISABLED) {
			if(--pModulo->timeout_tick == 0) {
				cambiarCtx = EncolarEventoFromISR(pModulo, SIG_TIMEOUT, 0);
				TimerDisarm(pModulo);
			}
		}
	}
	portEND_SWITCHING_ISR(cambiarCtx);
}

void 		TimerArm					( Modulo_t * modulo, unsigned int timeout ){
	portENTER_CRITICAL();
	modulo->timeout_tick = timeout;
	portEXIT_CRITICAL();
	return;
}

void 		TimerDisarm				( Modulo_t * modulo ){
	portENTER_CRITICAL();
	modulo->timeout_tick = TIMER_DISABLED;
	portEXIT_CRITICAL();
	return;
}
