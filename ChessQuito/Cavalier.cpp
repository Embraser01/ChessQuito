#include "Cavalier.h"


Cavalier::Cavalier(int color) : Piece(color)
{
	Name = "Cavalier";
	value = 3;
}

Cavalier::Cavalier(int color, int state) : Piece(color, state)
{
	Name = "Cavalier";
	value = 3;

}


Cavalier* Cavalier::clone(){
	Cavalier* tmp = new Cavalier(this->getColor());

	tmp->setState(this->getState());

	return tmp;
}


bool Cavalier::setMove(char pos1[2], char pos2[2]) {

	int x1 = pos1[0] - 'a';
	int y1 = pos1[1] - '0';

	int x2 = pos2[0] - 'a';
	int y2 = pos2[1] - '0';

	if (fabs((float)x2 - x1) == 2 && fabs((float)y2 -y1) == 1) { // En forme de L v1

		return true;
	}

	if (fabs((float)x2 - x1) == 1 && fabs((float)y2 - y1) == 2) { // En forme de L v2

		return true;
	}

	return false;
}


Cavalier::~Cavalier(void)
{
}
