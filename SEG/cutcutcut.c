#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "cutcutcut.h"
#include "pixel_operations.h"


void Cut(SDL_Surface* img, int xory, int where, int from, int to){
	if(xory){ //y, vertically
		for(int y = from ; y < to ; ++y){ 
			putpixel(img, where, y, SDL_MapRGB(img->format, 255, 0, 0));
		}
	}
	else{ //x, horizontally
		for(int x = from ; x < to ; ++x){ 
			putpixel(img, x, where, SDL_MapRGB(img->format, 255, 0, 0));
		}
	}
}

void MakingLines(SDL_Surface* img)
{
	int x, y = 0;
	Uint8 r = 0, g = 0, b = 0;
	while(y < img->h){
		x = 0;
		while(x < img->w && r==0 && g==0 && b==0){ 
			SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
			++x;
		}
		if(x == img->w)
			Cut(img, 1, y, 0, x);
		++y;
	}
	x = 0;
	while(x < img->w){
		y = 0;
		while(y < img->h && g==0 && b==0){ 
			SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
			++y;
		}
		if(y == img->h)
			Cut(img, 0, x, 0, y);
		++x;
	}
}

/*SDL_Surface* Darken(SDL_Surface* img)
{
	int thresh = 25, blanks_count = 0, black_spotted = 0;
	Uint32 pxl;
	Uint8 r, g, b; 
	for(int y = 0, y < img->h, ++y){
		for(int x = 0, x < img->w, ++x){
			pxl = getpixel(img, x, y);
			SDL_GetRGB(pxl, img->format, &r, &g, &b);
			if(r==255, g==255, b==255){
				
			}
		}
	}
	return img;
}*/

void MakingBlocks(SDL_Surface* img)
{
	SDL_Surface* dark_img = img;
	int x = 0, y = 0, making_block = 0;
	int x_tmp_min = img->w, x_tmp_max = 0, y_tmp_min = img->h, y_tmp_max = 0;
	Uint8 r, g, b;
	while(y < img->h){

		while(x < img->w){
			Uint32 pxl = getpixel(dark_img, x, y);
			SDL_GetRGB(pxl, img->format, &r, &g, &b);
			if(!making_block && r==255 && g==255 && b==255){
				making_block = 1;
				x_tmp_min = x < x_tmp_min ? x : x_tmp_min;
				y_tmp_min = y - 1;
			}
			if(making_block && r==0 && g==0 && b==0){
				x_tmp_max = x > x_tmp_max ? x : x_tmp_max; 
			}
			++x;
		}
		++y;
	}

}


