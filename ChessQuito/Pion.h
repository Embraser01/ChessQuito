#ifndef _PION_H
#define _PION_H


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
