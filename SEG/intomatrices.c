#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "intomatrices.h"

int* ToMatrix(SDL_Surface* img, int* x, int* y, int* matrix)
{
	Uint8 r, g, b;
	SDL_GetRGB(getpixel(img, *x, *y), img->format, &r, &g, &b);
	int done = 0, x_zero = *x, x_lim = img->w;
	while(!done){
		*x = x_zero;
		while(*x < x_lim){
			SDL_GetRGB(getpixel(img, *x, *y), img->format, &r, &g, &b);
			if(r != g){ //end of the line
				x_lim = *x;
				*matrix = -1;
				matrix++;
			}
			else{
				*matrix = (int) r == 0;
				matrix++;
			}
			*x++;
		}
		*y++;
		SDL_SGetRGB(getpixel(img, x_zero, *y), img->format, &r, &g, &b);	
		if(r != g || y >= img->h)
			done = 1;
	}

}
