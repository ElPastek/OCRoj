# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "network.h"

/*
NEURON *init_neuron(size_t len, size_t inputs, double *weights )
{
	NEURON *neuron = malloc(sizeof(NEURON));
	if (len != 0)
		neuron -> weights = weights;
	else
		neuron -> weights = NULL;
	neuron -> bias   = rand_1_1();
	neuron -> len    = len;
	neuron -> inputs = inputs;
	neuron -> val    = 0;
	return neuron;
}

NEURON **init__network()
{ 
	size_t nb_tot = nb_ins + nb_col * nb_hne + nb_out;
	
	NEURON** network = malloc(sizeof(NEURON*) * nb_tot ); //nb of n.
	size_t count = 0;
	size_t lvl   = 0;

	//nb of inputs
	for (; count < nb_ins ; count++)     
		network[count] = init_neuron(0, 0);
	//first hidden layer
	for (; count < nb_ins + nb_hne ; count++) 
		network[count] = init_neuron(nb_ins, 0);
	//other hidden layers
	for (; count < nb_ins + nb_hne * nb_col ; count++){ 
		network[count] = init_neuron(nb_hne, nb_ins + lvl * nb_hne);
		if (!( (count - 1) % nb_hne))
			lvl ++;
	}
	//output layer
	for (; count < nb_tot; count++)    
		network[count] = init_neuron(nb_hne , nb_tot - nb_hne - nb_out);

	return network;
}
*/

void create(char *path);

void read();

size_t find();//NEURON **network);