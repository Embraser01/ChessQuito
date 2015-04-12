#include "Fou.h"


Fou::Fou(int color) : Piece(color)
{
	Name = "Fou";
	value = 2;

}

Fou::Fou(int color, int state) : Piece(color, state)
{
	Name = "Fou";
	value = 2;
}

Fou* Fou::clone(){
	Fou* tmp = new Fou(this->getColor());

	tmp->setState(this->getState());

	return tmp;
}

bool Fou::setMove(char pos1[2], char pos2[2]){

	int x1 = pos1[0] - 'a';
	int y1 = pos1[1] - '0';

	int x2 = pos2[0] - 'a';
	int y2 = pos2[1] - '0';

	if ( fabs((float)x2 - x1) == fabs((float)y2 - y1)){ // Diagonal

		return true;
	}

	return false;
}



Fou::~Fou(void)
{
}
