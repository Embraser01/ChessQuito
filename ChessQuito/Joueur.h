#ifndef _JOUEUR_H
#define _JOUEUR_H


/*
	Joueur:
		Contient les informations du joueur,
		ainsi que les parties aux quelles il joue.
*/

#include <string>
#include "Partie.h"

using namespace std;


const int MAXPARTIES = 5; // Nombre de partie max par joueur

class Partie;

class Joueur
{
private:
	string nom; // Nom du joueur
	Partie* partie[MAXPARTIES]; // Partie à laquelle est relié le joueur ( NULL si aucune partie en cours);

public:
	Joueur(void);
	Joueur(string); // Pseudo du joueur
	Joueur(string, Partie*); // Pseudo du joueur, Partie à rejoindre

	Joueur(const Joueur& cpyJoueur); // Constructeur par copie
	Joueur& operator=(Joueur& cpyJoueur); // Operateur d'affectation

	string getNom() const;
	void setNom(string); // Changer le pseudo du joueur

	Partie* getPartie(int) const;
	bool setPartie(Partie*); // Permet d'ajouter le joueur à une partie ( si il lui reste une place)


	friend ostream& operator<<(ostream &flux, Joueur const& mJoueur); // Surcharge operateur <<
	~Joueur(void);
};

ostream& operator<<(ostream &flux, Joueur const& mJoueur);


#endif