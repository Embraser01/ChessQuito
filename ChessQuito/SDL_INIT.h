/* 
	Includes SDL et 
	définition de la fonction resize ( ==> main) 
*/

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_gfxPrimitives.h>


void resizeImage(SDL_Surface*& img, const double newwidth, const double newheight, bool x);