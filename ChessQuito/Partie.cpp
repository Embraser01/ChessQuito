#include "Partie.h"



Partie::Partie()
{
	time_t t = time(NULL);

	struct tm datetime;
	char  format[32];

	datetime = *localtime(&t);

	strftime(format, 32, "%Y_%m_%d-%H_%M_%S", &datetime);


	this->date = format;
	j1 = NULL;
	j2 = NULL;

	typePartie = -1;

	nCoup = 0;
	nDernierePrise = -1;

	for(int i = 0; i < TAILLE;i++)
		for(int j = 0; j < TAILLE; j++)
			p[i][j] = NULL;
}


Partie::Partie(string date)
{
	this->date = date;
	j1 = NULL;
	j2 = NULL;

	typePartie = -1;

	nCoup = 0;
	nDernierePrise = -1;

	for(int i = 0; i < TAILLE;i++)
		for(int j = 0; j < TAILLE; j++)
			p[i][j] = NULL;
}


Partie::Partie(const Partie& cpyPartie){

	time_t t = time(NULL);

	this->date = ctime(&t);
	j1 = NULL;
	j2 = NULL;

	typePartie = cpyPartie.typePartie;

	nCoup = cpyPartie.nCoup;
	nDernierePrise = cpyPartie.nDernierePrise;

	for(int i = 0; i < TAILLE;i++)
		for(int j = 0; j < TAILLE; j++)
			p[i][j] = cpyPartie.p[i][j]->clone();

}

Partie& Partie::operator=(Partie& cpyPartie){

	typePartie = cpyPartie.typePartie;

	nCoup = cpyPartie.nCoup;
	nDernierePrise = cpyPartie.nDernierePrise;

	/* ON supprime les anciennes pièces */ 

	for(int i = 0; i < TAILLE;i++)
		for(int j = 0; j < TAILLE; j++)
			if(p[i][j] != NULL)
				delete p[i][j];

	/* On clone les pieces de l'autre plateau */

	for(int i = 0; i < TAILLE;i++)
		for(int j = 0; j < TAILLE; j++)
			p[i][j] = cpyPartie.p[i][j]->clone();

	return cpyPartie;
}



void Partie::setTypePartie(int type){

	if(typePartie == -1 && type < 4 && type > 0)
		typePartie = type;
}

void Partie::setIsWhiteTiPlay(bool state)
{
	this->isWhiteToPlay = state;
}


void Partie::affichePlateau(ostream& flux) const{

	flux << "  |  A  |  B  |  C  |  D  |" << endl;
	flux << "---------------------------" << endl;
	for(int i = 0; i < TAILLE;i++){
		flux << i << " |";
		for(int j = 0; j < TAILLE; j++){
			if(p[j][i] == NULL)
				flux << "     |";
			else
				flux << "  " << p[j][i]->toString()[0] << p[j][i]->toString()[1] << " |";
		}
		flux << " "<< i << endl;
		flux << "---------------------------" << endl;
	}
	flux << "  |  A  |  B  |  C  |  D  |" << endl;

}



bool Partie::placePiece(Piece* piece, char pos2[3]){


	/* On recupère la position actuelle de la piece */

	char pos1[2];

	for(int i = 0; i < TAILLE; i++){
		for(int j = 0; j < TAILLE; j++){
			if( p[i][j] == piece){
				pos1[0] = i + 'a';
				pos1[1] = j + '0';
			}
		}
	}

	/* On récupère les coordonnées réelles de la piece ainsi que celles de la destination */

	int x1 = pos1[0] - 'a';
	int y1 = pos1[1] - '0';

	int x2 = pos2[0] - 'a';
	int y2 = pos2[1] - '0';


	/* On verifie que la destination est dans le plateau */

	if (x2 >= TAILLE || y2 >= TAILLE || x2 < 0 || y2 < 0) 
		return false;


	/* On gère les exceptions : 
	*	- Cavalier (Il saute par dessus les pieces et prends sur la case d'arrivée) 
	*	- Pion (Se déplace avant arrière de 1 et prend en diagonale) 
	*	- Roi ( Bouge de 1 case) 
	*/


	if (p[x1][y1]->getName() == "Cavalier" || p[x1][y1]->getName() == "Roi") {
		if (piece->setMove(pos1, pos2)) {

			// On vérifie que la destination est vide

			if (p[x2][y2] == NULL) {
				p[x2][y2] = p[x1][y1];
				p[x1][y1] = NULL;
				nCoup++;
				return true;
			}

			// Sinon si la couleur est différente

			if (p[x2][y2]->getColor() != piece->getColor()) {

				delete p[x2][y2];

				p[x2][y2] = p[x1][y1];
				p[x1][y1] = NULL;
				nCoup++;
				nDernierePrise = nCoup;
				return true;
			}	
		}
		return false;
	}


	if (p[x1][y1]->getName() == "Pion") {

		if (piece->setMove(pos1, pos2)) {

			// On vérifie que la destination est vide, (Avant//Arriere)

			if (p[x2][y2] == NULL && x1 == x2) {
				p[x2][y2] = p[x1][y1];
				p[x1][y1] = NULL;
				nCoup++;
				return true;
			}

			// Sinon si deplacement diagonale + pion adverse 

			if (p[x2][y2] != NULL && x1 != x2) {
				if (p[x2][y2]->getColor() != piece->getColor()) {

					delete p[x2][y2];

					p[x2][y2] = p[x1][y1];
					p[x1][y1] = NULL;
					nCoup++;
					nDernierePrise = nCoup;
					return true;
				}
			}
		}
		return false;
	}


	/* On valide le déplacement en fonction de la piece */

	if ( piece->setMove(pos1, pos2)){


		// On vérifie que la destination n'est pas prise par une autre piece de même couleur

		if (p[x2][y2] != NULL)
			if(p[x2][y2]->getColor() == piece->getColor())
				return false;


		// On récupère le xMax et yMax afin de pouvoir calculer le vecteur

		int xMin = x1;
		int xMax = x2;
		int yMin = y1;
		int yMax = y2;

		if (x1 > x2) {
			xMin = x2;
			xMax = x1;
		}
		if (y1 > y2) {
			yMin = y2;
			yMax = y1;
		}


		// On parcours toutes les cases, et si une case est entre les deux points, on return

		for (int x = xMin; x <= xMax; x++) {
			for (int y = yMin; y <= yMax; y++) {

				if(p[x][y] != NULL && (x != x1 || y != y1) && (x != x2 || y != y2)){ // On enleve la vérification des deux extrémitées du segment et on verifie si la case est vide ou pas

					if (((x2 - x1) * (y - y1)) - ((x - x1) * (y2 - y1)) == 0) {	// M est sur la droite formée par pos1 et pos2 et M est forcement entre pos1 et pos2 car la boucle for l'est

						return false;
					}	
				}
			}
		}


		/* A ce moment, il n'y pas de pièce entre les deux points */


		// Si la case de destination est vide, on bouge la piece

		if ( p[x2][y2] == NULL){
			p[x2][y2] = p[x1][y1];
			p[x1][y1] = NULL;
			nCoup++;
			return true;
		}

		// Si la place est prise, on vire la pièce et on place la nouvelle



		else { // Si de couleur differente

			delete p[x2][y2];

			p[x2][y2] = p[x1][y1];
			p[x1][y1] = NULL;
			nCoup++;
			nDernierePrise = nCoup;
			return true;
		}
	}
	return false;
}



bool Partie::initPiece(Piece* piece, char pos[3])
{
	int x = pos[0] - 'a';
	int y = pos[1] - '0';

	if (x >= TAILLE || y >= TAILLE || x < 0 || y < 0) // Si en dehors du plateau
		return false;


	if (piece->getState() == 0 && p[x][y] == NULL) {
		p[x][y] = piece;
		piece->setState(1);
		return true;
	}

	return false;
}


Piece*& Partie::operator()(int x, int y) {
	return p[x][y];
}


Piece* Partie::operator()(int x, int y) const {
	return p[x][y];
}



Piece*& Partie::operator()(char pos[3]) {
	int x = pos[0] - 'a';
	int y = pos[1] - '0';

	return p[x][y];
}


Piece* Partie::operator()(char pos[3]) const {
	int x = pos[0] - 'a';
	int y = pos[1] - '0';

	return p[x][y];
}




bool Partie::addJoueur(Joueur* j)
{
	if(j1 == NULL){
		j1 = j;
		return true;
	}
	if(j2 == NULL){
		j2 = j;
		return true;
	}
	return false;
}


bool Partie::isPartieInit(){

	for(int i = 0; i < TAILLE; i++){
		for(int j = 0; j < TAILLE; j++){
			if( p[i][j] != NULL){
				return true;
			}
		}
	}
	return false;
}

bool Partie::isPartieEnd(){

	if(typePartie == 1 || typePartie == 2){ // On regarde quelle regle est utilisé

		/* On regarde si ça fait plus de 5 déplacement qu'il n'y a pas eu de prise */

		if(nCoup - nDernierePrise >= 5)
			return true;


		/* On compte le nbre de piece restante sur le plateau */ 

		int nbPieceB = 0;
		int nbPieceN = 0;

		for(int i = 0; i < TAILLE; i++){
			for(int j = 0; j < TAILLE; j++){
				if( p[i][j] != NULL){
					if(p[i][j]->getColor() == 0)
						nbPieceB++;
					else
						nbPieceN++;
				}
			}
		}

		if(nbPieceB == 0 || nbPieceN == 0)
			return true;
	}
	else{ // Regle 3


	}
	return false;
}


int Partie::getGagnant(){


	if(typePartie == 1 || typePartie == 2){ // On regarde quelle regle est utilisé

		/* On ajoute la valeur des pièces Blanche et on soustrait celle des Noirs */

		int score = 0;

		for(int i = 0; i < TAILLE; i++){
			for(int j = 0; j < TAILLE; j++){
				if( p[i][j] != NULL){
					if(p[i][j]->getColor() == 0) // Blanc
						score+= p[i][j]->getValeur();
					else
						score-= p[i][j]->getValeur();
				}
			}
		}

		int gagnant = 2;

		if(score > 0){
			gagnant = 1;
		}
		else if(score < 0){
			gagnant = 0;
		}

		return gagnant;
	}
	return -1;
}


Partie::~Partie(void)
{
	if(j1 != NULL)
		j1->setPartie(this);
	if(j2 != NULL)
		j2->setPartie(this);


	for(int i = 0; i < TAILLE; i++)
		for(int j = 0; j < TAILLE; j++)
			if( p[i][j] != NULL){
				delete p[i][j];
			}	
}
