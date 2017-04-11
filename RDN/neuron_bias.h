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
	double val;
	double *weights;
	double error;
	//struct neuron *next;    //pointer on next neuron in current layer
	//int type //1 = input layer ; 2 = hidden 3 = ouputs
};

struct neuron *init_neuron(size_t len , struct neuron *prec)
{
	struct neuron *neuron = malloc(sizeof(struct neuron));
	//neuron -> inputs = prec;
	if (len != 0)
	{
		neuron -> weights = malloc(len * sizeof(double));
		for (size_t i = 0 ; i < len ; i++)
			(neuron -> weights)[i] = rand_1_1();//rand_0_1();
	}
	//else weights = [];
	neuron -> len = len;
	return neuron;
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

double n_output(struct neuron *inputs_begin, double *weights_begin, size_t len)
{
	double retour = 0;
	for (int i = 0 ; i < len ; i++)
		retour += ((inputs_begin + i) -> val) * *(weights_begin + i);

	return sigmoid(retour);
}
struct neuron **init_inputs_layer()
{
	struct neuron **layer = malloc(2 * sizeof(struct neuron));
	for (size_t i = 0 ; i < 2 ; i++)
	{
		layer[i] = init_neuron(2, NULL);
	}
	return layer;
}

struct neuron **init__layers(struct neuron *prec)
{
	struct neuron **layer = malloc(3 * sizeof(struct neuron));
	for (size_t i = 0 ; i < 3 ; i++)
		*(layer + i) = init_neuron(3, prec);
	return layer;
}