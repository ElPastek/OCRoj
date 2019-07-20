# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "network.h"


s_network *load_RDN_from_path(char *path)
{
    FILE* file = NULL;
    file = fopen(path, "r");


    size_t nb_ins; size_t nb_col; size_t nb_hne; size_t nb_out;
    assert(fscanf(file, "%zu,%zu,%zu,%zu", &nb_ins, &nb_col, &nb_hne, &nb_out));
    size_t nb_tot = nb_ins + nb_col * nb_hne + nb_out;

	printf(" nb_ins: %zu\n  nb_col: %zu\n  nb_hne: %zu\n  nb_out: %zu\n  nbtot: %zu\n",
			nb_ins, nb_col, nb_hne, nb_out, nb_tot);

    NEURON **network = malloc(sizeof(NEURON*) * nb_tot );

    s_network *container = malloc(sizeof(s_network));
    container->nb_ins = nb_ins;
    container->nb_col = nb_col;
    container->nb_hne = nb_hne;
    container->nb_out = nb_out;
    container->nb_tot = nb_tot;
    container->network = network;

	// init_neuron: prev, prev_len, next, next_len, *weights, bias
    for (size_t i = 0 ; i < nb_ins ; i++)
        network[i] = init_neuron(0, 0, 0, 0, NULL, NAN); //next and next_len are not 0 but not important ??
    for (size_t i = nb_ins ; i < nb_tot; i++) {
        size_t prev;
        size_t prev_len;
		size_t next;
		size_t next_len;
        double bias;
        assert(fscanf(file, "%zu %zu %zu %zu %lf",
		       &prev, &prev_len, &next, &next_len, &bias));
        double *weights = malloc(sizeof(double) * prev_len);
        for (size_t j = 0 ; j < prev_len ; j++) {
            fseek(file, +1, SEEK_CUR);
            assert(fscanf(file, "%lf", &weights[j]));
        }
        //printf("\n");
        network[i] = init_neuron(prev, prev_len, next, next_len, weights, bias);
    }
    fclose(file);
    return container;
}


void read_RDN(s_network *c, char *mode)
{
    FILE* fichier_O = NULL;
    FILE* fichier_I = NULL;
    fichier_O = fopen("./outputs_RDN.txt", "w+");
    fichier_I = fopen("./inputs_RDN.txt" , "r");
    rewind(fichier_I);
    rewind(fichier_O);
    size_t nb_scan;
    char charac;
    int inputs[c->nb_ins];
    assert(fscanf(fichier_I, "%zu", &nb_scan));

    for (size_t scan = 0 ; scan < nb_scan ; scan++)
    {
        fseek(fichier_I, +1, SEEK_CUR);
        for (size_t j = 0 ; j < c->nb_ins ; j++)
        {
            inputs[j] = fgetc(fichier_I) - 48;
        }
        eval(c, inputs);
        size_t found = find(c);
        charac = trans(found, mode);
        fputc(charac, fichier_O);
    }
    fclose(fichier_I);
    fclose(fichier_O);
}




/*
void load_RDN_from_path(char *path);

void read_RDN(char *mode);
*/