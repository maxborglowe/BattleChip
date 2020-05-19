# BattleShip

This project uses an NHD 4.3" FT812-chip (ctxl) sLCD to display the BattleShip app.

#Files

- commands_ftdi.h: Contains SPI functions and commands needed to interface with the LCD.
- definitions_ftdi.h: Contains definitions for ports, ddr, FT812 adresses, etc.
- commands_app.h: Functions used to execute EVE graphics commands, such as drawLine, moveObject, etc.
- game_engine.h: Zis is where we build ze game. 
- main.c: Main application.
- graphics. h: Controls the drawing of game objects onto the LCD using commands from previously listed files.
