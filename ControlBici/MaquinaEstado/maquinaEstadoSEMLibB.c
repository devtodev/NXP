/*
 * Id:        maquinaEstadoSEMLibB.c
 *
 * Function:  Contains all API functions.
 *
 * Generated: Wed Jul 30 22:11:22 2014
 *
 * Coder 6, 4, 1, 1980
 * 
 * This is an automatically generated file. It will be overwritten by the Coder.
 * 
 * DO NOT EDIT THE FILE!
 */


#include "maquinaEstadoSEMLibB.h"


#include <stdarg.h>


#if (VS_CODER_GUID != 0X002971a3dL)
#error The generated file does not match the SEMTypes.h header file.
#endif


#define CSV maquinaEstadoCSV


/*
 * State Identifier Definitions.
 */
#define MaquinaEstado_Region1_Reposo 0u
#define MaquinaEstado_Region1_Andando 1u
#define MaquinaEstado_Region1_Configuracion 2u
#define MaquinaEstado_Region1_Alarma 3u
#define MaquinaEstado_Region1_Alarma_MaquinEstado_StandBy 4u
#define MaquinaEstado_Region1_Alarma_MaquinEstado_Disparado 5u


static SEM_STATE_TYPE maquinaEstadoCSV[VS_NOF_STATE_MACHINES];


VS_UINT8 maquinaEstadoVSDeduct (SEM_EVENT_TYPE EventNo, ...)
{

  /* scoped for events */
  {
    SEM_STATE_TYPE WSV[VS_NOF_STATE_MACHINES] =
    {
      STATE_UNDEFINED,
      STATE_UNDEFINED
    };

    switch (EventNo)
    {
    case SE_RESET:
      {
        WSV[0] = MaquinaEstado_Region1_Reposo;
        WSV[1] = MaquinaEstado_Region1_Alarma_MaquinEstado_StandBy;
      }
      break;

    case activacionAlarma:
      {
        if ((CSV[0] == MaquinaEstado_Region1_Reposo))
        {
          notificarModlRoboAlarmaActivada();
          WSV[0] = MaquinaEstado_Region1_Alarma;
          WSV[1] = MaquinaEstado_Region1_Alarma_MaquinEstado_StandBy;
        }
      }
      break;

    case configurarInclinacionMaxima:
      {
        va_list ap;
        VS_INT inclinacionMaxima;
        va_start(ap, EventNo);
        inclinacionMaxima = (VS_INT)va_arg(ap, VS_INT);
        va_end(ap);
        if ((CSV[0] == MaquinaEstado_Region1_Configuracion))
        {
          notificarModConfigNuevaInclinacionMax(inclinacionMaxima);
          WSV[0] = MaquinaEstado_Region1_Configuracion;
        }
      }
      break;

    case configurarPulsacionesMaxima:
      {
        va_list ap;
        VS_INT pulsacionesMax;
        va_start(ap, EventNo);
        pulsacionesMax = (VS_INT)va_arg(ap, VS_INT);
        va_end(ap);
        if ((CSV[0] == MaquinaEstado_Region1_Configuracion))
        {
          notificarModConfigNuevaPulsacionMax(pulsacionesMax);
          WSV[0] = MaquinaEstado_Region1_Configuracion;
        }
      }
      break;

    case configurarValorRodado:
      {
        va_list ap;
        VS_INT rodado;
        va_start(ap, EventNo);
        rodado = (VS_INT)va_arg(ap, VS_INT);
        va_end(ap);
        if ((CSV[0] == MaquinaEstado_Region1_Configuracion))
        {
          notificarModConfigNuevoRodado(rodado);
          WSV[0] = MaquinaEstado_Region1_Configuracion;
        }
      }
      break;

    case configurarVelocidadMaxima:
      {
        va_list ap;
        VS_INT velocidadMaxima;
        va_start(ap, EventNo);
        velocidadMaxima = (VS_INT)va_arg(ap, VS_INT);
        va_end(ap);
        if ((CSV[0] == MaquinaEstado_Region1_Configuracion))
        {
          notificarModConfigNuevaVelMaxima(velocidadMaxima);
          WSV[0] = MaquinaEstado_Region1_Configuracion;
        }
      }
      break;

    case desactivacionAlarma:
      {
        if ((CSV[0] == MaquinaEstado_Region1_Alarma))
        {
          notificarModlRoboAlarmaDesactivada();
          WSV[0] = MaquinaEstado_Region1_Reposo;
        }
      }
      break;

    case empezarConfiguracion:
      {
        if ((CSV[0] == MaquinaEstado_Region1_Reposo))
        {
          notificarModConfiguracionComienzoConfig();
          WSV[0] = MaquinaEstado_Region1_Configuracion;
        }
      }
      break;

    case nuevaMedicionInclinacion:
      {
        va_list ap;
        VS_INT inclinacion;
        va_start(ap, EventNo);
        inclinacion = (VS_INT)va_arg(ap, VS_INT);
        va_end(ap);
        if ((CSV[0] == MaquinaEstado_Region1_Andando))
        {
          notificarModSaludNuevaInclinacion(inclinacion);
          WSV[0] = MaquinaEstado_Region1_Andando;
        }
      }
      break;

    case nuevaMedicionPulsaciones:
      {
        va_list ap;
        VS_INT pulsaciones;
        va_start(ap, EventNo);
        pulsaciones = (VS_INT)va_arg(ap, VS_INT);
        va_end(ap);
        if ((CSV[0] == MaquinaEstado_Region1_Andando))
        {
          notificarModSaludNuevaPulsaciones(pulsaciones);
          WSV[0] = MaquinaEstado_Region1_Andando;
        }
      }
      break;

    case nuevaMedicionVelocidad:
      {
        va_list ap;
        VS_INT velocidad;
        va_start(ap, EventNo);
        velocidad = (VS_INT)va_arg(ap, VS_INT);
        va_end(ap);
        if ((CSV[0] == MaquinaEstado_Region1_Reposo)
          && (velocidad > 0))
        {
          notificarModSaludComienzoMovimiento();
          WSV[0] = MaquinaEstado_Region1_Andando;
        }
        if ((CSV[0] == MaquinaEstado_Region1_Andando)
          && (velocidad == 0))
        {
          notificarModSaludFinMovimiento();
          if ((WSV[0] != STATE_UNDEFINED) && (WSV[0] != MaquinaEstado_Region1_Reposo))
          {
            return SES_CONTRADICTION;
          }
          WSV[0] = MaquinaEstado_Region1_Reposo;
        }
        if ((CSV[0] == MaquinaEstado_Region1_Andando)
          && (velocidad > 0))
        {
          notificarModSaludNuevaVelocidad(velocidad);
          if ((WSV[0] != STATE_UNDEFINED) && (WSV[0] != MaquinaEstado_Region1_Andando))
          {
            return SES_CONTRADICTION;
          }
          WSV[0] = MaquinaEstado_Region1_Andando;
        }
        if ((CSV[0] == MaquinaEstado_Region1_Alarma)
          && (CSV[1] == MaquinaEstado_Region1_Alarma_MaquinEstado_StandBy)
          && (velocidad > 0))
        {
          notificarModRoboNuevaVelocidad(velocidad);
          WSV[0] = MaquinaEstado_Region1_Alarma;
          WSV[1] = MaquinaEstado_Region1_Alarma_MaquinEstado_Disparado;
        }
      }
      break;

    case ropturaCadena:
      {
        if ((CSV[0] == MaquinaEstado_Region1_Alarma)
          && (CSV[1] == MaquinaEstado_Region1_Alarma_MaquinEstado_StandBy))
        {
          notificarModRoboRopturaCadena();
          WSV[0] = MaquinaEstado_Region1_Alarma;
          WSV[1] = MaquinaEstado_Region1_Alarma_MaquinEstado_Disparado;
        }
      }
      break;

    case shockDetectado:
      {
        if ((CSV[0] == MaquinaEstado_Region1_Alarma)
          && (CSV[1] == MaquinaEstado_Region1_Alarma_MaquinEstado_StandBy))
        {
          notificarModRoboShokDetectado();
          WSV[0] = MaquinaEstado_Region1_Alarma;
          WSV[1] = MaquinaEstado_Region1_Alarma_MaquinEstado_Disparado;
        }
      }
      break;

    case terminarConfiguracion:
      {
        if ((CSV[0] == MaquinaEstado_Region1_Configuracion))
        {
          notificarModConfiguracionFinConfig();
          WSV[0] = MaquinaEstado_Region1_Reposo;
        }
      }
      break;

    default:
      return SES_RANGE_ERR;
    }

    /* Change the state vector */
    {
      VS_UINT i;
      for (i = 0u; i < VS_NOF_STATE_MACHINES; ++i)
      {
        if (WSV[i] != STATE_UNDEFINED)
        {
          CSV[i] = WSV[i];
        }
      }
    }
  }

  return SES_OKAY;
}


void maquinaEstadoVSInitAll (void)
{
}
