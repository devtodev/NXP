/*
 * globales.h
 *
 *  Created on: 26/07/2014
 *      Author: alejandro
 */

#ifndef GLOBALES_H_
#define GLOBALES_H_
#include "lpc_176X_PeriphNames.h"
#include "Configuracion/configuracion_control.h"
#include "FrameworkEventos.h"
#include "UART.h"

#define DEGUB_ACTIVO
extern UART consolaDebug;
void UARTInitDEBUG();
res_t 	UARTputsDEBUG(const char * s);


volatile extern configuracionSistema_t configuracionSistema;

extern Modulo_t * ModuloConfiguracion;
extern Modulo_t * ModuloEstadistico;
extern Modulo_t * ModuloControlSalud;
extern Modulo_t * ModuloControlRobo;

#endif /* GLOBALES_H_ */
