#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


struct block {
	int x_zero, y_zero, x_end, y_end;
};

void MakingChars(SDL_Surface* line);
void MakingBlocks(SDL_Surface* img, struct block* blox);
