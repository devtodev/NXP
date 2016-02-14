#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "CuentaVueltas.h"
#include "Configuracion/configuracion_control.h"

extern configuracionSistema_t configuracionSistema;
extern xQueueHandle colaVueltas;

/*
 * QuinoxOO
 */

#define TIMEOUT_ESPERA_CUENTA_VUELTA	2000

void CuentaVueltasInterface (void * paramCola){
	portTickType cantidadticks;
	int evento;
	int dato, km, hora;
	while(1)
	{
		evento = 10;
		cantidadticks = 123;
		if (xQueueReceive(colaVueltas, &cantidadticks, TIMEOUT_ESPERA_CUENTA_VUELTA))
		//pdTRUE if an item was successfully received from the queue,
		{
			km = configuracionSistema.rodado*METRO_SOBRE_PULGADA * 1000;
			hora = (cantidadticks/portTICK_RATE_MS);
			dato = km/hora;
		}
		else
		{
		//otherwise pdFALSE
			dato = 0;
		}
		ponerEnColaEventos(evento,dato);
	}

}
