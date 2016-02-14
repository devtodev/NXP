/*
===============================================================================
 Name        : MPU_practica.c
 Author      : Carlos Miguens
 Version     :
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include "mpu.h"
// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {

	//Activate MemFault, UsageFault and BusFault handlers
	SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk | SCB_SHCSR_USGFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk;

    // TODO: insert code here
	//MPU
	mpuSetup();


    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}
