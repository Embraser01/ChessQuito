#ifndef _CAVALIER_H
#define _CAVALIER_H


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
