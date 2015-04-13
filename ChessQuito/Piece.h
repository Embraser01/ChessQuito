#ifndef _PIECE_H
#define _PIECE_H

/*
	Pi�ce:
		Class m�re, abstraite,
*/

#include <string>
#include <iostream>

using namespace std;

class Piece
{
private:
	int color; // Blanc : 0 Noir : 1
	int state; // Disponible : 0 Plac� : 1 Pris : 2
	
protected :
	string Name; // Nom de la piece
	int value; // Valeur de la pi�ce

public:
	Piece(void);
	Piece(int); // Couleur
	Piece(int, int); // Couleur, Etat

	virtual Piece* clone() = 0; // Permet de dupliquer une pi�ce ( virtual car pi�ces typ�es)

	string getName(){return Name;}
	int getColor(){return color;}
	int getState() { return state;}
	int getValeur() {return value;}


	void setState(int);
	virtual bool setMove(char[], char[]) = 0; // Renvoi true si le mouvement est possible false sinon
	char* toString(); // Convertie une pi�ce en string de type '{Premi�re lettre}{Couleur(N|B)}'

	virtual ~Piece(void);
};

#endif
