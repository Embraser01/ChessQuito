/*
*	ChessQuito
*/


/* Includes STANDARD */

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <Windows.h>
#include <fstream>




/* Includes ChessQuito */

#include "Joueur.h"
#include "Partie.h"

#include "UserInterface.h"


using namespace std;


/* Liste fonctions */


bool ajouterJoueur(string, Joueur***&);
bool updateJoueur(string, Joueur***&, int);
void deleteJoueur(Joueur***&, Joueur*);

void newPartie(Partie***&);
void deletePartie(Partie***&, Partie*);

void chargerJeu(Partie***&, Joueur***&);

void saveParties(Partie***&);
void saveJoueurs(Joueur***&);



//////////////////
//     MAIN     //
//////////////////

int main(int argc, char *argv[]) {


	/* On charge les sauvegardes */

	Joueur*** listeJoueur = NULL;
	Partie*** listePartie = NULL;

	chargerJeu(listePartie, listeJoueur);
	

	/* Initialisation de l'interface Utilisateur */

	UserInterface ui(listeJoueur, listePartie);

	ui.start();


	/* On enregistre les joueurs + les parties */

	saveJoueurs(listeJoueur);
	saveParties(listePartie);


	/* On supprime les listes de la mémoire */

	for(int i = 0; (*listePartie)[i] != NULL;i++){
		delete (*listePartie)[i];
	}
	delete [](*listePartie);

	for (int i = 0; (*listeJoueur)[i] != NULL; i++) {
		delete (*listeJoueur)[i];
	}
	delete[](*listeJoueur);

	return EXIT_SUCCESS;
}



////////////////////////
//     CHESSQUITO     //
////////////////////////



/* Surcharges cout */

ostream& operator<<(ostream &flux, Partie const& mPartie)
{
	mPartie.affichePlateau(flux);
	return flux;
}


/* Gestion (ajout|suppression) des (joueurs|parties) */

bool ajouterJoueur(string nom, Joueur***& listeJoueur) {

	int i = 0;

	for (; (*listeJoueur)[i] != NULL; i++)
		if (nom == (*listeJoueur)[i]->getNom()) {
			return false;
		}

	/* On commence agrandir le tableau de pointeur de joueurs */

	Joueur** tabTmp = new Joueur*[i + 2];
	for (int j = 0; j < i; j++) {
		tabTmp[j] = (*listeJoueur)[j];
	}

	tabTmp[i] = new Joueur(nom);

	tabTmp[i + 1] = NULL; // On met le dernier à NULL afin de pouvoir avoir un etat d'arret lors des tests sur la liste

	delete[](*listeJoueur); // On supprime l'ancien tableau

	(*listeJoueur) = tabTmp; // On assigne la nouvelle addresse du tableau

	return true;
}

bool updateJoueur(string nom, Joueur***& listeJoueur, int i) {

	for (int j = 0; (*listeJoueur)[j] != NULL; j++)
		if (nom == (*listeJoueur)[j]->getNom()) {
			return false;
		}

	(*listeJoueur)[i]->setNom(nom);
	return true;
}

void deleteJoueur(Joueur***& listeJoueur, Joueur* mJoueur) {

	int i = 0;
	for (; (*listeJoueur)[i] != NULL; i++);

	int id = 0;
	for (; (*listeJoueur)[id] != mJoueur; id++);


	/* On reduit le tableau de pointeur de joueurs */

	Joueur** tabTmp = new Joueur*[i];

	for (int j = 0, k = 0; j < i; j++) {
		if (id != j) {
			tabTmp[k] = (*listeJoueur)[j];
			k++;
		}
	}

	delete mJoueur;

	tabTmp[i - 1] = NULL; // On met le dernier à NULL afin de pouvoir avoir un etat d'arret lors des tests sur la liste

	delete[](*listeJoueur); // On supprime l'ancien tableau

	(*listeJoueur) = tabTmp; // On assigne la nouvelle addresse du tableau
}



void newPartie(Partie***& listePartie) {

	int i = 0;

	for (; (*listePartie)[i] != NULL; i++);


	/* On commence agrandir le tableau de pointeur de partie */

	Partie** tabTmp = new Partie*[i + 2];

	for (int j = 0; j < i; j++) {
		tabTmp[j] = (*listePartie)[j];
	}

	tabTmp[i] = new Partie();
	tabTmp[i + 1] = NULL; // On met le dernier à NULL afin de pouvoir avoir un etat d'arret lors des tests sur la liste

	delete[](*listePartie); // On supprime l'ancien tableau
	(*listePartie) = tabTmp; // On change l'addresse du tableau pointé par listePartie
}

void deletePartie(Partie***& listePartie, Partie* mPartie) {

	int i = 0;
	for (; (*listePartie)[i] != NULL; i++);

	int id = 0;
	for (; (*listePartie)[id] != mPartie; id++);


	/* On reduit le tableau de pointeur de joueurs */

	Partie** tabTmp = new Partie*[i];

	for (int j = 0, k = 0; j < i; j++) {
		if (id != j) {
			tabTmp[k] = (*listePartie)[j];
			k++;
		}
	}

	delete mPartie;

	tabTmp[i - 1] = NULL; // On met le dernier à NULL afin de pouvoir avoir un etat d'arret lors des tests sur la liste

	delete[](*listePartie); // On supprime l'ancien tableau

	(*listePartie) = tabTmp; // On assigne la nouvelle addresse du tableau
}


/* Fonctions de chargement des joueurs et parties */


void chargerJeu(Partie***& listePartie, Joueur***& listeJoueur) {


	cout << "Chargement des Joueurs .";

	/* On charge les joueurs */

	ifstream fichier("save/Joueurs.txt", ios::in);  // on ouvre en lecture

	if (fichier)  // si l'ouverture a fonctionné
	{
		string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue

		int i = 0;

		cout << ".";

		while (!fichier.eof()) {
			fichier.ignore(1000, '\n');
			i++;
		}

		listeJoueur = new Joueur**;
		(*listeJoueur) = new Joueur*[i];

		(*listeJoueur)[i - 1] = NULL;

		fichier.seekg(0, std::ios::beg);

		for (int j = 0; j < i - 1; j++) {
			cout << ".";
			getline(fichier, contenu, '\n');
			(*listeJoueur)[j] = new Joueur(contenu);
		}

		cout << endl;

		fichier.close();
	}
	else {
		cout << "Impossible de charger les joueurs !" << endl;
		listeJoueur = new Joueur**;
		(*listeJoueur) = new Joueur*[1];
		(*listeJoueur)[0] = NULL;
	}


	cout << "Chargement des Parties .";

	/* On charge maintenant les parties */

	ifstream fichier2("save/Parties.txt", ios::in);  // on ouvre en lecture

	if (fichier2)  // si l'ouverture a fonctionné
	{
		string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue

		cout << ".";
		int i = 0;

		while (!fichier2.eof()) {
			fichier2.ignore(1000, '\n');
			i++;
		}

		listePartie = new Partie**;
		(*listePartie) = new Partie*[i];
		(*listePartie)[i - 1] = NULL;


		fichier2.seekg(0, std::ios::beg);

		for (int j = 0; j < i - 1; j++) {

			cout << ".";


			/* On charge chaque fichier */

			string fileName;
			getline(fichier2, contenu, '\n');
			fileName = "save/parties/" + contenu + ".txt";

			ifstream tmp(fileName, ios::in);  // on ouvre en lecture


			/* On parcours les différentes propriétées du fichier */


			// Date

			getline(tmp, contenu, '\n');
			(*listePartie)[j] = new Partie(contenu);


			// Joueur 1

			getline(tmp, contenu, '\n'); 
			for (int k = 0; (*listeJoueur)[k] != NULL; k++) {
				if ((*listeJoueur)[k]->getNom() == contenu) {
					(*listePartie)[j]->addJoueur((*listeJoueur)[k]);
					break;
				}
			}

			

			// Joueur 2

			getline(tmp, contenu, '\n');
			for (int k = 0; (*listeJoueur)[k] != NULL; k++) {
				if ((*listeJoueur)[k]->getNom() == contenu) {
					(*listePartie)[j]->addJoueur((*listeJoueur)[k]);
					break;
				}
			}


			// Type de partie

			getline(tmp, contenu, '\n');
			(*listePartie)[j]->setTypePartie(atoi(contenu.c_str()), true);

			
			// IsWhiteToPlay

			getline(tmp, contenu, '\n');
			(*listePartie)[j]->setIsWhiteToPlay(atoi(contenu.c_str()));


			// Tableaux d'initialisation

			for (int k = 0; k < 4; k++) {
				

				getline(tmp, contenu, '_'); // Piece par Piece
				if (contenu == "NULL") {
					
					tmp.ignore(5, ' ');
					(*listePartie)[j]->setPBlanc(k, NULL);
				}
				else {
					
					int color;
					int state;

					tmp >> color;
					tmp.ignore(1); // UNDERSCORE
					tmp >> state;
					tmp.ignore(1); // SPACE


					if (contenu == "Tour") {
						(*listePartie)[j]->setPBlanc(k, new Tour(color, state));
					}
					else if (contenu == "Fou") {
						(*listePartie)[j]->setPBlanc(k, new Fou(color, state));
					}
					else if (contenu == "Roi") {
						(*listePartie)[j]->setPBlanc(k, new Roi(color, state));
					}
					else if (contenu == "Reine") {
						(*listePartie)[j]->setPBlanc(k, new Reine(color, state));
					}
					else if (contenu == "Cavalier") {
						(*listePartie)[j]->setPBlanc(k, new Cavalier(color, state));
					}
					else if (contenu == "Pion") {
						(*listePartie)[j]->setPBlanc(k, new Pion(color, state));
					}
				}
			}
			tmp.ignore(2, '\n');

			for (int k = 0; k < 4; k++) {

				getline(tmp, contenu, '_'); // Piece par Piece
				if (contenu == "NULL") {
					tmp.ignore(5, ' ');
					(*listePartie)[j]->setPNoir(k, NULL);
				}
				else {
					int color;
					int state;

					tmp >> color;
					tmp.ignore(1); // UNDERSCORE
					tmp >> state;
					tmp.ignore(1); // SPACE


					if (contenu == "Tour") {
						(*listePartie)[j]->setPNoir(k, new Tour(color, state));
					}
					else if (contenu == "Fou") {
						(*listePartie)[j]->setPNoir(k, new Fou(color, state));
					}
					else if (contenu == "Roi") {
						(*listePartie)[j]->setPNoir(k, new Roi(color, state));
					}
					else if (contenu == "Reine") {
						(*listePartie)[j]->setPNoir(k, new Reine(color, state));
					}
					else if (contenu == "Cavalier") {
						(*listePartie)[j]->setPNoir(k, new Cavalier(color, state));
					}
					else if (contenu == "Pion") {
						(*listePartie)[j]->setPNoir(k, new Pion(color, state));
					}
				}
			}
			tmp.ignore(2, '\n');





			// Chargement du plateau

			for (int l = 0; l < TAILLE; l++) {
				for (int k = 0; k < TAILLE; k++) {

					getline(tmp, contenu, '_'); // Piece par Piece
					if (contenu == "NULL") {
						tmp.ignore(5, ' ');
						(*(*listePartie)[j])(l, k) = NULL;
					}
					else {
						int color;
						int state;

						tmp >> color;
						tmp.ignore(1); // UNDERSCORE
						tmp >> state;
						tmp.ignore(1); // SPACE


						if (contenu == "Tour") {
							(*(*listePartie)[j])(l, k) = new Tour(color, state);
						}
						else if (contenu == "Fou") {
							(*(*listePartie)[j])(l, k) = new Fou(color, state);
						}
						else if (contenu == "Roi") {
							(*(*listePartie)[j])(l, k) = new Roi(color, state);
						}
						else if (contenu == "Reine") {
							(*(*listePartie)[j])(l, k) = new Reine(color, state);
						}
						else if (contenu == "Cavalier") {
							(*(*listePartie)[j])(l, k) = new Cavalier(color, state);
						}
						else if (contenu == "Pion") {
							(*(*listePartie)[j])(l, k) = new Pion(color, state);
						}
					}
				}
				tmp.ignore(2, '\n');
			}

			// Fin de la boucle

			tmp.close();
		}
	}
	else {
		cout << "Impossible de charger la sauvegarde !" << endl;
		listePartie = new Partie**;
		(*listePartie) = new Partie*[1];
		(*listePartie)[0] = NULL;
	}
}


void saveParties(Partie***& listePartie) {


	/* On commence par creer un registre des parties */

	ofstream fichier("save/Parties.txt", ios::out | ios::trunc);  //déclaration du flux et ouverture du fichier

	if (fichier)  // si l'ouverture a réussi
	{
		for (int i = 0; (*listePartie)[i] != NULL; i++) {
			fichier << (*listePartie)[i]->getDate() << endl;
		}


		fichier.close();  // on referme le fichier
	}
	else { // sinon
		cout << "Erreur durant l'enregistrement  !" << endl;
		return;
	}


	for (int i = 0; (*listePartie)[i] != NULL; i++) {

		string fileName = "save/parties/" + (*listePartie)[i]->getDate() + ".txt";

		ofstream fichier(fileName, ios::out | ios::trunc);  //déclaration du flux et ouverture du fichier

		if (fichier)  // si l'ouverture a réussi
		{

			/* On commence par enregistrer les différentes propriétées de la partie */

			fichier << (*listePartie)[i]->getDate() << endl;

			if ((*listePartie)[i]->getJ1() == NULL)
				fichier << "_é!#charSpeciauxà@_" << endl;
			else
				fichier << (*listePartie)[i]->getJ1()->getNom() << endl;

			if ((*listePartie)[i]->getJ2() == NULL)
				fichier << "_é!#charSpeciauxà@_" << endl;
			else
				fichier << (*listePartie)[i]->getJ2()->getNom() << endl;

			fichier << (*listePartie)[i]->getTypePartie() << endl
				<< (*listePartie)[i]->getIsWhiteToPlay() << endl;


			/* On enregistre les deux tableaux de pièce*/

			for (int j = 0; j < 4; j++) {
				if ((*listePartie)[i]->getPBlanc(j) != NULL)
					fichier << (*listePartie)[i]->getPBlanc(j)->getName() << "_" << (*listePartie)[i]->getPBlanc(j)->getColor() << "_" << (*listePartie)[i]->getPBlanc(j)->getState() << " ";
				else
					fichier << "NULL_0_0 ";
			}
			fichier << endl;

			for (int j = 0; j < 4; j++) {
				if ((*listePartie)[i]->getPNoir(j) != NULL)
					fichier << (*listePartie)[i]->getPNoir(j)->getName() << "_" << (*listePartie)[i]->getPNoir(j)->getColor() << "_" << (*listePartie)[i]->getPNoir(j)->getState() << " ";
				else
					fichier << "NULL_0_0 ";
			}
			fichier << endl;

			/* On enregistre le plateau */

			for (int j = 0; j < TAILLE; j++) {
				for (int k = 0; k < TAILLE; k++) {
					if ((*(*listePartie)[i])(j, k) != NULL)
						fichier << (*(*listePartie)[i])(j, k)->getName() << "_" << (*(*listePartie)[i])(j, k)->getColor() << "_" << (*(*listePartie)[i])(j, k)->getState() << " ";
					else
						fichier << "NULL_0_0 ";
				}
				fichier << endl;
			}

			fichier.close();  // on referme le fichier
		}
		else { // sinon
			cout << "Erreur durant l'enregistrement  !" << endl;
			return;
		}
	}

	cout << "Fin de l'enregistrement ! " << endl;
}


void saveJoueurs(Joueur***& listeJoueur) {


	ofstream fichier("save/Joueurs.txt", ios::out | ios::trunc);  //déclaration du flux et ouverture du fichier

	if (fichier)  // si l'ouverture a réussi
	{
		for (int i = 0; (*listeJoueur)[i] != NULL; i++) {
			fichier << (*listeJoueur)[i]->getNom() << endl;
		}


		fichier.close();  // on referme le fichier
	}
	else { // sinon
		cout << "Erreur durant l'enregistrement  !" << endl;
		return;
	}
}




///////////////////
//      SDL      //
///////////////////


/* Redimmensionne l'image */

void resizeImage(SDL_Surface*& img, const double newwidth, const double newheight, bool x)
{
	// Zoom function uses doubles for rates of scaling, rather than
	// exact size values. This is how we get around that:
	double zoomx = newwidth / (float)img->w;
	double zoomy = newheight / (float)img->h;
	SDL_Surface* sized = NULL;

	// This function assumes no smoothing, so that any colorkeys wont bleed.
	if (x)
		sized = zoomSurface(img, zoomx, zoomx, SMOOTHING_OFF);
	else
		sized = zoomSurface(img, zoomy, zoomy, SMOOTHING_OFF);


	SDL_FreeSurface(img);
	img = sized;
}