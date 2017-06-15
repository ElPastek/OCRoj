#include <assert.h>

struct mat{
	int c, l;
	char* data;
};

struct list{
	struct list* next;
	struct mat* m;
};

void ladd(struct list* l, struct mat* m){
	struct list* curr = l;
	assert(curr);
	for( ; curr->next != NULL; curr = curr->next);
	struct list* l_ = malloc(sizeof(struct list));
	l_->m = m;
	curr->next = l_;
	l_->next = NULL;
}

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
/*
void addspace(struct list* l){
	struct mat* m = malloc(struct )
}*/

char* resize(struct mat* mat){
	int x, y = 0;
	char* resized = calloc(257, sizeof(char));
	if(mat->c < 16 || mat->l < 16)
		for(int i = 0; i < 257; i++){ resized[i] = '0'; }
	while(y < mat->l){
		x = 0;
		while(x < mat->c){
			resized[(x*16/mat->c) + (y*16/mat->l) * 16] = mat->data[x + y *mat->c];
			++x;
		}
		++y;
	}
	mat->c = 16, mat->l = 16;
	resized[256] = '\n';
	return resized;
}

int __intoMat(SDL_Surface* img, struct list* l, int x, int y){
	int _x = x, x_max = x, y_max = y, i = 0;
	struct mat* mat = malloc(sizeof(struct mat));
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
	mat->data = resize(mat);
	ladd(l, mat);
	return x_max;
}


void intoMatrices(SDL_Surface* img)
{
	int x, y = 0, char_found=0;
	int spacex=0; //, lastcharx;
	Uint8 r, g, b;
	FILE* f = fopen("../RDN/Creation/inputs_RDN.txt", "w+");
	struct list* l = malloc(sizeof(struct list));
	l->next = NULL;
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
					int _x = __intoMat(img, l, x, y);
					mark(img, x, y);
					/*lastcharx = (int)((_x - x)*1.5);
					printf("%i ", lastcharx)*/
					x = _x;
				}
			}

			else{
				++x, ++spacex;
			//	if(spacex > lastcharx)

				//putpixel(img, x++, y, SDL_MapRGB(img->format, 0, 255, 255));
			}
		}
		//display_image(img);
		++y;
	}
	printf("Found %i char.\n", char_found);
	fprintf(f, "%i\n", char_found);
	for(; l->next ; l = l->next)
		fwrite(l->next->m->data, sizeof(char), 257, f);
	fclose(f);

	/*f = fopen("inputs_RDN.txt", "r");
	char* buf = calloc(257, sizeof(char));
	for(int i = 0; i < char_found ;++i){
		fscanf(f, "%s", buf);
		if(i > 649 && i < 700){
			for(int x = 0; x < 16 ; ++x){
				for(int y = 0; y < 16; ++y)
					printf("%c", buf[y + x*16] == '0' ? '.' : '#'); //jui debil
				printf("\n");
			}	
			printf("\n");
		}
	}*/

}
