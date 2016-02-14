/*
 * Globales.c
 *
 *  Created on: 29/07/2014
 *      Author: alejandro
 */

#include "globales.h"

UART consolaDebug;

void UARTInitDEBUG()
{
	UARTInit(&consolaDebug, UART_3, 9600, 8, 'n', 1);
}


res_t 	UARTputsDEBUG	(const char * s)
{
	static const char msg[] = "DEBUG: ";
#ifdef DEGUB_ACTIVO
	UARTputs(&consolaDebug, msg, UART_PUTS_BLOQUEANTE);
	UARTputs(&consolaDebug, s, UART_PUTS_BLOQUEANTE);
#endif
	return CAPI_EXITO;
}


