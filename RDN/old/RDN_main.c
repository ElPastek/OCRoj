# include "RDN_main.h"

#define MAX_EPOCH 5
//non-changing declare
static size_t nb_out;
static size_t nb_ins;
static size_t nb_hne;
static size_t nb_col;// = c->nb_col;
static size_t nb_tot;

void train(s_network *c, size_t nb_training_set, int ***inputs)
{
	//double r_results[nb_out];

	int epoch = 0;
	size_t one_wrong = 0;
	//size_t cc = 0;
	do
	{
		one_wrong = 0;
		for (size_t training_set = 0; training_set < nb_training_set; training_set++)
		{
			for (size_t out = 0 ; out < nb_out ; out++)
			{
				//**propagation of values**
				eval(c, inputs[training_set][out]);

				//**propagation of errors**
				size_t j = nb_tot;

				for (--j; j > (nb_tot - nb_out - 1); j--) //outputs
				{

					double is_stimul = (j + nb_out - nb_tot) == out;
					////derivative(network[j] -> val) *
					c->network[j]->error = is_stimul - (c->network[j]->val);
					c->network[j]->bias += c->network[j] -> error;
				}
				for (; j > (nb_ins - 1) ; j--) //hidden layers
				{
					double sum = 0;
					size_t next     = c->network[j]->next;
					size_t next_len = c->network[j]->next_len;
					size_t next_max = next + next_len;
					//size_t next = nb_tot - nb_out;
					//size_t next = ((j - nb_ins) / nb_hne + 1 ) * nb_hne + nb_ins;
					//size_t e = next + nb_hne	;

					for (; next < next_max; next++){
						sum += (c->network[next]->error) * (
							   (c->network[next]->weights)[(j - nb_ins) % nb_hne]);

					}
					c->network[j]->error = sum * derivative(c->network[j]->val);
					c->network[j]->bias += c->network[j]->error;
				}
				//**update of weight**
				for (j = nb_ins ; j < nb_tot ; j++)
				{
					NEURON *ne = c->network[j];
					size_t l = ne->prev_len;
					for (size_t k = 0 ; k < l ; k++)
					{
						((ne->weights)[k]) += 0.05 *
						( ne->error) *
						( c->network[(ne->prev)+k]->val);
					}
				}

				//**verification**
				char waited = (char)(out) +33;
				char real   = (char)(find(c)) + 33;
				printf("out: %zu scan: %zu ", out, out + (training_set * nb_out));
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


void save(s_network *container)
{
	FILE* fichier = NULL;
	fichier = fopen("../saved_RDN_LBIW.txt", "w+");
	rewind(fichier);

	fprintf(fichier, "%zu,%zu,%zu,%.zu\n", container->nb_ins,
										  container->nb_col,
										  container->nb_hne,
										  container->nb_out);
	for (size_t i = container->nb_ins ; i < container->nb_tot ; i++)
	{
		fprintf(fichier, "%zu %zu %zu %zu %lf",
			container->network[i]->prev,
			container->network[i]->prev_len,
			container->network[i]->next,
			container->network[i]->next_len,
			container->network[i]->bias);
		for (size_t j = 0 ; j < (container->network[i]->prev_len) ; j++)
			fprintf(fichier, " %lf", (container->network[i]->weights)[j]);
		fprintf(fichier, "\n");
	}
	fclose(fichier);
}

size_t prepare_training(FILE* file)
{
	size_t nb_training_set;

	assert(fscanf(file, "%zu", &nb_training_set));

	printf("NB_TRAINING: %zu\n", nb_training_set);
	return nb_training_set;
}

int ***open_training(FILE* file, s_network *c, size_t nb_training_set)
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

s_network *config_RDN(FILE* file)
{
	//size_t nb_ins = 0; size_t nb_col = 0; size_t nb_hne = 0; size_t nb_out = 0;
	assert(fscanf(file, "%zu,%zu,%zu,%zu", &nb_ins, &nb_col, &nb_hne, &nb_out));
	nb_tot = nb_ins + nb_col * nb_hne + nb_out;
	printf("%zu\n%zu\n%zu\n%zu\n%zu\n", nb_ins, nb_col, nb_hne, nb_out, nb_tot);

	NEURON **network = init__network(nb_ins, nb_col, nb_hne, nb_out);

	s_network *container = malloc(sizeof(s_network));
	container->nb_ins = nb_ins;
	container->nb_col = nb_col;
	container->nb_hne = nb_hne;
	container->nb_out = nb_out;
	container->nb_tot = nb_tot;
	container->network = network;

	return container;
}

int main(void)
{
	FILE* file = NULL;
	file = fopen("training", "r");

	s_network *container   = config_RDN(file);
	size_t nb_training_set = prepare_training(file);
	int ***inputs = open_training(file, container, nb_training_set);
	fclose(file);

	srand(time(NULL));

	printf("train\n");
	train(container, nb_training_set, inputs);
	printf("save\n");
	save(container);


	printf("frees\n");
	for (size_t set = 0; set < nb_training_set; ++set)
	{
		for (size_t out = 0; out < nb_out; ++out)
			free(inputs[set][out]);
		free(inputs[set]);
	}
	free(inputs);
	free_network(container);
	//free(container->network);
	//free(container);
	return 0;
}



/*
size_t nb_ins;
size_t nb_col;
size_t nb_hne;
size_t nb_out;
size_t nb_tot;
NEURON **network;

double *inputs;
size_t nb_training_set;
*/


/*
arg 1 : nb inputs
arg 2 & 3 : nb columns and nb neurons in hidden layer
arg 4 : nb outputs
*/
/*
for (int i = 0 ; i < argc ; i++)
	printf("Argument %d : %s \n", i+1, argv[i]);
(void)argv;

if (argc != 3){
	nb_col = 1;
	nb_hne = 80;
}
else{
	nb_col = 1;
	nb_hne = 3;
	//nb_col = atoi(argv[1]);
	//nb_hne = atoi(argv[2]);
}



int verif(double *tab, size_t len){
	int check = 1;
	for (size_t i = 0 ; (i < len) && check; i++) {
		check = tab[i] > 0.6;
		//if(i%5 == 0)
			printf("%f,",tab[i]);
	}
	printf("\n");
	return check;
	//return tab[0] > 0.9 && tab[1] < 0.1 && tab[2] > 0.9 && tab[3] < 0.1;
}

int verif_2(s_network *container, size_t wanted){
	size_t len = container->nb_tot;
	size_t wanted_adress = container->nb_ins + container->nb_col * container->nb_hne + wanted;
	double value_of_wanted = container->network[wanted_adress]->val;
	int is_superior = 1;
	for (size_t i = len - container->nb_out ; (i < len) && is_superior ; i++)
		is_superior = value_of_wanted >= container->network[i]->val;
	return is_superior;
}
*/

/*

//propagation of values
for (; j < nb_ins ; j++)
	c->network[j]->val = inputs[training_set][out][j]; //(out + (nb_out * training_set)) * nb_ins + j

for (; j < nb_tot ; j++)
	c->network[j]->val = n_output(c->network, j);*/
