/* Headers */
# include <SDL/SDL.h>
# include <SDL2/SDL_image.h>
# include "pixel_operations.c"
# include "grey_level.c"
# include "black_on_white.c"
# include "black_and_white.c"
# include "open_image.c"

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
  SDL_FreeSurface(image);
  return 0;
}
