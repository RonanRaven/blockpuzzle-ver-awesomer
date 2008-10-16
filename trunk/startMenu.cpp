#include "cli.h"
#include "startMenu.h"
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iostream>
using namespace std;

startMenu::startMenu()
{
	gamemode=NULL;
	GameModeSelected=false;
	MenuFinished=false;

}

void startMenu::drawMenu()
{
	cout<<"Welcome to the 'Block Puzzle Game'"<<endl;
	cout<<"Please select how you would like to play:"<<endl<<endl;

	cout<<"Play normally (n), \nwith expandable rows (r), \nwith expandable collumns (c), \nor with both (b), \n\nESC to pause and to view this menu, \nor press Q to quit:";
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