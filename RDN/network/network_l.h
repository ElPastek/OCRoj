#pragma once

#include "neuron_l.h"
#include "layer.h"

typedef struct s_network
{
	size_t nb_layer;
	LAYER **layers;
	size_t nb_ins;
	size_t nb_col;
	size_t nb_hne;
	size_t nb_out;
	size_t nb_tot;
} NETWORK;

NETWORK *init_network(size_t nb_ins, size_t nb_col, size_t nb_hne, size_t nb_out)
{
	NETWORK *network = (NETWORK*)malloc(sizeof(NETWORK));
	network->nb_layer = nb_col + 2;
	network->nb_ins = nb_ins;
	network->nb_col = nb_col;
	network->nb_hne = nb_hne;
	network->nb_out = nb_out;
	network->nb_tot = nb_ins + nb_col * nb_hne + nb_out;

	size_t layer_count = 0;

	LAYER *prev_layer;
	//**nb of inputs**

	// init_layer: neurons, nb_neuron, prev, next
	// init_neuron: weights_len, *weights, bias
	prev_layer = init_layer(NULL, nb_ins, NULL, NULL);
	for (size_t ins = 0; ins < nb_ins ; ++nb_ins)
		prev_layer->neurons[ins] = (NEURON*)init_neuron(0, NULL, NAN);
	network->layers[layer_count++] = prev_layer;

	for (size_t col = 0; col < nb_col; ++col)
	{
		LAYER *tmp = init_layer(NULL, nb_hne, prev_layer, NULL);
		prev_layer->next = tmp;
		prev_layer = tmp;

		for (size_t hne = 0; hne < nb_hne ; ++hne)
			prev_layer->neurons[hne] = (NEURON*)init_neuron(0, NULL, NAN);
		network->layers[layer_count++] = prev_layer;
	}

	LAYER *tmp = init_layer(NULL, nb_out, prev_layer, NULL);
	prev_layer->next = tmp;
	prev_layer = tmp;

	for (size_t ins = 0; ins < nb_ins ; ++nb_ins)
		prev_layer->neurons[ins] = (NEURON*)init_neuron(0, NULL, NAN);
	network->layers[layer_count++] = prev_layer;

	return network;
}


void eval(NETWORK *c, int inputs[])
{
	//propagation of values
	for (size_t j = 0; j < c->nb_ins ; ++j)
		c->layers[j]->neurons[j]->val = inputs[j];

	for (size_t layer_count = 1; layer_count < c->nb_layer ; ++layer_count)
	{
		LAYER *layer = c->layers[layer_count];
		for (size_t j = 0; j < layer->nb_neuron; ++j)
			layer->neurons[j]->val = n_output(layer, j);
	}
}

int find(NETWORK *c)
{
	LAYER *out_layer = c->layers[c->nb_layer - 1];
	size_t retour = 0;

	for (size_t i = 1; i < out_layer->nb_neuron; ++i)
		if (out_layer->neurons[i]->val > out_layer->neurons[retour]->val)
			retour = i;
	return retour;
}

void free_network(NETWORK *c)
{
	for(size_t nb_l = 0; nb_l < c->nb_layer; ++nb_l)
		free_layer(c->layers[nb_l]);
	free(c->layers);
	free(c);
}