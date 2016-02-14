#ifndef _visualSTATE_MAQUINAESTADOSEMLIBB_H
#define _visualSTATE_MAQUINAESTADOSEMLIBB_H

/*
 * Id:        maquinaEstadoSEMLibB.h
 *
 * Function:  Contains definitions needed for API functions.
 *
 * Generated: Wed Jul 30 22:11:22 2014
 *
 * Coder 6, 4, 1, 1980
 * 
 * This is an automatically generated file. It will be overwritten by the Coder.
 * 
 * DO NOT EDIT THE FILE!
 */


#include "maquinaEstadoSEMBDef.h"


#if (VS_CODER_GUID != 0X002971a3dL)
#error The generated file does not match the SEMTypes.h header file.
#endif


#ifndef VS_TRUE
#define VS_TRUE (1)
#endif


#ifndef VS_FALSE
#define VS_FALSE (0)
#endif


/*
 * Event Identifier Definitions.
 */
#define SE_RESET 0u
#define activacionAlarma 1u
#define configurarInclinacionMaxima 2u
#define configurarPulsacionesMaxima 3u
#define configurarValorRodado 4u
#define configurarVelocidadMaxima 5u
#define desactivacionAlarma 6u
#define empezarConfiguracion 7u
#define nuevaMedicionInclinacion 8u
#define nuevaMedicionPulsaciones 9u
#define nuevaMedicionVelocidad 10u
#define ropturaCadena 11u
#define shockDetectado 12u
#define terminarConfiguracion 13u


#ifndef VS_COMPLETION_CODES_DEFINED
#define VS_COMPLETION_CODES_DEFINED
enum
{
  /*
   * Status code:     SES_OKAY.
   *
   * Explanation:     Function performed successfully.
   *
   * Solution:        None.
   */
  SES_OKAY, /* 0 */


  /*
   * Status code:     SES_FOUND.
   *
   * Explanation:     The called function has returned an identifier index number.
   *
   * Solution:        Process the returned identifier index number. If the
   *                  function SEM_GetInput or SEM_GetOutput was called, the
   *                  function can be called again to find more events or
   *                  action expressions.
   */
  SES_FOUND, /* 1 */


  /*
   * Status code:     SES_ACTIVE.
   *
   * Explanation:     The completion code has one of the two expositions:
   *                  1)  A state/event deduction is started, while an event
   *                      inquiry is active. All inquired events have not been
   *                      returned by the function SEM_GetInput.
   *                  2)  An event inquiry is started, while a state/event
   *                      deduction is active. All deduced action expressions 
   *                      have not been returned by the function SEM_GetOutput 
   *                      and the SEM_NextState has not been called in order to 
   *                      complete the state/event deduction.
   *
   * Solution:        The completion code is a warning and perhaps the
   *                  application program should be rewritten. An event inquiry
   *                  and a state/event deduction should not be active at the
   *                  same time.
   */
  SES_ACTIVE, /* 2 */


  /*
   * Error code:      SES_CONTRADICTION.
   *
   * Explanation:     A contradiction has been detected between two states in a
   *                  state machine.
   *
   * Solution:        Check the VS System.
   */
  SES_CONTRADICTION, /* 3 */


  /*
   * Error code:      SES_RANGE_ERR.
   *
   * Explanation:     You are making a reference to an identifier that does not
   *                  exist. Note that the first index number is 0. If the 
   *                  VS System has 4 identifiers of the same type and you use a
   *                  function with the variable parameter = 4, the function 
   *                  will return an SES_RANGE_ERR error. In this case the 
   *                  highest variable index number is 3.
   *
   * Solution:        The application program will check the index parameters 
   *                  with one of the following symbols defined in the SEMBDef.h 
   *                  file:
   *
   *                    VS_NOF_EVENTS
   *                    VS_NOF_STATES
   *                    VS_NOF_ACTION_FUNCTIONS
   *                    VS_NOF_STATE_MACHINES
   */
  SES_RANGE_ERR, /* 4 */


  /*
   * Error code:      SES_TEXT_TOO_LONG.
   *
   * Explanation:     The requested text is longer than the specified maximum length.
   *
   * Solution:        Increase the maximum length.
   */
  SES_TEXT_TOO_LONG, /* 5 */


   /*
   * Error code:      SES_TYPE_ERR.
   *
   * Explanation:     A text function has been called with the wrong identifier
   *                  type or the specified text is not included in the VS System.
   *
   * Solution:        Use the identifier type symbols (EVENT_TYPE, STATE_TYPE
   *                  or ACTION_TYPE) defined in this file and remember
   *                  to include wanted text in the VS System.
   */
  SES_TYPE_ERR, /* 6 */


  /*
   * Error code:      SES_EMPTY.
   *
   * Explanation:     No events have been given to the SEM_Deduct function before
   *                  calling this function.
   *
   * Solution:        Call the SEM_Deduct function with an event number.
   */
  SES_EMPTY, /* 7 */


  /*
   * Error code:      SES_BUFFER_OVERFLOW.
   *
   * Explanation:     A destination buffer cannot hold the number of items found.
   *
   * Solution:        Call the function with an extended buffer as destination.
   */
  SES_BUFFER_OVERFLOW, /* 8 */


  /*
   * Error code:      SES_SIGNAL_QUEUE_FULL.
   *
   * Explanation:     Signal queue is full.
   *
   * Solution:        Increase the maximum signal queue size in the VS System or
   *                  via the VS Coder signal queue size option.
   */
  SES_SIGNAL_QUEUE_FULL, /* 9 */


  /*
   * Error code:      SES_NOT_INITIALIZED.
   *
   * Explanation:     The system has not been initialized.
   *
   * Solution:        Call the initialization function for the VS System.
   */
  SES_NOT_INITIALIZED /* 10 */
};
#endif /* VS_COMPLETION_CODES_DEFINED */


/* Identifier types, used when getting texts and explanations.*/
#ifndef VS_IDENTIFIER_TYPES_DEFINED
#define VS_IDENTIFIER_TYPES_DEFINED
enum {EVENT_TYPE, STATE_TYPE};
#endif /* VS_IDENTIFIER_TYPES_DEFINED */


/*
 * Name        : maquinaEstadoVSDeduct
 *
 * Description : The function deduces all the relevant action expressions on
 *               the basis of the given event, the internal current state
 *               vector and the transitions in the VS System. All the
 *               relevant action expressions are then called and all the
 *               next states are changed.
 *
 * Argument    : EventNo:
 *                 Event number to be processed.
 *
 *               Variable number of arguments:
 *                 Used if at least one event has a parameter.
 *                 The function call must include one argument for each type
 *                 name declared in the parameter list for each event.
 *                 
 *                 This sample declaration is for an event with three
 *                 parameters:
 *                 
 *                   EventName (VS_UINT8 par1, VS_CHAR par2, VS_INT par3)
 *                 
 *                 How to call the maquinaEstadoVSDeduct function for the
 *                 event EventName:
 *                 
 *                   maquinaEstadoVSDeduct(EventName, par1, par2, par3);
 *
 * Return      : Completion code:
 *
 *                 SES_CONTRADICTION:
 *                   Contradiction detected, the VS System is not
 *                   consistent. Check the VS System.
 *                   You will also get this error code here if you forget to
 *                   call the maquinaEstadoVSInitAll function.
 *
 *                 SES_SIGNAL_QUEUE_FULL:
 *                   The signal queue is full. Increase the signal queue
 *                   size in the VS System.
 *
 *                 SES_FOUND:
 *                   Success. The internal state vector was updated.
 *
 *                 SES_RANGE_ERR:
 *                   The event given to this function is out of range.
 *
 *                 SES_OKAY:
 *                   Success.
 *
 * Portability : ANSI-C Compiler.
 */
VS_UINT8 maquinaEstadoVSDeduct (SEM_EVENT_TYPE EventNo, ...);


/*
 * Name        : maquinaEstadoVSInitAll
 *
 * Description : The function is a wrapper to all initialization 
 *               functions. The function calls the following functions
 *               in the listed order (provided the specific function 
 *               exists): 
 *                 maquinaEstadoVSInitExternalVariables
 *                 maquinaEstadoVSInitInternalVariables
 *
 * Argument    : None.
 */
void maquinaEstadoVSInitAll (void);


/*
 * Action Function Prototypes
 */
extern VS_VOID notificarModConfigNuevaInclinacionMax (VS_INT nuevaInclinacionMax);
extern VS_VOID notificarModConfigNuevaPulsacionMax (VS_INT nuevaPulsacionMax);
extern VS_VOID notificarModConfigNuevaVelMaxima (VS_INT nuevaVelMax);
extern VS_VOID notificarModConfigNuevoRodado (VS_INT nuevoRodado);
extern VS_VOID notificarModConfiguracionComienzoConfig (VS_VOID);
extern VS_VOID notificarModConfiguracionFinConfig (VS_VOID);
extern VS_VOID notificarModRoboNuevaVelocidad (VS_INT nuevaVelocidad);
extern VS_VOID notificarModRoboRopturaCadena (VS_VOID);
extern VS_VOID notificarModRoboShokDetectado (VS_VOID);
extern VS_VOID notificarModSaludComienzoMovimiento (VS_VOID);
extern VS_VOID notificarModSaludFinMovimiento (VS_VOID);
extern VS_VOID notificarModSaludNuevaInclinacion (VS_INT nuevaInclinacion);
extern VS_VOID notificarModSaludNuevaPulsaciones (VS_INT nuevasPulsaciones);
extern VS_VOID notificarModSaludNuevaVelocidad (VS_INT nuevaVelocidad);
extern VS_VOID notificarModlRoboAlarmaActivada (VS_VOID);
extern VS_VOID notificarModlRoboAlarmaDesactivada (VS_VOID);
extern VS_VOID notificarModuloControlSalud (VS_VOID);


#endif /* ifndef _visualSTATE_MAQUINAESTADOSEMLIBB_H */
