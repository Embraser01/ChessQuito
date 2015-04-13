#ifndef _EDITBOX_H
#define _EDITBOX_H

/*
	EditBox :
		Permet d'avoir une zone d'édition en SDL, ne prend en charge que quelques caractères spéciaux
		Pour une majuscule, il faut déjà presser LSHIFT ou RSHIFT puis écrire la lettre demandé
*/

#include "SDL_INIT.h"

#include <string>
#include <iostream>

using namespace std;


class EditBox
{
private:

	SDL_Surface* ecran;
	TTF_Font* police; // Police d'écriture pour tout l'affichage

	SDL_Rect boxRect; // Position de la boite d'édition
	SDL_Color fgColor; // Couleur de l'écriture
	Uint32 bgColor; // Couleur de fond
	string txt; // Contient le texte tapé

	bool isSelect; // Permet de régler la couleur de l'encadré ( Vert si on peut écrire, Rouge sinon)

public:

	EditBox(SDL_Surface* ecran, TTF_Font* police, int x, int y, int width, int height, Uint32 bgColor, SDL_Color fgColor);

	int start(); // Gère l'écriture, renvoie -2 si QUIT

	void drawBox(); // Dessine la boite en fonction du texte ( rognage auto)


	string getText() { return txt; }

	void setText(string newTxt) { txt = newTxt; }

	bool isClicked(int x, int y); // Colision
	

	~EditBox();
};

#endif

