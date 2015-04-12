#ifndef _TOUR_H
#define _TOUR_H


#include "Piece.h"


class Tour :
	public Piece
{
public:
	Tour(int);
	Tour(int, int);

	Tour* clone();

	bool setMove(char[], char[]);

	~Tour(void);

};

#endif