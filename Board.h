//
//Bryant Hetherington
//
#ifndef BOARD_H
#define BOARD_H
#include "cli.h"
#include "piece.h"

#define rows 15
#define collumns 10

class Board
{
private:
	//int x, y;
	int row, col;
public:
	char** table;//[rows][collumns];
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

	int getrow(){return row;}
	int getcol(){return col;}
};
#endif