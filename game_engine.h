/*
 * game_engine.h
 *
 * Created: 2020-04-28 07:16:59
 *  Author: maxbo
 */ 

#include "definitions_ftdi"
#include "commands_ftdi.h"

#ifndef GAME_ENGINE_H_
#define GAME_ENGINE_H_

uint8_t DN = 1, UP = 2, L = 4, R = 8, SEL = 16;

void buttonInit()
{
	DDR_BUTTONS = 0x00; /* Set DDR of I/O bus A to INPUT */
}

void buttonPoll(void)
{
	switch (PIN_BUTTONS)
	{
		case BTN_DN: return DN;
		
		case BTN_UP: return UP;
		
		case BTN_L: return L;
		
		case BTN_R: return R;
		
		case BTN_SEL: return SEL;
	}
} 



void selectGameType(uint8_t game_type){
	if (game_type == 0)
	{
		initTwoPlayerGame();
	}
	else{
		initFreeForAll();
	}
}



void initTwoPlayerGame(void){
	
}

void initFreeForAll(void){
	
}

void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color, uint8_t width)
{
	
}


void drawSquare()
{
	
}


#endif /* GAME_ENGINE_H_ */