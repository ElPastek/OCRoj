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
	if (len != 0) {
		if (weights == NULL) {
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

/*
 * mode 0 = xor
 * mode 1 = OCR
 */
char trans(size_t input, size_t mode)
{
	if (mode)            //from 0  to 94
		return input + 32; //from 32 to 126
	else
		return input + 48; //0 or 1
}
