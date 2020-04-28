/*
 * BattleShip.c
 *
 * Created: 2020-04-15 07:49:10
 * Author : maxbo
 */ 


#define FCPU 1000000UL
#include <avr/io.h>
#include <stdio.h>
#include "commands_ftdi.h"
#include "definitions_ftdi.h"
#include "commands_app.h"

int main(void)
{
	spi_masterInit();
	ftdiInit();

// 	wr32_mem(RAM_DL + 12, CLEAR_COLOR_RGB(255, 0, 0));
// 	wr32_mem(RAM_DL + 16, CLEAR(1, 1, 1));
// 	wr32_mem(RAM_DL + 20, DISPLAY());
// 	wr32_mem(REG_DLSWAP, DLSWAP_FRAME);

	coproc_list_begin();
	coproc_dlstart();
	coproc_clear(1, 1, 1);
	coproc_clear(0, 0, 0);

	coproc_color_rgb(255, 0, 0);
	coproc_begin_primitive(POINT);
	coproc_point_size(50*16);
	coproc_vertex2II(20, 100, 0, 0);
	coproc_end();

	coproc_display();
	coproc_swap();

	coproc_list_end();
	
	initGame();
	
	uint8_t selectPointer = 0;
	uint8_t poll = 0;
	while(poll != SEL){
		if (buttonPoll() == R)
		{
			selectPointer++;
		}
		else if(buttonPoll() == L)
		{
			selectPointer--;
		}
		selectPointer = selectPointer%2;
		poll = buttonPoll();
	}
	
	selectGameType(selectPointer);
	
	while (1)
	{
		
	}
}



