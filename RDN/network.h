# include "neuron.h"

double sigmoid(double x)
{
	return 1.0 / (1.0 + exp(-x));
}

typedef struct s_network{
	size_t nb_ins;
	size_t nb_col;
	size_t nb_hne;
	size_t nb_out;
	size_t nb_tot;
	//double *inputs; 
	//double *results;
	NEURON **network; //simul 2 dimentions
}s_network;

NEURON **init__network(size_t nb_ins, size_t nb_col, size_t nb_hne, size_t nb_out)
{
	size_t nb_tot = nb_ins + nb_col * nb_hne + nb_out;
	NEURON** network = malloc(sizeof(NEURON*) * nb_tot ); //nb of n.
	size_t count = 0;

	// init_neuron: prev, prev_len, next, next_len, *weights, bias
	//**nb of inputs**
	for (; count < nb_ins ; count++)
		network[count] = init_neuron(0, 0,
									 nb_ins, nb_hne,
									 NULL, NAN);
	//**first hidden layer**
	size_t next_len = (nb_col<2) ? nb_out : nb_hne;
	for (; count < nb_ins + nb_hne ; count++){
		network[count] = init_neuron(0, nb_ins,
									 nb_ins+nb_hne, next_len,
									 NULL, NAN);
	}
	//**other hidden layers**
	size_t lvl = 2;
	next_len = (nb_col<3) ? nb_out : nb_hne;
	for (; count < nb_ins + nb_hne * nb_col ; count++)
{
		//printf("ping %zu", count);
		network[count] = init_neuron(nb_ins + (lvl-1)*nb_hne, nb_hne,
		                             nb_ins + (lvl+1)*nb_hne, next_len,
 									 NULL, NAN);
		if (((count - nb_ins + 1) % nb_hne) == 0){
			lvl ++;
			next_len = (nb_ins + lvl*nb_hne + nb_out != nb_tot) ? nb_out : nb_hne;
		}
	}
	//**output layer**
	size_t prev_len = nb_col? nb_hne:nb_ins;
	for (; count < nb_tot; count++)
		network[count] = init_neuron(nb_tot - nb_out - prev_len, prev_len,
									 0, 0,
									 NULL, NAN);
	return network;
}

double n_output(NEURON **network, size_t neuron_position)
{
	NEURON *neuron  = network[neuron_position];
	
	size_t prev_len = neuron->prev_len;
	double *weights = neuron->weights;
	size_t prev     = neuron->prev;

	double retour   = neuron -> bias;
	for (size_t i = 0 ; i < prev_len ; i++)
		retour += ( (network[prev + i])->val ) * weights[i];
	return sigmoid(retour);
}

void eval(s_network *c, int prev[])
{
	size_t j = 0;
	//propagation of values
	for (; j < c->nb_ins ; j++)
		c->network[j]->val = prev[j];

	for (; j < c->nb_tot ; j++)
		c->network[j]->val = n_output(c->network, j);
}

size_t find(s_network *c)
{
	size_t retour = c->nb_ins + c->nb_col * c->nb_hne;
	double max    = c->network[retour]->val;
	for (size_t i = retour + 1; i < c->nb_tot; i++)
	{
		if ((c->network[i]->val) > max)
		{
			max = c->network[i]->val;
			retour = i;
		}
	}
	return retour + c->nb_out - c->nb_tot;
}

void free_network(s_network *container)
{
	for(size_t count = 0; count < container->nb_tot; count++)
	{	
		free_neuron_content(container->network[count]);
		free(container->network[count]);
	}
	free(container->network);
	free(container);
}

/*
void free_structure_content(s_network *container)
{
	free_network_content(container);
}


size_t find()
{
	size_t retour = nb_ins + nb_col * nb_hne;
	double max    = network[retour] -> val;
	for (size_t i = retour + 1; i < nb_tot; i++) {
		if ((network[i]->val) > max) {
			max = network[i]->val;
			retour = i;
		}
	}
	return retour + nb_out - nb_tot;
}
*/

/*
NEURON **init__network()
{ 
	size_t nb_tot = nb_ins + nb_col * nb_hne + nb_out;
	
	NEURON** network = malloc(sizeof(NEURON*) * nb_tot ); //nb of n.
	size_t count = 0;
	size_t lvl   = 0;

	//nb of inputs
	for (; count < nb_ins ; count++)     
		network[count] = init_neuron(0, 0);
	//first hidden layer
	for (; count < nb_ins + nb_hne ; count++) 
		network[count] = init_neuron(nb_ins, 0);
	//other hidden layers
	for (; count < nb_ins + nb_hne * nb_col ; count++){ 
		network[count] = init_neuron(nb_hne, nb_ins + lvl * nb_hne);
		if (!( (count - 1) % nb_hne))
			lvl ++;
	}
	//output layer
	for (; count < nb_tot; count++)    
		network[count] = init_neuron(nb_hne , nb_tot - nb_hne - nb_out);

	return network;
}
*/
