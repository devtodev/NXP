#include "UART.h"

#define SALTOLINEA 		0
#define MAINMENU 		1
#define ESTACIONADO		2
#define CONFIGMENU 		3
#define RODADO 			4
#define VELOCIDADMAX	5
#define INCLINACIONMAX 6
#define PULSACIONESMAX 7
#define TITULOAPP		8
#define VERVALORES		9
#define ANDANDO			10
#define ALARMA			92
#define ALARMASALUD		100
#define ALARMAROBO		101

#define CANTTEXTOS		15
#define MAXBUFFINPUT   25


void inputBTChar(int *estado, char input, UART *consola);
void initconsola(UART *consolaBT);
void showMenu(UART *consola, int estado);
void interfazHumana(void * parametrosTarea);
