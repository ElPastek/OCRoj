/* segementation */

void findnearpixels(SDL_Surface* img, int* xy, int tolx, int toly, int whereto){
	int* xy_ = malloc(3*sizeof(int));
	int tx=tolx, ty=toly;
	xy_[0] = xy[0], xy_[1] = xy[1], xy_[2] = xy[2];

	switch(whereto){
		case 0: //r
			for(; xy[0] < img-> w && tolx; ++xy[0]){
			  if(getpixel(img, xy[0], xy[1]) == SDL_MapRGB(img->format, 255, 255, 255))
					tolx--;

				else{
					tolx = tx;
					
					findnearpixels(img, xy_, tolx, toly, 1);
					xy[0] = xy[0] > xy_[0] ? xy[0] : xy_[0];
					xy[1] = xy[1] > xy_[1] ? xy[1] : xy_[1];
				
					findnearpixels(img, xy_, tolx, toly, 3);
					xy[0] = xy[0] > xy_[0] ? xy[0] : xy_[0];
					xy[1] = xy[1] > xy_[1] ? xy[1] : xy_[1];
					xy[2] = xy[2] < xy_[2] ? xy[2] : xy_[2];
					
					findnearpixels(img, xy_, tolx, toly, 2);
					xy[0] = xy[0] > xy_[0] ? xy[0] : xy_[0];
					xy[1] = xy[1] > xy_[1] ? xy[1] : xy_[1];
					xy[2] = xy[2] < xy_[2] ? xy[2] : xy_[2];
				}
			}
			break;

		case 1: //rd
			for(; xy[0] < img->w && xy[1] < img->h && (tolx || toly); ++xy[0], ++xy[1]){
			  if(getpixel(img, xy[0], xy[1]) == SDL_MapRGB(img->format, 255, 255, 255)){
					tolx = tolx ? tolx - 1 : tolx;
					toly = toly ? toly - 1 : toly;
				}
				else
					tolx = tx, toly = ty;
			}
			break;

		case 2: //ld
			for(; xy[2] && xy[1] < img->h && (tolx || toly); --xy[2], ++xy[1]){
			  if(getpixel(img, xy[2], xy[1]) == SDL_MapRGB(img->format, 255, 255, 255)){
					tolx = tolx ? tolx - 1 : tolx;
					toly = toly ? toly - 1 : toly;
				}
				else{
					findnearpixels(img, xy_, tolx, toly, 3);
					xy[1] = xy[1] > xy_[1] ? xy[1] : xy_[1];	
					xy[2] = xy[2] < xy_[2] ? xy[2] : xy_[2];
				}
			}
			break;

		case 3: //d
			for(; xy[0] < img->h && toly; ++xy[1]){
			  if(getpixel(img, xy[0], xy[1]) == SDL_MapRGB(img->format, 255, 255, 255))
					toly--;

				else{
					toly = ty;
					findnearpixels(img, xy_, tolx, toly, 4);
					xy[2] = xy[2] < xy_[2] ? xy[2] : xy_[2];
				}
			}
			break;

		case 4: //l
			for(; xy[2] > 0 && tolx; --xy[2]){
			  if(getpixel(img, xy[2], xy[1]) == SDL_MapRGB(img->format, 255, 255, 255))
					tolx--;
				else
					tolx = tx;
			}
			break;

		default:
			printf("Something went wrong..\n");
	}
}
/*
int* findmethisblock(SDL_Surface* img, int x, int y, int tolx, int toly, Uint32 pxl){
  int* xy = findnearpixels(img, x, y, tolx, toly, 0);
	int* xy_=malloc(2*sizeof(int));
	xy_[0] = 0, xy_[1] = 0; 

	if(xy[0] < x + tolx)
		xy_ = findmethisblock(img, x + 1, y, tolx, toly, pxl);
	xy[0] = xy[0] > xy_[0] ? xy[0] : xy_[0];
	xy[1] = xy[1] > xy_[1] ? xy[1] : xy_[1];

	// la c ranger mdr
  xy_ = findnearpixels(img, x, y, tolx, toly, 1);
	xy[0] = xy[0] > xy_[0] ? xy[0] : xy_[0];
	xy[1] = xy[1] > xy_[1] ? xy[1] : xy_[1];
	if(xy[0] < x + tolx && xy[1] < y + toly)
		xy_ = findmethisblock(img, x + 1, y + 1, tolx, toly, pxl);
	xy[0] = xy[0] > xy_[0] ? xy[0] : xy_[0];
	xy[1] = xy[1] > xy_[1] ? xy[1] : xy_[1];
	
	xy_ = findnearpixels(img, x, y, tolx, toly, 3);
	xy[0] = xy[0] > xy_[0] ? xy[0] : xy_[0];
	xy[1] = xy[1] > xy_[1] ? xy[1] : xy_[1];
	if(x - 1 && xy[1] < y + toly)
		xy_ = findmethisblock(img, x - 1, y + 1, tolx, toly, pxl); 
	xy[0] = xy[0] > xy_[0] ? xy[0] : xy_[0];
	xy[1] = xy[1] > xy_[1] ? xy[1] : xy_[1];
	
	xy_ = findnearpixels(img, x, y, tolx, toly, 2);
	xy[0] = xy[0] > xy_[0] ? xy[0] : xy_[0];
	xy[1] = xy[1] > xy_[1] ? xy[1] : xy_[1];
	if(xy[1] < y + toly)
		xy_ = findmethisblock(img, x, y + 1, tolx, toly, pxl);
	xy[0] = xy[0] > xy_[0] ? xy[0] : xy_[0];
	xy[1] = xy[1] > xy_[1] ? xy[1] : xy_[1];

	return xy;
}
*/
void MakingBlocks(SDL_Surface* img)
{
	int x = 0, y = 0;
	int* xy = malloc(3*sizeof(int));
	//int* m = malloc(img->h*img->w)
	Uint8 r, b, g;
	SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
	while( y < img->h )
  {
		x = 0;
		while( x < img->w){
			SDL_GetRGB(getpixel(img, x, y), img->format, &r, &g, &b);
			if(r == 0){
				if(r == b){
					//lines are blue
					Uint32 pxl = SDL_MapRGB(img->format, 0, 0, 255);
					xy[0] = x, xy[1] = y, xy[2] = x; 					
					findnearpixels(img, xy, 13, 3, 0);
					
					for(int i = 0; i < (xy[0] - xy[2] + 3); i++){//maybe segfault
						putpixel(img, xy[2] + i - 3, y - 3, pxl);
						putpixel(img, xy[0] - i - 1, xy[1] - 1, pxl);
					}
					for(int i = 0; i < (xy[1] - y + 3; i++){
						putpixel(img, xy[2] - 3, y + i - 3, pxl); //maybe segfault
						putpixel(img, xy[0] - 1, xy[1] - 1 - i, pxl);
					}
					display_image(img);
					
					/*
					//characters are red
					pxl = SDL_MapRGB(img->format, 255, 0, 0);
					xy = findmethisblock(img, x, y, 3, 3, pxl);
					for(int i = 0; i < xy[0]; i++){//maybe segfault
						putpixel(img, x+i, y, pxl);
						putpixel(img, xy[0] - i, xy[1], pxl);
					}
					for(int i = 0; i < xy[1]; i++){
						putpixel(img, x, y + 1 + i, pxl); //maybe segfault
						putpixel(img, xy[0], xy[1] - i, pxl);
					}*/
					x = xy[0];
				}
				else{
					while(r != 0 || b != 255)
						SDL_GetRGB(getpixel(img, x++, y), img->format, &r, &g, &b);
				}
			}
			else
				++x;
		}	
		++y;
	}
}  
