#ifndef _ROI_H
#define _ROI_H

/*
	Roi:
		Hérite de Pièce,
		Mouvement limité à 1 case 
*/

#include "Piece.h"
class Roi :
	public Piece
{
public:
	Roi(int);
	Roi(int, int);

	Roi* clone();

	bool setMove(char[], char[]);
	~Roi(void);
};

#endif

