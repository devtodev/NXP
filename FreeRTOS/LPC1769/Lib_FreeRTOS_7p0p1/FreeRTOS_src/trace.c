/*
 * trace.c
 *
 *  Created on: May 7, 2013
 *      Author: Pablo M.
 */

//To be comatible with Lib_API_CAPI & Lib_MCU_176x
#include "UART.h"
#include "lpc_176X_PeriphNames.h"	//Lib_MCU_LPC176x

//To be compatible with FreeRTOS
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"


/*Defines*/
#define TRACE_UART_CONSOLE	UART_3

//#define USE_TRACE_KERNEL_DATA_PACKET

#define TRACE_KERNEL_DATA_PREFIX "kernel__"
#define TRACE_TASK_DATA_PREFIX "Task____"

#define TRACE_KERNEL_EVTTASKCREATED 0x0
#define TRACE_KERNEL_EVTTICKS 0x1

#define TRACE_TASK_EVTSWITCHOUT 0x0
#define TRACE_TASK_EVTSWITCHIN 0x1

UART trace_console;

/*Private Structures*/
typedef struct _TRACE_TASK_DATA_PACKET{
	char prefix[9];
	union{
		long tick;
		struct{
			char tick_ll;
			char tick_lh;
			char tick_hl;
			char tick_hh;
		};
	};
	char task[configMAX_TASK_NAME_LEN+1];
	char event;
	union{
		long stackwatermark;
		struct{
			char stack_ll;
			char stack_lh;
			char stack_hl;
			char stack_hh;
		};
	};
}TRACE_TASK_DATA_PACKET;

typedef struct _TRACE_KERNEL_DATA_PACKET{
	char prefix[9];
	union{
		long tick;
		struct{
			char tick_ll;
			char tick_lh;
			char tick_hl;
			char tick_hh;
		};
	};
	char event;
	char task[configMAX_TASK_NAME_LEN+1];
}TRACE_KERNEL_DATA_PACKET;

/*Private functions*/
void vMemCopy_N_Bytes(char * strSrc, char * strDst, unsigned int n)
{
	unsigned int i = 0;
	do{
		strDst[i] = strSrc[i];
		i++;
	}while(--n);

}

void vNumToChar_10Char(int num, char * ptr)
{
	do{
		*ptr = ((num%10)+0x30);
		num /=10;
		ptr++;
	}while(num);
}

bool bSendKernelPacketToUART(UART * uart, TRACE_KERNEL_DATA_PACKET * data)
{
	int status = 0;
	char buff[11]="0000000000";


	//if( UARTputs(&trace_console,"Kernel-EVT\r\n") == CAPI_ERROR)	status--;
	//if( UARTputs(&trace_console,"TS:") == CAPI_ERROR)	status--;
	//vNumToChar_10Char(data->tick,buff);
	//buff[11]='\0';
	//if( UARTputs(&trace_console,buff) == CAPI_ERROR)	status--;
	//if( UARTputs(&trace_console,"\n\r") == CAPI_ERROR)	status--;

	switch(data->event){
		case TRACE_KERNEL_EVTTASKCREATED:
			if(UARTputs(&trace_console,&data->task[0]) == CAPI_ERROR)	status--;
			if(UARTputs(&trace_console,"<-Create\n\r") == CAPI_ERROR)	status--;
			break;
		case TRACE_KERNEL_EVTTICKS:
			if( UARTputs(&trace_console,"Tick de OS\r\n") == CAPI_ERROR)	status--;
			break;
	}


	if(!status) return 1;
	else	return 0;

}

bool bSendTaskPacketToUART(UART * uart, TRACE_TASK_DATA_PACKET * data)
{
	int status = 0;
	char buff[11]="0000000000";
	char buff2[11]="0000000000";

	//if( UARTputs(&trace_console,"Kernel-EVT\r\n") == CAPI_ERROR)	status--;
	//if( UARTputs(&trace_console,"TS:") == CAPI_ERROR)	status--;
	//vNumToChar_10Char(data->tick,buff);
	//buff[11]='\0';
	//if( UARTputs(&trace_console,buff) == CAPI_ERROR)	status--;
	//if( UARTputs(&trace_console,"\n\r") == CAPI_ERROR)	status--;
	if(UARTputs(&trace_console,&data->task[0]) == CAPI_ERROR)	status--;

	switch(data->event){
		case TRACE_TASK_EVTSWITCHIN:
			if(UARTputs(&trace_console,"<-In\r\n") == CAPI_ERROR)	status--;
			break;
		case TRACE_TASK_EVTSWITCHOUT:
			if( UARTputs(&trace_console,"<-Out\r\n") == CAPI_ERROR)	status--;
			break;
	}

	//vNumToChar_10Char(data->stackwatermark,buff2);
	//buff[11]='\0';
	//if( UARTputs(&trace_console,buff2) == CAPI_ERROR)	status--;
	//if( UARTputs(&trace_console,"\n\r") == CAPI_ERROR)	status--;

	if(!status) return 1;
	else	return 0;

}

/*Trace Functions*/
void vTraceStart(void)
{
	UARTInit(&trace_console, TRACE_UART_CONSOLE, 115200, 8, 'n', 1);
	UARTputs(&trace_console, "Trace Log FreeRTOS\r\n");
}

void vTraceStop(void)
{
	UARTDeInit(&trace_console);
}


void vTraceEvtTaskCreated(signed char * tskName)
{
	TRACE_KERNEL_DATA_PACKET data;

	/*Packet arrange*/
	vMemCopy_N_Bytes(TRACE_KERNEL_DATA_PREFIX,&data.prefix[0],9);
	data.tick = (long)xTaskGetTickCount();
	data.event = TRACE_KERNEL_EVTTASKCREATED;
	vMemCopy_N_Bytes((char *)tskName,&data.task[0],configMAX_TASK_NAME_LEN);
	data.task[configMAX_TASK_NAME_LEN] = '\0';


	bSendKernelPacketToUART(&trace_console,&data);


}

void vTraceEvtTick(long ticks)
{
#ifdef USE_TRACE_KERNEL_DATA_PACKET
	TRACE_KERNEL_DATA_PACKET data;
	unsigned int i;

	/*Packet arrange*/
	vMemCopy_N_Bytes(TRACE_KERNEL_DATA_PREFIX,&data.prefix[0],9);
	data.tick = (long)ticks;
	data.event = TRACE_KERNEL_EVTTICKS;
	i=0;
	do{
		data.task[i]='T';
		i++;
	}while(i<configMAX_TASK_NAME_LEN);
	data.task[configMAX_TASK_NAME_LEN] = '\0';

	bSendKernelPacketToUART(&trace_console,&data);
#endif
}


void vTraceEvtSwitchOut(char * pcTaskName, xTaskHandle pxCurrentTCB)
{
	TRACE_TASK_DATA_PACKET data;

	/*Packet arrange*/
	vMemCopy_N_Bytes(TRACE_TASK_DATA_PREFIX,&data.prefix[0],9);
	data.tick = (long)xTaskGetTickCount();
	vMemCopy_N_Bytes(pcTaskName,&data.task[0],configMAX_TASK_NAME_LEN);
	data.task[configMAX_TASK_NAME_LEN] = '\0';
	data.event = TRACE_TASK_EVTSWITCHOUT;
	data.stackwatermark = uxTaskGetStackHighWaterMark(pxCurrentTCB);

	bSendTaskPacketToUART(&trace_console,&data);

}

void vTraceEvtSwitchIn(char * pcTaskName, xTaskHandle pxCurrentTCB)
{
	TRACE_TASK_DATA_PACKET data;

	/*Packet arrange*/
	vMemCopy_N_Bytes(TRACE_TASK_DATA_PREFIX,&data.prefix[0],9);
	data.tick = (long)xTaskGetTickCount();
	vMemCopy_N_Bytes(pcTaskName,&data.task[0],configMAX_TASK_NAME_LEN);
	data.task[configMAX_TASK_NAME_LEN] = '\0';
	data.event = TRACE_TASK_EVTSWITCHIN;
	data.stackwatermark = uxTaskGetStackHighWaterMark(pxCurrentTCB);

	bSendTaskPacketToUART(&trace_console,&data);

}
