/* Put image on Black & White color */

void To_Black_And_White(SDL_Surface *surface)
{
  for (int i = 0; i < (surface->w); i++)
  {
    for (int j = 0; j < (surface->h); j++)
    {
      Uint32 current_pixel = getpixel(surface, i, j);
      Uint8 r;
      Uint8 g;
      Uint8 b;
      SDL_GetRGB(current_pixel, surface->format, &r, &g, &b);
      if ((0.212671f*r + 0.715160f*g + 0.072169f*b) <= 153)
      {
        r = g = b = 0;
      }
      else
      {
        r = g = b = 255;
      }
      Uint32 exit_pixel = SDL_MapRGB(surface->format, r, g, b);
      putpixel(surface, i, j, exit_pixel);
    }
  }
}
