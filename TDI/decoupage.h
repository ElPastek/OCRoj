void color_lign (SDL_Surface *img, int i, int width)
{
  Uint32 pixel;
  for (int j = 0; j < width; j++)
  {
     pixel = SDL_MapRGB(img->format, 255, 0, 0);
     putpixel(img, j, i, pixel);
  }
}

void color_column (SDL_Surface *img, int i, int j, int z)
{
  Uint32 pixel;
  for (; j < i; j++)
  {
     pixel = SDL_MapRGB(img->format, 255, 0, 0);
     putpixel(img, z, j, pixel);
  }

}

int Lign_is_white (SDL_Surface *img, int i, int width)
{
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int resul = 1;

  for (int j = 0; j < width; j++)
  {
    pixel = getpixel(img, j, i);
    SDL_GetRGB(pixel, img->format, &r, &g, &b);
    if (r == 0 || g == 0 || b == 0)
    {
      resul = 0;
    }
  }
  return resul;
}

int Column_is_white (SDL_Surface *img, int i, int j, int z)
{
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;

  int resul = 1;

  for (; j < i; j++)
  {
    pixel = getpixel(img, z, j);
    SDL_GetRGB(pixel, img->format, &r, &g, &b);
    if (r == 0 || g == 0 || b == 0)
    {
      resul = 0;
    }
  }
  return resul;
}

void lign (SDL_Surface *img, int width, int height, int *tab)
{
  int resul = 0;
  for (int i = 0; i < height; i++)
  {
    if (!resul)
    {
      if(!Lign_is_white(img, i, width))
      {
        *(tab + i) = 1;
        if(i > 0)
        {
          color_lign(img, i - 1, width);
        }
        resul = 1;
      }
    }
    else
    {
      if(Lign_is_white(img, i, width))
      {
        color_lign(img, i, width);
        resul = 0;
      }
      else
      {
        *(tab + i) = 1;
      }
    }
  }
}

void column (SDL_Surface *img,int j, int i, int width)
{
  int resul = 0;

  for (int z = 0; z < width; z++)
  {
    if (!resul)
    {
      if (!Column_is_white(img, i, j, z))
      {
        resul = 1;
        if (z > 0)
        {
          color_column(img, i, j, z);
        }
      }
    }
    else
    {
      if(Column_is_white(img, i, j, z))
      {
        resul = 0;
        color_column(img, i, j, z);
      }
    }
  }
}

void letter(SDL_Surface *img, int width, int height, int *tab)
{
  int resul = 0;
  int j = 0;

  for (int i = 0; i < height; i++)
  {
    if (!resul)
    {
      if (*(tab + i))
      {
       resul = 1;
       j = i;
      }
    }
    else
    {
      if (!*(tab + i))
      {
        resul = 0;
        column(img, j, i, width);
        j = 0;
      }
    }
  }
}

void decoupages (SDL_Surface *img)
{
  int height = img->h;
  int width = img->w;
  int *tab = malloc(height * sizeof(int));

  for (int i = 0; i < height; i++)
  {
    *(tab + i) = 0;
  }
  lign(img, width, height, tab);
  letter(img, width, height, tab);
  SDL_SaveBMP(img, "NewImg.bmp");
}
