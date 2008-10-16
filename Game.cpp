//
//Bryant Hetherington
//
#include "Game.h"
#include "cli.h"
#include "random.h"
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iostream>
using namespace std;

#define sizeX 16
#define sizeY 2
#define droptime 480
#define rowstillgrow 5
#define maxsizerow 30
#define maxsizecol 25
#define minsizerow 10
#define minsizecol 6
Random random;//has some weird conflicts/errors if random is placed into game.h

Game::Game()
{
	gamerunning=true;
	rowscleared=0;
}


void Game::run()
{
	score = 0;
	nextBoard = new Board(6,5);
	int now, then=clock();
	int timeDelay=800;
	disableFlashingCursor();

	startx=board.getcol()/2;
	starty=0;

	//lets figure out where to print the title
	nextPiece.newpiece(random.getInt(0,6),0,0);
	piece.newpiece(random.getInt(0,6),startx,starty);
	//piece = nextPiece;
	while(gamerunning)
	{	
		while(!kbhit()&&gamerunning)
		{
			now=clock();
			processGameLogic(then, now);
			drawWorld();
			gotoxy(sizeX,sizeY);//to keep the screen from jittering around
			while(!kbhit()&&clock()<now+timeDelay)
			{
				Sleep(1);
			}
		}
		if(gamerunning)
		{
			input=getch();
			processInput();
		}
	}
	//game over X_X
	cout<<"GAME OVER"<<endl;
}

void Game::drawWorld()
{
	gotoxy(board.getcol()/2,sizeY-2);// 2 is right above where it's printed
	if(!menu.MenuFinished)
	{
		menu.drawMenu();
	}
	else
	{
		//brandon
		//draw next piece
		cout<<"Block Puzzle Game";
		board.draw(sizeX,sizeY);
		piece.draw(sizeX,sizeY);
		nextBoard->draw(5,7);
		nextPiece.draw(6,8);
		showLinesCleared(sizeX, sizeY);
		showScore(sizeX, sizeY);
		//brandon
		//show score (maybe instead of lines cleared) you can also create how score is done and implement it
	}
}

void Game::processGameLogic(int &then, int &now)
{
	//brandon
	//make the droptime not a defined value, but a variable that can change, and implement changing speed.
	if(now>then+(droptime / ((rowscleared / 15) + 1))&&menu.MenuFinished)
	{
		moveDown();
		then=now;
	}
	//check if the line is complete
	//checkline();
	int counter=0;
	for(int r=0;r<board.getrow();r++)
	{
		for(int c=0;c<board.getcol();c++)
		{
			if(board.checkAt(r,c)=='*')
				counter++;
			if(counter>=board.getcol())
			{
				board.deleterow(r);
				rowscleared++;
				score += 10;
				if(rowscleared%rowstillgrow==0)
				{
					//if(board.getcol()>minsizecol&&board.gboard.getrow()//if it is between the min and max let it grow/shrink
					if((menu.getMode()=='b'||menu.getMode()=='r')&&((board.getrow()>minsizerow)&&(board.getrow()<maxsizerow)))
						board.growRow(menu.getGrow());
					if((menu.getMode()=='b'||menu.getMode()=='c')&&((board.getcol()>minsizecol)&&(board.getcol()<maxsizecol)))
					{
						board.growCol(menu.getGrow());
						startx=(board.getcol()/2);
					}
					system("cls");
				}
			}
		}
		counter=0;
	}
}

void Game::processInput()
{
	if(!menu.MenuFinished)
	{
		system("cls");
		gamerunning=menu.menuInput(input);
	}
	else
	{
		switch(input)
		{
			//left arrow = -32 75 'K'
			//right arrow = -32 77 'M'
			//up arrow = -32 72 'H'
			//down arrow = -32 80 'P'
		case 'W':
		case 'w':
		case 'H'://up key
			upPressed();
			break;
		case 'A':
		case 'a':
		case 'K': //left key
			moveLeft();
			break;
		case 'S':
		case 's':
		case 'P'://down key
			moveDown();
			break;
		case 'D':
		case 'd':
		case 'M'://right key
			moveRight();
			break;
		case 'Q':
		case 'q':
			rotateCCW();
			break;
		case 'E':
		case 'e':
			rotateCW();
			break;
		case ' '://debug/display purposes only
			
			system("cls");
			if((menu.getMode()=='b'||menu.getMode()=='r')&&((board.getrow()>minsizerow)&&(board.getrow()<maxsizerow)))
				board.growRow(menu.getGrow());
			if((menu.getMode()=='b'||menu.getMode()=='c')&&((board.getcol()>minsizecol)&&(board.getcol()<maxsizecol)))
			{
				board.growCol(menu.getGrow());
				startx=(board.getcol()/2);
			}
			break;
			
		case 27:
			menu.setMode(0,false);
			menu.MenuFinished=false;
			system("cls");
			break;
		}
	}
}

void Game::moveLeft()
{
	piece.left();
	//if it hits something, or goes off the edge
	if(board.outside(piece)||board.collision(piece))
		piece.right();
}
void Game::moveRight()
{
	piece.right();
	//if it hits something, or goes off the edge
	if(board.outside(piece)||board.collision(piece))
		piece.left();
	
}
bool Game::moveDown()
{
	piece.down();
	//if it collides with something on the board, or if it gets to the bottom
	if(board.outside(piece)||board.collision(piece))
	{
		if(piece.getx()==startx&&piece.gety()<=1)
			gamerunning=false;
		piece.up();
		board.putblock(piece);
		piece.deletepiece();
		piece = nextPiece;
		piece.setXY(startx,starty);
		nextPiece.newpiece(random.getInt(0,6),0,0);
		score++;
		return true;
	}
	else
		return false;
}
void Game::rotateCW()
{

	piece.RotateCW();
	if(board.outside(piece)||board.collision(piece))
	{
		piece.RotateCCW();
	}
}
void Game::rotateCCW()
{
	piece.RotateCCW();
	if(board.outside(piece)||board.collision(piece))
	{
		piece.RotateCW();
	}
}
void Game::upPressed()
{
	int r=board.getrow()-piece.gety();
	for(int num=0;num<r;num++)
	{
		if(moveDown())
			break;
	}
}

void Game::showLinesCleared(int offsetX, int offsetY)
{
	gotoxy(startx-3,board.getrow()+offsetY+1);
	cout<<"Number of lines cleared: "<<rowscleared;
}

void Game::showScore(int offsetX, int offsetY)
{
	gotoxy(startx-3,board.getrow()+offsetY+2);
	cout<<"Score: "<< score;
}