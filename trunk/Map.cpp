#include "map.h"

char Map::checkAt(int r,int c)
{
	return table[r][c];
}

void Map::setAt(int r, int c, char ascii)
{
	table[r][c]=ascii;
}
void Map::createTable(int r, int c)
{
	row=r;
	col=c;

	table=new char* [row];
	for(int index=0;index<row;index++)
	{
		table[index]=new char[col];
	}
}
void Map::deleteTable()
{
	for(int r_count=0;r_count<row;r_count++)
	{
		delete table[r_count];
	}
	delete table;
}