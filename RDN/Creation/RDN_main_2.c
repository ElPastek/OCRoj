# include "neuron_2.h"
# include "RDN_main_2.h"

size_t nb_ins;
size_t nb_col;
size_t nb_hne;
size_t nb_out;
size_t nb_tot;
size_t nb_elem; 
double *inputs; //simul 2 dimentions
double *results;
NEURON **network;

void train()
{
	
	double r_results[nb_elem];

	int epoch = 0;

	do
	{
		for (size_t i = 0 ; i < nb_elem ; i++)
		{	

			size_t j = 0;
			//propagation of values
			for (; j < nb_ins ; j++)
				network[j] -> val = inputs[i * nb_ins + j];
			
			for (; j < nb_tot ; j++)
				network[j] -> val = n_output(network[j], network);

			//verification
			size_t found = find();
			size_t found_o = found + nb_ins + nb_hne * nb_col;
			/*printf("%f xor %f = %f\n", inputs[i * nb_ins], inputs[i * nb_ins + 1], network[found_o] -> val); */
			//network[nb_tot - 1] -> val);
			r_results[i] = network[found_o] -> val;//network[nb_tot - 1] -> val;
			
			//propagation of errors
			for (--j; j > nb_tot - nb_out - 1; j--) //outputs
			{
				//network[j] -> error = results[i] - (network[j] -> val);
				int is_stimul = (j + nb_out - nb_tot) == results[i];
				network[j] -> error = derivative(network[j] -> val) * //(results[i] - (network[j] -> val));
				(is_stimul - (network[j] -> val));
				network[j] -> bias += network[j] -> error;
			}
			for (; j > (nb_ins - 1) ; j--)//j > nb_tot - nb_out - nb_hne - 1; j--) //last hidden layer
			{
				double sum = 0;
				//size_t b = nb_tot - nb_out;
				size_t b = ((j - nb_ins) / nb_hne + 1 ) * nb_hne + nb_ins;
				size_t e = b + nb_hne	;
				for (; b < nb_tot && b < e; b++)
					sum += (network[b] -> error) * ((network[b] -> weights)[(j - nb_ins) % nb_hne]);
				network[j] -> error = sum * derivative(network[j] -> val);
				network[j] -> bias += network[j] -> error;
			}
			//update of weight
			for (j = nb_ins ; j < nb_tot ; j++)
			{
				size_t l = network[j] -> len;
				for (size_t k = 0 ; k < l ; k++)
				{
					((network[j] -> weights)[k]) += 0.2 *
					(network[j] -> error) *
					(network[(network[j] -> inputs) + k] -> val);
				}
			}
		}

		epoch++;
		//printf("epoch : %d\n", epoch);

	} while (!verif(r_results, nb_elem) && epoch < 100000);
		//(epoch < 1));
	if (epoch == 100000)
	{
		network = init__network(nb_ins, nb_col, nb_hne, nb_out);//, NULL, NULL);
		train();
	}
}

int verif(double tab[], size_t len)
{
	int check = 1;
	for (size_t i = 0 ; i < len && check; i++)
		check = tab[i] > 0.9;
	return check;
	//return tab[0] > 0.9 && tab[1] < 0.1 && tab[2] > 0.9 && tab[3] < 0.1;
}

size_t find()
{
	size_t retour = nb_ins + nb_col * nb_hne;
	double max    = network[nb_ins + nb_col * nb_hne] -> val;
	for (size_t i = nb_ins + nb_col * nb_hne + 1; i < nb_tot; i++) {
		if ((network[i] -> val) > max) {
			max = network[i] -> val;
			retour = i;
		}
	}
	return retour + nb_out - nb_tot;
}

void save()
{
	FILE* fichier = NULL;

	fichier = fopen("saved_RDN_LBIW.txt", "w+");
	fprintf(fichier, "%zu,%zu,%zu,%zu\n", nb_ins, nb_col, nb_hne, nb_out);
	for (size_t i = nb_ins ; i < nb_tot ; i++)
	{
		fprintf(fichier, "%zu,%lf,%zu", 
			network[i] -> len, 
			network[i] -> bias, 
			network[i] -> inputs);
		for (size_t j = 0 ; j < (network[i] -> len) ; j++)
			fprintf(fichier, ",%lf", (network[i] -> weights)[j]);
		fprintf(fichier, "\n");
	}
	fclose(fichier);
}

void open_training()
{
	FILE* fichier = NULL;
	fichier = fopen("training.txt", "r");
	assert(fscanf(fichier, "%zu,%zu,%zu", &nb_ins, &nb_out, &nb_elem));
	results = malloc(nb_elem * sizeof(double));
	inputs  = malloc(nb_elem * nb_ins * sizeof(double));
	for (size_t i = 0 ; i < nb_elem ; i++)
	{
		fseek(fichier, +1, SEEK_CUR);
		assert(fscanf(fichier, "%lf", &results[i]));
	}
	for (size_t i = 0 ; i < nb_elem ; i++)
	{
		for (size_t j = 0 ; j < nb_ins ; j++)
		{
			fseek(fichier, +1, SEEK_CUR);
			assert(fscanf(fichier, "%lf", &inputs[i * nb_ins + j]));
		}
	}
	fclose(fichier);
}

/*
arg 1 : nb inputs
arg 2 & 3 : nb columns and nb neurons in hidden layer
arg 4 : nb outputs 
*/
int main(int argc, char *argv[])
{
	//for (int i = 0 ; i < argc ; i++)
	//	printf("Argument %d : %s \n", i+1, argv[i]);

	if (argc != 3){
		nb_col = 1;
		nb_hne = 3;
	}
	else{
		nb_col = atoi(argv[1]);
		nb_hne = atoi(argv[2]);
	}
	open_training();

	nb_tot = nb_ins + nb_col * nb_hne + nb_out;

	srand(time(NULL));
	
	network = init__network(nb_ins, nb_col, nb_hne, nb_out);//, NULL, NULL);
	train();
	save();
	return 0;
}