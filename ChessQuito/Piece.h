#ifndef _PIECE_H
#define _PIECE_H


#include <string>
#include <iostream>

using namespace std;

class Piece
{
private:
	int color; // Blanc : 0 Noir : 1
	int state; // Disponible : 0 Placé : 1 Pris : 2
	
protected :
	string Name; // Nom de la piece
	int value; // Valeur de la pièce

public:
	Piece(void);
	Piece(int);
	Piece(int, int);

	virtual Piece* clone() = 0;

	string getName(){return Name;}
	int getColor(){return color;}
	int getState() { return state;}
	int getValeur() {return value;}


	void setState(int);
	virtual bool setMove(char[], char[]) = 0; // Renvoi true si le mouvement est possible false sinon
	char* toString(); // Convertie une pièce en string de type '{Première lettre}{Couleur(N|B)}'

	virtual ~Piece(void);
};

#endif
