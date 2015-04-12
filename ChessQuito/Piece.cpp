#include "Piece.h"


Piece::Piece(void){}

Piece::Piece(int color)
{
	Name = "Unkown";
	this->color = color;
	this->state = 0; // Disponible par defaut
}

Piece::Piece(int color, int state)
{
	Name = "Unkown";
	this->color = color;
	this->state = state;
}

void Piece::setState(int state)
{
	if(state >= 0 && state < 3)
		this->state = state;
}

char* Piece::toString() {

	char mString[2];

	if (color)
		mString[1] = 'N';
	else
		mString[1] = 'B';

	mString[0] = Name[0]; // Premiere lettre du Nom

	return mString;
}

Piece::~Piece(void){
}
