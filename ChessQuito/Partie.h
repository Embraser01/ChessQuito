#ifndef _PARTIE_H
#define _PARTIE_H


/*
	Partie:
		G�re tout ce qui est n�cessaire pour une partie
*/

#include <string>
#include <iostream>
#include <ctime>
#include <vector>

#include "Joueur.h"
#include "Piece.h"

#include "Fou.h"
#include "Tour.h"
#include "Cavalier.h"
#include "Reine.h"
#include "Roi.h"
#include "Pion.h"


using namespace std;

const int TAILLE=4;

class Joueur; // Pour que partie connaisse la class Joueur

class Partie
{
private:

	string date; // Date sous le format : "2015-11-30 23-42-55"

	Joueur* j1; // Pointeur sur le joueur 1
	Joueur* j2; // Pointeur sur le joueur 2

	Piece* p[TAILLE][TAILLE]; // Un �chiquier par partie

	Piece* pBlanc[4]; // Contient les pi�ces 
	Piece* pNoir[4];

	int typePartie; // Contient le num�ro de la r�gle utilis�


	bool isWhiteToPlay; // Permet de s'arreter dans une partie
	int nCoup; // Comptabilise le nombre de coup fait durant la partie
	int nDernierePrise; // Contient le numero du coup de la derni�re prise

	bool initPiece(Piece*, char[3]); // G�re le placement initial des pi�ces priv�e car appel� par la fonction placePiece uniquement

	bool deplacePiece(Piece*, char[]);
	bool deplacePiece(Piece*, int, int);

public:

	Partie(); // Date g�n�r� automatiquement
	Partie(string); // Date

	Partie(const Partie& cpyPartie); // Constructeur par copie
	Partie& operator=(Partie& cpyPartie); // Operateur d'affectation

	string getDate() const{ return date;}
	Joueur* getJ1() const {return j1;}
	Joueur* getJ2() const {return j2;}
	int getTypePartie() const {return typePartie;}
	bool getIsWhiteToPlay() const { return isWhiteToPlay; }


	Piece* getPNoir(int) const; // Renvoi la pi�ce i du tableau d'init
	Piece* getPBlanc(int) const; 

	void setPNoir(int, Piece*);
	void setPBlanc(int, Piece*);


	void setTypePartie(int, bool = false); // Met le type de partie ( num de la regle - possible une seule fois)
	void setIsWhiteToPlay(bool); // Permet de choisir le prochain joueur

	void affichePlateau(ostream& flux) const; // Permet cout << mPartie;


	Piece*& operator()(int ,int);
	Piece* operator()(int, int) const; // Permet de faire mPartie(i,j)
	Piece*& operator()(char[3]); 
	Piece* operator() (char[3]) const; // Permet de faire mPartie('a0');

	bool placePiece(Piece*, char[3]); // G�re les d�placements
	bool placePiece(Piece*, int, int);

	bool addJoueur(Joueur*); // Permet d'ajouter les joueurs � la partie



	vector<string> deplPossiblesSTL(string pos);
	vector<string> deplPossiblesSTL(int color);

	void afficheVector();

	bool placeAleatoireSTL(int );
	bool deplaceAleatoireSTL(int);


	bool isPartieInit(); // Retourne true si la partie a fini l'initialisation
	bool isPartieEnd(); // Renvoie true si la partie est termin�
	int getGagnant(); // Renvoie la couleur gagnante (Blanc : 0 | Noir : 1 | Egalit� : 2)

	~Partie(void);
};

#endif