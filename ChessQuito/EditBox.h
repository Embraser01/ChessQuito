#ifndef _EDITBOX_H
#define _EDITBOX_H


#include "SDL_INIT.h"

#include <string>
#include <iostream>

using namespace std;


class EditBox
{
private:

	SDL_Surface* ecran;
	TTF_Font* police; // Police d'écriture pour tout l'affichage

	SDL_Rect boxRect;
	SDL_Color fgColor;
	Uint32 bgColor;
	string txt;

	bool isSelect;

public:

	EditBox(SDL_Surface* ecran, TTF_Font* police, int x, int y, int width, int height, Uint32 bgColor, SDL_Color fgColor);
	int start();

	void drawBox();


	string getText() { return txt; }

	void setText(string newTxt) { txt = newTxt; }

	bool isClicked(int x, int y);
	

	~EditBox();
};

#endif

