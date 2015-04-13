#include "EditBox.h"



EditBox::EditBox(SDL_Surface * ecran, TTF_Font * police, int x, int y, int width, int height, Uint32 bgColor, SDL_Color fgColor)
{
	this->ecran = ecran;
	this->police = police;
	this->bgColor = bgColor;
	this->fgColor = fgColor;

	
	boxRect.h = height;
	boxRect.w = width;
	boxRect.x = x;
	boxRect.y = y;

	isSelect = false;
	
}


int EditBox::start()
{
	isSelect = true;

	drawBox();

	bool isShiftPressed = false;

	SDL_Event event;
	SDL_EnableUNICODE(true);

	while (true) {

		SDL_WaitEvent(&event);

		switch (event.type) {

		case SDL_QUIT:
			isSelect = false;
			return -2;
			break;

		case SDL_KEYDOWN:

			if (event.key.keysym.sym == SDLK_ESCAPE) {
				isSelect = false;
				drawBox();
				return -2;
			}

			if (event.key.keysym.sym == SDLK_RETURN) {
				isSelect = false;
				drawBox();
				return 0;
			}

			if (event.key.keysym.sym == SDLK_BACKSPACE && txt.length() > 0)
				txt.pop_back();

			if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT)
				isShiftPressed = true;


			else {

				switch (event.key.keysym.sym) {
				case SDLK_MINUS:
					txt += '-';
					break;
				case SDLK_KP0:
					txt += '0';
					break;
				case SDLK_KP1:
					txt += '1';
					break;
				case SDLK_KP2:
					txt += '2';
					break;
				case SDLK_KP3:
					txt += '3';
					break;
				case SDLK_KP4:
					txt += '4';
					break;
				case SDLK_KP5:
					txt += '5';
					break;
				case SDLK_KP6:
					txt += '6';
					break;
				case SDLK_KP7:
					txt += '7';
					break;
				case SDLK_KP8:
					txt += '8';
					break;
				case SDLK_KP9:
					txt += '9';
					break;
				}

				if (isShiftPressed) {

					switch (event.key.keysym.unicode) {
					case SDLK_a:
						txt += 'A';
						break;
					case SDLK_b:
						txt += 'B';
						break;
					case SDLK_c:
						txt += 'C';
						break;
					case SDLK_d:
						txt += 'D';
						break;
					case SDLK_e:
						txt += 'E';
						break;
					case SDLK_f:
						txt += 'F';
						break;
					case SDLK_g:
						txt += 'G';
						break;
					case SDLK_h:
						txt += 'H';
						break;
					case SDLK_i:
						txt += 'I';
						break;
					case SDLK_j:
						txt += 'J';
						break;
					case SDLK_k:
						txt += 'K';
						break;
					case SDLK_l:
						txt += 'L';
						break;
					case SDLK_m:
						txt += 'M';
						break;
					case SDLK_n:
						txt += 'N';
						break;
					case SDLK_o:
						txt += 'O';
						break;
					case SDLK_p:
						txt += 'P';
						break;
					case SDLK_q:
						txt += 'Q';
						break;
					case SDLK_r:
						txt += 'R';
						break;
					case SDLK_s:
						txt += 'S';
						break;
					case SDLK_t:
						txt += 'T';
						break;
					case SDLK_u:
						txt += 'U';
						break;
					case SDLK_v:
						txt += 'V';
						break;
					case SDLK_w:
						txt += 'W';
						break;
					case SDLK_x:
						txt += 'X';
						break;
					case SDLK_y:
						txt += 'Y';
						break;
					case SDLK_z:
						txt += 'Z';
						break;
					case SDLK_UNDERSCORE:
						txt += '_';
						break;
					}
					isShiftPressed = false;
				}
				else {
					switch (event.key.keysym.unicode) {
					case SDLK_a:
						txt += 'a';
						break;
					case SDLK_b:
						txt += 'b';
						break;
					case SDLK_c:
						txt += 'c';
						break;
					case SDLK_d:
						txt += 'd';
						break;
					case SDLK_e:
						txt += 'e';
						break;
					case SDLK_f:
						txt += 'f';
						break;
					case SDLK_g:
						txt += 'g';
						break;
					case SDLK_h:
						txt += 'h';
						break;
					case SDLK_i:
						txt += 'i';
						break;
					case SDLK_j:
						txt += 'j';
						break;
					case SDLK_k:
						txt += 'k';
						break;
					case SDLK_l:
						txt += 'l';
						break;
					case SDLK_m:
						txt += 'm';
						break;
					case SDLK_n:
						txt += 'n';
						break;
					case SDLK_o:
						txt += 'o';
						break;
					case SDLK_p:
						txt += 'p';
						break;
					case SDLK_q:
						txt += 'q';
						break;
					case SDLK_r:
						txt += 'r';
						break;
					case SDLK_s:
						txt += 's';
						break;
					case SDLK_t:
						txt += 't';
						break;
					case SDLK_u:
						txt += 'u';
						break;
					case SDLK_v:
						txt += 'v';
						break;
					case SDLK_w:
						txt += 'w';
						break;
					case SDLK_x:
						txt += 'x';
						break;
					case SDLK_y:
						txt += 'y';
						break;
					case SDLK_z:
						txt += 'z';
						break;
					case SDLK_UNDERSCORE:
						txt += '_';
						break;
					case SDLK_MINUS:
						txt += '-';
						break;
					}
				}
				
			}

			drawBox();
			break;

		case SDL_MOUSEBUTTONDOWN:
			int x = event.button.x;
			int y = event.button.y;

			if (!isClicked(x,y)) {
				isSelect = false;
				drawBox();
				return -1;
			}

			break;
		}
	}

	isSelect = false;
	drawBox();
	return -1;
}


void EditBox::drawBox()
{
	SDL_Surface* box;

	box = SDL_CreateRGBSurface(SDL_HWSURFACE, boxRect.w, boxRect.h, 32, 0, 0, 0, 0);


	/* On met le contour ( selection ou pas) */

	SDL_Rect tmpRect_select;
	tmpRect_select.h = boxRect.h + 4;
	tmpRect_select.w = boxRect.w + 4;
	tmpRect_select.x = boxRect.x - 2;
	tmpRect_select.y = boxRect.y - 2;

	Uint32 tmpColor;

	if (isSelect && txt.length() > 0) 
		tmpColor = SDL_MapRGB(ecran->format, 0, 255, 0);
	else
		tmpColor = SDL_MapRGB(ecran->format, 255, 0, 0);

	SDL_FillRect(ecran, &tmpRect_select, tmpColor); // On met le contour de la box


	SDL_FillRect(box, NULL, bgColor); // On rempli le fond du bouton

	if(txt.length() > 0){
		SDL_Surface* tmp;

		tmp = TTF_RenderText_Blended(police, txt.c_str(), fgColor);

		if (tmp->h > boxRect.h - 8)
			resizeImage(tmp, boxRect.h - 4, boxRect.h - 4, false);


		if (tmp->w > boxRect.w - 20) { // Si le texte est trop large

			SDL_Rect tmpRect;
			tmpRect.x = 10;
			tmpRect.y = (boxRect.h - tmp->h) / 2;


			SDL_Rect tmp2Rect;

			tmp2Rect.w = boxRect.w - 20;
			tmp2Rect.x = tmp->w - tmp2Rect.w;
			tmp2Rect.y = 0;
			tmp2Rect.h = tmp->h;


			SDL_BlitSurface(tmp, &tmp2Rect, box, &tmpRect);
		}
		else {
			SDL_Rect tmpRect;
			tmpRect.x = 10;
			tmpRect.y = (boxRect.h - tmp->h) / 2;

			SDL_BlitSurface(tmp, NULL, box, &tmpRect);
		}
		SDL_FreeSurface(tmp);
	}
	SDL_BlitSurface(box, NULL, ecran, &boxRect);
	SDL_Flip(ecran);

	SDL_FreeSurface(box);

	

}


bool EditBox::isClicked(int x, int y)
{
	if (x > boxRect.x && x < boxRect.x + boxRect.w && y > boxRect.y && y < boxRect.y + boxRect.h)
		return true;

	return false;
}

EditBox::~EditBox()
{
}
