#pragma once

#include "neuron_l.h"
#include "layer.h"

typedef struct s_network
{
	size_t nb_layer;
	LAYER **layers;
	size_t nb_ins;
	size_t nb_hid;
	size_t nb_hne;
	size_t nb_out;
	size_t nb_tot;
} NETWORK;

// Acces layers using:
// get_input_layer
// get_output_layer
// get_hidden_layers
// get_hidden_layer_number


LAYER *get_input_layer(NETWORK *c)
{
	return c->layers[0];
}

LAYER *get_output_layer(NETWORK *c)
{
	return c->layers[c->nb_layer - 1];
}

LAYER **get_hidden_layers(NETWORK *c)
{
	return c->layers + 1;
}

// let number of intern layer N
// 0 <= n < N
LAYER *get_hidden_layer_number(NETWORK *c, size_t n)
{
	return c->layers[1 + n];
}

NETWORK *init_network(size_t nb_ins, size_t nb_hid, size_t nb_hne, size_t nb_out)
{
	NETWORK *network = (NETWORK*) malloc(sizeof(NETWORK));
	network->nb_layer = nb_hid + 2;
	network->nb_ins = nb_ins;
	network->nb_hid = nb_hid;
	network->nb_hne = nb_hne;
	network->nb_out = nb_out;
	network->nb_tot = nb_ins + nb_hid * nb_hne + nb_out;

	size_t layer_count = 0;

	LAYER *prev_layer;
	//**nb of inputs**

	// init_layer: neurons, nb_neuron, prev, next
	// init_neuron: weights_len, *weights, bias
	prev_layer = init_layer(NULL, nb_ins, NULL, NULL);
	for (size_t ins = 0; ins < nb_ins ; ++nb_ins)
		prev_layer->neurons[ins] = init_neuron(0, NULL, NAN);
	network->layers[layer_count++] = prev_layer;

	for (size_t col = 0; col < nb_hid; ++col)
	{
		LAYER *tmp = init_layer(NULL, nb_hne, prev_layer, NULL);
		prev_layer->next = tmp;
		prev_layer = tmp;

		for (size_t hne = 0; hne < nb_hne ; ++hne)
			prev_layer->neurons[hne] = init_neuron(0, NULL, NAN);
		network->layers[layer_count++] = prev_layer;
	}

	LAYER *tmp = init_layer(NULL, nb_out, prev_layer, NULL);
	prev_layer->next = tmp;
	prev_layer = tmp;

	for (size_t ins = 0; ins < nb_ins ; ++nb_ins)
		prev_layer->neurons[ins] = init_neuron(0, NULL, NAN);
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

void compute_errors(NETWORK *c, size_t expected)
{
	compute_errors_output(get_output_layer(c), expected);

	LAYER **hiddens = get_hidden_layers(c);
	// for each hidden layers
	for (size_t i = 0; i < c->nb_hid; ++i)
		compute_errors_hidden(hiddens[i]);
}

void update_weights(NETWORK *c)
{
	LAYER **layers = c->layers;
	// iterate over all non input layers
	for (size_t j = 1; j < c->nb_layer ; ++j)
		update_layer_weights(layers[j]);
}

int find(NETWORK *c)
{
	LAYER *out_layer = get_output_layer(c);
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