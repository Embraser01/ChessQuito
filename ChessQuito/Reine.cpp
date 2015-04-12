#include "Reine.h"



Reine::Reine(int color) : Piece(color)
{
	Name = "Reine";
	value = 5;
}

Reine::Reine(int color, int state) : Piece(color, state)
{
	Name = "Reine";
	value = 5;
}


Reine* Reine::clone(){
	Reine* tmp = new Reine(this->getColor());

	tmp->setState(this->getState());

	return tmp;
}


bool Reine::setMove(char pos1[2], char pos2[2]) {

	int x1 = pos1[0] - 'a';
	int y1 = pos1[1] - '0';

	int x2 = pos2[0] - 'a';
	int y2 = pos2[1] - '0';

	if (fabs((float)x2 - x1) == fabs((float)y2 - y1)) { // Diagonale

		return true;
	}

	if (x1 == x2 && y1 != y2) { // Vertical

		return true;
	}

	if (y1 == y2 && x1 != x2) { // Horizontal
		return true;
	}

	return false;
}

Reine::~Reine(void)
{
}
