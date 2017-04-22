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
	double *weights;
	double *inputs;
	double bias;
	double error;
};

struct neuron* init_neuron(size_t len)
{
	struct neuron *neuron = malloc(sizeof(struct neuron));
	neuron -> inputs      = malloc(len * sizeof(double));
	neuron -> weights     = malloc(len * sizeof(double));
	for (size_t i = 0 ; i < len ; i++)
		*(neuron -> weights + i) = rand_1_1();//rand_0_1();
	neuron -> bias               = rand_1_1();//rand_0_1();
	neuron -> len = len;
}

void kill_neuron(struct neuron *neuron)
{
	free(neuron -> inputs);
	free(neuron -> weights);
	free(neuron);
}

double sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}

double derivative(double x)
{
	return x * (1 - x);
}

/*
double n_output(double *inputs_begin, double *weights_begin, double bias, size_t len)
{
	double retour = bias;
	for (int i = 0 ; i < len ; i++)
		retour += *(inputs_begin + i) * *(weights_begin + i);

	return sigmoid(retour);
}
*/

double n_output(struct neuron *neuron)
{
	double len      = neuron -> len;
	double bias     = neuron -> bias;
	double *weights = neuron -> weights;
	double *inputs  = neuron -> inputs;

	double retour = bias;
	for (size_t i = 0 ; i < len ; i++)
		retour += *(inputs + i) * *(weights + i);

	return sigmoid(retour);
}