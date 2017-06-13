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
char* resize(struct mat* mat){
	int x, y = 0;
	char* resized = calloc(101, sizeof(char));
	if(mat->c < 10 || mat->l < 10)
		for(int i = 0; i < 101; i++){ resized[i] = '0'; }
	while(y < mat->l){
		x = 0;
		while(x < mat->c){
			resized[(x*10/mat->c) + (y*10/mat->l) * 10] = mat->data[x + y *mat->c];
			++x;
		}
		++y;
	}
	mat->c = 10, mat->l = 10;
	resized[100] = '\n';
	free(mat->data);
	return resized;
}

int __intoMat(SDL_Surface* img, struct mat* mat, FILE *f, int x, int y){
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
	mat->c = x_max - x, mat->l = y_max - y;
	mat->data = calloc(mat->c*mat->l, sizeof(char));
	while(y < y_max){
		x = _x;
		while(x < x_max){
			SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
			mat->data[i] = r ? '0' : '1';
			++x, ++i;
		}
		++y;
	}
/*
	printf("%i %i\n", mat->c, mat->l); 
	for(int k = 0; k <= mat->c * mat->l; ++k)
		printf("%c", k%mat->c ? mat->data[k] : '\n');
*/
	mat->data = resize(mat);
	/*for(int k = 0; k <= mat->c * mat->l; ++k)
		printf("%c", k%mat->c ? mat->data[k] : '\n');
 */
	fwrite(mat->data, sizeof(char), 101, f);
	return x_max;
}


void intoMatrices(SDL_Surface* img)
{
	int x, y = 0, char_found=0;
	Uint8 r, g, b;
	FILE* f = fopen("training", "w+");
	struct mat* mat = malloc(sizeof(struct mat));
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
					//printf("Char found at %i\n", x);
					char_found++;
					int _x = __intoMat(img, mat, f, x, y);
					mark(img, x, y);
					x = _x;
				}
			}

			else
				++x;
		}
		++y;
	}
	printf("Found %i char.\n", char_found);
	fclose(f);
	free(mat);
}
