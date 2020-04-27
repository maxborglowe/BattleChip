#ifndef COMMANDS_FTDI_H_
#define COMMANDS_FTDI_H_

#define F_CPU 1000000UL /* define ATMEGA16 clock speed for delay.h */

#include "definitions_ftdi.h"
#include <util/delay.h>

/** pointer for the 4k coprocessor FIFO. Starts at 0, since no commands have yet been written to the FIFO*/
uint32_t cmd_offset = 0x00; 

//####################################################################
//				SPI SECTION
//####################################################################

/** Sets the SS_LCD-pin ACTIVE low, place at the start of read/write commands */
void ss_lcd_on(){
	DDRB |= (1<<SS_LCD);
	PORTB &= ~(1<<SS_LCD);
}

/** Sets the SS_LCD-pin INACTIVE high, place at the end of read/write commands */
void ss_lcd_off(){
	DDRB |= (1<<SS_LCD);
	PORTB |= (1<<SS_LCD);
}

/** Initialize MCU as master */
void spi_masterInit(){
	/* Set MOSI, SCK, and SS_LCD as output, all others input */
	DDR_SPI = (1<<MOSI) | (1<<SCK) | (SS_LCD);
	/* Enable SPI, Master, set clock division /16 */
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
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

//####################################################################
//				FTDI BASIC OPERATON SECTION
//####################################################################

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

/** Reads/writes data from/to specified adress in the FTDI RAM */
void adressReadWrite(uint32_t adress, uint8_t rw){
	spi_transmit((uint8_t)(adress>>16) | rw);		/* Send high byte + read/write command */
	spi_transmit((uint8_t)(adress>>8));	
	spi_transmit((uint8_t)(adress));				/* Send low byte */
}

/** read 1 byte of data from a specified adress in the FTDI memory*/
uint8_t rd8(uint32_t adress){
	uint8_t data8 = 0;
	
	ss_lcd_on();
	adressReadWrite(adress, MEM_RD);
	spi_transmit(0x00);							/* Send dummy byte */
	data8 = (uint8_t)(spi_receive(0x00));		/* Receive data while sending dummy byte */
	ss_lcd_off();
	
	return data8;
}

/** read 2 bytes of data from a specified adress in the FTDI memory*/
uint16_t rd16(uint32_t adress){
	uint16_t data16 = 0;
	
	ss_lcd_on();
	adressReadWrite(adress, MEM_RD);
	spi_transmit(0x00);							/* Send dummy byte */
	data16  = (uint8_t)(spi_receive(0x00));		/* Receive low byte while sending dummy byte */
	data16 |= (uint8_t)(spi_receive(0x00)<<8);	/* Receive high byte */
	ss_lcd_off();
	
	return data16;
}

/** read 4 bytes of data from a specified adress in the FTDI memory*/
uint32_t rd32(uint32_t adress){
	uint32_t data32 = 0;
	
	ss_lcd_on();
	adressReadWrite(adress, MEM_RD);
	spi_transmit(0x00);							/* Send dummy byte */
	data32  = (uint8_t)(spi_receive(0x00));		/* Receive low byte while sending dummy byte */
	data32 |= (uint8_t)(spi_receive(0x00)<<8);
	data32 |= (uint8_t)(spi_receive(0x00)<<16);
	data32 |= (uint8_t)(spi_receive(0x00)<<24);	/* Receive high byte */
	ss_lcd_off();
	
	return data32;
}

/** Writes 1 byte of data to a specified adress in the FTDI memory */
uint8_t wr8(uint32_t adress, uint8_t data8){
	ss_lcd_on();
	adressReadWrite(adress, MEM_WR);
	spi_transmit(data8);					/* Send data */
	ss_lcd_off();
}

/** Writes 2 bytes of data to a specified adress in the FTDI memory */
uint16_t wr16(uint32_t adress, uint16_t data16){
	ss_lcd_on();
	adressReadWrite(adress, MEM_WR);
	spi_transmit((uint8_t)(data16));		/* Send low byte */
	spi_transmit((uint8_t)(data16>>8));		/* Send high byte */
	ss_lcd_off();
}

/** Writes 4 bytes of data to a specified adress in the FTDI memory */
uint16_t wr32(uint32_t adress, uint32_t data32){
	ss_lcd_on();
	adressReadWrite(adress, MEM_WR);
	spi_transmit((uint8_t)(data32));		/* Send low byte */
	spi_transmit((uint8_t)(data32>>8));
	spi_transmit((uint8_t)(data32>>16));
	spi_transmit((uint8_t)(data32>>24));	/* Send high byte */
	ss_lcd_off();
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

/** Increment the RAM_DL pointer by increment. Since FIFO entries are 4 bytes wide, the offset is incremented by 4 for each entry.
	The AND operation makes sure that the offset never passes 4095, which is the full range of the FIFO memory */
void inc_cmd_offset(uint8_t increment){
	cmd_offset += increment;
	cmd_offset &= 0x0FFF;
}

/** Initialization sequence from Power Down mode using PDN-pin */
void ftdiInit(void){
	powerOff();
	_delay_ms(6);	/* Minimum delay for power down is 5ms */
	powerOn();
	_delay_ms(25);	/* Minimum delay for power up is 20ms (FT81X_Programmer_Guide, p.12) */
	host_command(CLKEXT, 0x00);
	host_command(CLKSEL, CLK_SPD_DEFAULT);
	host_command(ACTIVE, 0x00);
	_delay_ms(500); /* Min. delay 300ms according to pg. 8: brtchip.com/wp-content/uploads/Support/Documentation/Application_Notes/ICs/EVE/BRT_AN_014_FT81X_Simple_PIC_Library_Examples.pdf */
	
	wr16(REG_HCYCLE, 548);
	wr16(REG_HOFFSET, 43);
	wr16(REG_HSYNC0, 0);
	wr16(REG_HSYNC1, 41);
	wr16(REG_VCYCLE, 292);
	wr16(REG_VOFFSET, 12);
	wr16(REG_VSYNC0, 0);
	wr16(REG_VSYNC1, 10);
	wr8(REG_SWIZZLE, 0);
	wr8(REG_PCLK_POL, 1);
	wr8(REG_CSPREAD, 1);
	wr16(REG_HSIZE, 480);
	wr16(REG_VSIZE, 272);
	
	/* write first display list */
	wr32(RAM_DL + 0, CLEAR_COLOR_RGB(0, 0, 0));
	wr32(RAM_DL + 4, CLEAR(1, 1, 1));
	wr32(RAM_DL + 8, DISPLAY());
	
	wr8(REG_DLSWAP, DLSWAP_FRAME); //display list swap
	
	wr8(REG_GPIO_DIR, 0x80|rd8(REG_GPIO_DIR));
	wr8(REG_GPIO, 0x080|rd8(REG_GPIO)); //enable display bit
	
	wr8(REG_PCLK, 5); //after this display is visible on the LCD
	
	wr8(REG_PWM_DUTY, 0x20); /* Turn on backlight fully*/
}

/** Write 32 bit display list command to RAM_DL */
void dl_command(uint32_t command){
	
}

/** write 32 bit command to co-processor engine FIFO, RAM_CMD */
void coproc_command(uint32_t command){
	uint32_t adress = RAM_CMD + cmd_offset;
	
	wr32(adress, command);
	
	inc_cmd_offset(4);
}

#endif