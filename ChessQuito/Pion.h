#ifndef _PION_H
#define _PION_H

/*
	Pion:
		Hérite de Pièce,
		Mouvement verticaux ou diagonaux en fonction des pièces aux alentours
*/

#include "Piece.h"
class Pion :
	public Piece
{
public:
	Pion(int);
	Pion(int, int);

	Pion* clone();

	bool setMove(char[], char[]);

	~Pion(void);
};

#endif
