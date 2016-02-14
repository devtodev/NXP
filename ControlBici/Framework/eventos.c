/*
 * eventos.c
 *
 *  Created on: 15/06/2012
 *      Author: alejandro
 */

#include "FreeRTOS.h"
#include "queue.h"

#include "FrameworkEventos.h"
#include "MaquinaEstado/maquinaEstadoSEMLibB.h"

static xQueueHandle getColaEventos (int prioridad);
static fsm_ptr 		getManejadorEventos (Evento_t * evento);

void TareaDespachadoraEventos (void * paramColaEventos){
	/* Manejo de eventos de baja prioridad
	 * Esta siempre bloqueada salvo que tenga un evento que manejar.
	 * En cuanto hay un evento, lo despacho a la FSM correspondiente SIN BLOQUEAR */
	EventoDriver_t evn;

	xQueueHandle colaEventos = (xQueueHandle) paramColaEventos;

	for(;;){

		xQueueReceive(colaEventos, &evn, portMAX_DELAY);

		switch (evn.codigo)
		{
			case 0: maquinaEstadoVSDeduct(nuevaMedicionInclinacion, evn.dato);break;
			case 1: maquinaEstadoVSDeduct(shockDetectado, evn.dato);break;
			case 3: notificarModSaludTimeout();break;
			case 10: maquinaEstadoVSDeduct(nuevaMedicionVelocidad, evn.dato);break;
			case 20: maquinaEstadoVSDeduct(ropturaCadena);break;
			case 30: maquinaEstadoVSDeduct(nuevaMedicionPulsaciones, evn.dato);break;
			case 40: maquinaEstadoVSDeduct(activacionAlarma);break;
			case 50: maquinaEstadoVSDeduct(activacionAlarma);break;
			case 51: maquinaEstadoVSDeduct(desactivacionAlarma);break;
			case 52: maquinaEstadoVSDeduct(empezarConfiguracion);break;
			case 53: maquinaEstadoVSDeduct(terminarConfiguracion);break;
			case 54: maquinaEstadoVSDeduct(configurarValorRodado, evn.dato);break;
			case 55: maquinaEstadoVSDeduct(configurarVelocidadMaxima, evn.dato);break;
			case 56: maquinaEstadoVSDeduct(configurarInclinacionMaxima, evn.dato);break;
			case 57: maquinaEstadoVSDeduct(configurarPulsacionesMaxima, evn.dato);break;

		}



		//evn = EsperarEvento(colaEventos);


		//DespacharEvento(&evn);
	}
}

Evento_t EsperarEvento (xQueueHandle colaEventos)
{
	Evento_t evn;
	xQueueReceive(colaEventos, &evn, portMAX_DELAY);
	return evn;
}

void EncolarEvento (Modulo_t * receptor, Signal_t senial, int valor)
{
	xQueueHandle colaEventos = getColaEventos(receptor->prioridad);
	Evento_t evn;
	evn.receptor = receptor;
	evn.signal = senial;
	evn.valor = valor;

	xQueueSend(colaEventos, &evn, 0);
	return;
}

portBASE_TYPE EncolarEventoFromISR (Modulo_t * receptor, Signal_t senial, int valor)
{
	//xQueueHandle colaEventos = getColaEventos(receptor->prioridad);
	portBASE_TYPE cambiarCtx = pdFALSE;
	/*Evento_t evn;
	evn.receptor = receptor;
	evn.signal = senial;
	evn.valor = valor;
*/

	EventoDriver_t msg;

	msg.codigo = 3; //timeoutSalud
	msg.dato = 0;

	xQueueSendFromISR(colaEventosDrivers, &msg, &cambiarCtx);

	//xQueueSendFromISR(colaEventos, &evn, &cambiarCtx);
	return cambiarCtx;
}

static xQueueHandle getColaEventos(int prioridad)
{
	xQueueHandle colaEventos;
	switch (prioridad){
		case PRIORIDAD_BAJA:
			colaEventos = colaEventosPrioridadBaja;
			break;
		case PRIORIDAD_MEDIA:
			colaEventos = colaEventosPrioridadMedia;
			break;
		case PRIORIDAD_ALTA:
			colaEventos = colaEventosPrioridadAlta;
			break;
	}
}

void DespacharEvento(Evento_t *evento)
{
	fsm_ptr manejadorEventos = getManejadorEventos(evento);
	manejadorEventos(evento); //Al receptor del evento le paso el evento
}

static fsm_ptr getManejadorEventos (Evento_t * evento)
{
	return (evento->receptor)->manejadorEventos;
}
