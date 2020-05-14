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
/*definar lite grejer som kanske används*/
#define Rows 10
#define Cols 10

#define NumShips  5

#define Horizontelt    0
#define Vertikalt      1

#define PlayerOne    0
#define PlayerTwo    1


#define NORTH 0
#define SOUTH 1
#define WEST  2
#define EAST  3

typedef enum {
	CARRIER_L = 5,
	BATTLESHIP_L = 4,
	CRUISER_L = 3,
	SUBMARINE_L = 3,
	DESTROYER_L = 2
} ShipType;

typedef struct watercraft {
	char   symbol;
	short  length;
	char* name;
} WaterCraft;

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
/* en loop jag använde innan, pallar inte ta bort den än*/
void manuallyPlaceShipsOnGameBoard(Cell gameBoard[][Cols], WaterCraft ship[]) {
	int        i = 0, j = 0;
	Coordinate position[5];
	Boolean    isValid = FALSE;

	for (i = 0; i < NumShips; i++) {



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


/*Board ska vara 10x10 kommer behöva 2st
context_save och Context_restore för att byta plan*/
void initTwoPlayerGame(void){
	public int playerOneBoard[10][10];
	public int playerTwoBoard[10][10];
	
}
void placeShips{
	int cols = 0;
	int rows = 0;
	for(i = 0; i < NumShips; i++){
	while (buttonPoll != SEL)
	{
		if (cols <= 10 && cols >=0 && rows <= 10 && rows >= 0)
		{
			for
		
			if (buttonPoll == DN) {
			rows++;
			}
			if else(buttonPoll == UP) {
			rows--;
			}
			if else(buttonPoll == L){
			cols--;
			}
			if else(buttonPoll == R){
			cols++;
			}	


		}
		else
		{
			rows = 0;
			cols = 0;
		}/* placerar en 1:a i matrisen vilket betyder skepp. kommer användas när man skjuter*/
		playerOneBoard[rows][cols] = 1;
	}

	}
	/*placera antal skäpp*/
	for (i = 0; i < NumShips; i++) {
		/* sålänge man inte tryckt select så ska den navigera i matrisen*/
		while (buttonPoll != SEL)
		{/*nollar cols och rows om man går över/under sålänge*/
			if (cols <= 10 && cols >= 0 && rows <= 10 && rows >= 0)
			{
				for

					if (buttonPoll == DN) {
						rows++;
					}
				if else(buttonPoll == UP) {
					rows--;
				}
				if else(buttonPoll == L) {
					cols--;
				}
				if else(buttonPoll == R) {
					cols++;
				}


			}
			else
			{
				rows = 0;
				cols = 0;
			}
			playerTwoBoard[rows][cols] = 1;
		}
	}
}





#endif /* GAME_ENGINE_H_ */
