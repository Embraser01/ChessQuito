#ifndef _CAVALIER_H
#define _CAVALIER_H

/*
	Cavalier:
		H�rite de Pi�ce,
		Mouvement en L
*/

#include "Piece.h"


class Cavalier :
	public Piece
{

public:
	Cavalier(int);
	Cavalier(int, int);

	Cavalier* clone();

	bool setMove(char[], char[]);
	~Cavalier(void);
};

#endif
