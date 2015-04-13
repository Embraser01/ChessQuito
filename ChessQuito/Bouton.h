#ifndef _BOUTON_H
#define _BOUTON_H

/*
	Bouton:
		Permet de creer un bouton avec un texte, 
		une couleur de fond et une couleur de police.
		A une fonction de colision (isClicked),
		Positionn� aux coordonn�es pass�es.
*/

#include "SDL_INIT.h"


#include <string>
#include <iostream>

using namespace std;


class Bouton
{
private:

	SDL_Surface* ecran;
	TTF_Font* police; // Police d'�criture pour tout l'affichage

	SDL_Surface* btn; // Image du bouton ( cr�� au moment de la cr�ation de l'instance)
	SDL_Rect btnRect; // Contient les positions et la taille du bouton

public:
	Bouton(SDL_Surface* ecran,TTF_Font* police, string txtBtn, int x, int y, int width, int height, Uint32 bgColor, SDL_Color ftColor);

	void afficherBtn(); // Affiche le bouton sur l'�cran

	bool isClicked(int x, int y); // Gestion des colisions


	~Bouton();
};

#endif
