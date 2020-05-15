#ifndef COMMANDS_FTDI_H_
#define COMMANDS_FTDI_H_

#define F_CPU 1000000UL /* define ATMEGA16 clock speed for delay.h */

#include "definitions_ftdi.h"
#include <util/delay.h>

//####################################################################
//				MCU SECTION
//####################################################################


/** Initialize MCU as master */
void spi_masterInit(){
	/* Set MOSI, SCK, and SS_LCD as output, all others input */
	DDR_SPI = (1<<MOSI) | (1<<SCK) | (1<<SS_LCD);
	/* Enable SPI, Master, set clock division /16 */
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
}

/** Sets the SS_LCD pin ACTIVE low, place at the start of read/write commands */
void ss_lcd_on(){
	PORTB &= ~(1<<SS_LCD);
	//Nop() is placed to compensate for the SPI access time Tsac, as shown in fig 6.4.2 (SPI interface timing) in DS_FT81x.pdf
	nop();
}

/** Sets the SS_LCD pin INACTIVE high, place at the end of read/write commands */
void ss_lcd_off(){
	
	//Nop() is placed to compensate for the SS hold time Tcsnh, as shown in fig 6.4.2 (SPI interface timing) in DS_FT81x.pdf
	nop();
	PORTB |= (1<<SS_LCD);
}

/** Master transmit data to slave via SPI */
void spi_transmit(uint8_t data){
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission to complete */
	while(!(SPSR & (1<<SPIF)));
}

/** Master receive data from slave via SPI */
uint8_t spi_receive(uint8_t dummy){
	uint8_t readData = 0;
	
	SPDR = dummy;
	/* Wait for reception to complete */
	while(!(SPSR & (1<<SPIF)));
	/* Return SPI data register */
	readData = SPDR;
	return readData;
}

/** Sets the PDN-pin INACTIVE high */
void powerOn(){
	DDRB |= (1<<PDN);
	PORTB |= (1<<PDN);
}

/** Sets the PDN-pin ACTIVE low */
void powerOff(){
	DDRB |= (1<<PDN);
	PORTB &= ~(1<<PDN);
}

//####################################################################
//				FTDI TRANSPORT SECTION
//####################################################################

/** Writes data to specified adress in the FTDI RAM */
void adressWrite(uint32_t adress){
	spi_transmit((uint8_t)(adress>>16) | MEM_WR);		/* Send high byte + write command */
	spi_transmit((uint8_t)(adress>>8));	
	spi_transmit((uint8_t)(adress));					/* Send low byte */
}

/** Reads data from specified adress in the FTDI RAM */
void adressRead(uint32_t adress){
	spi_transmit((uint8_t)(adress>>16) | MEM_RD);		/* Send high byte + read command */
	spi_transmit((uint8_t)(adress>>8));
	spi_transmit((uint8_t)(adress));					/* Send low byte */
	spi_transmit(0x00);									/* Send dummy byte */
}

/** read 1 byte of data from a specified adress in the FTDI memory*/
uint8_t rd8_mem(uint32_t adress){
	uint8_t data8 = 0;
	
	ss_lcd_on();
	adressRead(adress);
	data8 = (uint8_t)(spi_receive(0x00));		/* Receive data while sending dummy byte */
	ss_lcd_off();
	
	return data8;
}

/** read 2 bytes of data from a specified adress in the FTDI memory*/
uint16_t rd16_mem(uint32_t adress){
	uint16_t data16 = 0;
	
	ss_lcd_on();
	adressRead(adress);
	data16  = (uint8_t)(spi_receive(0x00));		/* Receive low byte while sending dummy byte */
	data16 |= (uint8_t)(spi_receive(0x00)<<8);	/* Receive high byte */
	ss_lcd_off();
	
	return data16;
}

/** read 4 bytes of data from a specified adress in the FTDI memory*/
uint32_t rd32_mem(uint32_t adress){
	uint32_t data32 = 0;
	
	ss_lcd_on();
	adressRead(adress);
	data32  = (uint8_t)(spi_receive(0x00));		/* Receive low byte while sending dummy byte */
	data32 |= (uint8_t)(spi_receive(0x00)<<8);
	data32 |= (uint8_t)(spi_receive(0x00)<<16);
	data32 |= (uint8_t)(spi_receive(0x00)<<24);	/* Receive high byte */
	ss_lcd_off();
	
	return data32;
}

/** Writes 1 byte of data to a specified adress in the FTDI memory */
uint8_t wr8_mem(uint32_t adress, uint8_t data8){
	ss_lcd_on();
	adressWrite(adress);
	spi_transmit(data8);					/* Send data */
	ss_lcd_off();
}

/** Writes 2 bytes of data to a specified adress in the FTDI memory */
uint16_t wr16_mem(uint32_t adress, uint16_t data16){
	ss_lcd_on();
	adressWrite(adress);
	spi_transmit((uint8_t)(data16));		/* Send low byte */
	spi_transmit((uint8_t)(data16>>8));		/* Send high byte */
	ss_lcd_off();
}

/** Writes 4 bytes of data to a specified adress in the FTDI memory */
uint16_t wr32_mem(uint32_t adress, uint32_t data32){
	ss_lcd_on();
	adressWrite(adress);
	spi_transmit((uint8_t)(data32));		/* Send low byte */
	spi_transmit((uint8_t)(data32>>8));
	spi_transmit((uint8_t)(data32>>16));
	spi_transmit((uint8_t)(data32>>24));	/* Send high byte */
	ss_lcd_off();
}

//####################################################################
//				EVE TRANSPORT SECTION
//####################################################################

/** read 1 bytes of data from EVE */
uint8_t rd8_eve(uint32_t adress){
	uint8_t data8 = 0x00;

	data8 = (uint8_t)(spi_receive(0x00));		/* Receive data while sending dummy byte */

	return data8;
}

/** read 2 bytes of data from EVE */
uint16_t rd16_eve(uint32_t adress){
	uint16_t data16 = 0x0000;
	
	data16  = (uint8_t)(spi_receive(0x00));		/* Receive low byte while sending dummy byte */
	data16 |= (uint8_t)(spi_receive(0x00)<<8);	/* Receive high byte */
	
	return data16;
}

/** read 4 bytes of data from EVE */
uint32_t rd32_eve(uint32_t adress){
	uint32_t data32 = 0x00000000;

	data32  = (uint8_t)(spi_receive(0x00));		/* Receive low byte while sending dummy byte */
	data32 |= (uint8_t)(spi_receive(0x00)<<8);
	data32 |= (uint8_t)(spi_receive(0x00)<<16);
	data32 |= (uint8_t)(spi_receive(0x00)<<24);	/* Receive high byte */

	return data32;
}

/** Writes 1 byte of data to EVE (used in copro_command) */
uint8_t wr8_eve(uint8_t data8){

	spi_transmit(data8);					/* Send data */

}

/** Writes 2 byte of data to EVE (used in copro_command) */
uint16_t wr16_eve(uint16_t data16){

	spi_transmit((uint8_t)(data16));		/* Send low byte */
	spi_transmit((uint8_t)(data16>>8));		/* Send high byte */

}

/** Writes 4 byte of data to EVE (used in copro_command) */
uint16_t wr32_eve(uint32_t data32){

	spi_transmit((uint8_t)(data32));		/* Send low byte */
	spi_transmit((uint8_t)(data32>>8));
	spi_transmit((uint8_t)(data32>>16));
	spi_transmit((uint8_t)(data32>>24));	/* Send high byte */

}

//####################################################################
//				FTDI COMMAND SECTION
//####################################################################

void host_command(uint8_t command, uint8_t parameter){
	ss_lcd_on();
	spi_transmit(command);
	spi_transmit(parameter);
	spi_transmit(0x00);
	ss_lcd_off();
}

uint8_t eve_waitFifoEmpty(void){
	uint16_t rd_ptr, wr_ptr;
	
	do{
		rd_ptr = rd16_mem(REG_CMD_READ);
		wr_ptr = rd16_mem(REG_CMD_WRITE);
	}while((rd_ptr != wr_ptr) && (rd_ptr != 0xFFF));
	
	if (rd_ptr == 0xFFF)
	{
		return 0xFF;
	}
	else{
		return 0;
	}
}

/** Return the current position of the EVE write pointer */
uint32_t eve_getWritePtr(){
	uint32_t wr_ptr = rd32_mem(REG_CMD_WRITE);
	return wr_ptr;
}

#endif
