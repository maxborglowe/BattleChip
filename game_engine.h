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

/* Init. knappar */
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
	/* spelare 1:s gamebaord, 2D matris*/
	public int playerOneBoard[10][10];
	/* spelare 1:s skjutbana dvs var han/hon skjuter */
	public int playerOneShootBoard[10][10];
	/* samma för spealre 2*/
	public int playerTwoBoard[10][10];
	public int playerTwoShootBoard[10][10]
	
}
void placeShips{
	/* shiptype är en int mellan 0-5 där siffran bestämmer vilket skäpp (längd)  */
	int shipType = 0;
	/* starta länst uppe till vänster i matrisen dvs 0,0 */
	public int cols = 0;
	public int rows = 0;
	/* ska placera 5 skepp dvs numShips*/
	for(i = 0; i < NumShips; i++){
	/* stannar i while loopen så länge man inte trycker select så man kan använda alla andra knappar */
	while (buttonPoll != SEL)
	{
		/* ser till att man håller sig inom matrisen, gåt till 0,0 om man går utanför*/
		if (cols <= 10 && cols >=0 && rows <= 10 && rows >= 0)
		{
			
			/* navigering inom matrisen som bygger på button_poll*/
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
	/*här placeras skeppen ut beroende på type, alla skepp är i sidleds ); */
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
	/* kör while loopen så länge ingen har vunnit*/
while (noWinner) {
	while (buttonPoll != SEL)
	{
		/*samma navigering som i placeShip metoden*/
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
	/*Om spelare 1 skjuter på en plats och den platsen är markerad med ett skepp på spealer 2 så ska det vara en träff*/
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
	/*totalt ska man ha 17 unika träffar för att ha sänkt alla skepp*/
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
