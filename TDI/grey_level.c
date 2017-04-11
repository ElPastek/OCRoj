/* Grey level */

void To_GreyLevel(SDL_Surface *surface)
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
      Uint8 grey_level = (r*0.3 + g*0.59 + b*0.11)/3;
      r = grey_level;
      g = grey_level;
      b = grey_level;
      Uint32 exit_pixel = SDL_MapRGB(surface->format, r, g, b);
      putpixel(surface, i, j, exit_pixel);
    }
  }
}
