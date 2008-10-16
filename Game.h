//
//Bryant Hetherington
//
#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Piece.h"
#include "startMenu.h"


class Game
{
private:
	Board board;
	Board *nextBoard;
	Piece piece;
	Piece nextPiece;
	startMenu menu;

	bool gamerunning;
	char input;
	int rowscleared;
	int startx, starty;
	int score;
public:
	Game();
	void run();
	void processInput();
	void drawWorld();
	void processGameLogic(int &then, int &now);
	void showLinesCleared(int x, int y);
	void showScore(int x, int y);

	void moveLeft();
	void moveRight();
	bool moveDown();
	void rotateCW();
	void rotateCCW();
	void upPressed();
};

#endif