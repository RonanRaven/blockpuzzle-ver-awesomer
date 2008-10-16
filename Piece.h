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
	int color;
	int pieceType;
public:
	Map map;

	Piece();
	void newpiece(int number, int numx, int numy);
	void deletepiece();

	void draw(int x, int y);
	void RotateCW();
	void RotateCCW();
	void flipH();
	void flipV();
	void flipXY();

	void up();
	void down();
	void left();
	void right();

	void setXY(int numx, int numy){x=numx;y=numy;}

	int getx(){return x;}
	int gety(){return y;}
	int getcolor(){return color;}
	int getType(){return pieceType;}

	int getrow(){return map.getrow();}
	int getcol(){return map.getcol();}
	void setrow(int r){map.setrow(r);}
	void setcol(int c){map.setcol(c);}
	char checkAt(int r, int c){return map.checkAt(r,c);}
	void setAt(int r, int c, char ascii){map.setAt(r,c,ascii);}
};
#endif