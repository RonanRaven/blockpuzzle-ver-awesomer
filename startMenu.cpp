#include "cli.h"
#include "startMenu.h"
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

#define StartTime 500
#define Delaytime 1000

startMenu::startMenu()
{
	gamemode=NULL;
	GameModeSelected=false;
	MenuFinished=false;
	color1=7;
	int accum=0;

}

void startMenu::drawMenu(int &then,int &now)
{
	srand(time(0));
	
	int difference =now-then;
	accum +=difference;
	if(accum>StartTime)
	{
		color1=( (rand() %9)+7);
		accum=0;
		then = now;
	}
	setcolor(color1,COLOR_BLACK);
	cout<<"Welcome to the 'Block Puzzle Game'"<<endl;
	colorchange((accum<StartTime));
	cout<<"Please select how you would like to play:"<<endl<<endl;
	colorchange((accum<StartTime));
	cout<<"Play normally (n), ";
	colorchange((accum<StartTime));
	cout<< "\nwith expandable rows (r), ";
	colorchange((accum<StartTime));
	cout<< "\nwith expandable collumns (c), ";
	colorchange((accum<StartTime));
	cout<< "\nor with both (b), ";
	setcolor(COLOR_GRAY,COLOR_BLACK);
	cout<< "\n\nESC to pause and to view this menu, ";
	cout<< "\nor press Q to quit:";
	cout<<endl<<endl;
	if(gamemode=='r'||gamemode=='c'||gamemode=='b')
	{
		cout<<"You have chosen "<<gamemode<<"."<<endl;
		cout<<"Now, would you like the board to grow(g), or shrink(s)?";
	}
}


bool startMenu::menuInput(int input)
{
	if(!GameModeSelected)
	{
		switch(input)
		{
		case 'N':
		case 'n':
			gamemode='n';
			MenuFinished=true;
			break;
		case 'R':
		case 'r':
		case 'C':
		case 'c':
		case 'B':
		case 'b':
			gamemode=input;
			GameModeSelected=true;
			break;
		case 'Q':
		case 'q':
			return false;
		case 27:
			if(gamemode==NULL)
			{
				gamemode='n';
			}
			GameModeSelected=true;
			MenuFinished=true;
			return true;
		}
	}
	if(GameModeSelected)
	{
		switch(input)
		{
		case 'G':
		case 'g':
			amounttogrow=1;
			MenuFinished=true;
			break;
		case 'S':
		case 's':
			amounttogrow=-1;
			MenuFinished=true;
			break;
		case 27:
			return true;
		case 'Q':
		case 'q':
			return false;
		}

	}
	return true;

}

void startMenu::colorchange(bool answer)
{
	int color;
	if(answer)
	{
		 color=( (rand() %9)+7);
	}
	setcolor(color,COLOR_BLACK);
}