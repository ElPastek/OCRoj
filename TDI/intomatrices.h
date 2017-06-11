/*char* resize(struct mat* car){
	int* ratio = malloc(2*sizeof(int));
	*ratio = ntm
}*/

struct mat{
	int c, l;
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

int __intoMat(SDL_Surface* img, FILE *f, int x, int y){
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
	/*struct mat* mat = malloc(sizeof(struct mat));
	mat->c = x_max - x, mat->l = y_max - y;
	mat->data = malloc((mat->c) * (mat->l) * sizeof(char));*/
	printf("   cols = %i, y = %i, ymax = %i\n\n", x_max - x, y, y_max);
	while(y < y_max){
		x = _x;
		while(x < x_max){
			SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
			char curr = r == 0 ? '1' : '0';
			fputc(curr, f);
			printf("%i ", x);
			++x, ++i;
		}
		printf("\n");
		++y;
	}
	fputc('\n', f);
	//mat->data[i] = '\n', mat->data[i+1] = '\0';
	return x_max;
}

void dispCurr(SDL_Surface* img, int x, int y){
	putpixel(img, x, y, SDL_MapRGB(img->format, 0, 255, 255));
}

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
					while(x < img->w && r == g){
						++x;
						SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
					}
				}
				else{
					printf("Char found at %i\n", x);
					int _x = __intoMat(img, f, x, y);

					//char* char = resize(mat);
					
					//fputs(mat->data, f);
					mark(img, x, y);
					//x += mat->c;
					x = _x;
				}
			}

			else{
				putpixel(img, x, y, SDL_MapRGB(img->format, 0, 255, 255));
				++x;
			}
		}
		display_image(img);
		++y;
	}
	fclose(f);
}
