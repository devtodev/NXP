/*
 * evento.h
 *
 *  Created on: 11/05/2012
 *      Author: alejandro
 */

#ifndef EVENTOS_H_
#define EVENTOS_H_

#include "FrameworkEventos.h"

Evento_t	EsperarEvento (xQueueHandle colaEventos);
void 		TareaDespachadoraEventos ( void * colaEventos );

#endif /* EVENTO_H_ */
