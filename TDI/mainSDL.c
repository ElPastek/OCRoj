/* Headers */
# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include "open_image.h"
# include "pixel_operations.h"
# include "grey_level.h"
# include "black_and_white.h"
# include "segment.h"
//

int main()
{
  if(argc < 2)
    errx(1, "Please enter an image path.");
  init_sdl();
  SDL_Surface *image = load_image(argv[1]);
  //display_image(image);
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
