/*
 * robo_control.c
 *
 *  Created on: 26/07/2014
 *      Author: alejandro
 */

#include "FrameworkEventos.h"
#include "definiciones.h"
#include "baseboard.h"

#include "UART.h"
#include "lpc_176X_PinNames.h"


typedef enum EstadosRoboControlEnum {
	sROBO_CONTROL_IDLE		 = 0,
	sROBO_CONTROL_ALARMA_DESACTIVADA,
	sROBO_CONTROL_ALARMA_ACTIVADA,
	sROBO_CONTROL_ROBO_DETECTADO
} EstadosRoboControlEnum_t;

static int estado = sROBO_CONTROL_IDLE;
static Modulo_t * mod;
static const char msg[] = "Control Robo:";

#define		VECES_CONSECUTIVAS_VELOCIDAD_DETECTADA_DEFAULT	4
#define		VECES_CONSECUTIVAS_SHOCK_DETECTADO_DEFAULT	4
#define		VECES_CONSECUTIVAS_ROPTURA_CADENA_DEFAULT	0 /* se dispara la alarma al primer evento de roptura cadena detectado*/

int vecesRestantes_VelocidadDetectada = 0;
int vecesRestantes_ShockDetectado = 0;
int vecesRestantes_RopturaCadena = 0;

void dispararAlarmaRobo()
{
//	UARTputsDEBUG(msg);
	UARTputsDEBUG(" Alarma de robo DISPARADA!!!\r\n");
	//poner en la cola de la tarea sirena un mensaje dando la orden que se dispare la alarma de robo

	//avisar en la interfaz de usuario
	ponerEnColaDatos(92, 0, 0, 0);
};

detenerAlarmaRobo()
{
//	UARTputsDEBUG(msg);
	UARTputsDEBUG(" Alarma de robo DETENIDA!!!\r\n");
	//poner en la cola de la tarea sirena un mensaje dando la orden que se detenga la alarma de robo
};


void ModuloRoboControlInit(Modulo_t * modulo){

	vecesRestantes_VelocidadDetectada = VECES_CONSECUTIVAS_VELOCIDAD_DETECTADA_DEFAULT;
	vecesRestantes_ShockDetectado = VECES_CONSECUTIVAS_SHOCK_DETECTADO_DEFAULT;
	vecesRestantes_RopturaCadena = VECES_CONSECUTIVAS_ROPTURA_CADENA_DEFAULT;


	estado = sROBO_CONTROL_ALARMA_DESACTIVADA;
}

void ManejadorEventosControlRobo (Evento_t *evn){
	static char buf[50];
	switch(estado){
//-----------------------------------------------------------------------------
	case sROBO_CONTROL_IDLE:
		switch(evn->signal)
		{
			case SIG_MODULO_INICIAR:
				mod = (Modulo_t *)evn->valor;
				ModuloRoboControlInit(mod);
				break;

			default: //Ignoro el resto de las señales
				break;
		}
		break;
//-----------------------------------------------------------------------------
	case sROBO_CONTROL_ALARMA_DESACTIVADA:
		switch(evn->signal)
		{
			case SIG_ACTIVAR_ALARMA:
				estado = sROBO_CONTROL_ALARMA_ACTIVADA;
//				sprintf(buf," Alarma ACTIVADA\r\n");
//				UARTputsDEBUG(msg);
				UARTputsDEBUG(" Alarma ACTIVADA\r\n");

				vecesRestantes_VelocidadDetectada = VECES_CONSECUTIVAS_VELOCIDAD_DETECTADA_DEFAULT;
				vecesRestantes_RopturaCadena = VECES_CONSECUTIVAS_ROPTURA_CADENA_DEFAULT;
				vecesRestantes_ShockDetectado = VECES_CONSECUTIVAS_SHOCK_DETECTADO_DEFAULT;

				break;

			default: //Ignoro el resto de las señales
				break;
		}
		break;
//-----------------------------------------------------------------------------
	case sROBO_CONTROL_ROBO_DETECTADO:
		switch(evn->signal){
			case SIG_DESACTIVAR_ALARMA:
				estado = sROBO_CONTROL_ALARMA_DESACTIVADA;
				detenerAlarmaRobo();
				//sprintf(buf," Alarma DESACTIVADA\r\n");
				//UARTputsDEBUG(msg);
				UARTputsDEBUG(" Alarma DESACTIVADA\r\n");

				break;

			default: //Ignoro el resto de las señales
				break;
		}
		break;
//-----------------------------------------------------------------------------
	case sROBO_CONTROL_ALARMA_ACTIVADA:
		switch(evn->signal){
			case SIG_DESACTIVAR_ALARMA:
				estado = sROBO_CONTROL_ALARMA_DESACTIVADA;
				detenerAlarmaRobo(); //esto no es necesario pero por las dudas se hace igual
//				sprintf(buf," Alarma DESACTIVADA\r\n");
				UARTputsDEBUG(msg);
				UARTputsDEBUG(" Alarma DESACTIVADA\r\n");
				break;
			case SIG_NUEVA_VELOCIDAD:
				sprintf(buf," velocidad actual %d\r\n",evn->valor);
				UARTputsDEBUG(msg);
				UARTputsDEBUG(buf);

				if (evn->valor > 0)
				{
					if (vecesRestantes_VelocidadDetectada > 0)
					{
						vecesRestantes_VelocidadDetectada--;
					}
					else
					{
						dispararAlarmaRobo();
						estado = sROBO_CONTROL_ROBO_DETECTADO;
					}
				}
				else
				{
					vecesRestantes_VelocidadDetectada = VECES_CONSECUTIVAS_VELOCIDAD_DETECTADA_DEFAULT;
				}


				break;
			case SIG_ROPTURA_CADENA:
				sprintf(buf," roptura cadena detectada \r\n");
				UARTputsDEBUG(msg);
				UARTputsDEBUG(buf);

					if (vecesRestantes_RopturaCadena > 0)
					{
						vecesRestantes_RopturaCadena--;
					}
					else
					{
						dispararAlarmaRobo();
						estado = sROBO_CONTROL_ROBO_DETECTADO;
					}


				break;

			case SIG_SHOCK_DETECTADO:
				sprintf(buf," shock detectada \r\n");
				UARTputsDEBUG(msg);
				UARTputsDEBUG(buf);

					if (vecesRestantes_RopturaCadena > 0)
					{
						vecesRestantes_RopturaCadena--;
					}
					else
					{
						dispararAlarmaRobo();
						estado = sROBO_CONTROL_ROBO_DETECTADO;
					}

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
