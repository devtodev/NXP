/*
 * modulos.h
 *
 *  Created on: 11/05/2012
 *      Author: alejandro
 */

#ifndef MODULOS_H_
#define MODULOS_H_

#include "FreeRTOS.h"
#include "queue.h"

typedef struct Modulo_t Modulo_t;
typedef struct Evento_t Evento_t;
typedef struct EventoDriver_t EventoDriver_t;
typedef struct DatosDriver_t DatosDriver_t;

typedef void (*fsm_ptr) (Evento_t *);

struct Modulo_t {
	fsm_ptr	manejadorEventos;
	int		timeout_tick;
	int		prioridad;
	int		medicionesTomadas;
	int		medicionesObjetivo;
	int 	acumulado;
	int 	periodo;
};

struct Evento_t {
	Modulo_t *	receptor;
	int			signal;
	int			valor;
};

struct EventoDriver_t {
	int 		codigo;
	int			dato;
};

struct DatosDriver_t {
	int 		codigo;
	int			dato1;
	int			dato2;
	int			dato3;
};

Modulo_t * RegistrarModulo ( fsm_ptr manejadorEventos, int prioridad);
void 	DespacharEvento	( Evento_t * evn );

extern xQueueHandle colaEventosPrioridadBaja;
extern xQueueHandle colaEventosPrioridadMedia;
extern xQueueHandle colaEventosPrioridadAlta;
extern xQueueHandle colaEventosDrivers;
extern xQueueHandle colaMensajesUsuarios;

#endif /* MODULOS_H_ */
