/*
 * ADXL345_Simple.c
 *
 *  Created on: 29/07/2014
 *      Author: Augusto
 */
#include "lpc17xx_i2c.h"
#include "lpc17xx_clkpwr.h"
#include "lpc17xx_pinsel.h"
#include "ADXL345_Simple.h"



static int I2CWrite(uint8_t addr, uint8_t* buf, uint32_t len)
{
	I2C_M_SETUP_Type txsetup;

	txsetup.sl_addr7bit = addr;
	txsetup.tx_data = buf;
	txsetup.tx_length = len;
	txsetup.rx_data = NULL;
	txsetup.rx_length = 0;
	txsetup.retransmissions_max = 1;

	if (I2C_MasterTransferData(LPC_I2C2, &txsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		return (0);
	} else {
		return (-1);
	}
}

static int I2CWriteAndRead(uint8_t addr, uint8_t* buf_wr, uint32_t len_wr, uint8_t* buf_rd, uint32_t len_rd)
{
	I2C_M_SETUP_Type txsetup;

	txsetup.sl_addr7bit = addr;
	txsetup.tx_data = buf_wr;
	txsetup.tx_length = len_wr;
	txsetup.rx_data = buf_rd;
	txsetup.rx_length = len_rd;
	txsetup.retransmissions_max = 1;

	if (I2C_MasterTransferData(LPC_I2C2, &txsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		return (0);
	} else {
		return (-1);
	}
}



void Init_Accel()
{
	Init_I2C2();        // join i2c bus (address optional for master)
	uint8_t data [2];

	//Put the ADXL345 into +/- 4G range by writing the value 0x01 to the DATA_FORMAT register.
	data[0]=DATA_FORMAT;
	data[1]=0x01;
	I2CWrite(ADDR_DEVICE, data, strlen(data));
	//writeTo(DATA_FORMAT, 0x01);

	//Put the ADXL345 into Measurement Mode by writing 0x08 to the POWER_CTL register.
	data[0]=POWER_CTL;
	data[1]=0x08;
	I2CWrite(ADDR_DEVICE, data, strlen(data));
	//writeTo(POWER_CTL, 0x08);

	data[0]=INT_ENABLE;
	data[1]=0x80;
	I2CWrite(ADDR_DEVICE, data, strlen(data));
}

void Init_I2C2(){
		PINSEL_CFG_Type PinCfg;

		/* Initialize I2C2 pin connect */
		PinCfg.Funcnum = 2;
		PinCfg.Pinnum = 10;
		PinCfg.Portnum = 0;
		PINSEL_ConfigPin(&PinCfg);
		PinCfg.Pinnum = 11;
		PINSEL_ConfigPin(&PinCfg);

		// Initialize I2C peripheral
		I2C_Init(LPC_I2C2, 100000);

		/* Enable I2C2 operation */
		I2C_Cmd(LPC_I2C2, ENABLE);
}
/*
void writeTo(uint8_t address, uint8_t val) {

	//LPC_I2C_TypeDef LPC_I2C2;
	LPC_I2C2.I2ADR0 = ADDR_DEVICE;

	I2C_Start (LPC_I2C2);				// start transmission to device
	I2C_SendByte (LPC_I2C2, address);	// send register address
	I2C_SendByte (LPC_I2C2, val);		// send value to write
	I2C_Stop (LPC_I2C2);				// end transmission
}
*/

void readAccelSimple(int* ejes_xyz) {

	uint8_t buf_wr[1];
	buf_wr[0] = DATAX0;
	uint8_t buf_rd[6];

	I2CWriteAndRead(ADDR_DEVICE, buf_wr, strlen(buf_wr), buf_rd, strlen(buf_rd));//read the acceleration data from the ADXL345

	// each axis reading comes in 10 bit resolution, ie 2 bytes.  Least Significat Byte first!!
	// thus we are converting both bytes in to one int
	ejes_xyz[0] = (((int)buf_rd[1]) << 8) | buf_rd[0];
	ejes_xyz[1] = (((int)buf_rd[3]) << 8) | buf_rd[2];
	ejes_xyz[2] = (((int)buf_rd[5]) << 8) | buf_rd[4];


}
/*
void readAccel() {
  uint8_t howManyBytesToRead = 6;

  readFrom( DATAX0, howManyBytesToRead, _buff); //read the acceleration data from the ADXL345

  // each axis reading comes in 10 bit resolution, ie 2 bytes.  Least Significat Byte first!!
  // thus we are converting both bytes in to one int
  int x = (((int)_buff[1]) << 8) | _buff[0];
  int y = (((int)_buff[3]) << 8) | _buff[2];
  int z = (((int)_buff[5]) << 8) | _buff[4];
  //Serial.print("x: ");
  //Serial.print( x );
  //Serial.print(" y: ");
  //Serial.print( y );
  //Serial.print(" z: ");
  //Serial.println( z );

}
*/


/*
void readFrom(uint8_t address, int num, uint8_t _buff[]) {
	//LPC_I2C_TypeDef LPC_I2C2;
	LPC_I2C2.I2ADR0 = ADDR_DEVICE;

	I2C_Start (LPC_I2C2);				// start transmission to device
	I2C_SendByte (LPC_I2C2, address);             // sends address to read from
	I2C_Stop (LPC_I2C2);         // end transmission

	I2C_Start (LPC_I2C2);				// start transmission to device
	I2C_GetByte (LPC_I2C2, uint8_t *retdat, 1);
	Wire.requestFrom(DEVICE, num);    // request 6 bytes from device

  int i = 0;
  while(Wire.available())         // device may send less than requested (abnormal)
  {
    _buff[i] = Wire.read();    // receive a byte
    i++;
  }
  Wire.endTransmission();         // end transmission
}
*/
