/*
 * driver.c
 *
 *  Created on: 27/07/2014
 *      Author: alejandro
 */

#include "modulos.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

extern xQueueHandle colaEventosDrivers;
extern xQueueHandle colaMensajesUsuarios;

void ponerEnColaDatos(int evento, int dato1, int dato2, int dato3)
{
	DatosDriver_t dato;

	dato.codigo = evento;
	dato.dato1 = dato1;
	dato.dato2 = dato2;
	dato.dato3 = dato3;

	xQueueSend(colaMensajesUsuarios, &dato, portMAX_DELAY);
}

void ponerEnColaEventos(int evento, int dato)
{
	EventoDriver_t msg;

	msg.codigo = evento;
	msg.dato = dato;

	xQueueSend(colaEventosDrivers, &msg, portMAX_DELAY);
//	vTaskDelay(1000/portTICK_RATE_MS);
}
