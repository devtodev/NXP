/*
 * trace.h
 *
 *  Created on: May 7, 2013
 *      Author: Pablo M.
 */

#ifndef TRACE_H_
#define TRACE_H_

//To be compatible with FreeRTOS
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

extern void vTraceStart(void);
extern void vTraceStop(void);
extern void vTraceEvtTaskCreated(signed char * tskName);
extern void vTraceEvtTick(long ticks);
extern void vTraceEvtSwitchOut(char * pcTaskName, xTaskHandle pxCurrentTCB);
extern void vTraceEvtSwitchIn(char * pcTaskName, xTaskHandle pxCurrentTCB);

#endif /* TRACE_H_ */
