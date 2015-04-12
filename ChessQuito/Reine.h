#ifndef _REINE_H
#define _REINE_H


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
