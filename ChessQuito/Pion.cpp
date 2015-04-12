#include "Pion.h"



Pion::Pion(int color) : Piece(color)
{
	Name = "Pion";
	value = 1;
}

Pion::Pion(int color, int state) : Piece(color, state)
{
	Name = "Pion";
	value = 1;
}


Pion* Pion::clone(){
	Pion* tmp = new Pion(this->getColor());

	tmp->setState(this->getState());

	return tmp;
}



bool Pion::setMove(char pos1[2], char pos2[2]) {

	int x1 = pos1[0] - 'a';
	int y1 = pos1[1] - '0';

	int x2 = pos2[0] - 'a';
	int y2 = pos2[1] - '0';

	if (fabs((float)x2 - x1) == fabs((float)y2 - y1) && fabs((float)x2 - x1) == 1 && fabs((float)y2 - y1) == 1) { // Diagonale

		return true;
	}

	if (x1 == x2 && fabs((float)y2 - y1) == 1) { // Vertical

		return true;
	}

	return false;
}
Pion::~Pion(void)
{
}
