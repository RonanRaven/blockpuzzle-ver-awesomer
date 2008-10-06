//
//Bryant Hetherington
//
#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <time.h>

struct Random
{
	Random(){srand(time(NULL));}

	int getInt();
	int getInt(int from, int to);
	char getChar();
	char getChar(char from, char to);
	bool getBool();
};

int Random::getInt()
{
	return rand();
}
int Random::getInt(int from, int to)
{
	return ((rand()%(to+1-from))+from);
}
char Random::getChar()
{
	return (rand()%255);//how many ascii characters are there?
}
char Random::getChar(char from, char to)
{
	return ((rand()%(to+1-from))+from);
}
bool Random::getBool()
{
	if(rand()%1)
		return true;
	else
		return false;
}

#endif