/*
 * broadcast.c
 *
 *  Created on: 29/11/2011
 *      Author: alejandro
 */

#include "FrameworkEventos.h"
#include "definiciones.h"
#include "baseboard.h"

typedef enum estadosBroadcastEnum {
	sBROADCAST_IDLE		 = 0,
	sBROADCAST_NORMAL
} EstadosBroadcast_t;

#include "UART.h"
extern UART consola;
static int estadoBroadcast = sBROADCAST_IDLE;
const char pulsadorApretado[] = "Pulsador Apretado: ";
const char pulsadorLiberado[] = "Pulsador Liberado: ";

void ReenviarEvento (Modulo_t * modulo, Evento_t * evn)
{
	EncolarEvento(modulo, evn->signal, evn->valor);
}

void ManejadorEventosBroadcast (Evento_t * evn){
	char buf[100];
	switch(estadoBroadcast){
//-----------------------------------------------------------------------------
	case sBROADCAST_IDLE:
		switch(evn->signal){
		case SIG_MODULO_INICIAR:
			estadoBroadcast = sBROADCAST_NORMAL;
			break;
		default:
			break;
		}
		break;
//-----------------------------------------------------------------------------
	case sBROADCAST_NORMAL:
		/*switch(evn->signal){

		case SIG_LUZ_VALOR:
			EncolarEvento(ModuloLuzControl, evn->signal, evn->valor);
			break;

		case SIG_GAS_VALOR:
			EncolarEvento(ModuloGasControl, evn->signal, evn->valor);
			break;

		case SIG_EMERGENCIA_SI:
		case SIG_EMERGENCIA_NO:
			EncolarEvento(ModuloGasControl, 	evn->signal, evn->valor);
			EncolarEvento(ModuloLuzControl, 	evn->signal, evn->valor);
			EncolarEvento(ModuloInformeEstado,	evn->signal, evn->valor);
			break;

		case SIG_PULSADOR_APRETADO:
			sprintf(buf,"%d\r\n",evn->valor);
			UARTputs(&consola, pulsadorApretado, UART_PUTS_INTERRUPCIONES);
			UARTputs(&consola, buf, UART_PUTS_INTERRUPCIONES);
			ReenviarEvento(ModuloPuertaControl, evn);
			break;

		case SIG_PULSADOR_LIBERADO:
			sprintf(buf,"%d\r\n",evn->valor);
			UARTputs(&consola, pulsadorLiberado, UART_PUTS_INTERRUPCIONES);
			UARTputs(&consola, buf, UART_PUTS_INTERRUPCIONES);
			ReenviarEvento(ModuloPuertaControl, evn);
			break;

		default:
			break;
		}*/
		break;
//-----------------------------------------------------------------------------
	default:
		break;
	}
}
