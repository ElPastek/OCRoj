/* Put image in black and white */

void To_Black_On_White(SDL_Surface *surface)
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
      if ((0 <= r & r <=10)  & (0 <= g & g <=10) & (0 <= b & b <=10))
      {
        r = g = b = 255;
      }
      else
      {
        r = g = b = 0;
      }
      Uint32 exit_pixel = SDL_MapRGB(surface->format, r, g, b);
      putpixel(surface, i, j, exit_pixel);
    }
  }
}
