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

#include "Fou.h"
#include "Tour.h"
#include "Cavalier.h"
#include "Reine.h"
#include "Roi.h"
#include "Pion.h"

#include "UserInterface.h"


using namespace std;


/* Liste fonctions */


bool ajouterJoueur(string, Joueur***&);
bool updateJoueur(string, Joueur***&, int);
void newPartie(Partie***&);

void gestJoueur(Joueur***&);
void gestPartie(Partie***&);

void setJoueurPartie(Joueur***,Partie***);

void initPartie(Partie*);
void playPartie(Partie*);

void chargerJeu(Partie***&, Joueur***&);

void saveParties(Partie***&);
void saveJoueurs(Joueur***&);



//////////////////
//     MAIN     //
//////////////////

int main(int argc, char *argv[]) {
	
	bool continuer = true;


	Joueur*** listeJoueur = NULL;
	Partie*** listePartie = NULL;

	chargerJeu(listePartie, listeJoueur);
	

	UserInterface ui(listeJoueur, listePartie);

	ui.start();

	/*cout << "Bienvenue sur le jeu ChessQuito" << endl
		<< endl;

	char tmp[2] = { "\0" };

	while (tmp[0] != '4') {


		cout << "Choisissez entre :" << endl
			<< "\t 1. Gestionnaire de joueurs" << endl
			<< "\t 2. Gestionnaire de parties" << endl
			<< "\t 3. Ajouter un joueur a une partie" << endl
			<< endl
			<< "\t 4. Quitter" << endl;

		cin >> tmp;

		system("cls");


		switch (tmp[0]) {

		case '1':
			gestJoueur(listeJoueur);
			break;

		case '2':
			gestPartie(listePartie);
			break;

		case '3':
			setJoueurPartie(listeJoueur, listePartie);
			break;

		case '4':
			cout << "A bientot !" << endl;
			break;

		default:
			cout << "Rentrez un numero valide !" << endl;
			break;

		}
	}*/

	saveJoueurs(listeJoueur);
	saveParties(listePartie);


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

	for (int j = 0; (*listeJoueur)[j] != NULL; i++)
		if (nom == (*listeJoueur)[j]->getNom()) {
			return false;
		}

	(*listeJoueur)[i]->setNom(nom);
	return true;
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






/* Interfaces de gestion console */

void gestJoueur(Joueur***& listeJoueur) {

	char tmp[50] = { "\0" };

	string tmp2;
	int i = 0;

	while (tmp[0] != '5') {



		cout << "Accueil > Gestionnaire de Joueur" << endl
			<< endl
			<< "Choisissez entre :" << endl
			<< "\t 1. Afficher la liste des joueurs" << endl
			<< "\t 2. Ajouter un joueur" << endl
			<< "\t 3. Supprimer un joueur" << endl
			<< "\t 4. Modifier un joueur" << endl
			<< endl
			<< "\t 5. Sortir du gestionnaire" << endl;

		cin >> tmp;

		cout << endl;

		system("cls");

		switch (tmp[0]) {

		case '1':
			cout << "Accueil > Gestionnaire de Joueur > Liste des joueurs" << endl
				<< endl
				<< "Voici la liste des joueurs :" << endl;

			for (i = 0; (*listeJoueur)[i] != NULL; i++) {
				cout << "\t" << i << ". " << (*listeJoueur)[i]->getNom() << endl;
			}
			cout << "Rentrez un numero de la liste pour afficher son profil ou autre chose pour sortir" << endl;
			cin >> tmp2;

			if (atoi(tmp2.c_str()) < i && atoi(tmp2.c_str()) >= 0) {

				cout << *(*listeJoueur)[atoi(tmp2.c_str())] << endl
					<< "Rentrez n'importe quoi pour sortir" << endl;
				cin >> tmp2;
			}

			system("cls");
			break;


		case '2':
			cout << "Accueil > Gestionnaire de Joueur > Ajouter un joueur" << endl
				<< endl
				<< "\t Rentrez le nom du joueur :" << endl;
			cin >> tmp2;

			ajouterJoueur(tmp2, listeJoueur);

			system("cls");
			break;

		case '3':
			cout << "En cours de construction" << endl;
			break;

		case '4':
			cout << "En cours de construction" << endl;
			break;

		case '5':
			break;

		default:
			cout << "Rentrez un numero valide !" << endl;
			break;
		}
	}
}


void gestPartie(Partie***& listePartie) {

	char tmp[50] = { "\0" };

	string tmp2;
	int i = 0;

	while (tmp[0] != '4') {

		cout << "Accueil > Gestionnaire de Partie" << endl
			<< endl
			<< "Choisissez entre :" << endl
			<< "\t 1. Afficher la liste des parties en cours" << endl
			<< "\t 2. Creer une nouvelle partie" << endl
			<< "\t 3. Rejoindre une partie en cours" << endl
			<< endl
			<< "\t 4. Sortir du gestionnaire" << endl;

		cin >> tmp;

		system("cls");

		switch (tmp[0]) {

		case '1':
			cout << "Accueil > Gestionnaire de Partie > Liste des parties en cours" << endl
				<< endl
				<< "Voici la liste des parties :" << endl;
			for (i = 0; (*listePartie)[i] != NULL; i++) {
				cout << "\t" << i << ".  Du " << (*listePartie)[i]->getDate();

				if ((*listePartie)[i]->getJ1() != NULL) {
					cout << " Avec : \t" << (*listePartie)[i]->getJ1()->getNom();
					if ((*listePartie)[i]->getJ2() != NULL)
						cout << " Et " << (*listePartie)[i]->getJ2()->getNom() << endl;
				}
				else if ((*listePartie)[i]->getJ2() != NULL)
					cout << " Avec : \t" << (*listePartie)[i]->getJ2()->getNom() << endl;
			}
			cout << "Rentrez n'importe quoi pour sortir de la liste" << endl;
			cin >> tmp2;
			break;


		case '2':
			cout << "Accueil > Gestionnaire de Partie > Creer une nouvelle partie" << endl
				<< endl
				<< "\t Creation du nouvelle partie en cours :" << endl;

			newPartie(listePartie);

			cout << "Partie cree !" << endl;
			system("cls");
			break;


		case '3':

			cout << "Accueil > Gestionnaire de Partie > Rejoindre une partie" << endl
				<< endl
				<< "Voici la liste des parties :" << endl;

			for (i = 0; (*listePartie)[i] != NULL; i++) {
				cout << "\t" << i << ".  Du " << (*listePartie)[i]->getDate();
				if ((*listePartie)[i]->getJ1() != NULL) {
					cout << " Avec : \t" << (*listePartie)[i]->getJ1()->getNom();
					if ((*listePartie)[i]->getJ2() != NULL)
						cout << " Et \t" << (*listePartie)[i]->getJ2()->getNom() << endl;
				}
				else if ((*listePartie)[i]->getJ2() != NULL)
					cout << " Avec : \t" << (*listePartie)[i]->getJ2()->getNom() << endl;
			}
			cout << "Rentrez le numero de la partie a rejoindre" << endl;
			cin >> tmp2;
			if (atoi(tmp2.c_str()) < i && atoi(tmp2.c_str()) >= 0) {

				if (!(*listePartie)[atoi(tmp2.c_str())]->isPartieInit())
					initPartie((*listePartie)[atoi(tmp2.c_str())]);

				playPartie((*listePartie)[atoi(tmp2.c_str())]);
			}
			break;

		case '4':
			break;

		default:
			cout << "Rentrez un numero valide !" << endl;
			break;
		}
	}
}


void setJoueurPartie(Joueur*** listeJoueur, Partie*** listePartie) {

	string tmp;
	bool fini = false;

	system("cls");

	while (!fini) {

		cout << "Accueil > Ajouter un joueur a une partie" << endl
			<< endl;

		int i = 0;
		for (; (*listeJoueur)[i] != NULL; i++) {
			cout << "\t" << i << ". " << (*listeJoueur)[i]->getNom() << endl;
		}

		cout << "Selectionnez le joueur desire (STOP Pour quitter le menu):" << endl;

		cin >> tmp;

		if (tmp == "STOP")
			return;

		if (atoi(tmp.c_str()) >= i && atoi(tmp.c_str()) < 0) {
			cout << "Ce joueur n'existe pas !" << endl;
		}
		else {
			int numJoueur = atoi(tmp.c_str());

			// On affiche les parties en cours

			for (i = 0; (*listePartie)[i] != NULL; i++) {
				cout << "\t" << i << ".  Du " << (*listePartie)[i]->getDate();
				if ((*listePartie)[i]->getJ1() != NULL) {
					cout << "Avec : \t" << (*listePartie)[i]->getJ1()->getNom();
					if ((*listePartie)[i]->getJ2() != NULL)
						cout << " Et " << (*listePartie)[i]->getJ2()->getNom() << endl;
				}
				else if ((*listePartie)[i]->getJ2() != NULL)
					cout << "Avec : \t" << (*listePartie)[i]->getJ2()->getNom() << endl;
			}

			cout << "Selectionnez la partie que " << (*listeJoueur)[atoi(tmp.c_str())]->getNom() << " veut rejoindre :" << endl;

			cin >> tmp;

			if (tmp == "STOP")
				return;

			if (atoi(tmp.c_str()) >= i && atoi(tmp.c_str()) < 0) {
				cout << "Cette partie n'existe pas !" << endl;
			}
			else {
				if ((*listeJoueur)[numJoueur]->setPartie((*listePartie)[atoi(tmp.c_str())])) {
					cout << "Le joueur est bien dans la partie" << endl;
					fini = true;
				}
				else
					cout << "ERREUR : La partie est pleine ou le joueur a deja 5 parties en cours" << endl;

			}
		}
	}
}



/* Interfaces jeu */

void initPartie(Partie* mPartie) { // Permet aux joueurs de placer leurs pièces en fonction de la règle qu'ils ont choisie

	system("cls"); // On efface la console

				   /* On verifie que les deux joueurs sont bien dans la partie */

	if (mPartie->getJ1() == NULL || mPartie->getJ2() == NULL) {
		std::cout << "Il n'y a pas assez de joueur" << endl << endl;
		return;
	}


	/* Selection du type de la partie ( le numero de regle) */


	// Fait 2 tableaux de 4 piece ( un noir, un blanc)

	Piece* pBlanc[4];
	Piece* pNoir[4];


	// Tant que la regle n'est pas choisi

	while (mPartie->getTypePartie() == -1) {

		system("cls"); // On efface la console


		cout << "Quelle regle voulez-vous utiliser ?" << endl
			<< "1 \t 2 \t 3" << endl;

		char tmp[4];

		cin >> tmp;

		switch (tmp[0]) {

		case '1':
			cout << "Vous avez choisi la regle 1." << endl
				<< "Vous aurez les pièces suivantes :" << endl
				<< "Reine \t Tour \t Fou \t Cavalier" << endl;
			mPartie->setTypePartie(1);

			pBlanc[0] = new Reine(0);
			pBlanc[1] = new Tour(0);
			pBlanc[2] = new Fou(0);
			pBlanc[3] = new Cavalier(0);

			pNoir[0] = new Reine(1);
			pNoir[1] = new Tour(1);
			pNoir[2] = new Fou(1);
			pNoir[3] = new Cavalier(1);
			break;

		case '2':
			cout << "Vous avez choisi la regle 2." << endl
				<< "Vous aurez les pièces suivantes :" << endl
				<< "Pion \t Tour \t Fou \t Cavalier" << endl;
			mPartie->setTypePartie(2);

			pBlanc[0] = new Pion(0);
			pBlanc[1] = new Tour(0);
			pBlanc[2] = new Fou(0);
			pBlanc[3] = new Cavalier(0);

			pNoir[0] = new Pion(1);
			pNoir[1] = new Tour(1);
			pNoir[2] = new Fou(1);
			pNoir[3] = new Cavalier(1);
			break;

		case '3':
			cout << "Vous avez choisi la regle 3." << endl
				<< "Vous aurez les pièces suivantes :" << endl
				<< "Roi \t Tour \t Fou \t Cavalier" << endl;
			mPartie->setTypePartie(3);

			pBlanc[0] = new Roi(0);
			pBlanc[1] = new Tour(0);
			pBlanc[2] = new Fou(0);
			pBlanc[3] = new Cavalier(0);

			pNoir[0] = new Roi(1);
			pNoir[1] = new Tour(1);
			pNoir[2] = new Fou(1);
			pNoir[3] = new Cavalier(1);
			break;

		default:
			cout << "Cette regle n'existe pas" << endl << endl;
			break;
		}
	}


	/* On laisse maintenant les joueurs placer leurs pieces */


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {


			cout << endl << endl << *mPartie << endl;

			string pName;
			char add[4];


			cout << endl << " C'est au ";
			if (j == 0)
				cout << "Blanc";
			else
				cout << "Noir";


			cout << " de placer son " << i + 1 << " eme pion" << endl << endl;

			cout << "Quel pion voulez-vous placer :" << endl;

			// On affiche que les pions disponible

			for (int k = 0; k < 4; k++) {
				if (j == 0 && pBlanc[k] != NULL)
					cout << pBlanc[k]->getName() << " \t ";
				else if (j == 1 && pNoir[k] != NULL)
					cout << pNoir[k]->getName() << " \t ";
			}
			cout << endl;

			cin >> pName;


			/* On recherche l'id de la piece par rapport au nom */

			int idPiece = -1;

			for (int k = 0; k < 4; k++) {
				if (j == 0 && pBlanc[k] != NULL) {
					if (pName == pBlanc[k]->getName())
						idPiece = k;
				}
				else if (j == 1 && pNoir[k] != NULL) {
					if (pName == pNoir[k]->getName())
						idPiece = k;
				}
			}

			if (idPiece == -1) { // Si la piece n'est pas trouvé

				system("cls"); // On efface la console

				cout << "Cette piece nest pas disponible ou n'existe pas ==> Recommencez" << endl;
				j--;
			}
			else {


				/* On demande à l'utilisateur où le placer */

				cout << "Ou voulez-vous placer votre " << pName << " : " << endl << "De type (\"a2\")" << endl;

				cin >> add;

				system("cls"); // On efface la console


							   /* On essaye de placer les pièces */

				if (j == 0) {  // Blanc
					if (!mPartie->initPiece(pBlanc[idPiece], add)) {

						cout << "Emplacement deja pris ou hors du plateau ==> Recommencez" << endl;
						j--;
					}
					else { // On supprime la pièce du tableau temporaire

						pBlanc[idPiece] = NULL;
					}
				}
				else if (j == 1) {  // Noir
					if (!mPartie->initPiece(pNoir[idPiece], add)) {

						cout << "Emplacement deja pris ou hors du plateau ==> Recommencez" << endl;
						j--;
					}
					else { // On supprime la pièce du tableau temporaire

						pNoir[idPiece] = NULL;
					}
				}
			}
		}
	}

	cout << "Fin de l'initialisation !" << endl << *mPartie << endl << endl;
}


void playPartie(Partie* mPartie) {

	while (!mPartie->isPartieEnd()) {
		string sortir;
		cout << "Pour quitter la partie, tapez \"STOP\" sinon rentrez n'importe quoi :" << endl;
		cin >> sortir;

		if (sortir == "STOP")
			break;

		for (int j = 0; j < 2 && !mPartie->isPartieEnd(); j++) {

			system("cls"); // On efface la console

			cout << endl << endl << *mPartie << endl;

			string tmp2;
			char add[3];


			cout << endl << " C'est au ";
			if (j == 0)
				cout << "Blanc";
			else
				cout << "Noir";


			cout << " de jouer." << endl;

			cout << "Quel pion voulez-vous jouer :" << endl;

			// On affiche que les pions disponible

			for (int i = 0; i < TAILLE; i++) {
				for (int k = 0; k < TAILLE; k++) {
					if (j == 0 && (*mPartie)(i, k) != NULL) {
						if ((*mPartie)(i, k)->getColor() == 0)
							cout << (*mPartie)(i, k)->getName() << " \t ";
					}
					else if (j == 1 && (*mPartie)(i, k) != NULL) {
						if ((*mPartie)(i, k)->getColor() == 1)
							cout << (*mPartie)(i, k)->getName() << " \t ";
					}
				}
			}

			cout << endl;

			cin >> tmp2;


			/* On recherche l'id de la piece par rapport au nom */

			int idPieceX = -1;
			int idPieceY = -1;


			for (int i = 0; i < TAILLE; i++) {
				for (int k = 0; k < TAILLE; k++) {
					if (j == 0 && (*mPartie)(i, k) != NULL) {
						if ((*mPartie)(i, k)->getColor() == 0 && tmp2 == (*mPartie)(i, k)->getName()) {
							idPieceX = i;
							idPieceY = k;
						}
					}
					else if (j == 1 && (*mPartie)(i, k) != NULL) {
						if ((*mPartie)(i, k)->getColor() == 1 && tmp2 == (*mPartie)(i, k)->getName()) {
							idPieceX = i;
							idPieceY = k;
						}
					}
				}
			}


			if (idPieceX == -1) { // Si la piece n'est pas trouvé

				system("cls"); // On efface la console

				cout << "Cette piece nest pas disponible ou n'existe pas ==> Recommencez" << endl;
				j--;
			}
			else {


				/* On demande à l'utilisateur où le placer */

				cout << "Ou voulez-vous placer votre " << tmp2 << " : " << endl << "De type (\"a2\")" << endl;

				cin >> add;

				system("cls"); // On efface la console

				if (!mPartie->placePiece((*mPartie)(idPieceX, idPieceY), add)) { // Placement invalide
					cout << "Placement invalide ! ==> Recommencez" << endl;
					j--;
				}
			}
		}


	}

	if (mPartie->isPartieEnd()) {

		/* Fin de la partie */

		cout << "Bravo au joueur ";
		if (mPartie->getGagnant() == 0) {
			cout << mPartie->getJ1()->getNom() << endl;
		}
		else {
			cout << mPartie->getJ2()->getNom() << endl;
		}
	}
}


/* Fonctions de chargement des joueurs et parties */


void chargerJeu(Partie***& listePartie, Joueur***& listeJoueur) {


	cout << "Chargement des Joueurs !" << endl;

	/* On charge les joueurs */

	ifstream fichier("save/Joueurs.txt", ios::in);  // on ouvre en lecture

	if (fichier)  // si l'ouverture a fonctionné
	{
		string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue

		int i = 0;
		while (!fichier.eof()) {
			fichier.ignore(1000, '\n');
			i++;
		}

		listeJoueur = new Joueur**;
		(*listeJoueur) = new Joueur*[i];

		(*listeJoueur)[i - 1] = NULL;

		fichier.seekg(0, std::ios::beg);

		for (int j = 0; j < i - 1; j++) {

			getline(fichier, contenu, '\n');
			(*listeJoueur)[j] = new Joueur(contenu);
		}

		fichier.close();
	}
	else {
		cout << "Impossible de charger les joueurs !" << endl;
		listeJoueur = new Joueur**;
		(*listeJoueur) = new Joueur*[1];
		(*listeJoueur)[0] = NULL;
	}

	cout << "Chargement des Parties !" << endl;

	/* On charge maintenant les parties */

	ifstream fichier2("save/Parties.txt", ios::in);  // on ouvre en lecture

	if (fichier2)  // si l'ouverture a fonctionné
	{
		string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue

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


			/* On charge chaque fichier */

			string fileName;

			getline(fichier2, contenu, '\n');

			fileName = "save/parties/" + contenu + ".txt";


			ifstream tmp(fileName, ios::in);  // on ouvre en lecture


			getline(tmp, contenu, '\n'); // Date

			(*listePartie)[j] = new Partie(contenu);



			getline(tmp, contenu, '\n'); // Joueur 1

			for (int k = 0; (*listeJoueur)[k] != NULL; k++) {
				if ((*listeJoueur)[k]->getNom() == contenu) {

					(*listePartie)[j]->addJoueur((*listeJoueur)[k]);
					break;
				}
			}


			getline(tmp, contenu, '\n'); // Joueur 2

			for (int k = 0; (*listeJoueur)[k] != NULL; k++) {
				if ((*listeJoueur)[k]->getNom() == contenu) {

					(*listePartie)[j]->addJoueur((*listeJoueur)[k]);
					break;
				}
			}

			getline(tmp, contenu, '\n'); // Type Partie

			(*listePartie)[j]->setTypePartie(atoi(contenu.c_str()));


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
			fichier << (*listePartie)[i]->getDate() << endl
				<< (*listePartie)[i]->getJ1()->getNom() << endl
				<< (*listePartie)[i]->getJ2()->getNom() << endl
				<< (*listePartie)[i]->getTypePartie() << endl;


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