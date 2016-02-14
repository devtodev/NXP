/*
 * ADXL345_simple.h
 *
 *  Created on: 29/07/2014
 *      Author: Augusto
 */

#ifndef ADXL345_SIMPLE_H_
#define ADXL345_SIMPLE_H_

#define ADDR_DEVICE (0x53) // Device address as specified in data sheet


//byte _buff[6];

#define INT_ENABLE 	0x2E //Interrupt enable control
#define POWER_CTL 	0x2D	//Power Control Register
#define DATA_FORMAT 0x31
#define DATAX0 0x32	//X-Axis Data 0
#define DATAX1 0x33	//X-Axis Data 1
#define DATAY0 0x34	//Y-Axis Data 0
#define DATAY1 0x35	//Y-Axis Data 1
#define DATAZ0 0x36	//Z-Axis Data 0
#define DATAZ1 0x37	//Z-Axis Data 1


void Init_Accel(void);
void Init_I2C2(void);
void readAccelSimple(int*);


void writeTo(uint8_t, uint8_t);
void readAccel(void);
void readFrom(uint8_t, int, uint8_t);


#endif /* ADXL345_SIMPLE_H_ */
