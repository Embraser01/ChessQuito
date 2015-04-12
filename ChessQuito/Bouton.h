#ifndef _BOUTON_H
#define _BOUTON_H

#include "SDL_INIT.h"


#include <string>
#include <iostream>

using namespace std;


class Bouton
{
private:

	SDL_Surface* ecran;
	TTF_Font* police; // Police d'écriture pour tout l'affichage

	SDL_Surface* btn;
	SDL_Rect btnRect;

public:
	Bouton(SDL_Surface* ecran,TTF_Font* police, string txtBtn, int x, int y, int width, int height, Uint32 bgColor, SDL_Color ftColor);

	void afficherBtn();

	bool isClicked(int x, int y);


	~Bouton();
};

#endif
