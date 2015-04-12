#include "Joueur.h"

ostream& operator<<(ostream &flux, Joueur const& mJoueur){

	int nbPartie = 0;
	for(int i = 0;i < MAXPARTIES;i++){
		if(mJoueur.partie[i] != NULL)
			nbPartie++;
	}

	flux << endl << mJoueur.nom << "  a " << nbPartie << " partie(s) en cours :" << endl;

	for(int i = 0;i < MAXPARTIES;i++){
		if(mJoueur.partie[i] != NULL)
			flux << "\t" << i << ".  Du " << mJoueur.partie[i]->getDate();
	}
	flux << endl;
	return flux;

}


Joueur::Joueur(void)
{
	nom = "Default";
	for(int i = 0; i < MAXPARTIES; i++)
		partie[i] = NULL;
}

Joueur::Joueur(string nom)
{
	this->nom = nom;
	for(int i = 0; i < MAXPARTIES; i++)
		this->partie[i] = NULL;
}

Joueur::Joueur(string nom, Partie* partie)
{
	this->nom = nom;
	for(int i = 0; i < MAXPARTIES; i++)
		this->partie[i] = NULL;

	setPartie(partie);
}


Joueur::Joueur(const Joueur& cpyJoueur){

	nom = cpyJoueur.nom;
	nom.append("1");
}


Joueur& Joueur::operator=(Joueur& cpyJoueur){

	nom = cpyJoueur.nom;
	nom.append("1");
	return cpyJoueur;
}


void Joueur::setNom(string nom)
{
	this->nom = nom;
}

string Joueur::getNom() const
{
	return nom;
}


bool Joueur::setPartie(Partie* partie)
{
	/*if(partie == NULL){ // Si on recoit une partie à NULL, on supprime la partie du joueur
	this->partie = NULL;
	return true;
	}*/


	/* Si la partie envoyée est déjà dans les parties du joueur, on l'enleve des parties du joueur*/

	for(int i = 0; i < MAXPARTIES; i++){
		if(this->partie[i] == partie){
			this->partie[i] = NULL;
			return false;
		}
	}


	/* Ensuite, on regarde si le joueur peut encore rejoindre une autre partie */

	int nbParties = 0;
	for(int i = 0; i < MAXPARTIES; i++)
		if(this->partie[i] != NULL)
			nbParties++;

	if(nbParties == MAXPARTIES){return false;} // Si le joueur a atteinds la limite de parties


	/* Sinon, on trouve la premiere case vide et on met la partie dedans si il reste de la place */

	int i = 0;
	for(; this->partie[i] != NULL; i++);

	if(partie->addJoueur(this)){ // Si il reste de la place dans la partie
		this->partie[i] = partie;
		return true;
	}

	return false;
}

Partie* Joueur::getPartie(int i) const
{
	return partie[i];
}



Joueur::~Joueur(void)
{
	for(int i = 0; i < MAXPARTIES; i ++)
		if( partie[i] != NULL)
			delete partie[i];
}
