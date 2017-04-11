# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>


double rand_0_1()
{
	double i = (double)rand() / (double)RAND_MAX ;
	printf("test : %lf\n", i);
	return i;
}
double rand_1_1()
{
	double i = (double)rand() / (double)RAND_MAX - (double)0.5;
	printf("rand : %lf\n", i);
	return i;
}

struct neuron {
	size_t len;
	size_t inputs;
	double val;
	double *weights;
	double error;
};
typedef struct neuron neuron;

struct neuron *init_neuron(size_t len, size_t inputs)//, struct neuron *prec)
{
	struct neuron *neuron = malloc(sizeof(neuron));
	if (len != 0)
	{
		neuron -> weights = malloc(len * sizeof(double));
		for (size_t i = 0 ; i < len ; i++)
			(neuron -> weights)[i] = rand_1_1();//rand_0_1();
	}
	neuron -> len    = len;
	neuron -> inputs = inputs;
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

double n_output(struct neuron *inputs_begin, double *weights_begin, size_t len)
{
	double retour = 0;
	for (size_t i = 0 ; i < len ; i++)
		retour += ((inputs_begin + i) -> val) * *(weights_begin + i);

	return sigmoid(retour);
}


struct neuron **init__network()//size_t size)
{
	struct neuron** network = malloc(sizeof(struct neuron) * 6); //6 = nb of n.    9 = list of elem of weigths     sizeof(double) * 9 
	size_t count = 0;
	size_t lvl   = 0;

	for (; count < 2 ; count++)     //nb of inputs
		network[count] = init_neuron(0, 0);

	for (; count < 2 + 3 ; count++) //first hidden layer
		network[count] = init_neuron(2, 0);

	for (; count < 2 + 3 * 1; count++){ //other hidden layers
		network[count] = init_neuron(3, 2 + lvl * 3);
		if (!( (count - 1) % 3))
			lvl ++;
	}
	for (; count < 6 ; count++)     //output layer
		network[count] = init_neuron(3 , 5 - 0 - 3);
	return network;
}

/*
void kill_neuron(struct neuron *neuron)
{
	free(neuron -> inputs);
	free(neuron -> weights);
	free(neuron);
}
*/