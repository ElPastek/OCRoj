#include "lecture.h"
#include "neuron_2.h"

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
	for (int i = 0 ; i < nb_ins ; i++)
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

void read(double inputs[])
{
	size_t j = 0;
	//propagation of values
	for (; j < nb_ins ; j++)
		network[j] -> val = inputs[j];

	for (; j < nb_tot ; j++)
		network[j] -> val = n_output(network[j], network);
}

void find()
{

}


int main(int argc, char *argv[])
{
	//char *path_RDN[] = "saved_RDN.txt";
	create("saved_RDN_LBIW.txt");
	save();

	return 0;
}
