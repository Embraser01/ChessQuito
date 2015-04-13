#ifndef _TOUR_H
#define _TOUR_H

/*
	Tour:
		Hérite de Pièce,
		Mouvement verticaux ou horizontaux
*/

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