#pragma once

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
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

double NormalDistribution(double mu, double sigma)
{
	return (mu + sigma * RANDN);
}

typedef struct neuron
{
	double val;
	double error;
	double bias;
	// Backward link
	// null if first layer
	size_t weight_len;
	double *weights;
} NEURON;


void*init_neuron(size_t prev_len, double *weights, double bias)
{
	NEURON *neuron = (NEURON*)malloc(sizeof(NEURON));
	// Not first layer ?
	if (prev_len != 0 && weights == NULL)
	{
		weights = (double*)malloc(prev_len * sizeof(double));
		for (size_t i = 0 ; i < prev_len ; i++)
			(neuron -> weights)[i] = NormalDistribution(0, 1 / sqrt(prev_len));
	}
	neuron->weights = weights;
	neuron->weight_len = prev_len;

	if (isnan(bias))
		bias = rand_1_1();
	neuron->bias = bias;

	neuron->val = 0;
	return neuron;
}

/*
 * modes:
 *	bin
 *	94c
 */

enum RDN_TYPE_ANALYSIS
{
	C94,
	BIN,
};

char trans(size_t input, char *mode)
{
	if (!strcmp(mode, "94c")) //from 0  to 93
		return input + 33; //from 33 to 126 (doesnt need to deal with spaces)
	if (!strcmp(mode, "bin"))
		return input + 48; //0 or 1
	printf("wrong mode\n");
	return input;
}

void free_neuron(NEURON *neuron)
{
	free(neuron->weights);
	free(neuron);
}