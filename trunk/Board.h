//
//Bryant Hetherington
//
#ifndef BOARD_H
#define BOARD_H
#include "cli.h"
#include "piece.h"
#include "map.h"

#define rows 15
#define collumns 10

class Board
{
private:
	//int x, y;
	//int row, col;
public:
	//char** table;//[rows][collumns];
	Map map;
	int** color;//[rows][collumns];

	Board();
	void draw(int x, int y);

	void deleterow(int num);
	void deletecol(int num);
	void growRow(int numtogrow);
	void growCol(int numtogrow);

	void putblock(Piece &piece);
	bool collision(Piece &piece);
	bool outside(Piece &piece);

	int getrow(){return map.getrow();}
	int getcol(){return map.getcol();}
	void setrow(int r){map.setrow(r);}
	void setcol(int c){map.setcol(c);}
	char checkAt(int r, int c){return map.checkAt(r,c);}
	void setAt(int r, int c, char ascii){map.setAt(r,c,ascii);}
};
#endif