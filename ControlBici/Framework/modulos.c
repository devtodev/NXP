/*
 * modulos.c
 *
 *  Created on: 11/05/2012
 *      Author: alejandro
 */

#include "FreeRTOS.h"
#include "queue.h"

#include "definiciones.h"
#include "FrameworkEventos.h"

#define MAX_MODULOS 20
Modulo_t modulos[MAX_MODULOS];
Modulo_t * pModulo = &modulos[0];
int ultimoModulo = 0;

xQueueHandle colaEventosPrioridadBaja;
xQueueHandle colaEventosPrioridadMedia;
xQueueHandle colaEventosPrioridadAlta;
xQueueHandle colaEventosDrivers;
xQueueHandle colaMensajesUsuarios;

Modulo_t * RegistrarModulo (fsm_ptr manejadorEventos, int prioridad)
{
	if(ultimoModulo >= MAX_MODULOS)
		return;

	pModulo->manejadorEventos	= manejadorEventos;
	pModulo->timeout_tick		= TIMER_DISABLED;
	pModulo->prioridad 			= prioridad;

	ultimoModulo++;
	return pModulo++;
}

void IniciarTodosLosModulos ( void )
{
    int modulo;
    Evento_t evn;
    for (modulo = 0; modulo < ultimoModulo; ++modulo) {
    	//modulos[modulo].estado = 0;
    	evn.signal 		= SIG_MODULO_INICIAR;
    	evn.receptor 	= &modulos[modulo];
    	evn.valor 		= (int)evn.receptor;
    	DespacharEvento(&evn);
    }
}

int PromediarMediciones(Modulo_t * mod, int medicion, int* promedio)
{
	int promedio_listo;

	mod->acumulado += medicion;

	if(++mod->medicionesTomadas >= mod->medicionesObjetivo){
		*promedio 				= mod->acumulado / mod->medicionesTomadas;
		promedio_listo 			= SI;
		mod->acumulado 			= 0;
		mod->medicionesTomadas	= 0;
	} else {
		promedio_listo = NO;
	}

	return promedio_listo;
}

