/* Headers */
# include <SDL/SDL.h>
# include <SDL2/SDL_image.h>
# include "pixel_operations.h"
# include "grey_level.h"
# include "segment.h"
# include "black_on_white.h"
# include "black_and_white.h"
# include "open_image.h"

/* Main */
int main()
{
  init_sdl();
  SDL_Surface *image = load_image("/home/thomas/Images/ACE.jpg");
  display_image(image);
  To_GreyLevel(image);
  display_image(image);
  To_Black_And_White(image);
  //To_Black_On_White(image);
  display_image(image);
  MakingLines(image);
  display_image(image);
  SDL_FreeSurface(image);
  return 0;
}
