/*char* resize(struct mat* car){
	int* ratio = malloc(2*sizeof(int));
	*ratio = ntm
}*/

struct mat{
	size_t c, l;
	char* data;
};

void mark(SDL_Surface* img, int x, int _y){
	int y = _y;
	Uint8 r, g, b;
	SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
	while(y < img->h && r == g){
		putpixel(img, x, y, SDL_MapRGB(img->format, 0, 0, 255));
		++y;
		SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
	}
}

/*struct mat* __intoMat(SDL_Surface* img, int x, int y){
	int _x = x, x_max = x, y_max = y, i = 0;
	Uint8 r, g, b;
	SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
	while(x_max < img->w && r == g){
		SDL_GetRGB(getpixel(img, x_max, y), img->format, &r, &g, &b);
		x_max++;
	}
	r = g;
	while(y_max < img->h && r == g){
		SDL_GetRGB(getpixel(img, x, y_max), img->format, &r, &g, &b);
		y_max++;
	}
	struct mat* mat = malloc(sizeof(struct mat));
	mat->c = x_max - x, mat->l = y_max - y;
	mat->data = malloc((mat->c) * (mat->l) * sizeof(char));
	printf("   cols = %zu, y = %i, ymax = %i\n\n", mat->c, y, y_max);
	while(y < y_max){
		x = _x;
		while(x < x_max){
			SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
			mat->data[i] = r == 0 ? '1' : '0';
			++i;
		}
		++y;
	}
	mat->data[i] = '\n', mat->data[i+1] = '\0';
	return mat;
}*/
void intoMatrices(SDL_Surface* img)
{
	int x, y = 0;
	Uint8 r, g, b;
	FILE* f = fopen("training.txt", "w+");
	while(y < img->h)
  {
		x = 0;
		while(x < img->w)
    {
			SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
			if(r == g){
				if(g != b){
					while(x < img->w && r == g)
						++x;
				}
				else{
					printf("Char found at %i\n", x);
					//struct mat* mat = __intoMat(img, x, y);
					int _x = x, _y = y, x_max = x, y_max = y, i = 0;
					Uint8 r, g, b;
					SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
					while(x_max < img->w && r == g){
						SDL_GetRGB(getpixel(img, x_max, y), img->format, &r, &g, &b);
						x_max++;
					}
					r = g;
					while(y_max < img->h && r == g){
						SDL_GetRGB(getpixel(img, x, y_max), img->format, &r, &g, &b);
						y_max++;
					}
					struct mat* mat = malloc(sizeof(struct mat));
					mat->c = x_max - x, mat->l = y_max - y;
					mat->data = malloc((mat->c) * (mat->l) * sizeof(char));
					printf("   cols = %zu, y = %i, ymax = %i\n\n", mat->c, y, y_max);
					while(y < y_max){
						x = _x;
						while(x < x_max){
							SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
							mat->data[i] = r == 0 ? '1' : '0';
							++i;
						}
						++y;
					}
					mat->data[i] = '\n', mat->data[i+1] = '\0';
					x = _x, y = _y;

					//char* char = resize(mat);
					fputs(mat->data, f);
					mark(img, x, y);
					x += mat->c;
					free(mat);
				}
			}
			else
				++x;
		}
		++y;
	}
	fclose(f);
}
