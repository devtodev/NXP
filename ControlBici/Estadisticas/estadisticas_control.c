/*
 * estadisticas_control.c
 *
 *  Created on: 26/07/2014
 *      Author: alejandro
 */
/*
 * estadisticas_control.c
 *
 *  Created on: 26/07/2014
 *      Author: alejandro
 */

#include "FrameworkEventos.h"
#include "definiciones.h"
#include "baseboard.h"

#include "UART.h"
#include "lpc_176X_PinNames.h"
extern UART consola;

typedef enum EstadosEstadisticasControlEnum {
	sESTADISTICAS_CONTROL_IDLE		 = 0,
	sESTADISTICAS_CONTROL_CONTROLANDO,
	sESTADISTICAS_CONTROL_EMERGENCIA
} EstadosEstadisticasControlEnum_t;

static int hardwareEstadisticasControlInicializado = NO;
static int estado = sESTADISTICAS_CONTROL_IDLE;
static Modulo_t * mod;
static const char msg[] = "Control Estadisticas:";

/*PWMTimer FrecuenciaPWMEstadisticasControl;
PWMOut ControlEstadisticas;*/

void ModuloEstadisticasControlInit(Modulo_t * modulo){
	if(!hardwareEstadisticasControlInicializado){

	}
	estado = sESTADISTICAS_CONTROL_IDLE;
}

void ManejadorEventosControlEstadisticas (Evento_t *evn){
	char buf[10];
	switch(estado){
//-----------------------------------------------------------------------------
	case sESTADISTICAS_CONTROL_IDLE:
		switch(evn->signal)
		{
			case SIG_MODULO_INICIAR:
				mod = (Modulo_t *)evn->valor;
				ModuloEstadisticasControlInit(mod);
				break;

			default: //Ignoro el resto de las señales
				break;
		}
		break;
//-----------------------------------------------------------------------------
	case sESTADISTICAS_CONTROL_CONTROLANDO:
		switch(evn->signal)
		{
			/*case SIG_ESTADISTICAS_VALOR:
				PWMOutPonerCuentaTon(&ControlEstadisticas, evn->valor << 3);
				sprintf(buf," %d\r\n",evn->valor << 3);
				UARTputs(&consola, msg, UART_PUTS_INTERRUPCIONES);
				UARTputs(&consola, buf, UART_PUTS_INTERRUPCIONES);
				break;

			case SIG_EMERGENCIA_SI:
				estado = sESTADISTICAS_CONTROL_EMERGENCIA;
				break;
*/
			default: //Ignoro el resto de las señales
				break;
		}
		break;
//-----------------------------------------------------------------------------
	case sESTADISTICAS_CONTROL_EMERGENCIA:
		switch(evn->signal){
			/*case SIG_EMERGENCIA_NO:
				estado = sESTADISTICAS_CONTROL_CONTROLANDO;
				break;
*/
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
