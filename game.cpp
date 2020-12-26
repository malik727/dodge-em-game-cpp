//============================================================================
// Name        : game.cpp
// Author      : Malik Talha Saeed
// Version     : v1.0
// Copyright   : (c) Reserved
// Description : Basic 2D game of Dodge 'Em...
//============================================================================

#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
#include <fstream>

using namespace std;


int xVal = 340, yVal = 20, xValO= 420, yValO= 20, sely = 400, temp_score = 0; //declaring gloabl variable for coordinates
bool dot_Draw_Array[66] = {false}; //array for drawing conditions
int dot_location_Array[2][66]; //an array that stores location of all the dots
int userCarLoop = 1;
int motionState = 4;
int opponentCarLoop = 1;
int opponentMotionState = 4;
bool down_Pressed = false, up_Pressed = false, left_Pressed = false, right_Pressed = false, result1 = false, proceedNext = false, res_Draw = false;
bool gameWindow = false, startMenuWindow = true, highScoresWindow = false, gameSubWindow = false, helpWindow = false, gamePlay = true, loseWindow = false;
int lives = 3, level = 1;
int userCarSpeed = 5, opponentCarSpeed = 5;


void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}



void GameDisplay(){
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	// calling some functions from util.cpp file to help students

	//Square at 400,20 position
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	//Square at 250,250 position
	//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	//DrawString( 50, 800, "Score=0", colors[MISTY_ROSE]);
	//Triangle at 300, 450 position
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	//Circle at 50, 670 position
	//DrawCircle(50,670,10,colors[RED]);
	//Line from 550,50 to 550,480 with width 10
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	
	//Drawing Game Start Menu
	if(startMenuWindow == true)
	{
		float *scolorsel = colors[BROWN];
		int selx = 490, selwidth = 270, selheight = 40;
		float *option1_color = colors[LAWN_GREEN];
		float *option2_color = colors[DARK_VIOLET];
		float *option3_color = colors[BLUE];
		float *option4_color = colors[RED];
        if(sely == 400)
		{
			option1_color = colors[WHITE];
		}
		else
		{
			option1_color = colors[LAWN_GREEN];
		}
		if(sely == 350)
		{
			option2_color = colors[WHITE];
		}
		else
		{
			option2_color = colors[DARK_VIOLET];
		}
		if(sely == 300)
		{
			option3_color = colors[WHITE];
		}
		else
		{
			option3_color = colors[BLUE];
		}
		if(sely == 250)
		{
			option4_color = colors[WHITE];
		}
		else
		{
			option4_color = colors[RED];
		}
		
		DrawRectangle(selx, sely, selwidth, selheight, scolorsel);
		DrawString( 370, 750, "Dodge Em'", colors[WHITE]);
		DrawString( 500, 410, "StartGame [Press S]", option1_color);
		DrawString( 500, 360, "HighScores [Press H]", option2_color);
		DrawString( 500, 310, "Help [Press K]", option3_color);
		DrawString( 500, 260, "Exit [Press E]", option4_color);
	}
	if(helpWindow == true)
	{
		DrawRectangle(0, 0, 900, 900, colors[SANDY_BROWN]);
		DrawString( 340, 780, "GamePlay Help", colors[BROWN]);
		DrawString( 50, 660, "Game Functionality:", colors[BROWN]);
		DrawString( 50, 620, "Dodge Em' is a single player game in which user has to collect score dots", colors[BROWN]);
		DrawString( 50, 590, "and avoiding the enemy car at the same time.", colors[BROWN]);
		DrawString( 50, 530, "Controls:", colors[BROWN]);
		DrawString( 50, 490, "Game controls are quite easy as the user simple has to press UP/DOWN/LEFT", colors[BROWN]);
		DrawString( 50, 460, "/RIGHT arrow keys to control the car's flow.", colors[BROWN]);
		DrawString( 50, 400, "Levels:", colors[BROWN]);
		DrawString( 50, 360, "The game has four levels with varying difficulty.", colors[BROWN]);
		DrawString( 50, 310, "Other Keys:", colors[BROWN]);
		DrawString( 70, 270, "[P]: Pauses/Resumes the game during gameplay", colors[BROWN]);
		DrawString( 70, 240, "[esc]: Opens Sub Menu during gameplay", colors[BROWN]);
		DrawString( 170, 200, "*other keys are explained in their respective menus*", colors[BROWN]);
		DrawString( 260, 100, "Press [B] to go to Main Menu", colors[BLUE]);
	}
	if(highScoresWindow == true)
	{
		DrawString( 340, 800, "Current HighScores", colors[DARK_VIOLET]);
		int* ptr_readScore = readHighScore();
		int scoreTemp;
		int score_x = 400;
		int score_y = 600; 
		DrawRectangle(200, 280, 440, 400, colors[CORAL]);
		for(int scorei=0; scorei<10; scorei++)
		{
			scoreTemp = ptr_readScore[scorei];
			DrawString(score_x, score_y, " "+Num2Str(scoreTemp), colors[WHITE]);
			score_y-=30;
		}
		DrawString( 280, 200, "Press [B] to go to Main Menu", colors[CORAL]);
	}
	if(gameSubWindow == true)
	{
		DrawString( 300, 610, "Resume [Press R]", colors[WHITE]);
		DrawString( 300, 560, "Start New Game [Press N]", colors[WHITE]);
		DrawString( 300, 510, "HighScores [Press H]", colors[WHITE]);
		DrawString( 300, 460, "Help [Press K]", colors[WHITE]);
		DrawString( 300, 410, "Exit [Press E]", colors[WHITE]);
	}
	if(loseWindow == true)
	{
		DrawRectangle(0, 0, 900, 900, colors[RED]);
		DrawString(370, 550, "Game Over!", colors[WHITE]);
		if(res_Draw == true)
		{
			DrawString(370, 450, "Your Score : "+Num2Str(temp_score), colors[WHITE]);
			DrawRectangle(160, 390, 600, 40, colors[WHITE]);
			DrawString(180, 400, "Congratulation! Your score made it into HighScores!", colors[GREEN]);
			
		}
		else if(res_Draw == false)
		{
			DrawString(370, 440, "Your Score : "+Num2Str(temp_score), colors[WHITE]);
			DrawString(310, 410, "Better Luck Next Time!", colors[WHITE]);
			DrawString(200, 380, "You were unable to compete with HighScores.", colors[WHITE]);
		}
		DrawString( 280, 300, "Press [B] to go to Main Menu", colors[WHITE]);
	}
	//Main Game Graphics
    if(gameWindow == true)
	{
     	// Drawing Arena's Outermost
     	int gap_turn = 80;
     	int sx = 20;
     	int sy = 0;
     	int swidth = 400 - gap_turn/2; // half width
     	int sheight = 10;
     	float *scolor = colors[BROWN];
     	DrawRectangle(sx-20, sy, swidth, sheight, scolor); // bottom left
     	DrawRectangle(sx+20 + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
     	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth-10, scolor); // right down
     	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth-10, scolor); // right up
     	DrawRectangle(sx+20 + swidth + gap_turn, sy+800, swidth, sheight, scolor); // top left
     	DrawRectangle(sx-20, sy+800, swidth, sheight, scolor); // top right
     	DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth-10, scolor); // left up
     	DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth-10, scolor); // left down
     
     	// Drawing Arena's second outermost
     	gap_turn = 80;
     	sx = 100;
     	sy = 80;
     	swidth = 320 - gap_turn/2; // half width
     	sheight = 10;
     	float *scolor1 = colors[BROWN];
     	DrawRectangle(sx-20, sy, swidth, sheight, scolor1); // bottom left
     	DrawRectangle(sx+20 + swidth + gap_turn, sy, swidth, sheight, scolor1); // bottom right
     	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth-10, scolor1); // right down
     	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth-10, scolor1); // right up
     	DrawRectangle(sx+20 + swidth + gap_turn, sy+640, swidth, sheight, scolor1); // top left
     	DrawRectangle(sx-20, sy+640, swidth, sheight, scolor1); // top right
     	DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth-10, scolor1); // left up
     	DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth-10, scolor1); // left down
     
     	// Drawing Arena's third outermost
     	gap_turn = 80;
     	sx = 180;
     	sy = 160;
     	swidth = 240 - gap_turn/2; // half width
     	sheight = 10;
     	float *scolor2 = colors[BROWN];
     	DrawRectangle(sx-20, sy, swidth, sheight, scolor2); // bottom left
     	DrawRectangle(sx+20 + swidth + gap_turn, sy, swidth, sheight, scolor2); // bottom right
     	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth-10, scolor2); // right down
     	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth-10, scolor2); // right up
     	DrawRectangle(sx+20 + swidth + gap_turn, sy+480, swidth, sheight, scolor2); // top left
     	DrawRectangle(sx-20, sy+480, swidth, sheight, scolor2); // top right
     	DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth-10, scolor2); // left up
     	DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth-10, scolor2); // left down
     
     	// Drawing Arena's fourth outermost
     	gap_turn = 80;
     	sx = 260;
     	sy = 240;
     	swidth = 160 - gap_turn/2; // half width
     	sheight = 10;
     	float *scolor3 = colors[BROWN];
     	DrawRectangle(sx-20, sy, swidth, sheight, scolor3); // bottom left
     	DrawRectangle(sx+20 + swidth + gap_turn, sy, swidth, sheight, scolor3); // bottom right
     	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth-10, scolor3); // right down
     	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth-10, scolor3); // right up
     	DrawRectangle(sx+20 + swidth + gap_turn, sy+320, swidth, sheight, scolor3); // top left
     	DrawRectangle(sx-20, sy+320, swidth, sheight, scolor3); // top right
     	DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth-10, scolor3); // left up
     	DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth-10, scolor3); // left down
     
     	// Drawing Arena's innermost
     	gap_turn = 0;
     	sx = 340;
     	sy = 320;
     	swidth = 80 - gap_turn/2; // half width
     	sheight = 10;
     	float *scolor4 = colors[BROWN];
     	DrawRectangle(sx-20, sy, swidth, sheight, scolor4); // bottom left
     	DrawRectangle(sx+20 + swidth + gap_turn, sy, swidth, sheight, scolor4); // bottom right
     	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth, scolor4); // right down
     	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor4); // right up
     	DrawRectangle(sx+20 + swidth + gap_turn, sy+160, swidth, sheight, scolor4); // top left
     	DrawRectangle(sx-20, sy+160, swidth, sheight, scolor4); // top right
     	DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor4); // left up
     	DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor4); // left down
     
     	/* Score Generator */
     	int final_score = temp_score;
     	for(int i =0; i<66; i++)
     	{
     		if(dot_Draw_Array[i] == true)
     		{
     			final_score+=1;
     		}
     	}
     	DrawString( 650, 850, "SCORE = "+Num2Str(final_score), colors[MISTY_ROSE]);
     	/* End of score Generator */


     	/* Total Lives */
     	DrawString( 50, 850, "Lives = "+Num2Str(lives), colors[MISTY_ROSE]);
     	/* End code of total lives */

		/* Levels */
		DrawString( 340, 850, "Level = "+Num2Str(level), colors[MISTY_ROSE]);	 
		/* End code of levels */

		/*Code to check if all the dots have been eaten*/
		for(int i = 0; i<64; i++)
		{
			if(dot_Draw_Array[i] == false)
			{
				proceedNext = false;
				break;
			}
			else
			{
				proceedNext = true;
			}				
		}		
		if(proceedNext == true)
		{
			level = level + 1;
			for(int i = 0; i<66; i++)
			{
				dot_Draw_Array[i] = {false};
			}
			xVal = 320;
			yVal = 20;
			xValO = 420;
			yValO = 20;
			userCarLoop = 1;
			motionState = 4;
			opponentMotionState = 4;
			opponentCarLoop = 1;
			proceedNext = false;
		}
		if(level == 1 || level == 2)
		{
			userCarSpeed = 5;
			opponentCarSpeed = 5;
		}
		if(level == 3)
		{
			userCarSpeed = 10;
			opponentCarSpeed = 10;
		}
		/*End of code which checks all dots eaten*/

		if(xVal == xValO && yVal == yValO)
		{
			if(lives <= 0)
			{
				if(highScoresFunction(temp_score) == true)
				{
					res_Draw = true;
				}
				xVal = 320;
				yVal = 20;
				xValO = 420;
				yValO = 20;
				userCarLoop = 1;
				motionState = 4;
				opponentMotionState = 4;
				opponentCarLoop = 1;
				lives = 4;
				level = 1;
				for(int i = 0; i<66; i++)
				{
					dot_Draw_Array[i] = {false};
				}
				gameWindow = false;
				loseWindow = true;
			}
			if(lives > 0)
			{
				temp_score = final_score;
				lives -= 1;
				xVal = 320;
				yVal = 20;
				xValO = 420;
				yValO = 20;
				userCarLoop = 1;
				motionState = 4;
				opponentMotionState = 4;
				opponentCarLoop = 1;
				for(int i = 0; i<66; i++)
				{
					dot_Draw_Array[i] = {false};
				}
			}
		}
		

     	/* Dots Arrays */
     	int dots_i = 0;
     
     	/* Loops to Draw Dots */
     
     	//Quadrant I
     	int yl1 = 760;
     	float *slcolor = colors[BROWN]; 
     	int lradius = 10;
     	int xl1 = 50;
     	for(int loopi = 1; loopi<=16; loopi++)
     	{
     		if(xl1==370)
     		{
     			yl1 -= 80;
     			xl1 = 50;
     		}
     		dot_location_Array[0][dots_i] = xl1; //x coordinate
     		dot_location_Array[1][dots_i] = yl1; //y coordinate
     
     		if(dot_Draw_Array[dots_i] == false)
     		{
     			DrawCircle(xl1, yl1, lradius, slcolor);
     		}
     		dots_i++;
     		xl1+=80;
     	}
     
     	//Quadrant II
     	yl1 = 760;
     	lradius = 10;
     	xl1 = 550;
     	for(int loopi = 1; loopi<=16; loopi++)
     	{
     		if(xl1==870)
     		{
     			yl1 -= 80;
     			xl1 = 550;
     		}
     		dot_location_Array[0][dots_i] = xl1; //x coordinate
     		dot_location_Array[1][dots_i] = yl1; //y coordinate
     		if(dot_Draw_Array[dots_i] == false)
     		{
     		DrawCircle(xl1, yl1, lradius, slcolor);
     		}
     		dots_i++;
     		xl1+=80;
     	}
     
     	//Quadrant III
     	yl1 = 290;
     	lradius = 10;
     	xl1 = 50;
     	for(int loopi = 1; loopi<=16; loopi++)
     	{
     		if(xl1==370)
     		{
     			yl1 -= 80;
     			xl1 = 50;
     		}
     		dot_location_Array[0][dots_i] = xl1; //x coordinate
     		dot_location_Array[1][dots_i] = yl1; //y coordinate
     		if(dot_Draw_Array[dots_i] == false)
     		{
     		DrawCircle(xl1, yl1, lradius, slcolor);
     		}
     		dots_i++;
     		xl1+=80;
     	}
     
     	//Quadrant IV
     	yl1 = 290;
     	lradius = 10;
     	xl1 = 550;
     	for(int loopi = 1; loopi<=16; loopi++)
     	{
     		if(xl1==870)
     		{
     			yl1 -= 80;
     			xl1 = 550;
     		}
     		dot_location_Array[0][dots_i] = xl1; //x coordinate
     		dot_location_Array[1][dots_i] = yl1; //y coordinate
     		if(dot_Draw_Array[dots_i] == false)
     		{
     		DrawCircle(xl1, yl1, lradius, slcolor);
     		}
     		dots_i++;
     		xl1+=80;
     	}
     	/*End of loops to draw dots */
     
     	// Drawing user car
     	float x = xVal; 
     	float y = yVal; 
     	float width = 15; 
     	float height = 10;
     	float* color = colors[SANDY_BROWN]; 
     	float radius = 5.0;
     	DrawRoundRect(x, y, width, height, color, radius); // bottom left tyre
     	DrawRoundRect(x+width*3, y, width, height, color, radius); // bottom right tyre
     	DrawRoundRect(x+width*3, y+height*4, width, height, color, radius); // top right tyre
     	DrawRoundRect(x, y+height*4, width, height, color, radius); // top left tyre
     	DrawRoundRect(x, y+height*2, width, height, color, radius/2); // body left rect
     	DrawRoundRect(x+width, y+height, width*2, height*3, color, radius/2); // body center rect
     	DrawRoundRect(x+width*3, y+height*2, width, height, color, radius/2); // body right rect
     
     	// Drawing opponent car
     	float x1 = xValO; 
     	float y1 = yValO; 
     	float width1 = 15; 
     	float height1 = 10;
     	float* color1 = colors[BLUE_VIOLET]; 
     	float radius1 = 5.0;
     	DrawRoundRect(x1, y1, width1, height1, color1, radius1); // bottom left tyre
     	DrawRoundRect(x1+width1*3, y1, width1, height1, color1, radius1); // bottom right tyre
     	DrawRoundRect(x1+width1*3, y1+height1*4, width1, height1, color1, radius1); // top right tyre
     	DrawRoundRect(x1, y1+height1*4, width1, height1, color1, radius1); // top left tyre
     	DrawRoundRect(x1, y1+height1*2, width1, height1, color1, radius1/2); // body left rect
     	DrawRoundRect(x1+width1, y1+height1, width1*2, height1*3, color1, radius1/2); // body center rect
     	DrawRoundRect(x1+width1*3, y1+height1*2, width1, height1, color1, radius1/2); // body right rect
	}

	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	x = xVal;
	y = yVal;
	if (key	== GLUT_KEY_LEFT) 
	{
		if(((yVal>=360 && yVal<=400) && xVal == 100) || ((yVal>=360 && yVal<=400) && xVal == 180) || ((yVal>=360 && yVal<=400) && xVal == 260)  || ((yVal>=360 && yVal<=400) && xVal == 600) || ((yVal>=360 && yVal<=400) && xVal == 680) || ((yVal>=360 && yVal<=400) && xVal == 760))
		{
			left_Pressed = true;
		}

	/*	if((y==20 && x>20) || (y == 100 && x>100 && x!=760) || (y == 180 && x>180 && x!=680 && x!=760) || (y==260 && x>260 && x!=600 && x!=680 && x!=760) || (y==380 && x>20 && x!=520) || (y == 500 && x>260 && x!=600 && x!=680 && x!=760) || (y == 580 && x>180 && x!=680 && x!=760) || (y==660 && x>100 && x!=760) || (y==740 && x>20))
		{
			for(int i = 0; i<66; i++)
			{
				if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
				{
					dot_Draw_Array[i] = true;
				}
			}
            x-=10;
			xVal = x;	
			cout<<"-x: "<<x<<endl;
		}
		else
		{
			xVal = x;        
		}  */
	} 
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) 
	{

		if(((yVal>=360 && yVal<=400) && xVal == 100) || ((yVal>=360 && yVal<=400) && xVal == 180) || ((yVal>=360 && yVal<=400) && xVal == 520) || ((yVal>=360 && yVal<=400) && xVal == 600) || ((yVal>=360 && yVal<=400) && xVal == 680) || ((yVal>=360 && yVal<=400) && xVal == 20))
		{
			right_Pressed = true;
		}
	/*	if((y==20 && x<760) || (y==100 && x<680 && x!=20) || (y==180 && x<600 && x!=100 && x!=20) || (y==260 && x<520 && x!=180 && x!=100 && x!=20) || (y==380 && x<760 && x!=260) || (y == 500 && x<520 && x!=180 && x!=100 && x!=20) || (y == 580 && x<600 && x!=100 && x!=20) || (y==660 && x<680 && x!=20) || (y==740 && x<760))
		{
			for(int i = 0; i<66; i++)
			{
				if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
				{
					dot_Draw_Array[i] = true;
				}
			}
            x+=10;
			xVal = x;	
			cout<<"+x: "<<x<<endl;
		}
		else
		{
			xVal = x;
		}   */
	} 
	else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) 
	{
		if(((xVal<=390 && xVal>=350)&& yVal==20) || ((xVal<=390 && xVal>=350)&& yVal==100) || ((xVal<=390 && xVal>=350)&& yVal==180) || ((xVal<=390 && xVal>=350)&& yVal==500) || ((xVal <= 390 && xVal >= 350)&& yVal == 580) || ((xVal<=390 && xVal>=350)&& yVal == 660))
		{
			up_Pressed = true;
		}
	
	
	/*	if((x==20 && y<740)|| (x==100 && y<660 && y!=20) || (x==180 && y<580 && y!=20 && y!=100) || (x==260 && y<500 && y!=20 && y!=100 && y!=180) || (x==390 && y<740 && y!=260) || (x==520 && y<500 && y!=180 && y!=100 && y!=20) || (x==600 && y<580 && y!=100 && y!=20) || (x==680 && y<660 && y!=20) || (x==760 && y<740))
		{
			for(int i = 0; i<66; i++)
			{
				if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
				{
					dot_Draw_Array[i] = true;
				}
			}
			y+=10;
			yVal = y;
			cout<<"+y: "<<y<<endl;
		}
		else
		{
			yVal = y;
		}		*/
	}
	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) 
	{
		if(((xVal<=380 && xVal>=360)&& yVal==260) || ((xVal <= 380 && xVal >= 360)&& yVal == 180) || ((xVal<=380 && xVal>=360)&& yVal == 100) || ((xVal<=380 && xVal>=360) && yVal == 580) || ((xVal<=380 && xVal>=360)&&yVal==660) || ((xVal<=380 && xVal>=360)&& yVal==740))
		{
			down_Pressed = true;
		}
		
		/*if((x==20 && y>20 )|| (x==100 && y>100 && y!=740) || (x==180 && y>180 && y!=740 && y!=660) || (x==260 && y>260 && y!=740 && y!=660 && y!=580) || (x==390 && y>20 && y!=500) || (x==520 && y>260 && y!=740 && y!=660 && y!=580) || (x==600 && y>180 && y!=740 && y!=660) || (x==680 && y>100 && y!=740) || (x==760 && y>20))
		{
			for(int i = 0; i<66; i++)
			{
				if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
				{
					dot_Draw_Array[i] = true;
				}
			}
			y-=10;
			yVal = y; 
			cout<<"-y: "<<y<<endl;
		}
		else
		{
			yVal = y;
		} */
	}
	if(key == GLUT_KEY_UP && startMenuWindow == true && sely<400)
	{
		sely +=50; 
	}
	if(key == GLUT_KEY_DOWN && startMenuWindow == true && sely>250)
	{
		sely -=50; 
	}
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

		glutPostRedisplay();
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	
	if (key == 27 && (startMenuWindow == true || gameSubWindow == true)) //Escape key
	{
		exit(1); // exit the program when escape key is pressed.
	}
	if(key == 27 && gameWindow == true)
	{
		gameWindow = false;
		gameSubWindow = true;
	}
	if ((key == 'p' || key == 'P') && gamePlay == true && gameWindow == true)
	{
		gamePlay = false;
	}
	else if ((key == 'p' || key == 'P') && gamePlay == false && gameWindow == true)
	{
		gamePlay = true;
	}
	if((key == 'n' || key == 'N') && gameSubWindow == true)
	{
		xVal = 320;
		yVal = 20;
		xValO = 420;
		yValO = 20;
		userCarLoop = 1;
		motionState = 4;
		opponentMotionState = 4;
		opponentCarLoop = 1;
		for(int i = 0; i<66; i++)
		{
			dot_Draw_Array[i] = {false};
		}
		gameWindow = true;
		gameSubWindow = false;
	}
	if ((key == 'r' || key == 'R') && gameSubWindow == true)
	{
		gameSubWindow = false;
		gameWindow = true;
	}
	if((key == 'b' || key == 'B') && highScoresWindow == true && gameWindow == false)
	{
		highScoresWindow = false;
		startMenuWindow = true;
	}
	if((key == 'b' || key == 'B') && helpWindow == true && gameWindow == false)
	{
		helpWindow = false;
		startMenuWindow = true;
	}
	if((key == 'b' || key == 'B') && loseWindow == true && gameWindow == false)
	{
		highScoresFunction(temp_score);
		temp_score = 0;
		res_Draw = false;
		loseWindow = false;
		startMenuWindow = true;
	}
	if((key == 'h' || key == 'H') && startMenuWindow == true && gameWindow == false)
	{
		highScoresWindow = true;
		startMenuWindow = false;
	}
	if((key == 'k' || key == 'K') && startMenuWindow == true && gameWindow == false)
	{
		helpWindow = true;
		startMenuWindow = false;
	}
	if((key == 's' || key == 'S') && startMenuWindow == true && gameWindow == false)
	{
		gameWindow = true;
		startMenuWindow = false;
	}
	if(key == 13 && startMenuWindow == true && sely == 400) //Enter Key Check StartGame
	{
		gameWindow = true;
		startMenuWindow = false;
	}
	if(key == 13 && startMenuWindow == true && sely == 350) //Enter Key Check HighScores
	{
		highScoresWindow = true;
		startMenuWindow = false;
	}
	if(key == 13 && startMenuWindow == true && sely == 300) //Enter Key Check
	{
		helpWindow = true;
		startMenuWindow = false;
	}
	if(key == 13 && startMenuWindow == true && sely == 250) //Enter Key Check Exit
	{
		exit(1);
	}
	glutPostRedisplay();
}

void keysPressed(unsigned char key, int x, int y) {



}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {
	/* Opponent Car Functionality */
	if(gameWindow == true && gamePlay == true)
	{
		if(level == 1)
		{
			if(opponentMotionState == 1)
    		{
    			if((xValO == 760) && (yValO >= 20 && yValO <=735))
    				{
    					yValO+=5;
    				}
    				if(xValO == 760 && yValO == 740)
    				{
    					opponentMotionState = 2;
    				}
    			}
    		else if(opponentMotionState == 2)
    		{
    			if(yValO == 740 && (xValO>=25 && xValO<=760))
    			{
    				xValO-=5;
    			}
    			if(yValO == 740 && xValO == 20)
    			{
    				opponentMotionState = 3;
    			}
    		}
    		else if(opponentMotionState == 3)
    		{
    			if(xValO == 20 && (yValO>=25 && yValO<=740))
    			{
    				yValO-=5;
    			}
    			if(xValO == 20 && yValO==20)
    			{
    				opponentMotionState = 4;
    			}
    		}
    		else if(opponentMotionState == 4)
    		{
    			if(yValO==20 && (xValO>=20 && xValO<=755))
    			{
    				xValO+=5;
    			}
    			if(xValO == 760 && yValO == 20)
    			{
    				opponentMotionState = 1;
    			}
    		}
		}
		if(level == 2)
		{
    	switch(opponentCarLoop)
    	{
    		case 1:
    				if((userCarLoop == 2 || userCarLoop == 3 || userCarLoop == 4) && (xValO==380 && yValO==740))
    				{
    					yValO-=80;
    					opponentCarLoop = 2;
    				}
    				if(userCarLoop==2 && (xValO==380 && yValO==20))
    				{
    					yValO+=80;
    					opponentCarLoop = 2;
    				}
    				if(userCarLoop == 2 && (xValO==20 && yValO==360))
    				{
    					xValO+=80;
    					opponentCarLoop = 2;
    				}
    				if(userCarLoop == 2 && (xValO==680 && yValO==360))
    				{
    					xValO-=80;
    					opponentCarLoop = 2;
    				}
    				if(opponentMotionState == 1)
    				{
    					if((xValO == 760) && (yValO >= 20 && yValO <=735))
    					{
    						yValO+=5;
    					}
    					if(xValO == 760 && yValO == 740)
    					{
    						opponentMotionState = 2;
    					}
    				}
    				else if(opponentMotionState == 2)
    				{
    					if(yValO == 740 && (xValO>=25 && xValO<=760))
    					{
    						xValO-=5;
    					}
    					if(yValO == 740 && xValO == 20)
    					{
    						opponentMotionState = 3;
    					}
    				}
    				else if(opponentMotionState == 3)
    				{
    					if(xValO == 20 && (yValO>=25 && yValO<=740))
    					{
    						yValO-=5;
    					}
    					if(xValO == 20 && yValO==20)
    					{
    						opponentMotionState = 4;
    					}
    				}
    				else if(opponentMotionState == 4)
    				{
    					if(yValO==20 && (xValO>=20 && xValO<=755))
    					{
    						xValO+=5;
    					}
    					if(xValO == 760 && yValO == 20)
    					{
    						opponentMotionState = 1;
    					}
    				}
    				break;
    		case 2:
    				if(userCarLoop == 1 && (xValO==380 && yValO==660))
    				{
    					yValO+=80;
    					opponentCarLoop = 1;
    				}
    				if(userCarLoop==1 && (xValO==380 && yValO==100))
    				{
    					yValO-=80;
    					opponentCarLoop = 1;
    				}
    				if(userCarLoop == 1 && (xValO==100 && yValO==360))
    				{
    					xValO-=80;
    					opponentCarLoop = 1;
    				}
    				if(userCarLoop == 1 && (xValO==680 && yValO==360))
    				{
    					xValO+=80;
    					opponentCarLoop = 1;
    				}
    				if((userCarLoop == 3 || userCarLoop == 4) && (xValO==380 && yValO==660))
    				{
    					yValO-=80;
    					opponentCarLoop = 3;
    				}
    				if((userCarLoop == 3 || userCarLoop == 4) && (xValO==380 && yValO==100))
    				{
    					yValO+=80;
    					opponentCarLoop = 3;
    				}
    				if((userCarLoop == 3 || userCarLoop == 4) && (xValO==100 && yValO==360))
    				{
    					xValO+=80;
    					opponentCarLoop = 3;
    				}
    				if((userCarLoop == 3 || userCarLoop == 4) && (xValO==680 && yValO==360))
    				{
    					xValO-=80;
    					opponentCarLoop = 3;
    				}
    				if(opponentMotionState == 1)
    				{
    					if((xValO == 680) && (yValO >= 100 && yValO<=655))
    					{
    						yValO+=5;
    					}
    					if(xValO == 680 && yValO == 660)
    					{
    						opponentMotionState = 2;
    					}
    				}
    				else if(opponentMotionState == 2)
    				{
    					if(yValO == 660 && (xValO>=105 && xValO<=680))
    					{
    						xValO-=5;
    					}
    					if(yValO == 660 && xValO == 100)
    					{
    						opponentMotionState = 3;
    					}
    				}
    				else if(opponentMotionState == 3)
    				{
    					if(xValO == 100 && (yValO>=95 && yValO<=670))
    					{
    						yValO-=5;
    					}
    
    					if(xValO == 100 && yValO==100)
    					{
    						opponentMotionState = 4;
    					}
    				}
    				else if(opponentMotionState == 4)
    				{
    					if(yValO==100 && (xValO>=100 && xValO<=675))
    					{
    						xValO+=5;
    					}
    					if(xValO == 680 && yValO == 100)
    					{
    						opponentMotionState = 1;
    					}
    				}
    				break;
    		case 3:
    				if((userCarLoop == 1 || userCarLoop == 2) && (xValO==380 && yValO==580))
    				{
    					yValO+=80;
    					opponentCarLoop = 2;
    				}
    				if((userCarLoop == 1 || userCarLoop == 2) && (xValO==380 && yValO==180))
    				{
    					yValO-=80;
    					opponentCarLoop = 2;
    				}
    				if((userCarLoop == 1 || userCarLoop == 2) && (xValO==180 && yValO==360))
    				{
    					xValO-=80;
    					opponentCarLoop = 2;
    				}
    				if((userCarLoop == 1 || userCarLoop == 2) && (xValO==600 && yValO==360))
    				{
    					xValO+=80;
    					opponentCarLoop = 2;
    				}
    				if(userCarLoop == 4 && (xValO==380 && yValO==580))
    				{
    					yValO-=80;
    					opponentCarLoop = 4;
    				}
    				if(userCarLoop == 4 && (xValO==380 && yValO==180))
    				{
    					yValO+=80;
    					opponentCarLoop = 4;
    				}
    				if(userCarLoop == 4 && (xValO==100 && yValO==360))
    				{
    					xValO+=80;
    					opponentCarLoop = 4;
    				}
    				if(userCarLoop == 4 && (xValO==680 && yValO==360))
    				{
    					xValO-=80;
    					opponentCarLoop = 4;
    				}
    				if(opponentMotionState == 1)
    				{
    					if((xValO == 600) && (yValO >= 180 && yValO <=575))
    					{
    						yValO+=5;
    					}
    					if(xValO == 600 && yValO == 580)
    					{
    						opponentMotionState = 2;
    					}
    				}
    				else if(opponentMotionState == 2)
    				{
    					if(yValO == 580 && (xValO>=185 && xValO<=600))
    					{
    						xValO-=5;
    					}
    					if(yValO == 580 && xValO == 180)
    					{
    						opponentMotionState = 3;
    					}
    				}
    				else if(opponentMotionState == 3)
    				{
    					if(xValO == 180 && (yValO>=185 && yValO<=600))
    					{
    						yValO-=5;
    					}
    					if(xValO == 180 && yValO==180)
    					{
    						opponentMotionState = 4;
    					}
    				}
    				else if(opponentMotionState == 4)
    				{
    					if(yValO==180 && (xValO>=180 && xValO<=595))
    					{
    						xValO+=5;
    					}
    					if(xValO == 600 && yValO == 180)
    					{
    						opponentMotionState = 1;
    					}
    				}
    				break;
    		case 4:
    				if((userCarLoop == 1 || userCarLoop == 2 || userCarLoop == 3) && (xValO==380 && yValO==500))
    				{
    					yValO+=80;
    					opponentCarLoop = 3;
    				}
    				if((userCarLoop == 1 || userCarLoop == 2 || userCarLoop == 3) && (xValO==380 && yValO==260))
    				{
    					yValO-=80;
    					opponentCarLoop = 3;
    				}
    				if((userCarLoop == 1 || userCarLoop == 2 || userCarLoop == 3) && (xValO==260 && yValO==360))
    				{
    					xValO-=80;
    					opponentCarLoop = 3;
    				}
    				if((userCarLoop == 1 || userCarLoop == 2 || userCarLoop == 3) && (xValO==520 && yValO==360))
    				{
    					xValO+=80;
    					opponentCarLoop = 3;
    				}
    				if(opponentMotionState == 1)
    				{
    					if((xValO == 510) && (yValO >= 260 && yValO <=495))
    					{
    						yValO+=5;
    					}
    					if(xValO == 510 && yValO == 500)
    					{
    						opponentMotionState = 2;
    					}
    				}
    				else if(opponentMotionState == 2)
    				{
    					if(yValO == 500 && (xValO>=265 && xValO<=520))
    					{
    						xValO-=5;
    					}
    					if(yValO == 500 && xValO == 260)
    					{
    						opponentMotionState = 3;
    					}
    				}
    				else if(opponentMotionState == 3)
    				{
    					if(xValO==260 && (yValO>=265 && yValO<=500))
    					{
    						yValO-=5;
    					}
    					if(xValO==260 && yValO==260)
    					{
    						opponentMotionState = 4;
    					}
    				}
    				else if(opponentMotionState == 4)
    				{
    					if(yValO==260 && (xValO>=260 && xValO<=505))
    					{
    						xValO+=5;
    					}
    					if(xValO == 510 && yValO == 260)
    					{
    						opponentMotionState = 1;
    					}
    				}
    				break;
    	}
		}
		if(level == 3)
		{
			switch(opponentCarLoop)
    		{
    		case 1:
    				if((userCarLoop == 2 || userCarLoop == 3 || userCarLoop == 4) && (xValO==380 && yValO==740))
    				{
    					yValO-=80;
    					opponentCarLoop = 2;
    				}
    				if(userCarLoop==2 && (xValO==380 && yValO==20))
    				{
    					yValO+=80;
    					opponentCarLoop = 2;
    				}
    				if(userCarLoop == 2 && (xValO==20 && yValO==360))
    				{
    					xValO+=80;
    					opponentCarLoop = 2;
    				}
    				if(userCarLoop == 2 && (xValO==680 && yValO==360))
    				{
    					xValO-=80;
    					opponentCarLoop = 2;
    				}
    				if(opponentMotionState == 1)
    				{
    					if((xValO == 760) && (yValO >= 20 && yValO <=730))
    					{
    						yValO+=10;
    					}
    					if(xValO == 760 && yValO == 740)
    					{
    						opponentMotionState = 2;
    					}
    				}
    				else if(opponentMotionState == 2)
    				{
    					if(yValO == 740 && (xValO>=30 && xValO<=760))
    					{
    						xValO-=10;
    					}
    					if(yValO == 740 && xValO == 20)
    					{
    						opponentMotionState = 3;
    					}
    				}
    				else if(opponentMotionState == 3)
    				{
    					if(xValO == 20 && (yValO>=30 && yValO<=740))
    					{
    						yValO-=10;
    					}
    					if(xValO == 20 && yValO==20)
    					{
    						opponentMotionState = 4;
    					}
    				}
    				else if(opponentMotionState == 4)
    				{
    					if(yValO==20 && (xValO>=20 && xValO<=750))
    					{
    						xValO+=10;
    					}
    					if(xValO == 760 && yValO == 20)
    					{
    						opponentMotionState = 1;
    					}
    				}
    				break;
    		case 2:
    				if(userCarLoop == 1 && (xValO==380 && yValO==660))
    				{
    					yValO+=80;
    					opponentCarLoop = 1;
    				}
    				if(userCarLoop==1 && (xValO==380 && yValO==100))
    				{
    					yValO-=80;
    					opponentCarLoop = 1;
    				}
    				if(userCarLoop == 1 && (xValO==100 && yValO==360))
    				{
    					xValO-=80;
    					opponentCarLoop = 1;
    				}
    				if(userCarLoop == 1 && (xValO==680 && yValO==360))
    				{
    					xValO+=80;
    					opponentCarLoop = 1;
    				}
    				if((userCarLoop == 3 || userCarLoop == 4) && (xValO==380 && yValO==660))
    				{
    					yValO-=80;
    					opponentCarLoop = 3;
    				}
    				if((userCarLoop == 3 || userCarLoop == 4) && (xValO==380 && yValO==100))
    				{
    					yValO+=80;
    					opponentCarLoop = 3;
    				}
    				if((userCarLoop == 3 || userCarLoop == 4) && (xValO==100 && yValO==360))
    				{
    					xValO+=80;
    					opponentCarLoop = 3;
    				}
    				if((userCarLoop == 3 || userCarLoop == 4) && (xValO==680 && yValO==360))
    				{
    					xValO-=80;
    					opponentCarLoop = 3;
    				}
    				if(opponentMotionState == 1)
    				{
    					if((xValO == 680) && (yValO >= 100 && yValO<=650))
    					{
    						yValO+=10;
    					}
    					if(xValO == 680 && yValO == 660)
    					{
    						opponentMotionState = 2;
    					}
    				}
    				else if(opponentMotionState == 2)
    				{
    					if(yValO == 660 && (xValO>=110 && xValO<=680))
    					{
    						xValO-=10;
    					}
    					if(yValO == 660 && xValO == 100)
    					{
    						opponentMotionState = 3;
    					}
    				}
    				else if(opponentMotionState == 3)
    				{
    					if(xValO == 100 && (yValO>=100 && yValO<=670))
    					{
    						yValO-=10;
    					}
    
    					if(xValO == 100 && yValO==100)
    					{
    						opponentMotionState = 4;
    					}
    				}
    				else if(opponentMotionState == 4)
    				{
    					if(yValO==100 && (xValO>=100 && xValO<=670))
    					{
    						xValO+=10;
    					}
    					if(xValO == 680 && yValO == 100)
    					{
    						opponentMotionState = 1;
    					}
    				}
    				break;
    		case 3:
    				if((userCarLoop == 1 || userCarLoop == 2) && (xValO==380 && yValO==580))
    				{
    					yValO+=80;
    					opponentCarLoop = 2;
    				}
    				if((userCarLoop == 1 || userCarLoop == 2) && (xValO==380 && yValO==180))
    				{
    					yValO-=80;
    					opponentCarLoop = 2;
    				}
    				if((userCarLoop == 1 || userCarLoop == 2) && (xValO==180 && yValO==360))
    				{
    					xValO-=80;
    					opponentCarLoop = 2;
    				}
    				if((userCarLoop == 1 || userCarLoop == 2) && (xValO==600 && yValO==360))
    				{
    					xValO+=80;
    					opponentCarLoop = 2;
    				}
    				if(userCarLoop == 4 && (xValO==380 && yValO==580))
    				{
    					yValO-=80;
    					opponentCarLoop = 4;
    				}
    				if(userCarLoop == 4 && (xValO==380 && yValO==180))
    				{
    					yValO+=80;
    					opponentCarLoop = 4;
    				}
    				if(userCarLoop == 4 && (xValO==100 && yValO==360))
    				{
    					xValO+=80;
    					opponentCarLoop = 4;
    				}
    				if(userCarLoop == 4 && (xValO==680 && yValO==360))
    				{
    					xValO-=80;
    					opponentCarLoop = 4;
    				}
    				if(opponentMotionState == 1)
    				{
    					if((xValO == 600) && (yValO >= 180 && yValO <=570))
    					{
    						yValO+=10;
    					}
    					if(xValO == 600 && yValO == 580)
    					{
    						opponentMotionState = 2;
    					}
    				}
    				else if(opponentMotionState == 2)
    				{
    					if(yValO == 580 && (xValO>=190 && xValO<=600))
    					{
    						xValO-=10;
    					}
    					if(yValO == 580 && xValO == 180)
    					{
    						opponentMotionState = 3;
    					}
    				}
    				else if(opponentMotionState == 3)
    				{
    					if(xValO == 180 && (yValO>=190&&yValO<=600))
    					{
    						yValO-=10;
    					}
    					if(xValO == 180 && yValO==180)
    					{
    						opponentMotionState = 4;
    					}
    				}
    				else if(opponentMotionState == 4)
    				{
    					if(yValO==180 && (xValO>=180 && xValO<=590))
    					{
    						xValO+=10;
    					}
    					if(xValO == 600 && yValO == 180)
    					{
    						opponentMotionState = 1;
    					}
    				}
    				break;
    		case 4:
    				if((userCarLoop == 1 || userCarLoop == 2 || userCarLoop == 3) && (xValO==380 && yValO==500))
    				{
    					yValO+=80;
    					opponentCarLoop = 3;
    				}
    				if((userCarLoop == 1 || userCarLoop == 2 || userCarLoop == 3) && (xValO==380 && yValO==260))
    				{
    					yValO-=80;
    					opponentCarLoop = 3;
    				}
    				if((userCarLoop == 1 || userCarLoop == 2 || userCarLoop == 3) && (xValO==260 && yValO==360))
    				{
    					xValO-=80;
    					opponentCarLoop = 3;
    				}
    				if((userCarLoop == 1 || userCarLoop == 2 || userCarLoop == 3) && (xValO==520 && yValO==360))
    				{
    					xValO+=80;
    					opponentCarLoop = 3;
    				}
    				if(opponentMotionState == 1)
    				{
    					if((xValO == 510) && (yValO >= 260 && yValO <=490))
    					{
    						yValO+=10;
    					}
    					if(xValO == 510 && yValO == 500)
    					{
    						opponentMotionState = 2;
    					}
    				}
    				else if(opponentMotionState == 2)
    				{
    					if(yValO == 500 && (xValO>=270 && xValO<=520))
    					{
    						xValO-=10;
    					}
    					if(yValO == 500 && xValO == 260)
    					{
    						opponentMotionState = 3;
    					}
    				}
    				else if(opponentMotionState == 3)
    				{
    					if(xValO==260 && (yValO>=270&&yValO<=500))
    					{
    						yValO-=10;
    					}
    					if(xValO==260 && yValO==260)
    					{
    						opponentMotionState = 4;
    					}
    				}
    				else if(opponentMotionState == 4)
    				{
    					if(yValO==260 && (xValO>=260 && xValO<=500))
    					{
    						xValO+=10;
    					}
    					if(xValO == 510 && yValO == 260)
    					{
    						opponentMotionState = 1;
    					}
    				}
    				break;
    		}
		}
    	/* End of opponent car functionality */
    
    	/* User car functionality starts here */
    	if(userCarSpeed == 10)
    	{
    		switch(userCarLoop)
    		{
    			case 1:
    					if(up_Pressed == true)
    					{		
    						yVal+=80;
    						userCarLoop = 2;
    						up_Pressed = false;
    					}
    					if(down_Pressed == true)
    					{			
    						yVal-=80;
    						userCarLoop = 2;
    						down_Pressed = false;
    					}
    					if(left_Pressed == true)
    					{		
    						xVal-=80;
    						userCarLoop = 2;
    						left_Pressed = false;
    					}
    					if(right_Pressed == true)
    					{			
    						xVal+=80;
    						userCarLoop = 2;
    						right_Pressed = false;
    					}
    					if(motionState == 1)
    					{
    						if((xVal == 20) && (yVal >= 20 && yVal <=730))
    						{
    							yVal+=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(xVal == 20 && yVal == 740)
    						{
    							motionState = 2;
    						}
    					}
    					else if(motionState == 2)
    					{
    						if(yVal == 740 && (xVal>=20 && xVal <=750))
    						{
    							xVal+=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(yVal == 740 && xVal == 760)
    						{
    							motionState = 3;
    						}
    					}
    					else if(motionState == 3)
    					{
    						if(xVal == 760 && (yVal>=20&&yVal<=750))
    						{
    							yVal-=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(xVal == 760 && yVal==20)
    						{
    							motionState = 4;
    						}
    					}
    					else if(motionState == 4)
    					{
    						if(yVal==20 && (xVal>=30 && xVal<=760))
    						{
    							xVal-=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(xVal == 20 && yVal == 20)
    						{
    							motionState = 1;
    						}
    					}
    					break;
    			case 2:
    					if(up_Pressed == true)
    					{		
    						yVal+=80;
    						if(yVal==740)
    						{
    							userCarLoop = 1;
    						}
    						else if(yVal==180)
    						{
    							userCarLoop = 3;
    						}
    						up_Pressed = false;
    					}
    					if(down_Pressed == true)
    					{				
    						yVal-=80;
    						if(yVal==20)
    						{
    							userCarLoop = 1;
    						}
    						else if(yVal==580)
    						{
    							userCarLoop = 3;
    						}
    						down_Pressed = false;
    					}
    					if(left_Pressed == true)
    					{		
    						xVal-=80;
    						if(xVal==600)
    						{
    							userCarLoop = 3;
    						}
    						else if(xVal==20)
    						{
    							userCarLoop = 1;
    						}
    						left_Pressed = false;
    					}
    					if(right_Pressed == true)
    					{			
    						xVal+=80;
    						if(xVal==180)
    						{
    							userCarLoop = 3;
    						}
    					else if(xVal==760)
    					{
    						userCarLoop = 1;
    					}
    					right_Pressed = false;
    					}
    					if(motionState == 1)
    					{
    						if((xVal == 100) && (yVal >= 100 && yVal <=650))
    						{
    							yVal+=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(xVal == 100 && yVal == 660)
    						{
    							motionState = 2;
    						}
    					}
    					else if(motionState == 2)
    					{
    						if(yVal == 660 && (xVal>=100 && xVal <=670))
    						{
    							xVal+=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(yVal == 660 && xVal == 680)
    						{
    							motionState = 3;
    						}
    					}
    					else if(motionState == 3)
    					{
    						if(xVal == 680 && (yVal>=100&&yVal<=670))
    						{
    							yVal-=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(xVal == 680 && yVal==100)
    						{
    							motionState = 4;
    						}
    					}
    					else if(motionState == 4)
    					{
    						if(yVal==100 && (xVal>=100 && xVal<=680))
    						{
    							xVal-=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(xVal == 100 && yVal == 100)
    						{
    							motionState = 1;
    						}
    					}
    					break;
    			case 3:
    					if(up_Pressed == true)
    					{		
    						yVal+=80;
    						if(yVal==660)
    						{
    							userCarLoop = 2;
    						}
    						else if(yVal==260)
    						{
    							userCarLoop = 4;
    						}
    						up_Pressed = false;
    					}
    					if(down_Pressed == true)
    					{			
    						yVal-=80;
    						if(yVal==100)
    						{
    							userCarLoop = 2;
    						}
    						else if(yVal==500)
    						{
    							userCarLoop = 4;
    						}
    						down_Pressed = false;
    					}
    					if(left_Pressed == true)
    					{		
    						xVal-=80;
    						if(xVal==520)
    						{
    							userCarLoop = 4;
    						}
    						else if(xVal==100)
    						{
    							userCarLoop = 2;
    						}
    						left_Pressed = false;
    					}
    					if(right_Pressed == true)
    					{			
    						xVal+=80;
    						if(xVal==260)
    						{
    							userCarLoop = 4;
    						}
    						else if(xVal==680)
    						{
    							userCarLoop = 2;
    						}
    						right_Pressed = false;
    					}
    					if(motionState == 1)
    					{
    						if((xVal == 180) && (yVal >= 180 && yVal <=570))
    						{
    							yVal+=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(xVal == 180 && yVal == 580)
    						{
    							motionState = 2;
    						}
    					}
    					else if(motionState == 2)
    					{
    						if(yVal == 580 && (xVal>=180 && xVal <=590))
    						{
    							xVal+=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(yVal == 580 && xVal == 600)
    						{
    							motionState = 3;
    						}
    					}
    					else if(motionState == 3)
    					{
    						if(xVal == 600 && (yVal>=180&&yVal<=590))
    						{
    							yVal-=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(xVal == 600 && yVal==180)
    						{
    							motionState = 4;
    						}
    					}
    					else if(motionState == 4)
    					{
    						if(yVal==180 && (xVal>=180 && xVal<=600))
    						{
    							xVal-=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if((xVal == 180) && yVal == 180)
    						{
    							motionState = 1;
    						}
    					}
    					break;
    			case 4:
    					if(up_Pressed == true)
    					{		
    						yVal+=80;
    						userCarLoop = 3;
    						up_Pressed = false;
    					}
    					if(down_Pressed == true)
    					{			
    						yVal-=80;
    						userCarLoop = 3;
    						down_Pressed = false;
    					}
    					if(left_Pressed == true)
    					{		
    						xVal-=80;
    						userCarLoop = 3;
    						left_Pressed = false;
    					}
    					if(right_Pressed == true)
    					{			
    						xVal+=80;
    						userCarLoop = 3;
    						right_Pressed = false;
    					}
    					if(motionState == 1)
    					{
    						if((xVal == 260) && (yVal >= 260 && yVal <=490))
    						{
    							yVal+=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(xVal == 260 && yVal == 500)
    						{
    							motionState = 2;
    						}
    					}
    					else if(motionState == 2)
    					{
    						if(yVal == 500 && (xVal>=260 && xVal <=510))
    						{
    							xVal+=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(yVal == 500 && xVal == 520)
    						{
    							motionState = 3;
    						}
    					}
    					else if(motionState == 3)
    					{
    						if(xVal == 520 && (yVal>=260&&yVal<=510))
    						{
    							yVal-=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(xVal == 520 && yVal==260)
    						{
    							motionState = 4;
    						}
    					}
    					else if(motionState == 4)
    					{
    						if(yVal==260 && (xVal>=270 && xVal<=520))
    						{
    							xVal-=10;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if((xVal == 260) && yVal == 260)
    						{
    							motionState = 1;
    						}
    					}
    					break;
    		} 
    	}
    	else if(userCarSpeed == 5)
    	{
    
         	switch(userCarLoop)
         	{
         		case 1:
         				if(up_Pressed == true)
         				{		
         					yVal+=80;
         					userCarLoop = 2;
         					up_Pressed = false;
         				}
         				if(down_Pressed == true)
         				{			
         					yVal-=80;
         					userCarLoop = 2;
         					down_Pressed = false;
         				}
         				if(left_Pressed == true)
         				{		
         					xVal-=80;
         					userCarLoop = 2;
         					left_Pressed = false;
         				}
         				if(right_Pressed == true)
         				{			
         					xVal+=80;
         					userCarLoop = 2;
         					right_Pressed = false;
         				}
         				if(motionState == 1)
         				{
         					if((xVal == 20) && (yVal >= 20 && yVal <=735))
         					{
         						yVal+=userCarSpeed;
         					}
         					for(int i = 0; i<66; i++)
         					{
         						if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
         						{
         							dot_Draw_Array[i] = true;
         						}
         					}
         					if(xVal == 20 && yVal == 740)
         					{
         						motionState = 2;
         					}
         				}
         				else if(motionState == 2)
         				{
         					if(yVal == 740 && (xVal>=20 && xVal <=755))
         					{
         						xVal+=userCarSpeed;
         					}
         					for(int i = 0; i<66; i++)
         					{
         						if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
         						{
         							dot_Draw_Array[i] = true;
         						}
         					}
         					if(yVal == 740 && xVal == 760)
         					{
         						motionState = 3;
         					}
         				}
         				else if(motionState == 3)
         				{
         					if(xVal == 760 && (yVal>=20&&yVal<=750))
         					{
         						yVal-=userCarSpeed;
         					}
         					for(int i = 0; i<66; i++)
         					{
         						if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
         						{
         							dot_Draw_Array[i] = true;
         						}
         					}
         					if(xVal == 760 && yVal==20)
         					{
         						motionState = 4;
         					}
         				}
         				else if(motionState == 4)
         				{
         					if(yVal==20 && (xVal>=25 && xVal<=760))
         					{
         						xVal-=userCarSpeed;
         					}
         					for(int i = 0; i<66; i++)
         					{
         						if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
         						{
         							dot_Draw_Array[i] = true;
         						}
         					}
         					if(xVal == 20 && yVal == 20)
         					{
         						motionState = 1;
         					}
         				}
         				break;
         		case 2:
         				if(up_Pressed == true)
         				{		
         					yVal+=80;
         					if(yVal==740)
         					{
         						userCarLoop = 1;
         					}
         					else if(yVal==180)
         					{
         						userCarLoop = 3;
         					}
         					up_Pressed = false;
         				}
         				if(down_Pressed == true)
         				{			
         					yVal-=80;
         					if(yVal==20)
         					{
         						userCarLoop = 1;
         					}
         					else if(yVal==580)
         					{
         						userCarLoop = 3;
         					}
         					down_Pressed = false;
         				}
         				if(left_Pressed == true)
         				{		
         					xVal-=80;
         					if(xVal==600)
         					{
         						userCarLoop = 3;
         					}
         					else if(xVal==20)
         					{
         						userCarLoop = 1;
         					}
         					left_Pressed = false;
         				}
         				if(right_Pressed == true)
         				{			
         					xVal+=80;
         					if(xVal==180)
         					{
         						userCarLoop = 3;
         					}
         					else if(xVal==760)
         					{
         						userCarLoop = 1;
         					}
         					right_Pressed = false;
         				}
         				if(motionState == 1)
         				{
         					if((xVal == 100) && (yVal >= 100 && yVal <=655))
         					{
         						yVal+=5;
         					}
         					for(int i = 0; i<66; i++)
         					{
         						if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
         						{
         							dot_Draw_Array[i] = true;
         						}
         					}
         					if(xVal == 100 && yVal == 660)
         					{
         						motionState = 2;
         					}
         				}
         				else if(motionState == 2)
         				{
         					if(yVal == 660 && (xVal>=100 && xVal <=675))
         					{
         						xVal+=5;
         					}
         					for(int i = 0; i<66; i++)
         					{
         						if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
         						{
         							dot_Draw_Array[i] = true;
         						}
         					}
         					if(yVal == 660 && xVal == 680)
         					{
         						motionState = 3;
         					}
         				}
         				else if(motionState == 3)
         				{
         					if(xVal == 680 && (yVal>=100&&yVal<=670))
         					{
         						yVal-=5;
         					}
         					for(int i = 0; i<66; i++)
         					{
         						if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
         						{
         							dot_Draw_Array[i] = true;
         						}
         					}
         					if(xVal == 680 && yVal==100)
         					{
         						motionState = 4;
         					}
         				}
         				else if(motionState == 4)
         				{
         					if(yVal==100 && (xVal>=95 && xVal<=680))
         					{
         						xVal-=5;
         					}
         					for(int i = 0; i<66; i++)
         					{
         						if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
         						{
         							dot_Draw_Array[i] = true;
         						}
         					}
         					if(xVal == 100 && yVal == 100)
         					{
         						motionState = 1;
         					}
         				}
         				break;
         		case 3:
         				if(up_Pressed == true)
         				{		
         					yVal+=80;
         					if(yVal==660)
         					{
         						userCarLoop = 2;
         					}
         					else if(yVal==260)
         					{
         						userCarLoop = 4;
         					}
         					up_Pressed = false;
         				}
         				if(down_Pressed == true)
         				{			
         					yVal-=80;
         					if(yVal==100)
         					{
         						userCarLoop = 2;
         					}
         					else if(yVal==500)
         					{
         						userCarLoop = 4;
         					}
         					down_Pressed = false;
         				}
         				if(left_Pressed == true)
         				{		
         					xVal-=80;
         					if(xVal==520)
         					{
         						userCarLoop = 4;
         					}
         					else if(xVal==100)
         					{
         						userCarLoop = 2;
         					}
         					left_Pressed = false;
         				}
         				if(right_Pressed == true)
         				{			
         					xVal+=80;
         					if(xVal==260)
         					{
         						userCarLoop = 4;
         					}
         					else if(xVal==680)
         					{
         						userCarLoop = 2;
         					}
         					right_Pressed = false;
         				}
         				if(motionState == 1)
         				{
         					if((xVal == 180) && (yVal >= 180 && yVal <=575))
         					{
         						yVal+=5;
         					}
         					for(int i = 0; i<66; i++)
         					{
         						if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
         						{
         							dot_Draw_Array[i] = true;
         						}
         					}
         					if(xVal == 180 && yVal == 580)
         					{
         						motionState = 2;
         					}
         				}
         				else if(motionState == 2)
         				{
         					if(yVal == 580 && (xVal>=180 && xVal <=595))
         					{
         						xVal+=5;
         					}
         					for(int i = 0; i<66; i++)
         					{
         						if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
         						{
         							dot_Draw_Array[i] = true;
         						}
         					}
         					if(yVal == 580 && xVal == 600)
         					{
         						motionState = 3;
         					}
         				}
         				else if(motionState == 3)
         				{
         					if(xVal == 600 && (yVal>=175&&yVal<=590))
         					{
         						yVal-=5;
         					}
         					for(int i = 0; i<66; i++)
         					{
         						if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
         						{
         							dot_Draw_Array[i] = true;
         						}
         					}
         					if(xVal == 600 && yVal==180)
         					{
         						motionState = 4;
         					}
         				}
         				else if(motionState == 4)
         				{
         					if(yVal==180 && (xVal>=175 && xVal<=600))
         					{
         						xVal-=5;
         					}
         					for(int i = 0; i<66; i++)
         					{
         						if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
         						{
         							dot_Draw_Array[i] = true;
         						}
         					}
         					if((xVal == 180) && yVal == 180)
         					{
         						motionState = 1;
         					}
         				}
         				break;
    			case 4:
    					if(up_Pressed == true)
    					{		
    						yVal+=80;
    						userCarLoop = 3;
    						up_Pressed = false;
    					}
    					if(down_Pressed == true)
    					{			
    						yVal-=80;
    						userCarLoop = 3;
    						down_Pressed = false;
    					}
    					if(left_Pressed == true)
    					{		
    						xVal-=80;
    						userCarLoop = 3;
    						left_Pressed = false;
    					}
    					if(right_Pressed == true)
    					{			
    						xVal+=80;
    						userCarLoop = 3;
    						right_Pressed = false;
    					}
    					if(motionState == 1)
    					{
    						if((xVal == 260) && (yVal >= 260 && yVal <=495))
    						{
    							yVal+=5;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(xVal == 260 && yVal == 500)
    						{
    							motionState = 2;
    						}
    					}
    					else if(motionState == 2)
    					{
    						if(yVal == 500 && (xVal>=260 && xVal <=515))
    						{
    							xVal+=5;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(yVal == 500 && xVal == 520)
    						{
    							motionState = 3;
    						}
    					}
    					else if(motionState == 3)
    					{
    						if(xVal == 520 && (yVal>=255&&yVal<=510))
    						{
    							yVal-=5;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if(xVal == 520 && yVal==260)
    						{
    							motionState = 4;
    						}
    					}
    					else if(motionState == 4)
    					{	
    						if(yVal==260 && (xVal>=265 && xVal<=520))
    						{
    							xVal-=5;
    						}
    						for(int i = 0; i<66; i++)
    						{
    							if(dot_location_Array[0][i] == (xVal+30) && (dot_location_Array[1][i] == (yVal+30) || dot_location_Array[1][i] == (yVal+20)))
    							{
    								dot_Draw_Array[i] = true;
    							}
    						}
    						if((xVal == 260) && yVal == 260)
    						{
    							motionState = 1;
    						}
    					}
    					break;
    		}
    	}
	}
	/* User Car Function End */
    glutPostRedisplay();
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(10.0, Timer, 0);
}


void MousePressedAndMoved(int x, int y) 
{
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) 
{

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}
int highScoreFunc(int fileHighScore){
	bool highScoreFlag = false;
	string scoreline;
  	ifstream scoreFile("highscores.txt");
  	if (scoreFile.is_open())
  	{
    	while (getline(scoreFile, scoreline)) 
    	{
      		if(Str2Num(scoreline) < fileHighScore)
			{

			}
    	}
    	scoreFile.close();
  	}
	return highScoreFlag;
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	//b = new Board(60, 60); // create a new board object to use in the Display Function ...
	int width = 840, height = 900; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Dodge Em'"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	glutKeyboardUpFunc(keysPressed); // tell library which function to call when a key is pressed
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
