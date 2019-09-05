#pragma once

#include "neuron_l.h"
#include <stdlib.h>

#define ALPHA_LEARNING_RATE 0.05

double sigmoid(double x)
{
	return 1.0 / (1.0 + exp(-x));
}
double derivative_old(double x)
{
	return x * (1.0 - x);
}

double derivative(double x)
{
	return sigmoid(x) * (1 - sigmoid(x));
}

typedef struct layer
{
	// prev == null -> first layer
	struct layer *prev;
	// next == null -> last layer
	struct layer *next;
	size_t nb_neuron;
	NEURON **neurons;
} LAYER;

LAYER *init_layer(NEURON **neurons, size_t nb_neuron, LAYER *prev, LAYER *next)
{
	LAYER *l = (LAYER*) malloc(sizeof(LAYER));
	if (!neurons)
		neurons = (NEURON**) malloc(sizeof(NEURON*) * nb_neuron);
	l->neurons = neurons;
	l->nb_neuron = nb_neuron;
	l->prev = prev;
	l->next = next;
	return l;
}

double n_output(LAYER *layer, size_t neuron_position)
{
	NEURON *neuron  = layer->neurons[neuron_position];
	double *weights = neuron->weights;
	double retour   = neuron->bias;

	LAYER *prev_lay = layer->prev;
	size_t prev_len = prev_lay->nb_neuron;
	NEURON **prev   = prev_lay->neurons;

	for (size_t i = 0 ; i < prev_len ; ++i)
		retour += prev[i]->val * weights[i];
	return sigmoid(retour);
}

void compute_errors_output(LAYER *output, size_t expected)
{
	for (size_t j = 0; j < output->nb_neuron; ++j)
	{
		NEURON* cur = output->neurons[j];
		double is_stimul = j == expected;
		double error = is_stimul - cur->val;

		cur->error = error;
		cur->bias += error;
	}
}

void compute_errors_hidden(LAYER *curr_layer)
{
	// for each neuron in this layer
	for (size_t j = 0; j < curr_layer->nb_neuron; ++j)
	{
		double error = 0;
		NEURON *cur_neuron = curr_layer->neurons[j];
		LAYER *next_layer = curr_layer->next;
		// calculate error using next layer weights
		for (size_t n = 0; n < next_layer->nb_neuron; ++n)
		{
			NEURON *next_neuron = next_layer->neurons[n];
			error += (next_neuron->error * next_neuron->weights[j]);
		}
		error *= derivative(cur_neuron->val);

		cur_neuron->error = error;
		cur_neuron->bias += error;
	}
}

void update_layer_weights(LAYER *curr)
{
	LAYER *prev_layer = curr->prev;

	for (size_t i = 0; i < curr->nb_neuron; ++i)
	{
		NEURON *curr_neuron = curr->neurons[i];
		for (size_t j = 0; j < prev_layer->nb_neuron; ++j)
		{
			curr_neuron->weights[j] += ALPHA_LEARNING_RATE
				* curr_neuron->error
				* prev_layer->neurons[j]->val;
		}
	}
}

void free_layer(LAYER *l)
{
	for (size_t n = 0; n < l->nb_neuron; ++n)
		free_neuron(l->neurons[n]);
	free(l->neurons);
	free(l);
}

int is_input_layer(LAYER *l)
{
	return l->prev == NULL;
}

int is_output_layer(LAYER *l)
{
	return l->next == NULL;
}
