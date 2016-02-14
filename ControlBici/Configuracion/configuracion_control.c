/*
 * configuracion_control.c
 *
 *  Created on: 26/07/2014
 *      Author: alejandro
 */

#include "FrameworkEventos.h"
#include "definiciones.h"
#include "baseboard.h"
#include "stdio.h"

#include "UART.h"
#include "lpc_176X_PinNames.h"
#include "configuracion_control.h"


typedef enum EstadosConfiguracionControlEnum {
	sCONFIGURACION_CONTROL_IDLE		 = 0,
	sCONFIGURACION_LISTA,
	sCONFIGURACION_EN_PROGRESO

} EstadosConfiguracionControlEnum_t;



volatile configuracionSistema_t configuracionSistema;

static int estado = sCONFIGURACION_CONTROL_IDLE;
static Modulo_t * mod;
static const char msg[] = "Config:";

/*PWMTimer FrecuenciaPWMConfiguracionControl;
PWMOut ControlConfiguracion;*/

void ModuloConfiguracionControlInit(Modulo_t * modulo){
	configuracionSistema.rodado = RODADO_DEFAULT; //estos valores se podrían leer de la flash
	configuracionSistema.inclinacionMaxima = INCLIN_MAX_DEFAULT; //estos valores se podrían leer de la flash
	configuracionSistema.velocdiadMaxima = VEL_MAX_DEFAULT; //estos valores se podrían leer de la flash
	configuracionSistema.pulsacionesMaxima = PULSAC_MAX_DEFAULT; //estos valores se podrían leer de la flash


	estado = sCONFIGURACION_LISTA;
}

void ManejadorEventosConfiguracion (Evento_t *evn){
	char buf[50];
	switch(estado){
//-----------------------------------------------------------------------------
	case sCONFIGURACION_CONTROL_IDLE:
		switch(evn->signal)
		{
			case SIG_MODULO_INICIAR:
				mod = (Modulo_t *)evn->valor;
				ModuloConfiguracionControlInit(mod);
				break;

			default: //Ignoro el resto de las señales
				break;
		}
		break;
//-----------------------------------------------------------------------------
	case sCONFIGURACION_LISTA:
		switch(evn->signal)
		{
			case SIG_CONFIG_COMENZAR_CONFIG:
				estado = sCONFIGURACION_EN_PROGRESO;
				sprintf(buf," Comienzo Configuracion. \r\n");
				UARTputsDEBUG(msg);
				UARTputsDEBUG(buf);
				break;

		default: //Ignoro el resto de las señales
						break;
		}
		break;
//-----------------------------------------------------------------------------
	case sCONFIGURACION_EN_PROGRESO:
		switch(evn->signal)
		{
			case SIG_CONFIG_VELOCIDAD_MAXIMA:
				configuracionSistema.velocdiadMaxima =  evn->valor;
				sprintf(buf," nueva velocidad maxima: %d\r\n",evn->valor << 3);
				UARTputsDEBUG(msg);
				UARTputsDEBUG(buf);
				break;

			case SIG_CONFIG_INCLINACION_MAXIMA:
				configuracionSistema.inclinacionMaxima =  evn->valor;
				sprintf(buf," nueva inlinacion maxima: %d\r\n",evn->valor << 3);
				UARTputsDEBUG(msg);
				UARTputsDEBUG(buf);
			break;

			case SIG_CONFIG_PULSACIONES_MAXIMA:
				configuracionSistema.pulsacionesMaxima =  evn->valor;
				sprintf(buf," nuevas pulsaciones maxima: %d\r\n",evn->valor << 3);
				UARTputsDEBUG(msg);
				UARTputsDEBUG(buf);
			break;

			case SIG_CONFIG_RODADO:
				configuracionSistema.rodado =  evn->valor;
				sprintf(buf," nueva rodado maxima: %d\r\n",evn->valor << 3);
				UARTputsDEBUG(msg);
				UARTputsDEBUG(buf);
			break;

			case SIG_CONFIG_FINALIZAR_CONFIG:
				estado = sCONFIGURACION_LISTA;
				sprintf(buf," Fin Configuracion. \r\n");
				UARTputsDEBUG(msg);
				UARTputsDEBUG(buf);
			break;


			default: //Ignoro el resto de las señales
				break;
		}
		break;
//-----------------------------------------------------------------------------
		default:
			// Estoy en un estado invalido, tengo que reiniciar este modulo
			break;
	}
}
