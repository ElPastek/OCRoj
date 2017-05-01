#include "lecture.h"
#include "neuron_2.h"
#define TAILLE_MAX 1000

size_t nb_ins;
size_t nb_col;
size_t nb_hne;
size_t nb_out;
size_t nb_tot;
char *path_read	;
double bias;
double *weights;
NEURON **network;

void create(char *path)
{
	FILE* fichier = NULL;
	fichier = fopen(path, "r");
	fscanf(fichier, "%zu,%zu,%zu,%zu", &nb_ins, &nb_col, &nb_hne, &nb_out);
	nb_tot = nb_ins + nb_col * nb_hne + nb_out;
	network = malloc(sizeof(NEURON*) * nb_tot );
	for (size_t i = 0 ; i < nb_ins ; i++)
		network[i] = init_neuron(0, 0, NULL, NAN);
	size_t len;
	double bias;
	size_t inputs;
	double *weights;
	for (size_t i = 1 ; i < nb_col * nb_hne + nb_out + 1; i++) {
		fscanf(fichier, "%zu,%lf,%zu", &len, &bias, &inputs);
		weights = malloc(sizeof(double) * len);
		for (size_t j = 0 ; j < len ; j++) {
			fseek(fichier, +1, SEEK_CUR);
			fscanf(fichier, "%lf", &weights[j]);
		}
		
		network[nb_ins + i - 1] = init_neuron(len, inputs, weights, bias);
	}
	fclose(fichier);
}	
/*
void save()
{
	FILE* fichier = NULL;

	fichier = fopen("saved_RDN_LBIW_test.txt", "w");
	fprintf(fichier, "%zu,%zu,%zu,%zu\n", nb_ins, nb_col, nb_hne, nb_out);
	for (size_t i = nb_ins ; i < nb_tot ; i++)
	{
		fprintf(fichier, "%zu,%lf,%zu", 
			network[i] -> len, 
			network[i] -> bias, 
			network[i] -> inputs);
		for (size_t j = 0 ; j < (network[i] -> len) ; j++)
			fprintf(fichier, ",%lf", (network[i] -> weights)[j]);
		fprintf(fichier, "\n");
	}
	fclose(fichier);
}*/

void eval(double inputs[])
{
	size_t j = 0;
	//propagation of values
	for (; j < nb_ins ; j++)
		network[j] -> val = inputs[j];

	for (; j < nb_tot ; j++)
		network[j] -> val = n_output(network[j], network);
}

size_t find()
{
	size_t retour = nb_ins + nb_col * nb_hne;
	double max    = network[nb_ins + nb_col * nb_hne] -> val;
	for (size_t i = nb_ins + nb_col * nb_hne + 1; i < nb_tot; i++) {
		if ((network[i] -> val) > max) {
			max = network[i] -> val;
			retour = i;
		}
	}
	return retour + nb_out - nb_tot;
}

void read(size_t mode)
{
	FILE* fichier_O = NULL;
	FILE* fichier_I = NULL;
	fichier_O = fopen("outputs_RDN.txt", "w+");
	fichier_I = fopen("inputs_RDN.txt" , "r");
	rewind(fichier_I);
	rewind(fichier_O);
	size_t nb_scan;
	char charac;
	double inputs[nb_ins];
	fscanf(fichier_I, "%zu", &nb_scan);
	printf("nb_scan : %zu\n", nb_scan);
	for (size_t i = 0 ; i < nb_scan ; i++)
	{
		for (size_t j = 0 ; j < nb_ins ; j++)
		{
			fseek(fichier_I, +1, SEEK_CUR);
			fscanf(fichier_I, "%lf", &inputs[j]);
		}
		printf("inputs : %lf, %lf\n", inputs[0], inputs[1]);
		eval(inputs);
		size_t found = find();
		printf("%zu\n", found);
		charac = trans(found);
		fputc(charac, fichier_O);
	}
	fclose(fichier_I);
	fclose(fichier_O);
}


int main(int argc, char *argv[])
{
	//char *path_RDN[] = "saved_RDN.txt";
	size_t mode = argv [argc - 1];
	create("saved_RDN_LBIW.txt");
	read(mode);
	//save();
	/*double inputs[2] = {0 ,1};
	eval(inputs);
	size_t pos = find(network);
	printf("%lf\n", network[pos] -> val);*/
	return 0;
}