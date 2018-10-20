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

double NormalDistribution(double mu,double sigma)
{
	return (mu+sigma*RANDN);
}

typedef struct neuron{
	size_t prev;
	size_t prev_len;
	size_t next;
	size_t next_len;
	double val;
	double *weights;
	double error;
	double bias;
} NEURON;


double derivative(double x)
{
	return x * (1.0 - x);
}


NEURON *init_neuron(size_t prev, size_t prev_len, size_t next, size_t next_len, double *weights, double bias)
{
	NEURON *neuron = malloc(sizeof(NEURON));
	if (prev_len != 0) {
		if (weights == NULL) {
			neuron->weights = malloc(prev_len * sizeof(double));
			for (size_t i = 0 ; i < prev_len ; i++){
				(neuron -> weights)[i] = NormalDistribution(0, 1 / sqrt(prev_len));
				//printf("weights : %f\n", (neuron->weights)[i]);
			}
		}
		else
			neuron->weights = weights;
	}
	else //input neurons
		neuron->weights = NULL;

	if (isnan(bias))
	{
		neuron->bias = rand_1_1();
		//printf(" bias : %f\n", neuron->bias);
	}
	else
		neuron->bias = bias;

	neuron->prev = prev;
	neuron->next = next;
	neuron->prev_len = prev_len;
	neuron->next_len = next_len;
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

void free_neuron_content(NEURON *neuron)
{
	free(neuron->weights);
}


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
*/