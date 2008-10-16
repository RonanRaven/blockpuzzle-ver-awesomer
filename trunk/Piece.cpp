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
	map.table=NULL;
	//newpiece(random.getInt(0,6),4,0);
}

void Piece::draw(int offsetx, int offsety)
{	
	for(int r_count=0;r_count<getrow();r_count++)
	{		
		for(int c_count=0;c_count<getcol();c_count++)
		{			
			gotoxy(offsetx+x+c_count,offsety+y+r_count);
			if(checkAt(r_count,c_count)=='*')
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
	pieceType=number;
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
	case 7:
		file.open("F.txt");
		color=COLOR_MAGENTA;
		break;
	default:
		//*
		//
		file.open("D.txt");
		color=COLOR_WHITE;
		break;
	}
	//create the array depending on the file opened
	int temp;
	file>>temp;
	setcol(temp);
	file>>temp;
	setrow(temp);
	
	map.createTable(map.getrow(),map.getcol());

	char buffer;
	for(int r_count=0;r_count<getrow();r_count++)
	{
		for(int c_count=0;c_count<getcol();c_count++)
		{
			file.get(buffer);
			setAt(r_count,c_count,buffer);

			if(checkAt(r_count,c_count)=='\n'||checkAt(r_count,c_count)=='\r')
			{
				file.get(buffer);
				setAt(r_count,c_count,buffer);
			}
		}
	}

	file.close();
}
void Piece::deletepiece()
{
	//delete's
	map.deleteTable();
	map.table=NULL;
	setrow(0);
	setcol(0);
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
	char** newMap=new char*[getcol()];
	for(int r=0;r<getcol();r++)
	{
		newMap[r]=new char[getrow()];
		for(int c=0;c<getrow();c++)
		{
			//cout<<table[(getrow()-1)-c][r];
			newMap[r][c]=map.checkAt((getrow()-1)-c,r);
		}
		cout<<endl;
	}
	map.deleteTable();
	map.table=newMap;

	int temp=getrow();
	setrow(getcol());
	setcol(temp);
	//x=x+1;
	//y=y-1;
}
void Piece::RotateCCW()
{
	char** newMap=new char*[getcol()];
	for(int r=0;r<getcol();r++)
	{
		newMap[r]=new char[getrow()];
		for(int c=0;c<getrow();c++)
		{
			//cout<<table[(getrow()-1)-c][r];
			newMap[r][c]=map.checkAt(c,(getcol()-1)-r);
		}
		cout<<endl;
	}
	map.deleteTable();
	map.table=newMap;
	
	int temp=getrow();
	setrow(getcol());
	setcol(temp);
}
void Piece::flipH()
{
	char** newMap=new char*[getrow()];
	for(int r=0;r<getrow();r++)
	{
		newMap[r]=new char[getcol()];
		for(int c=0;c<getcol();c++)
		{
			newMap[r][c]=map.checkAt(r,(getcol()-1)-c);
		}
	}
	map.deleteTable();
	map.table=newMap;
}
void Piece::flipV()
{
	char** newMap=new char*[getrow()];
	for(int r=0;r<getrow();r++)
	{
		newMap[r]=new char[getcol()];
		for(int c=0;c<getcol();c++)
		{
			newMap[r][c]=map.checkAt((getrow()-1)-r,c);
		}
	}
	map.deleteTable();
	map.table=newMap;
}
//getrow() = height
//getcol() = width
/*
//cw
char** newMap=new char*[getcol()];
	for(int c=0;r<getcol();c++)
	{
		newMap[r]=new char[getcol()];
		for(int c=0;c<getcol();c++)
		{
			newMap[r][c]=table[(getrow()-1)r][c];
		}
	}
	delete table;
	table=newMap;
	*/