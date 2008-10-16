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

	int getInt(){return rand();}
	int getInt(int from, int to){return ((rand()%(to+1-from))+from);}
	char getChar(){return (rand()%255);}//how many ascii characters are there?
	char getChar(char from, char to){return ((rand()%(to+1-from))+from);}
	bool getBool(){if(rand()%1){return true;}else{return false;}}//randomly returns true or false 
};

#endif