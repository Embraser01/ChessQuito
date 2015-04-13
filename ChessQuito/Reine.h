#ifndef _REINE_H
#define _REINE_H

/*
	Reine:
		H�rite de Pi�ce,
		Mouvement verticaux ou horizontaux ou diagonaux
*/

#include "Piece.h"


class Reine :
	public Piece
{
public:
	Reine(int);
	Reine(int, int);

	Reine* clone();

	bool setMove(char[], char[]);
	~Reine(void);
};

#endif
