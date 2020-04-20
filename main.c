/*
 * BattleShip.c
 *
 * Created: 2020-04-15 07:49:10
 * Author : maxbo
 */ 


#define FCPU 1000000UL
#include <avr/io.h>
#include <stdio.h>
#include <definitions_ftdi.h>

int main(void)
{
	spi_masterInit();
	ftdiInit();
	
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
	wr32(RAM_DL+0,CLEAR_COLOR_RGB(0,0,0));
	wr32(RAM_DL+4,CLEAR(1,1,1));
	wr32(RAM_DL+8,DISPLAY());
	
	wr8(REG_DLSWAP,DLSWAP_FRAME);//display list swap
	wr8(REG_GPIO_DIR,0x80 | rd8(REG_GPIO_DIR));
	wr8(REG_GPIO,0x080 | rd8(REG_GPIO));//enable display bit
	
	wr8(REG_PCLK,5);//after this display is visible on the LCD
	
	while (1)
	{
		
	}
}



