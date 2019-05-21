# include "network.h"

/*
char *mapGen(size_t i, size_t nb_ins){
	size_t map_size = nb_out;
	char *map = malloc(sizeof(char) * );
	for (size_t nb = 0 ; nb < nb_ins ; nb++){
		map[nb] =
	}
	return map;
}
//test
char **mapFill(char *map, size_t n){
	char *str = malloc(sizeof(char *) * nb_ins);
}
//test
char *cchar(size_t i, size_t n, size_t nb_ins){
	return mapFill(mapGen(i, nb_ins), n);
}
*/

char *rchar(size_t which_char, size_t how_many){
	char *str = malloc(sizeof(char) * how_many);
	for(size_t n = 0 ; n < how_many ; n++){
		int r = rand() % 3;
		if (r==2) r=which_char;
		str[n] = r;
	}
	printf(str);
	return str;
}

//NE MARCHE PAS !!!!!!!!!!!!!!!!!!!!!!

void makeset(FILE* file, size_t number, size_t nb_out, size_t nb_ins){
	fprintf(file, "%zu,%zu,%zu\n", nb_ins, nb_out, number);

	size_t seed = rand() % nb_out;
	printf("seed : %zu", seed);
	//alphabet
	for (size_t n = 0 ; n < number ; n++)
	{
		//lettre
		size_t number_of_zero = 1;
		size_t turn_of_zero = 0; //boolean
		for (size_t i = 0 ; i < nb_out ; i++){
			if (!turn_of_zero){
				fprintf(file, rchar(1, 1));
				turn_of_zero = 1;
			}
			else{
				fprintf(file, rchar(0, number_of_zero));
				turn_of_zero = 0;
				number_of_zero++;
			}

		}
		fprintf(file, "\n");
	}
}

void create(){
	FILE *training = NULL;
	FILE *verif    = NULL;
	FILE *test     = NULL;
	training = fopen("../Creation/training", "w+");
	verif    = fopen("../Creation/verif", "w+");

	size_t nb_ins = 256;
	size_t nb_out = 94;
	makeset(training, 10, nb_out, nb_ins);
	makeset(verif, 3, nb_out, nb_ins);

/*
	fprintf(training, "%zu %zu %zu %zu\n", nb_ins, nb_col, nb_hne, nb_out);
	for (size_t i = nb_ins ; i < nb_tot ; i++)
	{
		fprintf(training, "%zu %lf %zu",
			network[i] -> len,
			network[i] -> bias,
			network[i] -> inputs);
		for (size_t j = 0 ; j < (network[i] -> len) ; j++)
			fprintf(training, " %lf", (network[i] -> weights)[j]);
		fprintf(training, "\n");
	}
	*/

	fclose(training);
	fclose(verif);
}

int main(void){
	create();
	return 1;
}