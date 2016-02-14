#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "Interrupcion.h"
#include "modulos.h"
#include "GPIO.h"

extern xQueueHandle colaVueltas;
extern xQueueHandle colaPulsacion;
extern xSemaphoreHandle rupturaCadena;
extern xSemaphoreHandle botonRobo;
extern portTickType ContarTicksVueltas;
extern portTickType ContarTicksSalud;

void EINT3_IRQHandler(void)
{
	static signed portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;

	if(LPC_GPIOINT->IO0IntStatF & (1<<4)) //Cuando la interrupcion se lanzo porque el sensor detecto la rueda
	{
		xQueueSendFromISR(colaVueltas,  &ContarTicksVueltas, &xHigherPriorityTaskWoken);
		ContarTicksVueltas = 0;
		LPC_GPIOINT->IO0IntClr = 1<<4;
	}

	if(LPC_GPIOINT->IO2IntStatF & (1<<3)) //Cuando la interrupcion se lanzo porque el sensor detecto un Pulso
	{
		xQueueSendFromISR(colaPulsacion,  &ContarTicksSalud, &xHigherPriorityTaskWoken);
		ContarTicksSalud = 0;
		LPC_GPIOINT->IO2IntClr = 1<<3;
	}

	if(LPC_GPIOINT->IO2IntStatF & (1<<4)) //Cuando la interrupcion se lanzo porque el sensor detecto La rotura de la cadena
	{
		xSemaphoreGiveFromISR(rupturaCadena, &xHigherPriorityTaskWoken);
		LPC_GPIOINT->IO2IntClr = 1<<4;
	}

	if(LPC_GPIOINT->IO2IntStatF & (1<<0)) //Cuando la interrupcion se lanzo porque el sensor detecto el boton de robo
	{
		xSemaphoreGiveFromISR(botonRobo, &xHigherPriorityTaskWoken);
		LPC_GPIOINT->IO2IntClr = 1<<0;
	}

	// Si la tarea asociada tiene mayor prioridad que la que
	//se esta ejecutando
   if(xHigherPriorityTaskWoken == pdTRUE)
	   // se realiza un cambio de contexto manualmente
	   //(no se pasa por el scheduler).
	   vPortYieldFromISR ();
}
