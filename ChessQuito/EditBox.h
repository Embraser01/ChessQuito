#ifndef _EDITBOX_H
#define _EDITBOX_H

/*
	EditBox :
		Permet d'avoir une zone d'�dition en SDL, ne prend en charge que quelques caract�res sp�ciaux
		Pour une majuscule, il faut d�j� presser LSHIFT ou RSHIFT puis �crire la lettre demand�
*/

#include "SDL_INIT.h"

#include <string>
#include <iostream>

using namespace std;


class EditBox
{
private:

	SDL_Surface* ecran;
	TTF_Font* police; // Police d'�criture pour tout l'affichage

	SDL_Rect boxRect; // Position de la boite d'�dition
	SDL_Color fgColor; // Couleur de l'�criture
	Uint32 bgColor; // Couleur de fond
	string txt; // Contient le texte tap�

	bool isSelect; // Permet de r�gler la couleur de l'encadr� ( Vert si on peut �crire, Rouge sinon)

public:

	EditBox(SDL_Surface* ecran, TTF_Font* police, int x, int y, int width, int height, Uint32 bgColor, SDL_Color fgColor);

	int start(); // G�re l'�criture, renvoie -2 si QUIT

	void drawBox(); // Dessine la boite en fonction du texte ( rognage auto)


	string getText() { return txt; }

	void setText(string newTxt) { txt = newTxt; }

	bool isClicked(int x, int y); // Colision
	

	~EditBox();
};

#endif

