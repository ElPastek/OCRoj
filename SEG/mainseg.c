#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "pixel_operations.h"
#include "cutcutcut.h"
#include "intomatrices.h"
void wait_for_keypressed(void) {
  SDL_Event event;
  for (;;) {
    SDL_PollEvent( &event );
    switch (event.type) {
    case SDL_KEYDOWN: return;
    default: break;
    }
  }
}

SDL_Surface* OnLoad(char* file)
{
	SDL_Surface *img;
  
	SDL_Init(SDL_INIT_EVERYTHING);

	if ((img = IMG_Load(file)) == NULL){
    errx(3, "can't load %s: %s", file, IMG_GetError());
	}

  return img;
}

SDL_Surface* Display(SDL_Surface* img)
{
	SDL_Surface* screen;
	if ((screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT)) == NULL){
		errx(1, "Couldn't set %dx%d video mode: %s\n", img->w, img->h, SDL_GetError());
	}
	if (SDL_BlitSurface(img, NULL, screen, NULL) < 0){
		warnx("BlitSurface error: %s\n", SDL_GetError());
	}
	SDL_UpdateRect(screen, 0, 0, img->w, img->h);
 
	wait_for_keypressed();

	return screen;
}

int main()
{
	
	SDL_Surface* image = OnLoad("ex.jpg");
	Display(image);
	MakingBlocks(image);
	Display(image);
	
	
	return 0;
}
