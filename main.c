/*
 * BattleShip.c
 *
 * Created: 2020-04-15 07:49:10
 * Author : maxbo
 */ 


#define FCPU 1000000UL
#include <avr/io.h>
#include <stdio.h>
#include "commands_EVE.h"
#include "commands_ftdi.h"

int main(void)
{
	spi_masterInit();
	ftdiInit();
	
	
	while (1)
	{
		
	}
}



