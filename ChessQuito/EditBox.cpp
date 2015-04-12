#include "EditBox.h"



EditBox::EditBox(SDL_Surface * ecran, TTF_Font * police, string & txt, int x, int y, int width, int height, Uint32 bgColor, SDL_Color fgColor)
{
	this->ecran = ecran;
	this->police = police;
	this->txt = txt;
	this->bgColor = bgColor;
	this->fgColor = fgColor;

	
	boxRect.h = height;
	boxRect.w = width;
	boxRect.x = x;
	boxRect.y = y;
	

	drawBox();
}


void EditBox::drawBox()
{
	SDL_Surface* box;

	box = SDL_CreateRGBSurface(SDL_HWSURFACE, boxRect.w, boxRect.h, 32, 0, 0, 0, 0);


	SDL_FillRect(box, NULL, bgColor); // On rempli le fond du bouton

	SDL_Surface* tmp;

	tmp = TTF_RenderText_Blended(police, txt.c_str(), fgColor);

	if (tmp->w > boxRect.w - 20)
		resizeImage(tmp, boxRect.w - 10, boxRect.w - 10, true);
	if (tmp->h > boxRect.h - 8)
		resizeImage(tmp, boxRect.h - 4, boxRect.h - 4);

	SDL_Rect tmpRect;
	tmpRect.x = (boxRect.w - tmp->w) / 2;
	tmpRect.y = (boxRect.h - tmp->h) / 2;

	SDL_BlitSurface(tmp, NULL, box, &tmpRect);


	SDL_FreeSurface(box);
	SDL_FreeSurface(tmp);
}


EditBox::~EditBox()
{
}
