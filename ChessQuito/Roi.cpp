#include "Roi.h"



Roi::Roi(int color) : Piece(color)
{
	Name = "Roi";
	value = 0;
}

Roi::Roi(int color, int state) : Piece(color, state)
{
	Name = "Roi";
	value = 0;
}


Roi* Roi::clone(){
	Roi* tmp = new Roi(this->getColor());

	tmp->setState(this->getState());

	return tmp;
}

bool Roi::setMove(char pos1[2], char pos2[2]) {

	int x1 = pos1[0] - 'a';
	int y1 = pos1[1] - '0';

	int x2 = pos2[0] - 'a';
	int y2 = pos2[1] - '0';

	if (fabs((float)x2 - x1) <= 1 && fabs((float)y2 - y1) <= 1 && (x1 != x2 || y1 != y2)) { // Deplacement de 1 

		return true;
	}

	return false;
}



Roi::~Roi(void)
{
}
