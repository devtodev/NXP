#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "Alarma.h"
#include "modulos.h"
#include "GPIO.h"

GPIO led;

void IntegridadCadenaInterface (void * paramSemaforo){

	xSemaphoreHandle RupturaCadena = ((xSemaphoreHandle) paramSemaforo);
	int evento;
	int dato;
	xSemaphoreTake(RupturaCadena,portMAX_DELAY);
	while(1)
	{
		xSemaphoreTake(RupturaCadena,portMAX_DELAY);

		evento = 20;
		dato = 0;

		ponerEnColaEventos(evento,dato);
	}
}

void MedidorPulsacionCardiacaInterface (void * paramCola){

	xQueueHandle ColaPulsacion = (xQueueHandle) paramCola;
	portTickType cantidadticks;
	int evento;
	int dato;
	while(1)
	{
		xQueueReceive(ColaPulsacion, &cantidadticks, portMAX_DELAY);

		evento = 30;
		dato = ((SEGUNDOS_POR_MINUTO*1000)/(cantidadticks/portTICK_RATE_MS));

		ponerEnColaEventos(evento,dato);
	}

}



void BotonActivacionAlarmaInterface (void * paramSemaforo){

	xSemaphoreHandle BotonRobo = ((xSemaphoreHandle) paramSemaforo);
	int evento;
	int dato;
	xSemaphoreTake(BotonRobo,portMAX_DELAY);
	while(1)
	{
		xSemaphoreTake(BotonRobo,portMAX_DELAY);

		evento = 40;
		dato = 0;

		ponerEnColaEventos(evento,dato);
	}
}

void SirenaInterface (void * paramColaControlSirena){

	xQueueHandle cola = (xQueueHandle) paramColaControlSirena;
	EventoDriver_t PaqueteSirena;
	while(1)
	{
		xQueueReceive(cola, &PaqueteSirena, portMAX_DELAY);

		switch ( PaqueteSirena.codigo ) {
		case 80:
			Activar(&led);
		break;
		case 81:
			Activar(&led);
			vTaskDelay(500/portTICK_RATE_MS);
			Pasivar(&led);
			vTaskDelay(500/portTICK_RATE_MS);
			Activar(&led);
			vTaskDelay(500/portTICK_RATE_MS);
			Pasivar(&led);
		break;
		case 82:
			Pasivar(&led);
		break;
		}
	}
		//	Estrucutra.evento = '80'; //ACTIVAR ALARMA ROBO

	//	Estrucutra.evento = '81'; //ACTIVAR ALARMA SALUD

	//	Estrucutra.evento = '82'; //DESACTIVAR ALARMA

}
