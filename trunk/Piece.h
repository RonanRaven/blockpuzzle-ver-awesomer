//
//Bryant Hetherington
//
#ifndef PIECE_H
#define PIECE_H
class Piece
{
private:
	int x, y;
	int col, row;
	int color;
public:
	char** block;

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
	int getcol(){return col;}
	int getrow(){return row;}
	int getcolor(){return color;}
};

#endif