/*# include <stdio.h>
# include <stdlib.h>*/
# include "neuron.h"

struct s_network{
	size_t nb_ins;
	size_t nb_col;
	size_t nb_hne;
	size_t nb_out;
	size_t nb_tot;
	double *inputs; //simul 2 dimentions
	double *results;
	NEURON **network;
};

NEURON **init__network(size_t nb_ins, size_t nb_col, size_t nb_hne, size_t nb_out)//, double **weights, double *bias)
{
	size_t nb_tot = nb_ins + nb_col * nb_hne + nb_out;
	NEURON** network = malloc(sizeof(NEURON*) * nb_tot ); //nb of n.
	size_t count = 0;
	size_t lvl   = 0;

	//nb of inputs
	for (; count < nb_ins ; count++)
		network[count] = init_neuron(0, 0, NULL, NAN);//, NULL, 0);
	//first hidden layer
	for (; count < nb_ins + nb_hne ; count++)
		network[count] = init_neuron(nb_ins, 0, NULL, NAN);//, weights[count - nb_ins], bias[count - nb_ins]);
	//other hidden layers
	for (; count < nb_ins + nb_hne * nb_col ; count++){
		network[count] = init_neuron(nb_hne, nb_ins + lvl * nb_hne, NULL, NAN);//, weights[count - nb_ins], bias[count - nb_ins]);
		if (!( (count - 1) % nb_hne))
			lvl ++;
	}
	//output layer
	for (; count < nb_tot; count++)
		network[count] = init_neuron(nb_hne , nb_tot - nb_hne - nb_out, NULL, NAN);
	//, weights[count - nb_ins], bias[count - nb_ins]);
	return network;
}