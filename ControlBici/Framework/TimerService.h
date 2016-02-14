/*
 * timeout.h
 *
 *  Created on: 29/11/2011
 *      Author: alejandro
 */

#ifndef TIMEOUT_H_
#define TIMEOUT_H_

#include "FrameworkEventos.h"

#define TIMER_DISABLED ((int)-1)

void 		TimerArm	( Modulo_t * modulo, unsigned int time );
void 		TimerDisarm	( Modulo_t * modulo );

#endif /* TIMEOUT_H_ */
