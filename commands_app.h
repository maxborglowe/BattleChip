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
uint16_t cmd_offset = 0x0000;
uint32_t dl_offset = RAM_DL;

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
	
	while(rd8_mem(REG_ID) != 0x7C){
	}
	
	while(rd8_mem(REG_CPURESET) != 0x00){
	}
	
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
	
	wr8_mem(REG_PWM_DUTY, 50); /* Turn off backlight */
	
	/* write first display list */
	wr32_mem(RAM_DL + 0, CLEAR(1, 1, 1));
	wr32_mem(RAM_DL + 4, CLEAR_COLOR_RGB(0, 0, 200));
	wr32_mem(RAM_DL + 8, DISPLAY());
	
	wr8_mem(REG_DLSWAP, DLSWAP_FRAME); //display list swap
	
	wr8_mem(REG_GPIO_DIR, 0x80|rd8_mem(REG_GPIO_DIR));
	wr8_mem(REG_GPIO, 0x080|rd8_mem(REG_GPIO)); //enable display bit
	
	wr8_mem(REG_PCLK, 5); //after this display is visible on the LCD
}

/** write 32 bit command to co-processor engine FIFO, RAM_CMD */
void coproc_list_begin(void){
	cmd_offset = eve_waitFifoEmpty();
	
	ss_lcd_on();
	adressWrite(RAM_CMD + cmd_offset);
}

void coproc_list_end(void){
	ss_lcd_off();
	wr32_mem(REG_CMD_WRITE, (cmd_offset));
	cmd_offset = eve_waitFifoEmpty();s
}

void coproc_begin_primitive(uint8_t primitive){
	wr32_eve(BEGIN(primitive));
	inc_cmd_offset(4);
}

void coproc_color_rgb(uint8_t red, uint8_t green, uint8_t blue){
	wr32_eve(COLOR_RGB(red, green, blue));
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

void coproc_display(void){
	wr32_eve(DISPLAY());
	inc_cmd_offset(4);
}

void coproc_dlstart(void){
	wr32_eve(CMD_DLSTART);
	inc_cmd_offset(4);
}

void coproc_end(void){
	wr32_eve(END());
	inc_cmd_offset(4);
}

coproc_clear_color_rgb(uint8_t red, uint8_t green, uint8_t blue){
	wr32_eve(CLEAR_COLOR_RGB(red, green, blue));
	inc_cmd_offset(4);
}

void coproc_point_size(uint16_t point_size){
	wr32_eve(POINT_SIZE(point_size));
	inc_cmd_offset(4);
}

void coproc_clear(uint8_t c, uint8_t s, uint8_t t){
	wr32_eve(CLEAR(c, s, t));
	inc_cmd_offset(4);
}

/** Swap the current display list */
void coproc_swap(void){
	wr32_eve(CMD_SWAP);
	inc_cmd_offset(4);
}



#endif /* COMMANDS_APP_H_ */
