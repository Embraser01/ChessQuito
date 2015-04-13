#ifndef _PION_H
#define _PION_H

/*
	Pion:
		H�rite de Pi�ce,
		Mouvement verticaux ou diagonaux en fonction des pi�ces aux alentours
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
