//
//Bryant Hetherington
//
#include "Board.h"
#include <iostream>
using namespace std;
#include <conio.h>




Board::Board()
{
	row=rows;
	col=collumns;

	table=new char* [row];
	color=new int* [row];
	for(int index=0;index<row;index++)
	{
		table[index]=new char[col];
		color[index]=new int[col];
	}

	for(int r=0; r<row;r++)
	{
		for(int c=0;c<col;c++)
		{
			table[r][c]=' ';
		}
	}
}

void Board::draw(int offsetx, int offsety)
{	
	for(int r=-1;r<row+1;r++)
	{
		for(int c=-1;c<col+1;c++)
		{
			
			if(r==-1&&c==-1)//top left
			{
				gotoxy(c+offsetx, offsety+r);
				cout<<(char)201;
			}
			else if(r==-1&&c==col)//top right
			{
				gotoxy(c+offsetx, offsety+r);
				cout<<(char)187;
			}
			else if(r==row&&c==-1)//bottom left
			{
				gotoxy(c+offsetx, offsety+r);
				cout<<(char)200;
			}
			else if(r==row&&c==col)//bottom right
			{
				gotoxy(c+offsetx, offsety+r);
				cout<<(char)188;
			}
			else if(c==-1||c==col)
			{
				gotoxy(c+offsetx, offsety+r);
				cout<<(char)186;
			}
			else if(c>=0&&c<col)//top and bottom
			{
				gotoxy(c+offsetx, offsety-1);
				cout<<(char)205;
				gotoxy(c+offsetx, offsety+row);
				cout<<(char)205;

				if(r>=0&&r<row)
				{
					//draw the board
					gotoxy(c+offsetx, r+offsety);
					if(table[r][c]==' ')
					{
						setcolor(COLOR_BLACK,COLOR_WHITE);
						cout<<' ';
						setcolor(COLOR_GRAY,COLOR_BLACK);
					}
					else if(table[r][c]=='*')
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
	for(int r=0; r<row;r++)
	{
		for(int c=0;c<col;c++)
		{
			gotoxy(c+offsetx, r+offsety);
			if(table[r][c]==' ')
			{
				setcolor(COLOR_BLACK,COLOR_WHITE);
				cout<<' ';
				setcolor(COLOR_GRAY,COLOR_BLACK);
			}
			else if(table[r][c]=='*')
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
			if(piece.block[r][c]!=' ')
			{
				table[r+piece.gety()][c+piece.getx()]=piece.block[r][c];
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
			if(table[piece.gety()+r_count][piece.getx()+c_count]=='*' && piece.block[r_count][c_count]=='*')
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
	if(piece.getx()+piece.getcol()>col)
		return true;
	//x-- (to the left)
	else if(piece.getx()<0)
		return true;
	//y++ (to the bottom)
	else if(piece.gety()+piece.getrow()>row)
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
		for(int c=0;c<col;c++)
		{
			if(r>0)
			{
				table[r][c]=table[r-1][c];
				color[r][c]=color[r-1][c];
			}
			else
			{
				table[r][c]=' ';
			}
		}
	}
}

void Board::deletecol(int num)
{
	for(int c=num;c>=0;c--)
	{
		for(int r=0;r<row;r++)
		{
			if(c>0)
			{
				table[r][c]=table[r][c-1];
				color[r][c]=color[r][c-1];
			}
			else
			{
				table[r][c]=' ';
			}
		}
	}
}

void Board::growRow(int numtogrow)
{
	row+=numtogrow;
	char** newMap=new char*[row];
	int** newColor=new int*[row];
	for(int r=0;r<row;r++)
	{
		newMap[r]=new char[col];
		newColor[r]=new int[col];
		for(int c=0;c<col;c++)
		{
			if(r>=row-numtogrow)
			{
				newMap[r][c]=' ';
				newColor[r][c]=15;//white
			}
			else
			{
				newMap[r][c]=table[r][c];
				newColor[r][c]=color[r][c];
			}
		}
	}
	delete table;
	delete color;
	table=newMap;
	color=newColor;
	//delete the empty rows at the bottom
	for(int r=row-numtogrow;r<row;r++)
	{
		deleterow(r);
	}
}
void Board::growCol(int numtogrow)//re-visit
{
	col+=numtogrow;
	char** newMap=new char*[row];
	int** newColor=new int*[row];
	for(int r=0;r<row;r++)
	{
		newMap[r]=new char[col];
		newColor[r]=new int[col];
		for(int c=0;c<col;c++)
		{
			if(c>=col-numtogrow)
			{
				newMap[r][c]=' ';
				newColor[r][c]=15;//white
			}
			else
			{
				newMap[r][c]=table[r][c];
				newColor[r][c]=color[r][c];
			}
		}
	}
	delete table;
	delete color;
	table=newMap;
	color=newColor;
	//delete the empty rows at the right
	for(int c=col-numtogrow;c<col;c++)
	{
		deletecol(c);
	}
}