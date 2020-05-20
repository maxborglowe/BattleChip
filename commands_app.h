/*
 * commands_app.h
 *
 * Created: 2020-04-28 07:33:35
 *  Author: maxbo
 */ 

#include "definitions_ftdi.h"
#include "commands_ftdi.h"

#ifndef COMMANDS_APP_H_
#define COMMANDS_APP_H_

/** pointer for the 4k coprocessor FIFO. Starts at 0, since no commands have yet been written to the FIFO*/
uint16_t cmd_offset = RAM_CMD;
uint32_t dl_offset = RAM_DL;

/** Increment the RAM_CMD pointer by increment. Since FIFO entries are 4 bytes wide, the offset is incremented by 4 for each entry.
	The AND operation makes sure that the offset never passes 4095, which is the full range of the FIFO circular buffer */
void inc_cmd_offset(uint8_t increment){
	cmd_offset += increment;
	cmd_offset &= 0x0FFF; //decimal 4095
}

/** Increment the RAM_DL pointer by increment. Since FIFO entries are 4 bytes wide, the offset is incremented by 4 for each entry.
	The AND operation makes sure that the offset never passes 8191, which is the full range of the FIFO circular buffer */
void inc_dl_offset(uint8_t increment){
	dl_offset += increment;
	dl_offset &= 0xFFFF; //decimal 8191
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
	_delay_ms(500); /* Min. delay 300ms to let the processor do some housekeeping, 
			according to pg. 8: brtchip.com/wp-content/uploads/Support/Documentation/Application_Notes/ICs/EVE/BRT_AN_014_FT81X_Simple_PIC_Library_Examples.pdf */
	
	//Reads the chip ID and continues ID is correct
	readChipID();
	
	//waits for reset
	waitForReset();
	
	wr16_mem(REG_HCYCLE, 548);
	wr16_mem(REG_HOFFSET, 43);
	wr16_mem(REG_HSYNC0, 0);
	wr16_mem(REG_HSYNC1, 41);
	wr16_mem(REG_VCYCLE, 292);
	wr16_mem(REG_VOFFSET, 12);
	wr16_mem(REG_VSYNC0, 0);
	wr16_mem(REG_VSYNC1, 10);
	wr8_mem(REG_SWIZZLE, 0);
	wr8_mem(REG_PCLK_POL, 1);
	wr8_mem(REG_CSPREAD, 1);
	wr16_mem(REG_HSIZE, 480);
	wr16_mem(REG_VSIZE, 272);
	
	wr8_mem(REG_PWM_DUTY, 100);
	wr8_mem(REG_PWM_HZ, 1000);
	
	/* write first display list */
	
	dl_offset = RAM_DL;
	wr32_mem(dl_offset, CLEAR(1, 1, 1));
	inc_dl_offset(4);
	wr32_mem(dl_offset, CLEAR_COLOR_RGB(0, 0, 0));
	inc_dl_offset(4);
	wr32_mem(dl_offset, DISPLAY());
	
	wr8_mem(REG_DLSWAP, DLSWAP_FRAME); //display list swap
	
	wr8_mem(REG_PCLK, 5); //after this display is visible on the LCD
}

/** start writing burst commands to the RAM FIFO */
void coproc_list_begin(void){
	waitFifoEmpty();
	cmd_offset = getWritePtr();
	ss_lcd_on();
	adressWrite(RAM_CMD + cmd_offset);
}

/** End of previously started burst command to the RAM FIFO*/
void coproc_list_end(void){
	ss_lcd_off();
	wr32_mem(REG_CMD_WRITE, cmd_offset);
	waitFifoEmpty();
}

/** Draw graphic primitive. See definitions_ftdi.h for available primitives. */
void coproc_begin_primitive(uint8_t primitive){
	wr32_eve(BEGIN(primitive));
	inc_cmd_offset(4);
}

void coproc_color_rgb(uint8_t red, uint8_t green, uint8_t blue){
	wr32_eve(COLOR_RGB(red, green, blue));
	inc_cmd_offset(4);
}


void coproc_vertex_format(uint8_t frac){
	wr32_eve(VERTEX_FORMAT(frac));
	inc_cmd_offset(4);
}

void coproc_vertex2F(uint16_t x, uint16_t y){
	wr32_eve(VERTEX2F(x, y));
	inc_cmd_offset(4);
}

void coproc_vertex2II(uint16_t x, uint16_t y, uint8_t handle, uint8_t cell){
	wr32_eve(VERTEX2II(x, y, handle, cell));
	inc_cmd_offset(4);
}

void coproc_line_width(uint16_t width){
	wr32_eve(LINE_WIDTH(width));
	inc_cmd_offset(4);
}

/** End of display list. NOTE: Programmed graphics isn't drawn on-screen until coproc_swap is executed */
void coproc_display(void){
	wr32_eve(DISPLAY());
	inc_cmd_offset(4);
}

/** Co-processor starts new display list */
void coproc_dlstart(void){
	wr32_eve(CMD_DLSTART);
	inc_cmd_offset(4);
}

/** Finish drawing graphics primitive */
void coproc_end(void){
	wr32_eve(END());
	inc_cmd_offset(4);
}

/** Clear the screen to chosen color */
coproc_clear_color_rgb(uint8_t red, uint8_t green, uint8_t blue){
	wr32_eve(CLEAR_COLOR_RGB(red, green, blue));
	inc_cmd_offset(4);
}

/** Set width of point primitive */
void coproc_point_size(uint16_t point_size){
	wr32_eve(POINT_SIZE(point_size));
	inc_cmd_offset(4);
}

/** Clear color, stencil, and tag buffer */
void coproc_clear(uint8_t c, uint8_t s, uint8_t t){
	wr32_eve(CLEAR(c, s, t));
	inc_cmd_offset(4);
}

/** Swap the current display list to print the programmed graphics on-screen */
void coproc_swap(void){
	wr32_eve(CMD_SWAP);
	inc_cmd_offset(4);
}

/** Poll the read/write pointers REG_CMD_READ and REG_CMD_WRITE until they are equal, meaning the RAM FIFO is empty */
uint8_t waitFifoEmpty(void){
	uint16_t rd_ptr, wr_ptr;
	
	do{
		rd_ptr = rd16_mem(REG_CMD_READ); //Read Read pointer value in fifo
		wr_ptr = rd16_mem(REG_CMD_WRITE); //Read Write pointer value in fifo
	}while((rd_ptr != wr_ptr) && (rd_ptr != 0xFFF)); //Wait for pointers to reach matching values
	
	if (rd_ptr == 0xFFF) //error detection
	{
		return 0xFF;
	}
	else{			//successful matching pointer values
		return 0;
	}
}

/** Return the current position of the EVE write pointer */
uint32_t getWritePtr(void){
	uint32_t wr_ptr = rd32_mem(REG_CMD_WRITE);
	return wr_ptr;
}

/** Wait for CPU reset */
void waitForReset(void){
	while(rd8_mem(REG_CPURESET) != 0x00){
	}
}

/** Checks the chip ID. If 0x7C is read, the chip corresponds the Bridgetech FT812 */
void readChipID(void){
	while(rd8_mem(REG_ID) != 0x7C){
	}
}
		 
void checkFreeSpace(uint16_t offset){
	uint16_t howfull, free;
	uint32_t rdPtr = 0;
	
	rdPtr = rd32_mem(REG_CMD_READ);
	howfull = ((offset - (uint16_t rdPtr) & 4095);
	free = (4096 - 4) - howfull;
		return free;
}


#endif /* COMMANDS_APP_H_ */
