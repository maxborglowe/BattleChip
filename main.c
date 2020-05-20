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
#include "game_engine.h"
#include "graphics.h"

int main(void)
{
	spi_masterInit();	//Initialize MCU as SPI master
	ftdiInit();		//Initialization sequence for FT812 chip
	buttonInit();		//Initialize button inputs
	
	//replay game forever and ever and ever and ever
	while(1){
		placeShips();
		//run game as long as there is no winner
		while(noWinner == true){
			shootShips();
		}
		
		//print winner when game is over
		if(winner == 1){
			[print function]("Player One won!");
		}
		else if(winner == 2){
			[print function]("Player Two won!");
		}
	}
}



