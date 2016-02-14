/*
* salud_control.c
 *
 *  Created on: 26/07/2014
 *      Author: Alejandro Permingeat
 */

#include "FrameworkEventos.h"
#include "definiciones.h"
#include "baseboard.h"
#include "globales.h"
#include "Drivers/driver.h"

#include "UART.h"
#include "lpc_176X_PinNames.h"
extern UART consola;

#define		VECES_CONSECUTIVAS_VELOCIDAD_MAYOR_MAXIMA_DEFAULT	4
#define		VECES_CONSECUTIVAS_INCLINACION_MAYOR_MAXIMA_DEFAULT	4
#define		VECES_CONSECUTIVAS_PULSACIONES_MAYOR_MAXIMA_DEFAULT	4

#define		VECES_CONSECUTIVAS_VELOCIDAD_MENOR_MAXIMA_DEFAULT	4
#define		VECES_CONSECUTIVAS_INCLINACION_MENOR_MAXIMA_DEFAULT	4
#define		VECES_CONSECUTIVAS_PULSACIONES_MENOR_MAXIMA_DEFAULT	4

typedef enum EstadosSaludControlEnum {
	sSALUD_CONTROL_IDLE		 = 0,
	sSALUD_CONTROL_DETENIDO,
	sSALUD_CONTROL_ACTIVO,
	sSALUD_CONTROL_INACTIVO,
	sSALUD_CONTROL_EMERGENCIA
} EstadosLuzControlEnum_t;

static int hardwareLuzControlInicializado = NO;
static int estado = sSALUD_CONTROL_IDLE;
static Modulo_t * mod;
static const char msg[] = "Control Salud:";

int vecesRestantes_VelocidadMaxSuperada = 0;
int vecesRestantes_InclinacionMaxSuperada = 0;
int vecesRestantes_PulsacionesMaxSuperada = 0;

int vecesRestantes_VelocidadMenorMaxima = 0;
int vecesRestantes_InlcinacionMenorMaxima = 0;
int vecesRestantes_PulsacionesMenorMaxima = 0;

/*PWMTimer FrecuenciaPWMLuzControl;
PWMOut ControlLuz;*/

void dispararAlarmaSalud()
{
	char buf[50];
	sprintf(buf," Alarma de salud DISPARADA!!! %d\r\n");
	UARTputsDEBUG(msg);
	UARTputsDEBUG(buf);
	//poner en la cola de la tarea sirena un mensaje dando la orden que se dispare la alarma de salud
};

detenerAlarmaSalud()
{
	char buf[50];
	sprintf(buf," Alarma de salud DETENIDA!!! %d\r\n");
	UARTputsDEBUG(msg);
	UARTputsDEBUG(buf);
	//poner en la cola de la tarea sirena un mensaje dando la orden que se dispare la alarma de salud
};

void ModuloSaludControlInit(Modulo_t * modulo){
	if(!hardwareLuzControlInicializado){

	}
	vecesRestantes_VelocidadMaxSuperada = VECES_CONSECUTIVAS_VELOCIDAD_MAYOR_MAXIMA_DEFAULT;
	vecesRestantes_InclinacionMaxSuperada = VECES_CONSECUTIVAS_INCLINACION_MAYOR_MAXIMA_DEFAULT;
	vecesRestantes_PulsacionesMaxSuperada = VECES_CONSECUTIVAS_PULSACIONES_MAYOR_MAXIMA_DEFAULT;

	vecesRestantes_VelocidadMenorMaxima = 0;
	vecesRestantes_InlcinacionMenorMaxima = 0;
	vecesRestantes_PulsacionesMenorMaxima = 0;

	modulo->periodo			=   1000;
	TimerArm(modulo, modulo->periodo);
	mod = modulo;
	estado = sSALUD_CONTROL_DETENIDO;
}

void ManejadorEventosControlSalud (Evento_t *evn){
	char buf[50];
	static int velocidad, inclinacion, pulsaciones;
	switch(estado){
//-----------------------------------------------------------------------------
	case sSALUD_CONTROL_IDLE:
		switch(evn->signal)
		{
			case SIG_MODULO_INICIAR:
				mod = (Modulo_t *)evn->valor;
				ModuloSaludControlInit(mod);
				break;

			default: //Ignoro el resto de las señales
				break;
		}
		break;
//-----------------------------------------------------------------------------
	case sSALUD_CONTROL_DETENIDO:
		switch(evn->signal)
		{
			case SIG_COMIENZO_MOVIMIENTO:
				sprintf(buf," Andando!! %d\r\n",evn->valor);
				//UARTputsDEBUG(msg);
				UARTputsDEBUG(buf);
				estado = sSALUD_CONTROL_ACTIVO;
				break;

			default: //Ignoro el resto de las señales
				break;
		}
		break;
//-----------------------------------------------------------------------------
	case sSALUD_CONTROL_ACTIVO:


		switch(evn->signal)
		{
			case SIG_TIMEOUT:
					sprintf(buf," Informar vel %d, inclin %d, puls %d\r\n",velocidad, inclinacion,pulsaciones);
					UARTputsDEBUG(buf);
					ponerEnColaDatos(EVENT_INFORMACION_DATOS_ACTUALES,velocidad, inclinacion,pulsaciones);
					//ponerEnColaDatos(EVENT_INFORMACION_DATOS_ACTUALES,50, 60,70);

					break;

			case SIG_FIN_MOVIMIENTO:
					sprintf(buf," Detenido %d\r\n",evn->valor);
					UARTputsDEBUG(buf);
					estado = sSALUD_CONTROL_DETENIDO;
					break;

			case SIG_NUEVA_VELOCIDAD:
				sprintf(buf," velocidad actual %d\r\n",evn->valor);
				//UARTputsDEBUG(msg);
				UARTputsDEBUG(buf);
				velocidad = evn->valor;
				if (evn->valor >= configuracionSistema.velocdiadMaxima)
				{
					if (vecesRestantes_VelocidadMaxSuperada > 0)
					{
						vecesRestantes_VelocidadMaxSuperada--;
					}
					else
					{
						dispararAlarmaSalud();
						estado = sSALUD_CONTROL_EMERGENCIA;
						vecesRestantes_VelocidadMenorMaxima = VECES_CONSECUTIVAS_VELOCIDAD_MENOR_MAXIMA_DEFAULT;

					}
				}
				else
				{
					vecesRestantes_VelocidadMaxSuperada = VECES_CONSECUTIVAS_VELOCIDAD_MAYOR_MAXIMA_DEFAULT;
				}


				break;

			case SIG_NUEVA_INCLINACION:
				sprintf(buf," inclinación actual %d\r\n",evn->valor);
				UARTputsDEBUG(msg);
				UARTputsDEBUG(buf);
				inclinacion = evn->valor;
				if (evn->valor >= configuracionSistema.inclinacionMaxima)
				{
					if (vecesRestantes_InclinacionMaxSuperada > 0)
					{
						vecesRestantes_InclinacionMaxSuperada--;
					}
					else
					{
						dispararAlarmaSalud();
						estado = sSALUD_CONTROL_EMERGENCIA;
						vecesRestantes_InlcinacionMenorMaxima = VECES_CONSECUTIVAS_INCLINACION_MENOR_MAXIMA_DEFAULT;
					}
				}
				else
				{
					vecesRestantes_InclinacionMaxSuperada = VECES_CONSECUTIVAS_INCLINACION_MAYOR_MAXIMA_DEFAULT;
				}

				break;

			case SIG_NUEVA_PULSACIONES:
				sprintf(buf," pulsaciones actuales %d\r\n",evn->valor);
				UARTputsDEBUG(msg);
				UARTputsDEBUG(buf);
				pulsaciones = evn->valor;
				if (evn->valor >= configuracionSistema.pulsacionesMaxima)
				{
					if (vecesRestantes_PulsacionesMaxSuperada > 0)
					{
						vecesRestantes_PulsacionesMaxSuperada--;
					}
					else
					{
						dispararAlarmaSalud();
						estado = sSALUD_CONTROL_EMERGENCIA;
						vecesRestantes_PulsacionesMenorMaxima = VECES_CONSECUTIVAS_PULSACIONES_MENOR_MAXIMA_DEFAULT;
					}
				}
				else
				{
					vecesRestantes_PulsacionesMaxSuperada = VECES_CONSECUTIVAS_PULSACIONES_MAYOR_MAXIMA_DEFAULT;
				}

				break;


			default: //Ignoro el resto de las señales
				break;
		}
		break;
//-----------------------------------------------------------------------------
	case sSALUD_CONTROL_EMERGENCIA:

		//para salir del estado de emergencia se deben leer n veces consecutivas los valores
		//de los indicadores de velocidad, pulsaciones e inclinacion por debajo de
		//sus respectivos valores máximos.
		switch(evn->signal){
			case SIG_TIMEOUT:
					sprintf(buf," Informar vel %d, inclin %d, puls %d\r\n",velocidad, inclinacion,pulsaciones);
					UARTputsDEBUG(buf);
					ponerEnColaDatos(EVENT_INFORMACION_DATOS_ACTUALES,velocidad, inclinacion,pulsaciones);

					break;
			case SIG_FIN_MOVIMIENTO:
				sprintf(buf," Detenido %d\r\n",evn->valor);
				UARTputsDEBUG(buf);
				estado = sSALUD_CONTROL_DETENIDO;
				break;

			case SIG_NUEVA_VELOCIDAD:
				sprintf(buf," velocidad actual %d\r\n",evn->valor << 3);
				UARTputsDEBUG(msg);
				UARTputsDEBUG(buf);
				velocidad = evn->valor;
				if (evn->valor < configuracionSistema.velocdiadMaxima)
				{
					if (vecesRestantes_VelocidadMenorMaxima > 0)
					{
						vecesRestantes_VelocidadMenorMaxima--;
					}
				}
				else
				{
					vecesRestantes_VelocidadMenorMaxima = VECES_CONSECUTIVAS_VELOCIDAD_MENOR_MAXIMA_DEFAULT;
				}

				break;

		case SIG_NUEVA_INCLINACION:
			sprintf(buf," inclinación actual %d\r\n",evn->valor << 3);
			UARTputsDEBUG(msg);
			UARTputsDEBUG(buf);
			inclinacion = evn->valor;
			if (evn->valor < configuracionSistema.inclinacionMaxima)
			{
				if (vecesRestantes_InlcinacionMenorMaxima > 0)
				{
					vecesRestantes_InlcinacionMenorMaxima--;
				}
			}
			else
			{
				vecesRestantes_InlcinacionMenorMaxima = VECES_CONSECUTIVAS_INCLINACION_MENOR_MAXIMA_DEFAULT;
			}

			break;

		case SIG_NUEVA_PULSACIONES:
			sprintf(buf," pulsaciones actuales %d\r\n",evn->valor << 3);
			UARTputsDEBUG(msg);
			UARTputsDEBUG(buf);
			pulsaciones = evn->valor;
			if (evn->valor < configuracionSistema.pulsacionesMaxima)
			{
				if (vecesRestantes_PulsacionesMenorMaxima > 0)
				{
					vecesRestantes_PulsacionesMenorMaxima--;
				}
			}
			else
			{
				vecesRestantes_PulsacionesMenorMaxima = VECES_CONSECUTIVAS_INCLINACION_MENOR_MAXIMA_DEFAULT;
			}
			break;

		default: //Ignoro el resto de las señales
				break;
		if ((vecesRestantes_VelocidadMenorMaxima == 0) &&
				(vecesRestantes_VelocidadMenorMaxima == 0) &&
				(vecesRestantes_VelocidadMenorMaxima == 0))
		{
			//si durante n veces consecutivas los valores
			//de los indicadores de velocidad, pulsaciones e inclinacion por debajo de
			//sus respectivos valores máximos, decretar el fin de la alarma de velocidad
			detenerAlarmaSalud();
			estado = sSALUD_CONTROL_ACTIVO;
			vecesRestantes_PulsacionesMaxSuperada = VECES_CONSECUTIVAS_PULSACIONES_MAYOR_MAXIMA_DEFAULT;
			vecesRestantes_InclinacionMaxSuperada = VECES_CONSECUTIVAS_INCLINACION_MAYOR_MAXIMA_DEFAULT;
			vecesRestantes_VelocidadMaxSuperada = VECES_CONSECUTIVAS_VELOCIDAD_MAYOR_MAXIMA_DEFAULT;
			vecesRestantes_VelocidadMenorMaxima = 0;
			vecesRestantes_InlcinacionMenorMaxima = 0;
			vecesRestantes_PulsacionesMenorMaxima = 0;
		}

		}
		break;
//-----------------------------------------------------------------------------
		default:
			// Estoy en un estado invalido, tengo que reiniciar este modulo
			break;
	}
	if(evn->signal == SIG_TIMEOUT)
	{
		TimerArm(mod, mod->periodo);
	}
}
