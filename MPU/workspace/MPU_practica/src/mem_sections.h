/*
 * mem_sections.h
 *
 *  Created on: 25/04/2013
 *      Author: PR
 */

#ifndef MEM_SECTIONS_H_
#define MEM_SECTIONS_H_

#include "mpu.h"

/* Code memory */
#define CODE_MEMORY_1		0x000004000
#define CODE_MEMORY_1_LEN	0x00080000	/* 512k */
#define CODE_MEMORY_1_NAME	".Flash"

#define CODE_MEMORY_2		0x1B000000
#define CODE_MEMORY_2_LEN	0x00080000	/* 512k */
#define CODE_MEMORY_2_NAME	".Flash2"

/* User global variables */
#define USER_RAM 			0x10000000
#define USER_RAM_SIZE 		0x4000		/* 16k */
#define USER_RAM_NAME		".data.$RAM"

/* User heap */
#define USER_HEAP			0x10004000
#define	USER_HEAP_SIZE		0x4000		/* 16k */
#define USER_HEAP_NAME		".data.$RAM"

/* M0 Core RAM */
#define CORE_M0_RAM			0x10080000
#define CORE_M0_RAM_SIZE	0xA000
#define CORE_M0_RAM_NAME	".data.$RAM2"

/* User stacks */
#define USER_STACKS 		0x20000000
#define USER_STACKS_SIZE	0x8000		/* 32k */
#define USER_STACKS_NAME	".data.$RAM3"

/* Kernel global variables and stack */
#define KERNEL_RAM 			0x20008000
#define KERNEL_RAM_SIZE 	0x4000		/* 16k */
#define KERNEL_RAM_NAME		".data.$RAM4"

/* Kernel heap */
#define KERNEL_HEAP			0x2000C000
#define	KERNEL_HEAP_SIZE	0x4000		/* 16k */
#define KERNEL_HEAP_NAME	".data.$RAM5"

/* Peripherals */
#define PERIPH_REGION		0x40000000
#define PERIPH_REGION_SIZE	0x20000000


#endif /* MEM_SECTIONS_H_ */
