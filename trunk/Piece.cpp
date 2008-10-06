//
//Bryant Hetherington
//
#include "Piece.h"
#include "cli.h"

#include <fstream>
#include <iostream>
#include <time.h>
using namespace std;
//#include "random.h";
//Random random;

Piece::Piece()
{	
	block=NULL;
	//newpiece(random.getInt(0,6),4,0);
}

void Piece::draw(int offsetx, int offsety)
{	
	for(int r_count=0;r_count<row;r_count++)
	{		
		for(int c_count=0;c_count<col;c_count++)
		{			
			gotoxy(offsetx+x+c_count,offsety+y+r_count);
			if(block[r_count][c_count]=='*')
			{
				setcolor(color,COLOR_BLACK);
				cout<<(char)254;//the square
				setcolor(COLOR_GRAY,COLOR_BLACK);
			}
		}
	}
}

void Piece::newpiece(int number, int numx, int numy)
{
	x=numx;
	y=numy;
	color=COLOR_CYAN;
	ifstream file;
	switch(number)
	{// open files according to which tetrad
	case 0:
		//**
		//**
		file.open("X.txt");
		color=COLOR_DARK_BLUE;
		break;
	case 1:
		//** 
		// **
		file.open("Z.txt");
		color=COLOR_CYAN;
		break;
	case 2:
		// **
		//** 
		file.open("BZ.txt");
		color=COLOR_GREEN;
		break;
	case 3:
		// * 
		//***
		file.open("T.txt");
		color=COLOR_DARK_YELLOW;
		break;
	case 4:
		//* 
		//* 
		//**
		file.open("L.txt");
		color=COLOR_MAGENTA;
		break;
	case 5:
		// *
		// *
		//**
		file.open("BL.txt");
		color=COLOR_DARK_GRAY;
		break;
	case 6:
		//*
		//*
		//*
		//*
		file.open("I.txt");
		color=COLOR_RED;
		break;
	default:
		//*
		//
		file.open("D.txt");
		color=COLOR_WHITE;
		break;
	}
	//create the array depending on the file opened
	file>>col;
	file>>row;
	
	block=new char* [row];
	for(int index=0;index<row;index++)
	{
		block[index]=new char[col];
	}

	for(int r_count=0;r_count<row;r_count++)
	{
		for(int c_count=0;c_count<col;c_count++)
		{
			file.get(block[r_count][c_count]);
			if(block[r_count][c_count]=='\n'||block[r_count][c_count]=='\r')
			{
				file.get(block[r_count][c_count]);
			}
		}
	}

	file.close();
}
void Piece::deletepiece()
{
	//delete's
	for(int r_count=0;r_count<row;r_count++)
	{
		delete block[r_count];
	}
	delete block;
	block=NULL;
	row=0;
	col=0;
	x=0;
	y=0;
}
void Piece::up()
{
	y--;
}
void Piece::down()
{
	y++;
}
void Piece::left()
{
	x--;
}
void Piece::right()
{
	x++;
}
void Piece::RotateCW()
{
	char** newMap=new char*[col];
	for(int r=0;r<col;r++)
	{
		newMap[r]=new char[row];
		for(int c=0;c<row;c++)
		{
			//cout<<block[(row-1)-c][r];
			newMap[r][c]=block[(row-1)-c][r];
		}
		cout<<endl;
	}
	delete block;
	block=newMap;

	int temp=row;
	row=col;
	col=temp;

	//x=x+1;
	//y=y-1;
}
void Piece::RotateCCW()
{
	char** newMap=new char*[col];
	for(int r=0;r<col;r++)
	{
		newMap[r]=new char[row];
		for(int c=0;c<row;c++)
		{
			//cout<<block[(row-1)-c][r];
			newMap[r][c]=block[c][(col-1)-r];
		}
		cout<<endl;
	}
	delete block;
	block=newMap;
	
	int temp=row;
	row=col;
	col=temp;
}
void Piece::flipH()
{
	char** newMap=new char*[row];
	for(int r=0;r<row;r++)
	{
		newMap[r]=new char[col];
		for(int c=0;c<col;c++)
		{
			newMap[r][c]=block[r][(col-1)-c];
		}
	}
	delete block;
	block=newMap;
}
void Piece::flipV()
{
	char** newMap=new char*[row];
	for(int r=0;r<row;r++)
	{
		newMap[r]=new char[col];
		for(int c=0;c<col;c++)
		{
			newMap[r][c]=block[(row-1)-r][c];
		}
	}
	delete block;
	block=newMap;
}
//row = height
//col = width
/*
//cw
char** newMap=new char*[col];
	for(int c=0;r<col;c++)
	{
		newMap[r]=new char[col];
		for(int c=0;c<col;c++)
		{
			newMap[r][c]=block[(row-1)r][c];
		}
	}
	delete block;
	block=newMap;
	*/