# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <assert.h>


double rand_0_1()
{
	double i = (double)rand() / (double)RAND_MAX ;
	return i;
}
double rand_1_1()
{
	double i = (double)rand() / (double)RAND_MAX - (double)0.5;
	return i;
}

typedef struct neuron{
	size_t len;
	double val;
	double *weights;
	double error;
	double bias;
	size_t inputs;
} NEURON;

NEURON *init_neuron(size_t len, size_t inputs)//NEURON *inputs)
{
	NEURON *neuron = malloc(sizeof(NEURON));
	if (len != 0)
	{
		neuron -> weights = malloc(len * sizeof(double));
		for (size_t i = 0 ; i < len ; i++)
			(neuron -> weights)[i] = rand_1_1();//rand_0_1();
	}
	neuron -> bias   = rand_1_1();
	neuron -> len    = len;
	neuron -> inputs = inputs;
	neuron -> val    = 0;
	return neuron;
}

double sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}

double derivative(double x)
{
	return x * (1 - x);
}

double n_output(NEURON *neuron, NEURON **network)//, NEURON *inputs)
{
	double len      = neuron -> len;
	double *weights = neuron -> weights;
	size_t inputs   = neuron -> inputs;

	double retour   = neuron -> bias;
	for (size_t i = 0 ; i < len ; i++)
		retour += ((network[inputs + i]) -> val) * weights[i];
	return sigmoid(retour);
}


NEURON **init__network(size_t nb_ins, size_t nb_col, size_t nb_hne, size_t nb_out)//size_t size)
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