#ifndef __CLI_H
#define __CLI_H

/*
http://www.adrianxw.dk/SoftwareSite/Consoles/Consoles5.html
CONSOLE_CURSOR_INFO cursorInfo = {1, false};
SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
http://www.adrianxw.dk/SoftwareSite/index.html
*/

#define COLOR_BLACK	0
#define COLOR_DARK_BLUE 1
#define COLOR_DARK_GREEN 2
#define COLOR_DARK_CYAN 3
#define COLOR_DARK_RED 4
#define COLOR_DARK_MAGENTA 5
#define COLOR_DARK_YELLOW 6
#define COLOR_GRAY 7
#define COLOR_DARK_GRAY 8
#define COLOR_BLUE 9
#define COLOR_GREEN 10
#define COLOR_CYAN 11
#define COLOR_RED 12
#define COLOR_MAGENTA 13
#define COLOR_YELLOW 14
#define COLOR_WHITE 15

/// sets the command line cursor position
void gotoxy(int x, int y);

/// sets colors of the command line
void setcolor(int fcolor, int bcolor);

/// gives the last known X location of the mouse
int getMouseX();

/// gives the last known Y location of the mouse
int getMouseY();

/// stops the flashing underscore cursor
void disableFlashingCursor();

/// returns true if the right mouse button is pressed
bool isRightMousePressed();

/// returns true if the left mouse button is pressed
bool isLeftMousePressed();

#endif