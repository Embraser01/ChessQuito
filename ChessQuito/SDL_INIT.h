/* Includes SDL */

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_gfxPrimitives.h>


void resizeImage(SDL_Surface*& img, const double newwidth, const double newheight, bool x = false)
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