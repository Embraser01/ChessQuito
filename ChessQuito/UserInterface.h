#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H


#include "SDL_INIT.h"

#include "Joueur.h"
#include "Partie.h"

#include "Bouton.h"
#include "EditBox.h"



/* On importe les fonctions qu'on devra utiliser */

bool ajouterJoueur(string, Joueur***&); 
bool updateJoueur(string, Joueur***&, int i);
void newPartie(Partie***&);


/* Constantes */

const int TX = 1000; // Largeur de la fenetre
const int TY = 700; // Hauteur de la fenetre

const int WIDTH = 700; // Largeur de la zone de "JEU"

const int CASE_X = 100;
const int CASE_Y = 100;


class UserInterface
{
private:

	SDL_Surface* ecran; // Contient l'ecran d'affichage
	TTF_Font* police; // Police d'�criture pour tout l'affichage

	SDL_Rect navBar; // Rectangle de la barre de navigation
	SDL_Rect plateau; // Rectangle du plateau

	Joueur*** listeJoueur; // Utilis� seulement pour la lecture
	Partie*** listePartie; // ( affichage des listes des parties et joueurs)


	/* Liste des boutons */

	SDL_Color btnFontColor;
	Uint32 btnColor;

	Bouton* btnSortir;

	Bouton* btnGestJoueurs;
	Bouton* btnGestParties;

	Bouton* btnAddJoueur;
	Bouton* btnUpdateJoueur;
	Bouton* btnDeleteJoueur;
	Bouton* btnValider;

	Bouton* btnPlayPartie;
	Bouton* btnNewPartie;
	Bouton* btnDeletePartie;

	Bouton** btnListe;


	EditBox* eb;


	int mode; // Modes d'affichage	0. Jouer Partie		1. Accueil	2. Gestionnaire Joueurs	3. Gestionnaire Parties		4. AjouterJoueur	5. UpdateJoueur
	int selection; // Int qui contient l'indice de la partie ou du joueur selectionn�	-1 si rien de selectionn�

	string pseudo; // Utilis� pour ajouter un joueur ou modifier un joueur



	int checkEventMenu(int x, int y); // Permet de naviguer dans les diff�rents menus, si mode == 0 alors on verifie que la barre laterale

	char* checkEventPartie(int x, int y); // Renvoie les coordonn�es cliquer sur l'echiquier (ex: "a2");
	int checkEventListe(int x, int y); // Change l'�tat de selection en l'id de la partie/ du joueur ou -1 si ailleurs
	int checkEventEditBox();


public:
	UserInterface(Joueur***, Partie***);


	void start(); // Lance la gestion des events


	void dPlateau();
	void dNavBar();

	
	int getMode() { return mode; }
	int getSelect() { return selection; }
	string getPseudo() { return pseudo; }
	
	~UserInterface();
};

#endif
