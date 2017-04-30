#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "cutcutcut.h"
#include "pixel_operations.h"


void Cut(SDL_Surface* img, int xory, int where, int from, int to)
{
	if(xory)
  { //y, vertically
		for(int y = from ; y < img->h && y < to ; ++y)
    {
			putpixel(img, where, y, SDL_MapRGB(img->format, 255, 0, 0));
		}
	}
	else
  { //x, horizontally
		for(int x = from ; x < img->w && x < to ; ++x)
    {
			putpixel(img, x, where, SDL_MapRGB(img->format, 255, 0, 0));
		}
	}
}

int CutPrecise(SDL_Surface* img, int x, int y, int xory)
{
	Uint8 r=255, g=255, b=255;
	if(xory){
		int y_ = y, blackpxlfound = 0;
		while(y_ < img->h){
			blackpxlfound = blackpxlfound || (r == 0 && g == 0);
			++y_;
			SDL_GetRGB(getpixel(img, x, y_), img->format, &r, &g, &b);
		}
		if(!blackpxlfound)
			Cut(img, 1, x, y, y_);
		return y_;
	}
	else{
		int x_ = x, blackpxlfound = 0;
		while(x_ < img->w && r == g){
			blackpxlfound = blackpxlfound || (r == 0 && g == 0);
			++x_;
			SDL_GetRGB(getpixel(img, x_, y), img->format, &r, &g, &b);
		}
		if(!blackpxlfound)
			Cut(img, 0, y, x, x_);
		return x_;
	}
}

void MakingBlocks(SDL_Surface* img)
{
	int x, y = 0;
	Uint8 r, g, b;
	while(y < img->h)
  {
		x = 0;
		SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
		while(x < img->w && r != 0)
    {
			SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
			++x;
		}
		if(x == img->w)
			Cut(img, 0, y, 0, x);
		++y;
	}
	x = 0;
	while(x < img->w)
  {
		y = 0;
		SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
		while(y < img->h && r != 0)
    {
			SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
			++y;
		}
		if(y == img->h)
			Cut(img, 1, x, 0, y);
		++x;
	}
	
	x = 0, y = 0;
	SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
	while(x < img->w){
		while(y < img->h){
			SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
			y = g==255 ? CutPrecise(img, x, y, 1) : y + 1;
		}
		++x;
	}  
	x = 0, y = 0;
	while(y < img->h){
		while(x < img->w){
			SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
			x = g==255 ? CutPrecise(img, x, y, 0) : x + 1;
			}
		++y;
		}
}  

