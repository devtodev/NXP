#ifndef _visualSTATE_MAQUINAESTADOSEMBDEF_H
#define _visualSTATE_MAQUINAESTADOSEMBDEF_H

/*
 * Id:        maquinaEstadoSEMBDef.h
 *
 * Function:  SEM Defines Header File.
 *
 * Generated: Wed Jul 30 22:11:22 2014
 *
 * Coder 6, 4, 1, 1980
 * 
 * This is an automatically generated file. It will be overwritten by the Coder.
 * 
 * DO NOT EDIT THE FILE!
 */


#include "maquinaEstadoSEMTypes.h"


#if (VS_CODER_GUID != 0X002971a3dL)
#error The generated file does not match the SEMTypes.h header file.
#endif


/*
 * Number of Identifiers.
 */
#define VS_NOF_ACTION_EXPRESSIONS        0X011u  /*  17 */
#define VS_NOF_ACTION_FUNCTIONS          0X009u  /*   9 */
#define VS_NOF_EVENT_GROUPS              0X000u  /*   0 */
#define VS_NOF_EVENTS                    0X00eu  /*  14 */
#define VS_NOF_EXTERNAL_VARIABLES        0X000u  /*   0 */
#define VS_NOF_GUARD_EXPRESSIONS         0X002u  /*   2 */
#define VS_NOF_INSTANCES                 0X001u  /*   1 */
#define VS_NOF_INTERNAL_VARIABLES        0X000u  /*   0 */
#define VS_NOF_SIGNALS                   0X000u  /*   0 */
#define VS_NOF_STATE_MACHINES            0X002u  /*   2 */
#define VS_NOF_STATES                    0X006u  /*   6 */


/*
 * Undefined State.
 */
#define STATE_UNDEFINED                  0X0FFu  /* 255 */


/*
 * Undefined Event.
 */
#define EVENT_UNDEFINED                  0X0FFu  /* 255 */


/*
 * Undefined Event Group.
 */
#define EVENT_GROUP_UNDEFINED            0X0FFu  /* 255 */


/*
 * Event Termination ID.
 */
#define EVENT_TERMINATION_ID             0X0FFu  /* 255 */


#endif /* ifndef _visualSTATE_MAQUINAESTADOSEMBDEF_H */
