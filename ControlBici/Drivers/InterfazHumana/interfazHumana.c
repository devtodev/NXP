#include "interfazHumana.h"
#include "UART.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "string.h"
#include "modulos.h"
#include <stdlib.h>
#include "Drivers/driver.h"

#define height 			80

char *texto[CANTTEXTOS];
char saltoLinea[] = "\r\n";
char mainmenu[] = "MENU PRINCIPAL\r\n\r\n  1) Andar \r\n  2) Estacionado \r\n  3) Configuracion \r\n  4) Ver valores \r\n\0";
char configmenu[] = "CONFIGURACION \r\n\r\n  1) Rodado \r\n  2) Velocidad Maxima \r\n  3) Inclinacion Maxima \r\n  4) Pulsaciones Limite \r\n  5) Menu Principal \r\n\0";
char titulo[] = "MAQUINA DE ABORDO PARA BICICLETA\r\n\r\n \0";
char modoEstacionado[] = "MODO ESTACIONADO \r\n\r\n  M) Para volver al menu principal. \r\n\0";
char setRodado[] = "RODADO \r\n\r\n m) Menu de configuracion \r\n\r\n o ingrese el rodado en pulgadas:\0";
char maxVelocidad[] = "VELOCIDAD MAXIMA \r\n\r\n m) Menu de configuracion \r\n\r\n o ingrese la velocidad max en km/h: \0";
char maxPulsaciones[] = "PUSACIONES MAXIMA \r\n\r\n m) Menu de configuracion \r\n\r\n o ingrese la pulsacion/segundo max: \0";
char maxInclinacion[] = "INCLINACION MAXIMA \r\n\r\n m) Menu de configuracion \r\n\r\n o ingrese la inclinacion max en grados: \0";
char verValores[] = "VALORES\r\n\r\n\0";
int swAlarmaSeguridadON = 0;

int cambiarEstado(int nuevoEstado);
int addDatoBuffer(char input, UART *consolaBT, char *bufferInput);
void blanquearPantalla(UART *consolaBT);
void showAlertaSeguridad(UART *consolaBT);
void showAlertaSalud(UART *consolaBT);
int banderaShowMenu;
int iBuffer;
extern UART consolaBT;
extern xQueueHandle colaMensajesUsuarios;

int cambiarEstado(int nuevoEstado)
{
	banderaShowMenu = 0;
	return nuevoEstado;
}

char rodado[MAXBUFFINPUT];
char velocidadMaxima[MAXBUFFINPUT];
char pulsacionesMaxima[MAXBUFFINPUT];
char inclinacionMaxima[MAXBUFFINPUT];

void inputBTChar(int *estado, char input, UART *consolaBT)
{
	int temp = 0;
	if (input == 's') banderaShowMenu = 0;
	switch (*estado)
	{
		case MAINMENU:
			if (input == '1') *estado = cambiarEstado(ANDANDO);
			if (input == '2') *estado = cambiarEstado(ESTACIONADO);
			if (input == '3') *estado = cambiarEstado(CONFIGMENU);
			if (input == '4') *estado = cambiarEstado(VERVALORES);
			break;
		case ANDANDO:
			if (input == 'm') *estado = cambiarEstado(MAINMENU);
			break;
		case CONFIGMENU:
			if (input == '1') *estado = cambiarEstado(RODADO);
			if (input == '2') *estado = cambiarEstado(VELOCIDADMAX);
			if (input == '3') *estado = cambiarEstado(INCLINACIONMAX);
			if (input == '4') *estado = cambiarEstado(PULSACIONESMAX);
			if (input == '5') *estado = cambiarEstado(MAINMENU);
			if (input == 'm') *estado = cambiarEstado(MAINMENU);
			break;
		case ESTACIONADO:
			if (input == 'm')
			{
				*estado = cambiarEstado(MAINMENU);
				swAlarmaSeguridadON = 0;
			}
			break;
		case RODADO:
			if (input == 'm') *estado = cambiarEstado(CONFIGMENU);
			if (addDatoBuffer(input, consolaBT, (char *) &rodado[0]))
			{
				iBuffer = 0;
				*estado = cambiarEstado(VERVALORES);
				temp = atoi((char *) &rodado[0]);
				ponerEnColaEventos(EVENT_HI_MENU_SET_RODADO,atoi((char *) &rodado[0]));
			}
			break;
		case VELOCIDADMAX:
			if (input == 'm') *estado = cambiarEstado(CONFIGMENU);
			if (addDatoBuffer(input, consolaBT, (char *) &velocidadMaxima[0]))
			{
				iBuffer = 0;
				*estado = cambiarEstado(VERVALORES);
				temp = atoi((char *) &velocidadMaxima[0]);
				ponerEnColaEventos(EVENT_HI_MENU_SET_VELOCIDAD_MAX,atoi((char *) &velocidadMaxima[0]));
			}
			break;
		case INCLINACIONMAX:
			if (input == 'm') *estado = cambiarEstado(CONFIGMENU);
			if (addDatoBuffer(input, consolaBT, (char *) &inclinacionMaxima[0]))
			{
				iBuffer = 0;
				*estado = cambiarEstado(VERVALORES);
				temp =  atoi((char *) &inclinacionMaxima[0]);
				ponerEnColaEventos(EVENT_HI_MENU_SET_INCLINACION_MAX,atoi((char *) &inclinacionMaxima[0]));
			}
			break;
		case PULSACIONESMAX:
			if (input == 'm') *estado = cambiarEstado(CONFIGMENU);
			if (addDatoBuffer(input, consolaBT, (char *) &pulsacionesMaxima[0]))
			{
				iBuffer = 0;
				*estado = cambiarEstado(VERVALORES);
				temp = atoi((char *)  &pulsacionesMaxima[0]);
				ponerEnColaEventos(EVENT_HI_MENU_SET_PULSACIONES_MAX,atoi((char *)  &pulsacionesMaxima[0]));
			}
			break;
		case VERVALORES:
			if (input == 'm') *estado = cambiarEstado(CONFIGMENU);
			break;
	}
}

int addDatoBuffer(char input, UART *consolaBT, char *bufferInput)
{
	int respuesta = -1;
	if ((input <= '9') && (input >= '0'))
	{
		UARTputc(consolaBT, input);
		bufferInput[iBuffer] = input;
		iBuffer++;
		bufferInput[iBuffer] = '\0';
	}

	return (input == '\n');
}

void showAlertaSalud(UART *consolaBT)
{
	DatosDriver_t datos;
	char dato1[33];
	char dato2[33];
	char dato3[33];
	if (xQueueReceive(colaMensajesUsuarios, &datos, 100))
	{
		if (datos.codigo == ALARMA)
		{
			//dato1 = (datos.dato1 == ALARMASALUD)? "Alarma salud activada ! \r\n" : "Alarma seguridad activada ! \r\n";
			UARTputs(consolaBT, dato1, UART_PUTS_BLOQUEANTE);
		} else {
			itoa(datos.dato1, dato1, 10);
			itoa(datos.dato2, dato2, 10);
			itoa(datos.dato3, dato3, 10);

			UARTputs(consolaBT, "Andando... \r\n", UART_PUTS_BLOQUEANTE);
			UARTputs(consolaBT, strcat(dato1, " Velocidad \r\n"), UART_PUTS_BLOQUEANTE);
			UARTputs(consolaBT, strcat(dato2, " Inclinacion \r\n"), UART_PUTS_BLOQUEANTE);
			UARTputs(consolaBT, strcat(dato3, " Pulsaciones \r\n"), UART_PUTS_BLOQUEANTE);
			UARTputs(consolaBT, "m) Main Menu \r\n", UART_PUTS_BLOQUEANTE);
		}
	}
}

/**
 * TODO: probar void showAlertaSeguridad(UART *consolaBT);
 * TODO: probar void showAlertaSalud(UART *consolaBT);
 */

void showAlertaSeguridad(UART *consolaBT)
{
	char *dato1 = "                          ";
	DatosDriver_t datos;
	if (swAlarmaSeguridadON == 0)
	{
		if (xQueueReceive(colaMensajesUsuarios, &datos, 100))
		{
			if (datos.codigo == ALARMA)
			{
				swAlarmaSeguridadON = 1;
				dato1 = (datos.dato1 == ALARMASALUD)? "Alarma salud activada ! \r\n" : "Alarma seguridad activada ! \r\n";
				UARTputs(consolaBT, dato1, UART_PUTS_BLOQUEANTE);
			}
		} else {
			UARTputs(consolaBT, "Alarma activada... ",UART_PUTS_BLOQUEANTE);
			UARTputs(consolaBT, texto[SALTOLINEA],UART_PUTS_BLOQUEANTE);
			UARTputs(consolaBT, "m) Main Menu", UART_PUTS_BLOQUEANTE);
			UARTputs(consolaBT, texto[SALTOLINEA],UART_PUTS_BLOQUEANTE);
			UARTputs(consolaBT, "OK ",UART_PUTS_BLOQUEANTE);
			UARTputs(consolaBT, texto[SALTOLINEA],UART_PUTS_BLOQUEANTE);
		}
	}
}

void showMenu(UART *consolaBT, int estado)
{
	char temp[] = "             ";
	if (banderaShowMenu == 0)
	{
		blanquearPantalla(consolaBT);
		UARTputs(consolaBT, texto[TITULOAPP],UART_PUTS_BLOQUEANTE);
		UARTputs(consolaBT, texto[estado],UART_PUTS_BLOQUEANTE);

		switch (estado)
		{
			case CONFIGMENU :
						ponerEnColaEventos(EVENT_HI_MODO_CONFIGURACION_ENTRAR,0);
			break;
			case MAINMENU :
						ponerEnColaEventos(EVENT_HI_MODO_CONFIGURACION_SALIR,0);
						ponerEnColaEventos(EVENT_HI_MODO_ESTACIONADO_DESACTIVO,0);
			break;
			case ESTACIONADO :
						ponerEnColaEventos(EVENT_HI_MODO_ESTACIONADO_ACTIVO,0);
			break;
			case VERVALORES:
						UARTputs(consolaBT, "Rodado: ",UART_PUTS_BLOQUEANTE);
						UARTputs(consolaBT, rodado,UART_PUTS_BLOQUEANTE);
						UARTputs(consolaBT, "''\r\n",UART_PUTS_BLOQUEANTE);
						UARTputs(consolaBT, "Max. velocidad: ",UART_PUTS_BLOQUEANTE);
						UARTputs(consolaBT, velocidadMaxima,UART_PUTS_BLOQUEANTE);
						UARTputs(consolaBT, " km/h\r\n",UART_PUTS_BLOQUEANTE);
						UARTputs(consolaBT, "Max. inclinacion: ",UART_PUTS_BLOQUEANTE);
						UARTputs(consolaBT, inclinacionMaxima,UART_PUTS_BLOQUEANTE);
						UARTputs(consolaBT, " grados \r\n",UART_PUTS_BLOQUEANTE);
						UARTputs(consolaBT, "Max. pulsaciones/minuto: ",UART_PUTS_BLOQUEANTE);
						UARTputs(consolaBT, pulsacionesMaxima,UART_PUTS_BLOQUEANTE);
						UARTputs(consolaBT, texto[SALTOLINEA],UART_PUTS_BLOQUEANTE);
						UARTputs(consolaBT, texto[SALTOLINEA],UART_PUTS_BLOQUEANTE);
						UARTputs(consolaBT, "  m) Menu de configuracion",UART_PUTS_BLOQUEANTE);
						break;
		}
	}
	banderaShowMenu = 1;
}

void blanquearPantalla(UART *consolaBT)
{
	int i;
	for (i = 0; i < height; i++)
		UARTputs(consolaBT, texto[SALTOLINEA],UART_PUTS_BLOQUEANTE);
	i = i + 1;
}

void initconsola(UART *consolaBT)
{
	texto[SALTOLINEA] = saltoLinea;
	texto[MAINMENU] = mainmenu;
	texto[CONFIGMENU] = configmenu;
	texto[TITULOAPP] = titulo;
	texto[ESTACIONADO] = modoEstacionado;
	texto[RODADO] = setRodado;
	texto[VELOCIDADMAX] = maxVelocidad;
	texto[PULSACIONESMAX] = maxPulsaciones;
	texto[INCLINACIONMAX] = maxInclinacion;
	texto[VERVALORES] = verValores;
	blanquearPantalla(consolaBT);
}

void interfazHumana(void * parametrosTarea)
{
	portTickType ticker = xTaskGetTickCount();
	int estado = MAINMENU;
	char input;

	while(1)
	{
		if (estado == ESTACIONADO)
			showAlertaSeguridad(&consolaBT);
		if (estado == ANDANDO) showAlertaSalud(&consolaBT);
		showMenu(&consolaBT, estado);

		// lee un caracter desde el BT
		if (!ColaVacia(&consolaBT.colaRx))
		{
			input = UARTgetc(&consolaBT);
			inputBTChar(&estado, input, &consolaBT);
		}
	}
}
