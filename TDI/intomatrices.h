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

void resize(struct mat* mat, FILE* ft){
	int dif[2];
	dif[0] = mat->c - 10, dif[1] = mat->l - 10;
	//resizing horizontaly
	if(dif[0] > 0);
	if(dif[0] < 0);
	//resizing verticaly
	if(dif[1] > 0);
	if(dif[1] < 0);
	mat->data[mat->c * mat->l + 1] = '0';
	fputs(mat->data, ft);
	fputs('\n', ft);
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
	return x_max;
}


void intoMatrices(SDL_Surface* img)
{
	int x, y = 0, char_found=0;
	Uint8 r, g, b;
	FILE* f = fopen("tmp", "w+");
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
					char_found++;
					int _x = __intoMat(img, f, x, y);
					mark(img, x, y);
					x = _x;
				}
			}

			else{
				++x;
			}
		}
		++y;
	}
	fclose(f);
	f = fopen("tmp", "r");
	FILE* ft = fopen("training","w+");
	fprintf(ft, "i,o,%i\n", char_count);
	struct mat* mat = malloc(sizeof(struct mat));
	mat->l = 0;
	char* buf[255];
	fgets(buf, 255, f);
	while(buf[0] != EOF){
		mat->c = (int)buf[0] - 48;
		if(buf[1] != '\n')
			mat->c = mat->c * 10 + (int)buf[1] - 48;
		fgets(buf, 255, f);
		for(;buf[mat->c * mat->l + 1] != '0'; ++mat->l);
		mat->data = (char*)buf;
		resize(mat, ft); //print resized 10(?)*10matrix into training.
		fgets(buf, 255, f);
	}
}
