/*
 * game_engine.h
 *
 * Created: 2020-04-28 07:16:59
 *  Author: maxbo
 */ 

#include "definitions_ftdi"
#include "commands_ftdi.h"
#include <stdbool.h>

#ifndef GAME_ENGINE_H_
#define GAME_ENGINE_H_

#define DDR_BUTTONS DDRA
#define PIN_BUTTONS PINA
#define BTN_UP PA0
#define BTN_DN PA1
#define BTN_L PA2
#define BTN_R PA3
#define BTN_SEL PA4

uint8_t DN = 1, UP = 2, L = 4, R = 8, SEL = 16;

/** definar lite grejer som kanske används */
#define Rows 10
#define Cols 10

#define NumShips  5

public int playerOneBoard[][];
public int playerOneShootBoard[][];

public int playerTwoBoard[][];
public int playerTwoShootBoard[][]

	int winner = 0;
	public int colSel = 0;
	public int rowSel = 0;
	int playerOneHit = 0;
	int playerTwoHit = 0;
	public bool toggle;
	public bool setup;
	public int shipType = 0;
	public int turn = 0;
	
	bool noWinner = true;
	
void buttonInit()
{
	DDR_BUTTONS = 0x00; /* Set DDR of I/O bus A to INPUT */
}


/** Polls the five pushbuttons */
void buttonPoll(void)
{
	switch (PIN_BUTTONS)
	{
		case BTN_DN: return DN;
		
		case BTN_UP: return UP;
			
		case BTN_L: return L;
		
		case BTN_R: return R;
		
		case BTN_SEL: return SEL;
			
		//debouncing delay
		_delay_ms(100);
	}
}

void selectGameType(uint8_t game_type){
	if (game_type == 0)
	{
		initTwoPlayerGame();
	}
// 	else{
// 		initFreeForAll();
// 	}
}

/** Initialize game boards.
	player...Board = an overview of each player's own placement of ships on the board. 1 = ship placed, 0 = no ship placed
	player...shootBoard = represents each player's hit board = overview of which parts of the board that the player has shot at.  */
void initTwoPlayerGame(void){
	playerOneBoard[Rows][Cols];
	playerOneShootBoard[Rows][Cols];

	playerTwoBoard[Rows][Cols];
	playerTwoShootBoard[Rows][Cols];
}

/** Waits for player to press the select button */
void waitForSelect(void){
	
	while (buttonPoll != SEL)
	{
		if(buttonPoll == L) {
			colSel = (colSel - 1)%Cols;
			drawCursor();					//drawCursor() is placed in the if-satsers so as not to draw unless a button is pushed :)
		}
		else if(buttonPoll == R) {
			colSel = (colSel + 1)%Cols;
			drawCursor();
		}
		if (buttonPoll == DN) {
			rowSel = (rowSel + 1)%Rows;
			drawCursor();
		}
		else if(buttonPoll == UP) {
			rowSel = (rowSel - 1)%Rows;
			drawCursor();
		}
		
		//pushing left and right simultaneously generates a toggle which is used when toggling between friendly and shoot boards
		if(buttonPoll() == L + R){
			toggle != toggle;
		}
	}
}

/** Let players place ships on their boards, starting with player 1 */
void placeShips{
	int colSel = 0;
	int rowSel = 0;
	setup = true;
	
	//player 2
	for(int i = 0; i < NumShips; i++){
		
		waitForSelect();
		
		NumShips++;
		if (shipType == 0) {
			playerOneBoard[rowSel][colSel] = 1;
			playerOneBoard[rowSel][colSel + 1] = 1;
			playerOneBoard[rowSel][colSel + 2] = 1;
			playerOneBoard[rowSel][colSel + 3] = 1;
			playerOneBoard[rowSel][colSel + 4] = 1;
			shipType++;
			
		}
		
		else if (shipType == 1) {
			playerOneBoard[rowSel][colSel] = 1;
			playerOneBoard[rowSel][colSel + 1] = 1;
			playerOneBoard[rowSel][colSel + 2] = 1;
			playerOneBoard[rowSel][colSel + 3] = 1;
			shipType++;
		}
		
		else if (shipType == 2) {
			playerOneBoard[rowSel][colSel] = 1;
			playerOneBoard[rowSel][colSel + 1] = 1;
			playerOneBoard[rowSel][colSel + 2] = 1;
			shipType++;
		}
		
		else if (shipType == 3) {
			playerOneBoard[rowSel][colSel] = 1;
			playerOneBoard[rowSel][colSel + 1] = 1;
			playerOneBoard[rowSel][colSel + 2] = 1;
			shipType++;
		}
		else if (shipType == 4) {
			playerOneBoard[rowSel][colSel] = 1;
			playerOneBoard[rowSel][colSel + 1] = 1;
			shipType = 0;
		}
		drawBoard();
	}
	
	//player 2
	for (int i = 0; i < NumShips; i++) {
		
		waitForSelect();
		
		NumShips++;
		if (shipType == 0) {
			playerTwoBoard[rowSel][colSel] = 1;
			playerTwoBoard[rowSel][colSel + 1] = 1;
			playerTwoBoard[rowSel][colSel + 2] = 1;
			playerTwoBoard[rowSel][colSel + 3] = 1;
			playerTwoBoard[rowSel][colSel + 4] = 1;
			shipType++;
		}
		else if (shipType == 1) {
			playerTwoBoard[rowSel][colSel] = 1;
			playerTwoBoard[rowSel][colSel + 1] = 1;
			playerTwoBoard[rowSel][colSel + 2] = 1;
			playerTwoBoard[rowSel][colSel + 3] = 1;
			shipType++;
		}
		else if (shipType == 2) {
			playerTwoBoard[rowSel][colSel] = 1;
			playerTwoBoard[rowSel][colSel + 1] = 1;
			playerTwoBoard[rowSel][colSel + 2] = 1;
			shipType++;
		}
		else if (shipType == 3) {
			playerTwoBoard[rowSel][colSel] = 1;
			playerTwoBoard[rowSel][colSel + 1] = 1;
			playerTwoBoard[rowSel][colSel + 2] = 1;
			shipType++;
		}
		else if (shipType == 4) {
			playerTwoBoard[rowSel][colSel] = 1;
			playerTwoBoard[rowSel][colSel + 1] = 1;
		}
	}
	
	setup = false;
	
}

/** Game commences as each player is allowed to take turn shooting each others' ships
	ShootBoard: 0 = no shot attempted; 1 = shot, but missed; 2 = shot, and hit!*/
void shootShips(void){
	
	//Player one's turn
	if(noWinner == true) {
		waitForSelect();
	}
	
	if (playerTwoBoard[rowSel][colSel] == 1 && playerOneShootBoard[rowSel][colSel] == 0) {
		playerOneShootBoard[rowSel][colSel] = 2;
		playerOneHit++;
		if (playerOneHit == 17) {
			winner = 1;
			noWinner = false;
		}
	}
	else{
		playerOneShootBoard[rowSel][colSel] = 1;
	}

	//Player two's turn
	if(noWinner == true) {
		waitForSelect();
	}
	
	if (playerOneBoard[rowSel][colSel] == 1 && playerTwoShootBoard[rowSel][colSel] == 0) {
		playerTwoShootBoard[rowSel][colSel] = 2;
		playerTwoHit++;
		if (playerTwoHit == 17) {
			winner = 2;
			noWinner = false;
		}
	}
	else{
		playerTwoShootBoard[rowSel][colSel] = 1;
	}
}

#endif /* GAME_ENGINE_H_ */
