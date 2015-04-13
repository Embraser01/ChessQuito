#include "UserInterface.h"



UserInterface::UserInterface(Joueur*** listeJoueur, Partie*** listePartie)
{
	
	this->listeJoueur = listeJoueur;
	this->listePartie = listePartie;

	mode = 1; // Page d'accueil 
	selection = -1;


	/* Initialisation de la SDL */

	SDL_Init(SDL_INIT_VIDEO);
	if (TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	police = TTF_OpenFont("fonts/Roboto-Regular.ttf", 60); // Police/Fonts du texte


	ecran = SDL_SetVideoMode(TX, TY, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("ChessQuito | Projet C++ | Fernandes Marc-Antoine", NULL);


	/* On cr�e les boutons necessaires et on met les autres � NULL */

	btnColor = SDL_MapRGB(ecran->format, 129, 199, 132);
	btnFontColor = { 0,0,0 };
	
	btnSortir = new Bouton(ecran, police, "SORTIR", WIDTH + 10, TY - 75, TX - WIDTH - 20, 70, btnColor, btnFontColor);

	btnGestJoueurs = new Bouton(ecran, police, "Gestionnaire Joueurs", WIDTH + 10, 100, TX - WIDTH - 20, 70, btnColor, btnFontColor);
	btnGestParties = new Bouton(ecran, police, "Gestionnaire Parties", WIDTH + 10, 200, TX - WIDTH - 20, 70, btnColor, btnFontColor);

	btnAddJoueur = NULL;
	btnUpdateJoueur = NULL;
	btnDeleteJoueur = NULL;
	btnValider = NULL;

	btnPlayPartie = NULL;
	btnNewPartie = NULL;
	btnDeletePartie = NULL;

	btnListe = NULL;


	/* On initialise l'EditBox */

	Uint32 bgColor = SDL_MapRGB(ecran->format, 255, 255, 255);
	SDL_Color fontColor = { 0, 0, 0 };

	
	eb = new EditBox(ecran, police, 300, 300, 250, 45, bgColor, fontColor);


	/* On positionne la barre de navigation et le plateau */

	navBar.h = TY;
	navBar.w = TX - WIDTH;
	navBar.x = WIDTH;
	navBar.y = 0;

	plateau.h = TY;
	plateau.w = WIDTH;
	plateau.x = 0;
	plateau.y = 0;

	dNavBar();
	dPlateau();
	

	SDL_Flip(ecran);
}




void UserInterface::start()
{

	bool continuer = true;


	SDL_Event event;

	while (continuer) {

		SDL_WaitEvent(&event);
		switch (event.type) {

		case SDL_QUIT:
			continuer = 0;
			break;

		case SDL_KEYDOWN:

			if (event.key.keysym.sym == SDLK_ESCAPE)
				continuer = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			int action = checkEventMenu(event.button.x, event.button.y); 

			if (action == 0)
				continuer = false;

			else if (action == -1) { // Pas dans le menu

				if (mode == 0) {
					checkEventPartie(event.button.x, event.button.y);
				}
				else if (mode == 2 || mode == 3) {

					checkEventListe(event.button.x, event.button.y);
				}
				else if (mode == 4 || mode == 5) {

					int jsp = checkEventEditBox();
						
					if (jsp == -1)
						continuer = false;
					else {
						mode = 2;
						dPlateau();
						dNavBar();
					}
				}
			}
			break;
		}
	}
}



void UserInterface::dPlateau()
{
	SDL_FillRect(ecran, &plateau, SDL_MapRGB(ecran->format, 207, 216, 220)); // On met l'arriere plan


	if (mode == 0) {


		if ((*listePartie)[selection]->getJ1() == NULL || (*listePartie)[selection]->getJ2() == NULL) {


		}

		SDL_Rect contour;
		contour.h = CASE_Y * TAILLE + 8;
		contour.w = CASE_X * TAILLE + 8;
		contour.x = 96;
		contour.y = 96;

		SDL_FillRect(ecran, &contour, SDL_MapRGB(ecran->format, 144, 164, 174)); // On met l'arriere plan

		SDL_Rect caseRect;
		caseRect.h = CASE_Y;
		caseRect.w = CASE_X;
		caseRect.x = 100;
		caseRect.y = 100;

		for (int i = 0; i < TAILLE; i++) {
			caseRect.x = 100;

			for (int j = 0; j < TAILLE; j++) {
				Uint32 color;

				if((j + i)%2 == 0)
					color = SDL_MapRGB(ecran->format, 246, 228, 151);
				else
					color =  SDL_MapRGB(ecran->format, 189, 141, 70);

				SDL_FillRect(ecran, &caseRect, color ); // On met la case

				caseRect.x += CASE_X;
			}

			caseRect.y += CASE_Y;
		}
	}
	else if (mode == 1) {

		SDL_Surface* tmp1;
		SDL_Surface* tmp2;
		SDL_Surface* tmp3;

		SDL_Color fontColor = { 0, 0, 0 };

		tmp1 = TTF_RenderText_Blended(police, "Bienvenue", fontColor);
		tmp2 = TTF_RenderText_Blended(police, "Sur le jeu", fontColor);
		tmp3 = TTF_RenderText_Blended(police, "ChessQuito", fontColor);

		SDL_Rect txtTmp;
		txtTmp.x = 100;
		txtTmp.y = 100;

		SDL_BlitSurface(tmp1, NULL, ecran, &txtTmp);

		txtTmp.x += 100;
		txtTmp.y += 100;

		SDL_BlitSurface(tmp2, NULL, ecran, &txtTmp);

		txtTmp.x += 100;
		txtTmp.y += 100;

		SDL_BlitSurface(tmp3, NULL, ecran, &txtTmp);

		SDL_FreeSurface(tmp1);
		SDL_FreeSurface(tmp2);
		SDL_FreeSurface(tmp3);
	}
	else if (mode == 2) {

		SDL_Surface* tmp;

		tmp = TTF_RenderText_Blended(police, "Accueil  >  Gestionnaire des Joueurs", btnFontColor);
		
		resizeImage(tmp, WIDTH - 100, WIDTH - 100, true);

		SDL_Rect tmpRect;
		tmpRect.x = (WIDTH - tmp->w) / 2;
		tmpRect.y = 20;

		SDL_BlitSurface(tmp, NULL, ecran, &tmpRect);
		SDL_FreeSurface(tmp);


		Uint32 bgColor = SDL_MapRGB(ecran->format, 255, 255, 255);

		SDL_Rect listeRect;

		listeRect.x = 50;
		listeRect.y = 100;


		if (btnListe != NULL) {
			for (int i = 0; btnListe[i] != NULL; i++)
				delete btnListe[i];
			delete btnListe;
		}
		int nb;
		for (nb = 0; (*listeJoueur)[nb] != NULL; nb++);

		btnListe = new Bouton*[nb + 1];
		btnListe[nb] = NULL;

		for (int i = 0; btnListe[i] != NULL; i++) {
			if (i == selection) {

				Uint32 bgColorbis = SDL_MapRGB(ecran->format, 200, 200, 200);
				btnListe[i] = new Bouton(ecran, police, (*listeJoueur)[i]->getNom(), listeRect.x, listeRect.y, WIDTH - 100, 26, bgColorbis, btnFontColor);
			}
			else {
				btnListe[i] = new Bouton(ecran, police, (*listeJoueur)[i]->getNom(), listeRect.x, listeRect.y, WIDTH - 100, 26, bgColor, btnFontColor);
			}
			btnListe[i]->afficherBtn();
			listeRect.y += 28;
		}
	}
	else if (mode == 3) {

		SDL_Surface* tmp;

		tmp = TTF_RenderText_Blended(police, "Accueil  >  Gestionnaire des Parties", btnFontColor);

		resizeImage(tmp, WIDTH - 100, WIDTH - 100, true);

		SDL_Rect tmpRect;
		tmpRect.x = (WIDTH - tmp->w) / 2;
		tmpRect.y = 20;

		SDL_BlitSurface(tmp, NULL, ecran, &tmpRect);



		Uint32 bgColor = SDL_MapRGB(ecran->format, 255, 255, 255);

		SDL_Rect listeRect;

		listeRect.x = 50;
		listeRect.y = 100;


		if (btnListe != NULL) {
			for (int i = 0; btnListe[i] != NULL; i++)
				delete btnListe[i];
			delete btnListe;
		}
		int nb;
		for (nb = 0; (*listePartie)[nb] != NULL; nb++);

		btnListe = new Bouton*[nb + 1];
		btnListe[nb] = NULL;

		for (int i = 0; btnListe[i] != NULL; i++) {
			string txt = to_string(i) + ".    " + (*listePartie)[i]->getDate();

			if ((*listePartie)[i]->getJ1() != NULL) {
				txt += " Avec " + (*listePartie)[i]->getJ1()->getNom();
				if ((*listePartie)[i]->getJ2() != NULL)
					txt += " Et " + (*listePartie)[i]->getJ2()->getNom();
			}
			else if((*listePartie)[i]->getJ2() != NULL)
				txt += " Avec " + (*listePartie)[i]->getJ2()->getNom();


			if (i == selection) {
				Uint32 bgColorbis = SDL_MapRGB(ecran->format, 200, 200, 200);
				btnListe[i] = new Bouton(ecran, police, txt, listeRect.x, listeRect.y, WIDTH - 100, 26, bgColorbis, btnFontColor);
			}
			else {
				btnListe[i] = new Bouton(ecran, police, txt, listeRect.x, listeRect.y, WIDTH - 100, 26, bgColor, btnFontColor);
			}
			btnListe[i]->afficherBtn();
			listeRect.y += 28;
		}

	}
	else if (mode == 4) {

		SDL_Surface* tmp;

		tmp = TTF_RenderText_Blended(police, "Accueil  >  Gestionnaire des Joueurs  >  Nouveau joueur", btnFontColor);

		resizeImage(tmp, WIDTH - 100, WIDTH - 100, true);

		SDL_Rect tmpRect;
		tmpRect.x = (WIDTH - tmp->w) / 2;
		tmpRect.y = 20;

		SDL_BlitSurface(tmp, NULL, ecran, &tmpRect);
		SDL_FreeSurface(tmp);

		eb->setText("Defaut");
		eb->drawBox();

	}
	else if (mode == 5) {

		SDL_Surface* tmp;

		tmp = TTF_RenderText_Blended(police, "Accueil  >  Gestionnaire des Joueurs  >  Modifier joueur", btnFontColor);

		resizeImage(tmp, WIDTH - 100, WIDTH - 100, true);

		SDL_Rect tmpRect;
		tmpRect.x = (WIDTH - tmp->w) / 2;
		tmpRect.y = 20;

		SDL_BlitSurface(tmp, NULL, ecran, &tmpRect);
		SDL_FreeSurface(tmp);

		eb->setText((*listeJoueur)[selection]->getNom());
		eb->drawBox();
		
	}
	SDL_Flip(ecran);
}

void UserInterface::dNavBar()
{


	SDL_FillRect(ecran, &navBar, SDL_MapRGB(ecran->format, 144, 164, 174)); // On met la navBar

	if (mode == 0) {
		
	}
	else if (mode == 1) {

		btnSortir->afficherBtn();

		btnGestJoueurs->afficherBtn();
		btnGestParties->afficherBtn();


	}
	else if (mode == 2) {

		btnSortir->afficherBtn();

		if(btnAddJoueur == NULL)
			btnAddJoueur = new Bouton(ecran, police, "Ajouter un joueur", WIDTH + 10, 100, TX - WIDTH - 20, 70, btnColor, btnFontColor);

		if(btnUpdateJoueur == NULL)
			btnUpdateJoueur = new Bouton(ecran, police, "Modifier le joueur selectionn�", WIDTH + 10, 200, TX - WIDTH - 20, 70, btnColor, btnFontColor);

		if(btnDeleteJoueur == NULL)
			btnDeleteJoueur = new Bouton(ecran, police, "Supprimer le joueur selectionn�", WIDTH + 10, 300, TX - WIDTH - 20, 70, btnColor, btnFontColor);


		btnAddJoueur->afficherBtn();
		btnUpdateJoueur->afficherBtn();
		btnDeleteJoueur->afficherBtn();

	}
	else if (mode == 3) {

		btnSortir->afficherBtn();

		if(btnNewPartie == NULL)
			btnNewPartie = new Bouton(ecran, police, "Cr�er une nouvelle partie", WIDTH + 10, 100, TX - WIDTH - 20, 70, btnColor, btnFontColor);

		if(btnPlayPartie == NULL)
			btnPlayPartie = new Bouton(ecran, police, "Jouer � la partie s�l�ctionn�e", WIDTH + 10, 200, TX - WIDTH - 20, 70, btnColor, btnFontColor);

		if(btnDeletePartie == NULL)
			btnDeletePartie = new Bouton(ecran, police, "Supprimer la partie selectionn�", WIDTH + 10, 300, TX - WIDTH - 20, 70, btnColor, btnFontColor);


		btnNewPartie->afficherBtn();
		btnPlayPartie->afficherBtn();
		btnDeletePartie->afficherBtn();
	}
	else if (mode == 4 || mode == 5) {

		btnSortir->afficherBtn();

		if (btnValider == NULL)
			btnValider = new Bouton(ecran, police, "Valider", WIDTH + 10, 500, TX - WIDTH - 20, 70, btnColor, btnFontColor);
		
		btnValider->afficherBtn();


	}
}





int UserInterface::checkEventMenu(int x, int y)
{
	if (x < WIDTH)
		return -1;


	if (mode == 0) {

		if (btnSortir->isClicked(x, y)) {
			mode = 1;
			dNavBar();
			dPlateau();
			return 3;
		}
	}
	else if (mode == 1) {

		if (btnSortir->isClicked(x, y))
			return 0;

		if (btnGestJoueurs->isClicked(x, y)) {
			mode = 2;
			dNavBar();
			dPlateau();
			return -1;
		}

		if (btnGestParties->isClicked(x, y)) {
			mode = 3;
			dNavBar();
			dPlateau();
			return -1;
		}
	}
	else if (mode == 2) {

		if (btnSortir->isClicked(x, y)) {
			mode = 1;
			dNavBar();
			dPlateau();
			return -1;
		}

		if (btnAddJoueur->isClicked(x, y)) {
			mode = 4;
			dPlateau();
			dNavBar();
			return 5;
		}

		if (btnUpdateJoueur->isClicked(x, y) && selection != -1) {
			mode = 5;
			dPlateau();
			dNavBar();
			return 4;
		}

		if (btnDeleteJoueur->isClicked(x, y) && selection != -1) {
			deleteJoueur(listeJoueur, (*listeJoueur)[selection]);
			selection = -1;
			dPlateau();
			return 6;
		}
	}
	else if (mode == 3) {

		if (btnSortir->isClicked(x, y)) {
			mode = 1;
			dNavBar();
			dPlateau();
			return -1;
		}

		if (btnNewPartie->isClicked(x, y)) {
			newPartie(listePartie);
			dPlateau();
			return 2;
		}

		if (btnPlayPartie->isClicked(x, y) && selection != -1) {
			return 7;
		}

		if (btnDeletePartie->isClicked(x, y) && selection != -1) {
			deletePartie(listePartie, (*listePartie)[selection]);
			selection = -1;
			dPlateau();
			return 1;
		}


	}
	else if (mode == 4 || mode == 5) {

		if (btnSortir->isClicked(x, y)) {
			mode = 2;
			dNavBar();
			dPlateau();
			return -1;
		}

		if (btnValider->isClicked(x, y)) {
			return 8;
		}

	}
	return -1;
}



char * UserInterface::checkEventPartie(int x, int y)
{


	return NULL;
}

int UserInterface::checkEventListe(int x, int y)
{
	if (mode != 2 && mode != 3)
		return -1;

	selection = - 1;

	for (int i = 0; btnListe[i] != NULL; i++) {
		if (btnListe[i]->isClicked(x, y)) {
			selection = i;
			break;
		}
	}

	if (selection != -1)
		dPlateau();
	return 0;
}

int UserInterface::checkEventEditBox()
{
	bool isEditionFinish = false;

	while (!isEditionFinish) {

		int res = eb->start();

		if (res == -2) { // Quitter le jeu
			return -1;
		}
		SDL_Event event;
		SDL_WaitEvent(&event);

		if (btnSortir->isClicked(event.button.x, event.button.y)) {
			return 1;
		}

		if ((btnValider->isClicked(event.button.x, event.button.y) || res == 0) && eb->getText().length() > 0) {

			if (mode == 4) {
				if (!ajouterJoueur(eb->getText(), listeJoueur)) {

					dPlateau();

					SDL_Surface* tmp;

					tmp = TTF_RenderText_Blended(police, "Le nom est d�j� pris !", btnFontColor);

					resizeImage(tmp, 250, 250, true);

					SDL_Rect tmpRect;
					tmpRect.x = 300;
					tmpRect.y = 360;

					SDL_BlitSurface(tmp, NULL, ecran, &tmpRect);
					SDL_FreeSurface(tmp);
				}
				else
					isEditionFinish = true;
			}
			else {
				if (!updateJoueur(eb->getText(), listeJoueur, selection)) {

					dPlateau();

					SDL_Surface* tmp;

					tmp = TTF_RenderText_Blended(police, "Le nom est d�j� pris !", btnFontColor);

					resizeImage(tmp, 250, 250, true);

					SDL_Rect tmpRect;
					tmpRect.x = 300;
					tmpRect.y = 360;

					SDL_BlitSurface(tmp, NULL, ecran, &tmpRect);
					SDL_FreeSurface(tmp);
				}
				else
					isEditionFinish = true;
			}	
		}
		
	}
	return 0;
}



UserInterface::~UserInterface()
{

	/* On delete les boutons */

	if(btnSortir != NULL)
		delete btnSortir;

	if (btnGestJoueurs != NULL)
		delete btnGestJoueurs;
	if (btnGestParties != NULL)
		delete btnGestParties;

	if (btnAddJoueur != NULL)
		delete btnAddJoueur;
	if (btnUpdateJoueur != NULL)
		delete btnUpdateJoueur;
	if (btnDeleteJoueur != NULL)
		delete btnDeleteJoueur;
	if (btnValider != NULL)
		delete btnValider;

	if (btnPlayPartie != NULL)
		delete btnPlayPartie;
	if (btnNewPartie != NULL)
		delete btnNewPartie;
	if (btnDeletePartie != NULL)
		delete btnDeletePartie;

	if (btnListe != NULL) {
		for (int i = 0; btnListe[i] != NULL; i++)
			delete btnListe[i];
		delete btnListe;
	}


	/* On delete l'EditBox */

	delete eb;

	/* On ferme les modules */

	TTF_CloseFont(police);
	TTF_Quit();
	SDL_Quit();
}
