/* segementation */

void Cut(SDL_Surface* img, int xory, int where, int from, int to)
{
	if(xory)
  { //y, vertically
		for(int y = from ; y < img->h && y < to ; ++y)
    {
			putpixel(img, where, y, SDL_MapRGB(img->format, 255, 0, 0));
		}
	}
	else
  { //x, horizontally
		for(int x = from ; x < img->w && x < to ; ++x)
    {
			putpixel(img, x, where, SDL_MapRGB(img->format, 255, 0, 0));
		}
	}
}

void MakingLines(SDL_Surface* img)
{
	int x, y = 0;
	Uint8 r, g, b;
	while(y < img->h)
  {
		x = 0;
		SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
		while(x < img->w && r != 0)
    {
			SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
			++x;
		}
		if(x == img->w)
			Cut(img, 0, y, 0, x);
		++y;
	}
	x = 0;
	while(x < img->w)
  {
		y = 0;
		SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
		while(y < img->h && r != 0)
    {
			SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
			++y;
		}
		if(y == img->h)
			Cut(img, 1, x, 0, y);
		++x;
	}
}
