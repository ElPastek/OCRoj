# include "mainSDL.h"

int main(int argc, char *argv[])
{
  if(argc < 2)
    errx(1, "Please enter an image path.");
  init_sdl();
  SDL_Surface *image = load_image(argv[1]);
  display_image(image);
  To_GreyLevel(image);
  //display_image(image);
  To_Black_And_White(image);
  //To_Black_On_White(image);
  //display_image(image);
  MakingBlocks(image);
  //display_image(image);
  intoMatrices(image);
  //display_image(image);
  SDL_FreeSurface(image);
  return 0;
}
