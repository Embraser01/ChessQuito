#ifndef _JOUEUR_H
#define _JOUEUR_H

#include <string>
#include "Partie.h"

using namespace std;

const int MAXPARTIES = 5;

class Partie;

class Joueur
{
private:
	string nom; // Nom du joueur
	Partie* partie[MAXPARTIES]; // Partie à laquelle est relié le joueur ( NULL si aucune partie en cours);

public:
	Joueur(void);
	Joueur(string);
	Joueur(string, Partie*);

	Joueur(const Joueur& cpyJoueur);
	Joueur& operator=(Joueur& cpyJoueur);

	string getNom() const;
	void setNom(string);

	Partie* getPartie(int) const;
	bool setPartie(Partie*); // Permet d'ajouter ke joueur à une partie ( si aucune partie en cours)


	friend ostream& operator<<(ostream &flux, Joueur const& mJoueur);
	~Joueur(void);
};

ostream& operator<<(ostream &flux, Joueur const& mJoueur);


#endif