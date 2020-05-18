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


/*Board ska vara 10x10 kommer behöva 2st
context_save och Context_restore för att byta plan*/
void initTwoPlayerGame(void){
	public int playerOneBoard[10][10];
	public int playerOneShootBoard[10][10];

	public int playerTwoBoard[10][10];
	public int playerTwoShootBoard[10][10]
	
}
void placeShips{
	int shipType = 0;
	public int cols = 0;
	public int rows = 0;
	for(i = 0; i < NumShips; i++){
	while (buttonPoll != SEL)
	{
		if (cols <= 10 && cols >=0 && rows <= 10 && rows >= 0)
		{
			
		
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
		}
		
	}
	NumShips++;
	if (shipType == 0) {
		playerOneBoard[rows][cols] = 1;
		playerOneBoard[rows][cols + 1] = 1;
		playerOneBoard[rows][cols + 2] = 1;
		playerOneBoard[rows][cols + 3] = 1;
		playerOneBoard[rows][cols + 4] = 1;
		shipType++;
	}
	else if (shipType == 1) {
		playerOneBoard[rows][cols] = 1;
		playerOneBoard[rows][cols + 1] = 1;
		playerOneBoard[rows][cols + 2] = 1;
		playerOneBoard[rows][cols + 3] = 1;
		shipType++;
	}
	else if (shipType == 2) {
		playerOneBoard[rows][cols] = 1;
		playerOneBoard[rows][cols + 1] = 1;
		playerOneBoard[rows][cols + 2] = 1;
		shipType++;
	}
	else if (shipType == 3) {
		playerOneBoard[rows][cols] = 1;
		playerOneBoard[rows][cols + 1] = 1;
		playerOneBoard[rows][cols + 2] = 1;
		shipType++;
	}
	else if (shipType == 4) {
		playerOneBoard[rows][cols] = 1;
		playerOneBoard[rows][cols + 1] = 1;
	}
	}
	/*placera antal skäpp*/
	for (i = 0; i < NumShips; i++) {
		/* sålänge man inte tryckt select så ska den navigera i matrisen*/
		while (buttonPoll != SEL)
		{
			/*nollar cols och rows om man går över/under sålänge*/
			if (cols <= 10 && cols >= 0 && rows <= 10 && rows >= 0)
			{
				

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
			
		}
		NumShips++;
		if (shipType == 0) {
			playerTwoBoard[rows][cols] = 1;
			playerTwoBoard[rows][cols + 1] = 1;
			playerTwoBoard[rows][cols + 2] = 1;
			playerTwoBoard[rows][cols + 3] = 1;
			playerTwoBoard[rows][cols + 4] = 1;
			shipType++;
		}
		else if (shipType == 1) {
			playerTwoBoard[rows][cols] = 1;
			playerTwoBoard[rows][cols + 1] = 1;
			playerTwoBoard[rows][cols + 2] = 1;
			playerTwoBoard[rows][cols + 3] = 1;
			shipType++;
		}
		else if (shipType == 2) {
			playerTwoBoard[rows][cols] = 1;
			playerTwoBoard[rows][cols + 1] = 1;
			playerTwoBoard[rows][cols + 2] = 1;
			shipType++;
		}
		else if (shipType == 3) {
			playerTwoBoard[rows][cols] = 1;
			playerTwoBoard[rows][cols + 1] = 1;
			playerTwoBoard[rows][cols + 2] = 1;
			shipType++;
		}
		else if (shipType == 4) {
			playerTwoBoard[rows][cols] = 1;
			playerTwoBoard[rows][cols + 1] = 1;
		}
	}
}
void shootShips{
	public int winner = 0;
	public int cols = 0;
	public int rows = 0;
	public int playerOneHit = 0;
	public int playerTwoHit = 0;
	bool noWinner = true;
while (noWinner) {
	while (buttonPoll != SEL)
	{
		if (cols <= 10 && cols >= 0 && rows <= 10 && rows >= 0) {
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

	}
	playerOneShootBoard[rows][cols] = 1;
	if (playerOneShotBoard[rows][cols] == 1 && playerTwoBoard[rows][cols] == 1) {
		playerOneHits++;
	}

	while (buttonPoll != SEL)
	{
		if (cols <= 10 && cols >= 0 && rows <= 10 && rows >= 0) {
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

	}
	playerTwoShootBoard[rows][cols] = 1;
	if (playerTwoShotBoard[rows][cols] == 1 && playerOneBoard[rows][cols] == 1) {
		playerTwoHits++;
	}

	if (playerOneHits == 17) {
		winner = 1;
		noWinner = false;
	}
	else if (playerTwoHits == 17) {
		winner = 2;
		noWinner = false;
	}
}
}





#endif /* GAME_ENGINE_H_ */
