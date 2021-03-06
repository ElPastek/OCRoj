# include "RDN_main_l.h"
// NOTE: _l = layer = new version WIP

#define MAX_EPOCH 5

void train(NETWORK *c, size_t nb_training_set, int ***inputs)
{
	//double r_results[nb_out];

	int epoch = 0;
	size_t one_wrong = 0;

	do
	{
		one_wrong = 0;
		for (size_t training_set = 0; training_set < nb_training_set; training_set++)
		{
			for (size_t out = 0 ; out < c->nb_out ; out++)
			{
				//**propagation of values**
				eval(c, inputs[training_set][out]);

				//**propagation of errors**
				compute_errors(c, out);

				//**update of weight**
				update_weights(c);

				//**verification**
				char waited = (char)(out) + 33;
				char real   = (char)(find(c)) + 33;
				printf("out: %zu scan: %zu ", out, out + (training_set * c->nb_out));
				printf(" %c -> %c   e : %d\n", waited, real, epoch);

				one_wrong = one_wrong || (waited != real);
				if (waited != real)
					printf("ERROR HERE %d -> %d\n", waited, real);
				//network[nb_tot - 1] -> val);
				//r_results[out] = //network[found_o] -> val;//network[nb_tot - 1] -> val;
				//	c->network[out + nb_ins + nb_hne * nb_col]->val;

			}
			printf("epoch : %d\n", epoch);
			epoch++;
		}
	} while (one_wrong && epoch < MAX_EPOCH	); //) );     //!(verif(r_results, nb_out))

	/*
	if (epoch == 1000000)
	{
		for (size_t o = 0; o < 10 ; o++)
		printf("ERRR \n \n \n \n \n \n \n \n");
		network = init__network(nb_ins, nb_col, nb_hne, nb_out);
		train();
	}*/
}


void save(NETWORK *c)
{
	FILE* f = fopen("../saved_RDN_LBIW.txt", "w+");
	rewind(f);

	fprintf(f, "%zu,%zu,%zu,%.zu\n",
		c->nb_ins, c->nb_hid, c->nb_hne, c->nb_out);

	for (size_t layer_count = 1; layer_count < c->nb_layer; ++layer_count)
	{
		LAYER *layer = c->layers[layer_count];
		fprintf(f, "%zu\n", layer->nb_neuron);
		for (size_t n_count = 0; n_count < layer->nb_neuron; ++n_count)
		{
			NEURON *neuron = layer->neurons[n_count];
			fprintf(f, "%lf %zu",
				neuron->bias,
				neuron->weight_len);
			for (size_t w = 0 ; w < neuron->weight_len; ++w)
				fprintf(f, " %lf", neuron->weights[w]);
		fprintf(f, "\n");
		}
	}
	fclose(f);
}

size_t prepare_training(FILE* file)
{
	size_t nb_training_set;

	fscanf(file, "%zu", &nb_training_set);

	printf("NB_TRAINING: %zu\n", nb_training_set);
	return nb_training_set;
}

int ***open_training(FILE* file, NETWORK *c, size_t nb_training_set)
{
	int ***inputs = malloc(nb_training_set * sizeof(int **));
	//[nb_training_set][c->nb_out][c->nb_ins]  //* (c->nb_out) * (c->nb_ins)

	for (size_t set = 0 ; set < nb_training_set ; set++) //* nb_out
	{
		inputs[set] = malloc(c->nb_out * sizeof(int **));
		for (size_t out = 0 ; out < c->nb_out ; out++)
		{
			fseek(file, +2, SEEK_CUR); // line feed + carriage return
			inputs[set][out] = malloc(c->nb_ins * sizeof(int *));
			for (size_t ins = 0 ; ins < c->nb_ins ; ins++)
			{
				inputs[set][out][ins] = fgetc(file) - '0';
				//printf("%d", inputs[set][out][ins]);
			}
			//printf("\nTraining set number: %zu", set);
			//printf(" out :%zu", out);
		}
	}
	return inputs;
}

// File is open and won't be closed here
NETWORK *config_RDN(FILE* file)
{
	size_t nb_out;
	size_t nb_ins;
	size_t nb_hne;
	size_t nb_col;
	printf("Retreiving network meta data\n");
	assert(fscanf(file, "%zu,%zu,%zu,%zu", &nb_ins, &nb_col, &nb_hne, &nb_out));
	size_t nb_tot = nb_ins + nb_col * nb_hne + nb_out;
	printf("%zu\n%zu\n%zu\n%zu\n%zu\n", nb_ins, nb_col, nb_hne, nb_out, nb_tot);
	printf("Init network...\n");
	NETWORK *c = init_network(nb_ins, nb_col, nb_hne, nb_out);
	printf("Init done\n");
	return c;
}

int main(void)
{
	FILE* file = fopen("training", "r");

	NETWORK *c = config_RDN(file);
	size_t nb_training_set = prepare_training(file);
	int ***inputs = open_training(file, c, nb_training_set);
	fclose(file);

	srand(time(NULL));

	printf("train\n");
	train(c, nb_training_set, inputs);
	printf("save\n");
	save(c);


	printf("frees\n");
	for (size_t set = 0; set < nb_training_set; ++set)
	{
		for (size_t out = 0; out < c->nb_out; ++out)
			free(inputs[set][out]);
		free(inputs[set]);
	}
	free(inputs);
	free_network(c);
	return 0;
}
