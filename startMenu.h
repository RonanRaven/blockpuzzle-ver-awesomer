#ifndef STARTMENU_H
#define STARTMENU_H

class startMenu
{
private:
	char gamemode;
	int amounttogrow;
	bool GameModeSelected;
	int color1;
	int accum;
public:
	bool MenuFinished;

	startMenu();
	char getMode(){return gamemode;}
	void setMode(char a_mode){ gamemode=a_mode;}
	void setMode(char a_mode, bool a_reset){ gamemode=a_mode; GameModeSelected=a_reset;}
	int  getGrow(){return amounttogrow;}
	void setGrow(int a_grow) { amounttogrow=a_grow;}
	void drawMenu(int&, int&);
	bool menuInput(int);
	void colorchange(bool);
};

#endif