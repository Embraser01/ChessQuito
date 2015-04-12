#include "Bouton.h"



Bouton::Bouton(SDL_Surface * ecran, TTF_Font * police, string txtBtn, int x, int y, int width, int height, Uint32 bgColor, SDL_Color ftColor)
{
	this->ecran = ecran;
	this->police = police;
	
	btnRect.h = height;
	btnRect.w = width;
	btnRect.x = x;
	btnRect.y = y;


	btn = SDL_CreateRGBSurface(SDL_HWSURFACE, btnRect.w, btnRect.h, 32, 0, 0, 0, 0);


	SDL_FillRect(btn, NULL, bgColor); // On rempli le fond du bouton

	SDL_Surface* tmp;

	tmp = TTF_RenderText_Blended(police, txtBtn.c_str() ,ftColor);

	if (tmp->w > width - 20)
		resizeImage(tmp, width - 10, width - 10, true);
	if (tmp->h > height - 8)
		resizeImage(tmp, height - 4, height - 4);

	SDL_Rect tmpRect;
	tmpRect.x = (width - tmp->w) / 2;
	tmpRect.y = (height - tmp->h) / 2;

	SDL_BlitSurface(tmp, NULL, btn, &tmpRect);


	SDL_FreeSurface(tmp);
}


void Bouton::afficherBtn()
{
	SDL_BlitSurface(btn, NULL, ecran, &btnRect);
	SDL_Flip(ecran);
}



bool Bouton::isClicked(int x, int y)
{
	if (x > btnRect.x && x < btnRect.x + btnRect.w && y > btnRect.y && y < btnRect.y + btnRect.h) 
		return true;
	
	return false;
}


Bouton::~Bouton()
{
	SDL_FreeSurface(btn);
}
