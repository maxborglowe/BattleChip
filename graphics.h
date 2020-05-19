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

void drawBoard(){
	drawBoardBoundaries(boardOrigoX, boardOrigoY, boxWidth);
	
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
void drawFriendly(void){
		for (int i = 0; i < Rows; i++)
		{
			if (playerOneBoard)
			{
				
			}
		}
	}

void drawShip(){
	
}

#endif /* GRAPHICS_H_ */
