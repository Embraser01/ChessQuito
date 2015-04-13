#ifndef _FOU_H
#define _FOU_H

/*
	Fou:
		H�rite de Pi�ce,
		Mouvement diagonaux
*/

#include "Piece.h"


class Fou :
	public Piece
{

public:
	Fou(int);
	Fou(int, int);

	Fou* clone();

	bool setMove(char[], char[]);
	~Fou(void);
};

#endif