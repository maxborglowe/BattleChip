# BattleShip

This project uses an NHD 4.3" FT812-chip (ctxl) LCD to display the BattleShip app.

#Files

- commands_ftdi.h: SPI functions and basic communication commands such as wr8_mem, rd16_mem, etc.
- definitions_ftdi.h: Definitions for ports, ddr, FT812 adresses and commands, etc.
- commands_app.h: Uses functions from commands_ftdi to send executable commands to the RAM FIFO.
- game_engine.h: Zis is where we build ze game.
- graphics.h: Controls the drawing of game objects onto the LCD using commands from commands_app.h.
- main.c: Main application.
