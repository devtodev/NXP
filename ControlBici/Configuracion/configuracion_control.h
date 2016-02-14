/*
 * configuracion_control.h
 *
 *  Created on: 26/07/2014
 *      Author: alejandro
 */

#ifndef CONFIGURACION_CONTROL_H_
#define CONFIGURACION_CONTROL_H_

#include "modulos.h"

#define RODADO_DEFAULT			20
#define VEL_MAX_DEFAULT			30
#define INCLIN_MAX_DEFAULT		15
#define PULSAC_MAX_DEFAULT		150


typedef struct
{
	int rodado;
	int inclinacionMaxima;
	int velocdiadMaxima;
	int pulsacionesMaxima;
}  configuracionSistema_t;

void ManejadorEventosConfiguracion (Evento_t *evn);



#endif /* CONFIGURACION_CONTROL_H_ */
