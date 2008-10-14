//
//Bryant Hetherington
//
#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Piece.h"

class Game
{
private:
	Board board;
	Piece piece;
	bool gamerunning;
	char input;
	//int timepassed;
	int rowscleared;
	int startx, starty;
public:
	Game();
	void run();
	void processInput();
	void drawWorld();
	void processGameLogic(int &then, int &now);
	void showLinesCleared(int x, int y);

	void moveLeft();
	void moveRight();
	bool moveDown();
	void rotateCW();
	void rotateCCW();
	void upPressed();
};

#endif