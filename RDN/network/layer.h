#pragma once

#include "neuron_l.h"
#include <stdlib.h>

double derivative(double x)
{
	return x * (1.0 - x);
}

double sigmoid(double x)
{
	return 1.0 / (1.0 + exp(-x));
}

typedef struct layer
{
	// prev == null -> first layer
	LAYER *prev;
	// next == null -> last layer
	LAYER *next;
	size_t nb_neuron;
	NEURON **neurons;
} LAYER;

LAYER *init_layer(NEURON **neurons, size_t nb_neuron, LAYER *prev, LAYER *next)
{
	LAYER *l = (LAYER*)malloc(sizeof(LAYER));
	if (!neurons)
		neurons = (NEURON**)malloc(sizeof(NEURON*) * nb_neuron);
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

void free_layer(LAYER *l)
{
	for (size_t n = 0; n < l->nb_neuron; ++n)
		free_neuron(l->neurons[n]);
	free(l->neurons);
	free(l);
}