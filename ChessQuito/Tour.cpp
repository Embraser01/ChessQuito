#include "Tour.h"




Tour::Tour(int color) : Piece(color)
{
	Name = "Tour";
	value = 4;
}

Tour::Tour(int color, int state) : Piece(color, state)
{
	Name = "Tour";
	value = 4;

}


Tour* Tour::clone(){
	Tour* tmp = new Tour(this->getColor());

	tmp->setState(this->getState());

	return tmp;
}

bool Tour::setMove(char pos1[2], char pos2[2]){

	int x1 = pos1[0] - 'a';
	int y1 = pos1[1] - '0';

	int x2 = pos2[0] - 'a';
	int y2 = pos2[1] - '0';

	if ( x1 == x2 && y1 != y2){ // Vertical

		return true;
	}

	if ( y1 == y2 && x1 != x2){ // Horizontal
		return true;
	}

	return false;
}

Tour::~Tour(void)
{
}
