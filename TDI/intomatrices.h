#include <assert.h>

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

void resize(struct mat* mat, FILE* ft, char* resized){
	int x, y = 0;
	while(y < mat->l){
		x = 0;
		while(x < mat->c){
			resized[(x*10/mat->c) + (y*10/mat->l) * mat->c] = mat->data[x + y *mat->c];
			++x;
		}
		++y;
	}
	memcpy(mat->data, resized, 101);
	mat->c = 10, mat->l = 10;
	mat->data[100] = '\0';
	printf("[%s]\n", mat->data);
	fputs(mat->data, ft);
	fputc('\n', ft);
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
	fprintf(f, "%i %i\n", x_max - x, y_max - y);
	while(y < y_max){
		x = _x;
		while(x < x_max){
			SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
			char curr = r == 0 ? '1' : '0';
			fputc(curr, f);
			++x, ++i;
		}
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
	printf("Found %i char.\n", char_found);
	fclose(f);
	f = fopen("tmp", "r");
	FILE* ft = fopen("training","w+");
	fprintf(ft, "i,o,%i\n", char_found);
	struct mat* mat = malloc(sizeof(struct mat));
	mat->l = 0;
	char* buf = calloc(2048, sizeof(char));
	char* resized = calloc(101, sizeof(char));
	fscanf(f, "%i", &mat->c);
	fgets(buf, 5, f);
	for(;char_found > 0; char_found--){
		printf("Char remaining : %i.\n", 1 + char_found);
		int k = (int)buf[1] == '\0' ? 1 : 2;
		//int l = k + (int)buf[k + 2] == '\n' ? 2 : 3;
		mat->l = strtoul(buf, (char**)(buf + k) , 10);
		//mat->l = strtoul(buf + k + 1, (char**)(buf + l), 10); 
		fgets(buf, 2048, f);
		printf("%i %i \n", mat->c, mat->l);
		//for(; buf[mat->c * mat->l + 1] != '\n' ; ++mat->l);
		memcpy(mat->data, buf, mat->c * mat->l + 1);
		resize(mat, ft, resized); //print resized 10(?)*10matrix into training.
		fscanf(f, "%i", &mat->c);
		fgets(buf, 5, f);
	}
	free(mat);
	fclose(f);
	fclose(ft);
}
