# include "neuron_2.h"
# include "RDN_main_2.h"

size_t nb_ins;
size_t nb_col;
size_t nb_hne;
size_t nb_out;
size_t nb_tot;
NEURON **network;

void train()//char *argv[])
{
	double inputs[4][2] = {
		{0,1},
		{0,0},
		{1,0},
		{1,1}
	}; 
	double results[4] = {1,0,1,0};
	
	double r_results[4];

	int epoch = 0;

	do
	{
		for (size_t i = 0 ; i < 4 ; i++)
		{	

			size_t j = 0;
			//propagation of values
			for (; j < nb_ins ; j++)
				network[j] -> val = inputs[i][j];
			
			for (; j < nb_tot ; j++)
				network[j] -> val = n_output(network[j], network);

			//verification
			printf("%f xor %f = %f\n", inputs[i][0], inputs[i][1], network[nb_tot - 1] -> val);
			r_results[i] = network[nb_tot - 1] -> val;
			
			//propagation of errors
			for (--j; j > nb_tot - nb_out - 1; j--) //outputs
			{
				//network[j] -> error = results[i] - (network[j] -> val);
				network[j] -> error = derivative(network[j] -> val) * (results[i] - (network[j] -> val));
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
			/*
			for (; j > (nb_ins - 1) ; j--) //other hidden layers
			{
				double sum = 0;
				size_t b = ((j - nb_ins) / nb_hne + 1 ) * nb_hne + nb_ins;
				size_t e = b + nb_hne	;
				for (; b < e ; b++)
						sum += (network[b] -> error) * ((network[b] -> weights)[(j - nb_ins) % nb_hne]);
				network[j] -> error = sum * derivative(network[j] -> val);
				network[j] -> bias += network[j] -> error;
			} */
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
		printf("epoch : %d\n", epoch);

	} while (!verif(r_results) && epoch < 100000);
	if (epoch == 100000)
	{
		network = init__network(nb_ins, nb_col, nb_hne, nb_out);//, NULL, NULL);
		train();
	}
}

int verif(double tab[])
{
	return tab[0] > 0.9 && tab[1] < 0.1 && tab[2] > 0.9 && tab[3] < 0.1;
}

void save()
{
	FILE* fichier = NULL;

	fichier = fopen("saved_RDN_LBIW.txt", "w");
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

/*
arg 1 : nb inputs
arg 2 & 3 : nb columns and nb neurons in hidden layer
arg 4 : nb outputs 
*/
int main(int argc, char *argv[])
{
	printf("%lf\n", sqrt(-1));
	for (int i = 0 ; i < argc ; i++)
		printf("Argument %d : %s \n", i+1, argv[i]);
	//assert(argc == 5);
	if (argc != 5){
		nb_ins = 2;
		nb_col = 1;
		nb_hne = 3;
		nb_out = 1;
	}
	else{
		nb_ins = atoi(argv[1]);
		nb_col = atoi(argv[2]);
		nb_hne = atoi(argv[3]);
		nb_out = atoi(argv[4]);
	}
	nb_tot = nb_ins + nb_col * nb_hne + nb_out;

	srand(time(NULL));
	
	network = init__network(nb_ins, nb_col, nb_hne, nb_out);//, NULL, NULL);
	train();
	save();
	return 0;
}