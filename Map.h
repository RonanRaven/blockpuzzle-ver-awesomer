#pragma once

class Map
{
protected:
	int col, row;
public:
	char** table;

	void setAt(int row, int column, char ascii);
	char checkAt(int row,int column);
	int getrow(){return row;}
	int getcol(){return col;}

	void setrow(int r){row=r;}
	void setcol(int c){col=c;}

	void createTable(int row, int column);
	void deleteTable();
};