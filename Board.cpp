//
//Bryant Hetherington
//
#include "Board.h"
#include <iostream>
using namespace std;
#include <conio.h>




Board::Board()
{
	setrow(rows);
	setcol(collumns);

	map.table=new char* [getrow()];
	color=new int* [getrow()];
	for(int index=0;index<getrow();index++)
	{
		map.table[index]=new char[getcol()];
		color[index]=new int[getcol()];
	}

	for(int r=0; r<getrow();r++)
	{
		for(int c=0;c<getcol();c++)
		{
			map.table[r][c]=' ';
		}
	}
}

Board::Board(int row,int coll)
{
	setrow(row);
	setcol(coll);

	map.table=new char* [getrow()];
	color=new int* [getrow()];
	for(int index=0;index<getrow();index++)
	{
		map.table[index]=new char[getcol()];
		color[index]=new int[getcol()];
	}

	for(int r=0; r<getrow();r++)
	{
		for(int c=0;c<getcol();c++)
		{
			map.table[r][c]=' ';
		}
	}
}

void Board::draw(int offsetx, int offsety)
{	
	for(int r=-1;r<getrow()+1;r++)
	{
		for(int c=-1;c<getcol()+1;c++)
		{
			
			if(r==-1&&c==-1)//top left
			{
				gotoxy(c+offsetx, offsety+r);
				cout<<(char)201;
			}
			else if(r==-1&&c==getcol())//top right
			{
				gotoxy(c+offsetx, offsety+r);
				cout<<(char)187;
			}
			else if(r==getrow()&&c==-1)//bottom left
			{
				gotoxy(c+offsetx, offsety+r);
				cout<<(char)200;
			}
			else if(r==getrow()&&c==getcol())//bottom right
			{
				gotoxy(c+offsetx, offsety+r);
				cout<<(char)188;
			}
			else if(c==-1||c==getcol())
			{
				gotoxy(c+offsetx, offsety+r);
				cout<<(char)186;
			}
			else if(c>=0&&c<getcol())//top and bottom
			{
				gotoxy(c+offsetx, offsety-1);
				cout<<(char)205;
				gotoxy(c+offsetx, offsety+getrow());
				cout<<(char)205;

				if(r>=0&&r<getrow())
				{
					//draw the board
					gotoxy(c+offsetx, r+offsety);
					if(map.table[r][c]==' ')
					{
						setcolor(COLOR_BLACK,COLOR_WHITE);
						cout<<' ';
						setcolor(COLOR_GRAY,COLOR_BLACK);
					}
					else if(map.table[r][c]=='*')
					{
						setcolor(color[r][c],COLOR_BLACK);
						cout<<(char)254;//the square
						setcolor(COLOR_GRAY,COLOR_BLACK);
					}
				}
			}
		}
	}

/*
	//system("cls");
	for(int r=0; r<getrow();r++)
	{
		for(int c=0;c<getcol();c++)
		{
			gotoxy(c+offsetx, r+offsety);
			if(map.table[r][c]==' ')
			{
				setcolor(COLOR_BLACK,COLOR_WHITE);
				cout<<' ';
				setcolor(COLOR_GRAY,COLOR_BLACK);
			}
			else if(map.table[r][c]=='*')
			{
				setcolor(color[r][c],COLOR_BLACK);
				cout<<(char)254;//the square
				setcolor(COLOR_GRAY,COLOR_BLACK);
			}
		}
		cout<<endl;
	}
*/

}
void Board::putblock(Piece &piece)
{
	for(int r=0;r<piece.getrow();r++)
	{
		for(int c=0;c<piece.getcol();c++)
		{
			if(piece.checkAt(r,c)!=' ')
			{
				setAt(r+piece.gety(),c+piece.getx(),piece.checkAt(r,c));
				//map.table[r+piece.gety()][c+piece.getx()]=piece.checkAt(r,c);//piece.map.table[r][c];
				color[r+piece.gety()][c+piece.getx()]=piece.getcolor();
			}
		}
	}
}
bool Board::collision(Piece &piece)
{
	bool collide = false;
	for(int r_count=0;r_count<piece.getrow();r_count++)
	{
		for(int c_count=0;c_count<piece.getcol();c_count++)
		{
			if(checkAt(piece.gety()+r_count,piece.getx()+c_count)=='*' && piece.checkAt(r_count,c_count)=='*')
			{
				return true;
				//break;
			}
		}
	}
	return false;
}
bool Board::outside(Piece &piece)
{
	//x++ (to the right)
	if(piece.getx()+piece.getcol()>getcol())
		return true;
	//x-- (to the left)
	else if(piece.getx()<0)
		return true;
	//y++ (to the bottom)
	else if(piece.gety()+piece.getrow()>getrow())
		return true;
	//y-- (to the top)
	else if(piece.gety()<0)
		return true;
	else
		return false;
}
void Board::deleterow(int num)
{
	for(int r=num;r>=0;r--)
	{
		for(int c=0;c<getcol();c++)
		{
			if(r>0)
			{
				map.table[r][c]=map.table[r-1][c];
				color[r][c]=color[r-1][c];
			}
			else
			{
				map.table[r][c]=' ';
			}
		}
	}
}

void Board::deletecol(int num)
{
	for(int c=num;c>=0;c--)
	{
		for(int r=0;r<getrow();r++)
		{
			if(c>0)
			{
				map.table[r][c]=map.table[r][c-1];
				color[r][c]=color[r][c-1];
			}
			else
			{
				map.table[r][c]=' ';
			}
		}
	}
}

void Board::growRow(int numtogrow)
{
	setrow(getrow()+numtogrow);
	char** newMap=new char*[getrow()];
	int** newColor=new int*[getrow()];
	for(int r=0;r<getrow();r++)
	{
		newMap[r]=new char[getcol()];
		newColor[r]=new int[getcol()];
		for(int c=0;c<getcol();c++)
		{
			if(r>=getrow()-numtogrow)
			{
				newMap[r][c]=' ';
				newColor[r][c]=15;//white
			}
			else
			{
				newMap[r][c]=map.table[r][c];
				newColor[r][c]=color[r][c];
			}
		}
	}
	delete map.table;
	delete color;
	map.table=newMap;
	color=newColor;
	//delete the empty rows at the bottom
	for(int r=getrow()-numtogrow;r<getrow();r++)
	{
		deleterow(r);
	}
}
void Board::growCol(int numtogrow)//re-visit
{
	setcol(getcol()+numtogrow);
	char** newMap=new char*[getrow()];
	int** newColor=new int*[getrow()];
	for(int r=0;r<getrow();r++)
	{
		newMap[r]=new char[getcol()];
		newColor[r]=new int[getcol()];
		for(int c=0;c<getcol();c++)
		{
			if(c>=getcol()-numtogrow)
			{
				newMap[r][c]=' ';
				newColor[r][c]=15;//white
			}
			else
			{
				newMap[r][c]=map.table[r][c];
				newColor[r][c]=color[r][c];
			}
		}
	}
	delete map.table;
	delete color;
	map.table=newMap;
	color=newColor;
	//delete the empty rows at the right
	for(int c=getcol()-numtogrow;c<getcol();c++)
	{
		deletecol(c);
	}
}