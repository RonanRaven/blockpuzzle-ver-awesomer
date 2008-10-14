//
//Bryant Hetherington
//
#include "Map.h"
#ifndef PIECE_H
#define PIECE_H
class Piece
{
private:
	int x, y;
	//int col, row;
	int color;
public:
	//char** table;
	Map map;

	Piece();
	void newpiece(int number, int numx, int numy);
	void deletepiece();

	void draw(int x, int y);
	//void setXY(int x, int y);
	void RotateCW();
	void RotateCCW();
	void flipH();
	void flipV();
	void flipXY();

	void up();
	void down();
	void left();
	void right();

	int getx(){return x;}
	int gety(){return y;}
	int getcolor(){return color;}

	int getrow(){return map.getrow();}
	int getcol(){return map.getcol();}
	void setrow(int r){map.setrow(r);}
	void setcol(int c){map.setcol(c);}
	char checkAt(int r, int c){return map.checkAt(r,c);}
	void setAt(int r, int c, char ascii){map.setAt(r,c,ascii);}

};
#endif