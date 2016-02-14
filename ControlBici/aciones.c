#include "MaquinaEstado/maquinaEstadoSEMLibB.h"
#include "globales.h"

VS_VOID notificarModConfigNuevaInclinacionMax (VS_INT nuevaInclinacionMax)
{
    Evento_t evn;

    evn.signal 		= SIG_CONFIG_INCLINACION_MAXIMA;
   	evn.receptor 	= ModuloConfiguracion;
   	evn.valor 		= (int)nuevaInclinacionMax;
   	DespacharEvento(&evn);

}

VS_VOID notificarModConfigNuevaPulsacionMax (VS_INT nuevaPulsacionMax)
{
    Evento_t evn;

    evn.signal 		= SIG_CONFIG_PULSACIONES_MAXIMA;
   	evn.receptor 	= ModuloConfiguracion;
   	evn.valor 		= (int)nuevaPulsacionMax;
   	DespacharEvento(&evn);

}

VS_VOID notificarModConfigNuevaVelMaxima (VS_INT nuevaVelMax)
{
    Evento_t evn;

    evn.signal 		= SIG_CONFIG_VELOCIDAD_MAXIMA;
   	evn.receptor 	= ModuloConfiguracion;
   	evn.valor 		= (int)nuevaVelMax;
   	DespacharEvento(&evn);
}

VS_VOID notificarModConfigNuevoRodado (VS_INT nuevoRodado)
{
    Evento_t evn;

    evn.signal 		= SIG_CONFIG_RODADO;
   	evn.receptor 	= ModuloConfiguracion;
   	evn.valor 		= (int)nuevoRodado;
   	DespacharEvento(&evn);
}

VS_VOID notificarModConfiguracionComienzoConfig (VS_VOID)
{

	Evento_t evn;

	evn.signal 		= SIG_CONFIG_COMENZAR_CONFIG;
	evn.receptor 	= ModuloConfiguracion;
	evn.valor 		= 0;
	DespacharEvento(&evn);

}

VS_VOID notificarModConfiguracionFinConfig (VS_VOID)
{

	Evento_t evn;

	evn.signal 		= SIG_CONFIG_FINALIZAR_CONFIG;
	evn.receptor 	= ModuloConfiguracion;
	evn.valor 		= 0;
	DespacharEvento(&evn);
}

VS_VOID notificarModRoboNuevaVelocidad (VS_INT nuevaVelocidad)
{
	Evento_t evn;

	evn.signal 		= SIG_NUEVA_VELOCIDAD;
	evn.receptor 	= ModuloControlRobo;
	evn.valor 		= (int)nuevaVelocidad;
	DespacharEvento(&evn);
}

VS_VOID notificarModRoboRopturaCadena (VS_VOID)
{
	Evento_t evn;

	evn.signal 		= SIG_ROPTURA_CADENA;
	evn.receptor 	= ModuloControlRobo;
	evn.valor 		= 0;
	DespacharEvento(&evn);
}

VS_VOID notificarModRoboShokDetectado (VS_VOID)
{
	Evento_t evn;

	evn.signal 		= SIG_SHOCK_DETECTADO;
	evn.receptor 	= ModuloControlRobo;
	evn.valor 		= 0;
	DespacharEvento(&evn);
}

VS_VOID notificarModSaludNuevaInclinacion (VS_INT nuevaInclinacion)
{
	Evento_t evn;

	evn.signal 		= SIG_NUEVA_INCLINACION;
	evn.receptor 	= ModuloControlSalud;
	evn.valor 		= (int)nuevaInclinacion;
	DespacharEvento(&evn);
}

VS_VOID notificarModSaludNuevaPulsaciones (VS_INT nuevasPulsaciones)
{
	Evento_t evn;

	evn.signal 		= SIG_NUEVA_PULSACIONES;
	evn.receptor 	= ModuloControlSalud;
	evn.valor 		= (int)nuevasPulsaciones;
	DespacharEvento(&evn);
}

VS_VOID notificarModSaludNuevaVelocidad (VS_INT nuevaVelocidad)
{
	Evento_t evn;

	evn.signal 		= SIG_NUEVA_VELOCIDAD;
	evn.receptor 	= ModuloControlSalud;
	evn.valor 		= (int)nuevaVelocidad;
	DespacharEvento(&evn);
}

VS_VOID notificarModlRoboAlarmaActivada (VS_VOID)
{
	Evento_t evn;

	evn.signal 		= SIG_ACTIVAR_ALARMA;
	evn.receptor 	= ModuloControlRobo;
	evn.valor 		= 0;
	DespacharEvento(&evn);
}

VS_VOID notificarModlRoboAlarmaDesactivada (VS_VOID)
{
	Evento_t evn;

	evn.signal 		= SIG_DESACTIVAR_ALARMA;
	evn.receptor 	= ModuloControlRobo;
	evn.valor 		= 0;
	DespacharEvento(&evn);
}

extern VS_VOID notificarModSaludComienzoMovimiento (VS_VOID)
{
	Evento_t evn;

	evn.signal 		= SIG_COMIENZO_MOVIMIENTO;
	evn.receptor 	= ModuloControlSalud;
	evn.valor 		= 0;
	DespacharEvento(&evn);
}

extern VS_VOID notificarModSaludFinMovimiento (VS_VOID)
{
	Evento_t evn;

	evn.signal 		= SIG_FIN_MOVIMIENTO;
	evn.receptor 	= ModuloControlSalud;
	evn.valor 		= 0;
	DespacharEvento(&evn);
}

extern VS_VOID notificarModSaludTimeout (VS_VOID)
{
	Evento_t evn;

	evn.signal 		= SIG_TIMEOUT;
	evn.receptor 	= ModuloControlSalud;
	evn.valor 		= 0;
	DespacharEvento(&evn);
}
