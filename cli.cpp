#include "cli.h"


#include <windows.h>

void gotoxy(int x, int y)
{
	COORD point;
	point.X = x;
	point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void setcolor(int fcolor, int bcolor = 0)
{
	//this function sets the color of the console output
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		(WORD)((bcolor << 4) | fcolor ));
}

// records the last known state of the mouse
MOUSE_EVENT_RECORD __mouseEvent;
KEY_EVENT_RECORD __keyEvent;

void getInput()
{
    INPUT_RECORD InRec;
    DWORD NumRead;
	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &InRec, 1, &NumRead);
	switch(InRec.EventType)
	{
		case MOUSE_EVENT:
			__mouseEvent = InRec.Event.MouseEvent;
			break;
		case KEY_EVENT:
			__keyEvent = InRec.Event.KeyEvent;
	}
}

int getMouseX()
{
	getInput();
	return __mouseEvent.dwMousePosition.X;
}

int getMouseY()
{
	getInput();
	return __mouseEvent.dwMousePosition.Y;
}

bool isLeftMousePressed()
{
	getInput();
	return __mouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED;
}

bool isRightMousePressed()
{
	getInput();
	return __mouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED;
}

int getKey()
{
	getInput();
	char c = __keyEvent.uChar.AsciiChar;
	__keyEvent.uChar.AsciiChar = 0;
	return c;
}

void disableFlashingCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo = {1, false};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}