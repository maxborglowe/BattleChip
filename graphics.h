/*
 * graphics.h
 *
 * Created: 2020-05-19 11:17:31
 *  Author: maxbo
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

uint8_t boardOrigoX = 115;
uint8_t boardOrigoY = 11; /* These starting coordinates will make sure the board is nice and centered when the sides
							of each box that make up the playing field are 25 units wide. */
uint8_t boxWidth = 25;
uint8_t lineWidth = 1;
uint8_t pointWidth = 10;

void drawBoard(){
	coproc_clear_color_rgb(0, 0, 0); //clears screen of old junk
	drawBoardBoundaries(boardOrigoX, boardOrigoY, boxWidth); //draws a border matrix in which ships are placed
	
	//draws shoot/friedly board depending on toggle value
	if(toggle == false){
		drawShootBoard();
	}
	else if(toggle == true){
		drawFriendlyBoard();
	}
	toggle = false;
}

/** draw point on board*/
void drawPoint(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b){
	coproc_color_rgb(r, g, b);
	coproc_point_size(pointWidth);
	coproc_begin_primitive(POINT);
	coproc_vertex2F(boardOrigoX + x * boxWidth - boxWidth/2, boardOrigoY + y * boxWidth - boxWidth/2);
	//stop drawing primitives
	coproc_end();
	coproc_display();
}

void drawBoardBoundaries(uint8_t startX, uint8_t startY, uint8_t boxWidth){
	coproc_color_rgb(255, 255, 255); //Set line color to WHITE
	coproc_line_width(lineWidth);			 //1 pixel wide lines will be drawn
	coproc_begin_primitive(LINE);			//start drawing line
	
	//draw row lines
	for(int i = 0; i <= Rows; i++){
		
		coproc_vertex2F(startX, startY + i*boxWidth);
		coproc_vertex2F(startX + Rows*boxWidth, startY + i*boxWidth);
	}
	//draw column lines
	for(int k = 0; k <= Cols; k++){
		coproc_vertex2F(startX + k*boxWidth, startY);
		coproc_vertex2F(startX + k*boxWidth, startY + Cols*boxWidth);
	}
	
	//stop drawing primitives
	coproc_end();
	coproc_display();
}

/** draws the player's own placed ships on the board*/
void drawFriendlyBoard(void){
	for (int i = 0; i < Rows; i++)
	{
		for (int k = 0; k < Cols; k++)
		{
			if (playerOneBoard[i][k] == 1)
			{
				drawPoint(i, k, 255, 255, 255);
			}
		}
	}
}

/** draw board that represents all the positions that the player has shot at */
void drawShootBoard(void){
	for (int i = 0; i < Rows; i++)
	{
		for (int k = 0; k < Cols; k++)
		{
			//draw white dot if shoot and miss
			if (playerOneBoard[i][k] == 1)
			{
				drawPoint(i, k, 255, 255, 255);
			}
			//draw red dot if shoot and hit
			else if (playerOneBoard[i][k] == 2)
			{
				drawPoint(i, k, 0, 255, 0);
			}
		}
	}
	//update cursor
	drawCursor();
}

/** Draws a yellow cursor dot on the board, and if in setup mode - the ships to be placed are shown and updated aswell */
void drawCursor(){
	
	//yellow color
	int r = 255, g = 255, b = 0;
	
	drawPoint(rowSel, colSel, r, g, b);
	
	if (setup == true)
	{
		if(shipType == 0){
			drawPoint(rowSel, colSel, r, g, b);
			drawPoint(rowSel, colSel + 1, r, g, b);
			drawPoint(rowSel, colSel + 2, r, g, b);
			drawPoint(rowSel, colSel + 3, r, g, b);
			drawPoint(rowSel, colSel + 4, r, g, b);
		}
		else if(shipType == 1){
			drawPoint(rowSel, colSel, r, g, b);
			drawPoint(rowSel, colSel + 1, r, g, b);
			drawPoint(rowSel, colSel + 2, r, g, b);
			drawPoint(rowSel, colSel + 3, r, g, b);
		}
		else if(shipType == 2){
			drawPoint(rowSel, colSel, r, g, b);
			drawPoint(rowSel, colSel + 1, r, g, b);
			drawPoint(rowSel, colSel + 2, r, g, b);
		}
		else if(shipType == 3){
			drawPoint(rowSel, colSel, r, g, b);
			drawPoint(rowSel, colSel + 1, r, g, b);
			drawPoint(rowSel, colSel + 2, r, g, b);
		}
		else if(shipType == 4){
			drawPoint(rowSel, colSel, r, g, b);
			drawPoint(rowSel, colSel + 1, r, g, b);
		}
	}
}

#endif /* GRAPHICS_H_ */
