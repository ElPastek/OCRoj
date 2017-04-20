# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <assert.h>

#define RAND ((double) rand())/((double) RAND_MAX)
#define TWOPI 2.0*3.141592653589793238462643383279502884197169399375
#define RANDN sqrt(-2.0*log(RAND))*cos(TWOPI*RAND)

double rand_1_1()
{
	double i = (double)rand() / (double)RAND_MAX - (double)0.5;
	return i;
}
double NormalDistribution(double mu,double sigma)
{
	return (mu+sigma*RANDN);
}

typedef struct neuron{
	size_t len;
	double val;
	double *weights;
	double error;
	double bias;
	size_t inputs;
} NEURON;

double sigmoid(double x)
{
	return 1.0 / (1.0 + exp(-x));
}

double derivative(double x)
{
	return x * (1.0 - x);
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

NEURON *init_neuron(size_t len, size_t inputs, double *weights, double bias)
{
	NEURON *neuron = malloc(sizeof(NEURON));
	if (len != 0)
	{
		if (weights == NULL)
		{
			neuron -> weights = malloc(len * sizeof(double));
			for (size_t i = 0 ; i < len ; i++)
				(neuron -> weights)[i] = NormalDistribution(0, 1 / sqrt(len));
		}
		else
			neuron -> weights = weights;
	}
	else
		neuron -> weights = NULL;

	if (isnan(bias))
		neuron -> bias = rand_1_1();
	else
		neuron -> bias = bias;

	neuron -> len    = len;
	neuron -> inputs = inputs;
	neuron -> val    = 0;
	return neuron;
}

NEURON **init__network(size_t nb_ins, size_t nb_col, size_t nb_hne, size_t nb_out)//, double **weights, double *bias)
{
	size_t nb_tot = nb_ins + nb_col * nb_hne + nb_out;
	/*//test NULL
	if (weights == NULL && bias == NULL) {
		weights = malloc((nb_tot - nb_ins) * sizeof(double));
		bias    = malloc((nb_tot - nb_ins) * sizeof(double));
		for (size_t i = 0 ; i < nb_tot - nb_ins ; i++)
		{
			weights[i] = NULL;
			bias[i]    = NAN;
		}
	}*/
	
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
		network[count] = init_neuron(nb_hne , nb_tot - nb_hne - nb_out, NULL, NAN);//, weights[count - nb_ins], bias[count - nb_ins]);

	return network;
}