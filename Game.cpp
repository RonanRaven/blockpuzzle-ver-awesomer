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

#define sizeX 8
#define sizeY 5
#define droptime 480
#define rowstillgrow 5
#define maxsizerow 25
#define maxsizecol 20
#define minsizerow 10
#define minsizecol 6

Random random;
char gamemode;
int amounttogrow;

Game::Game()
{
	gamerunning=true;
	rowscleared=0;
}


void Game::run()
{
	char boardtype;
	int now, then=clock();
	int timeDelay=800;
	disableFlashingCursor();

	startx=board.getcol()/2;
	starty=0;

	//lets figure out where to print the title

	piece.newpiece(random.getInt(0,6),startx,starty);

	cout<<"Welcome to the 'Block Puzzle Game'"<<endl;
	cout<<"Please select how you would like to play:"<<endl<<endl;

	cout<<"Play normally (n), \nwith expandable rows (y), \nwith expandable collumns (c), \nor with both (b): ";
	cin>>gamemode;
	while(gamemode!='n'&&gamemode!='y'&&gamemode!='c'&&gamemode!='b')
	{
		system("cls");
		cout<<"Play normally (n), \nwith expandable rows (y), \nwith expandable collumns (c), \nor with both (b): ";
		cin>>gamemode;
	}
	cout<<endl;
	if(gamemode=='y'||gamemode=='c'||gamemode=='b')
	{
		cout<<"Now, would you like the board to grow(g), or shrink(s)?";
		cin>>boardtype;
		while(boardtype!='g'&&boardtype!='s')
		{
			system("cls");
			cout<<"Now, would you like the board to grow(g), or shrink(s)?";
			cin>>boardtype;
		}
		if(boardtype=='g')
			amounttogrow=1;
		else //its s
			amounttogrow=-1;
	}

	system("cls");
	while(gamerunning)
	{	
		while(!kbhit())
		{
			now=clock();
			processGameLogic();
			drawWorld();
			gotoxy(sizeX,sizeY);//to keep the screen from jittering around
			if(now>then+droptime)
			{
				moveDown();
				then=now;
			}
			while(!kbhit()&&clock()<now+timeDelay)
			{
				Sleep(1);
			}
		}
		input=getch();
		processInput();
	}
	//game over X_X
	cout<<"GAME OVER"<<endl;
}

void Game::drawWorld()
{
	gotoxy(board.getcol()/2,sizeY-2);// 2 is right above where it's printed
	cout<<"Block Puzzle Game";
	board.draw(sizeX,sizeY);
	piece.draw(sizeX,sizeY);
	showLinesCleared(sizeX, sizeY);
}

void Game::processGameLogic()
{
	//check if the line is complete
	//checkline();
	int counter=0;
	for(int r=0;r<board.getrow();r++)
	{
		for(int c=0;c<board.getcol();c++)
		{
			if(board.table[r][c]=='*')
				counter++;
			if(counter>=board.getcol())
			{
				board.deleterow(r);
				rowscleared++;
				if(rowscleared%rowstillgrow==0)
				{
					//if(board.getcol()>minsizecol&&board.gboard.getrow()//if it is between the min and max let it grow/shrink
					if((gamemode=='b'||gamemode=='r')&&((board.getrow()>minsizerow)&&(board.getrow()<maxsizerow)))
						board.growRow(amounttogrow);
					if((gamemode=='b'||gamemode=='c')&&((board.getcol()>minsizecol)&&(board.getcol()<maxsizecol)))
					{
						board.growCol(amounttogrow);
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
		if((gamemode=='b'||gamemode=='r')&&((board.getrow()>minsizerow)&&(board.getrow()<maxsizerow)))
			board.growRow(amounttogrow);
		if((gamemode=='b'||gamemode=='c')&&((board.getcol()>minsizecol)&&(board.getcol()<maxsizecol)))
		{
			board.growCol(amounttogrow);
			startx=(board.getcol()/2);
		}
		break;
		
	case 27:
		gamerunning=false;
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
		piece.newpiece(random.getInt(0,6),startx,starty);
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