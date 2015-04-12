#ifndef _PARTIE_H
#define _PARTIE_H


#include <string>
#include <iostream>
#include <ctime>

#include "Joueur.h"
#include "Piece.h"

using namespace std;

const int TAILLE=4;
typedef Piece* Plateau[TAILLE][TAILLE]; // Echequier

class Joueur;

class Partie
{
private:

	string date;

	Joueur* j1;
	Joueur* j2;

	Plateau p;

	int typePartie;

	int nCoup;
	int nDernierePrise;

public:
	Partie();
	Partie(string);

	Partie(const Partie& cpyPartie);
	Partie& operator=(Partie& cpyPartie);

	string getDate() const{ return date;}
	Joueur* getJ1() const {return j1;}
	Joueur* getJ2() const {return j2;}
	int getTypePartie() const {return typePartie;}


	void setTypePartie(int); // Met le type de partie ( num de la regle)

	void affichePlateau(ostream& flux) const; // Permet cout << mPartie;


	Piece*& operator()(int ,int);
	Piece* operator()(int, int) const; // Permet de faire mPartie(i,j)
	Piece*& operator()(char[3]); 
	Piece* operator() (char[3]) const; // Permet de faire mPartie('a0');

	bool placePiece(Piece*, char[3]); // Gère les déplacements
	bool initPiece(Piece*, char[3]); // Gère le placement initial des pièces

	bool addJoueur(Joueur*); // Permet d'ajouter les joueurs à la partie


	bool isPartieInit(); // Retourne true si la partie a fini l'initialisation
	bool isPartieEnd(); // Renvoie true si la partie est terminé
	int getGagnant(); // Renvoie la couleur gagnante (Blanc : 0 | Noir : 1 | Egalité : 2)

	~Partie(void);
};

#endif