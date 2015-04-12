#ifndef _FOU_H
#define _FOU_H


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