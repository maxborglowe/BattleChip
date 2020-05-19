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

void drawBoard(uint8_t selectBoard){
	toggle = false;
	coproc_clear_color_rgb(0, 0, 0);
	drawBoardBoundaries(boardOrigoX, boardOrigoY, boxWidth);
	drawCursor();
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

/** */
void drawFriendlyBoard(void){
	for (int i = 0; i < Rows; i++)
	{
		for (int k = 0; k < Cols; k++)
		{
			if (playerOneBoard[i][k] == 1)
			{
				coproc_color_rgb(255, 255, 255);
				coproc_point_size(pointWidth);
				coproc_vertex2F(boardOrigoX + i * boxWidth - boxWidth/2, boardOrigoY + k * boxWidth - boxWidth/2);
				coproc_end();
				coproc_display();
			}
		}
	}
}

void drawShootBoard(void){
	for (int i = 0; i < Rows; i++)
	{
		for (int k = 0; k < Cols; k++)
		{
			//draw white dot if shoot and miss
			if (playerOneBoard[i][k] == 1)
			{
				coproc_color_rgb(255, 255, 255);
				coproc_point_size(pointWidth);
				coproc_vertex2F(boardOrigoX + i * boxWidth - boxWidth/2, boardOrigoY + k * boxWidth - boxWidth/2);
				coproc_end();
				coproc_display();
			}
			//draw red dot if shoot and hit
			else if (playerOneBoard[i][k] == 2)
			{
				coproc_color_rgb(0, 255, 0);
				coproc_point_size(pointWidth);
				coproc_vertex2F(boardOrigoX + i * boxWidth - boxWidth/2, boardOrigoY + k * boxWidth - boxWidth/2);
				coproc_end();
				coproc_display();
			}
		}
	}
}

void drawCursor(){
	coproc_color_rgb(255, 255, 0);
	coproc_point_size(pointWidth);
	coproc_vertex2F(boardOrigoX + rowSel * boxWidth - boxWidth/2, boardOrigoY + colSel * boxWidth - boxWidth/2);
	//stop drawing primitives
	coproc_end();
	coproc_display();
}

#endif /* GRAPHICS_H_ */
