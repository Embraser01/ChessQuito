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

	void drawBox();

public:
	EditBox(SDL_Surface* ecran, TTF_Font* police, string& txt, int x, int y, int width, int height, Uint32 bgColor, SDL_Color fgColor);
~EditBox();
};

#endif

