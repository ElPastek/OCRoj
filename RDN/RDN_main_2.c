# include "neuron_2.h"

size_t nb_ins;
size_t nb_col;
size_t nb_hne;
size_t nb_out;

void train(NEURON **network)//char *argv[])
{
	size_t nb_tot = nb_ins + nb_col * nb_hne + nb_out;
	double inputs[4][2] = {
		{0,1},
		{0,0},
		{1,0},
		{1,1}
	}; 
	double results[4] = {1,0,1,0};
	

	int epoch = 0;

	do
	{
		for (size_t i = 0 ; i < 4 ; i++)
		{
			//propagation of values
			for (size_t j = 0 ; j < nb_ins ; j++)
				network[j] -> val = inputs[i][j];
			
			for (size_t j = nb_ins ; j < nb_tot ; j++)
				network[j] -> val = n_output(network[j], network);

			printf("%f xor %f = %f\n", inputs[i][0], inputs[i][1], network[5] -> val);

			//propagation of errors
			for (size_t j = 5 ; j < 6 ; j++) //outputs
			{
				network[j] -> error = results[i] - (network[j] -> val);
				(network[j] -> bias) += (network[j] -> error);
			}

			for (size_t j = 4 ; j > 1 ; j--) //others
			{	
				double sum = 0;
				for (size_t c = 5 ; c < 6 ; c++)
					sum += (network[c] -> error) * ((network[c] -> weights)[j-2]);
				network[j] -> error = sum * derivative(network[j] -> val);
				network[j] -> bias += network[j] -> error;
			}

			//update of weigth
			for (size_t j = 2 ; j < 6 ; j++)
			{
				size_t l = network[j] -> len;
				for (size_t k = 0 ; k < l ; k++)
				{
					((network[j] -> weights)[k]) += 
					(network[j] -> error) *
					(network[(network[j] -> inputs) + k] -> val);
				}
			}
		}

		printf("epoch : %d\n", epoch);
		epoch++;
	} while (epoch < 1000);
	/* 
	kill_neuron(n_1);
	kill_neuron(n_2);
	kill_neuron(n_3);
	kill_neuron(n_f);
	*/
}

/*
arg 1 : nb inputs
arg 2 & 3 : nb columns and nb neurons in hidden layer
arg 4 : nb outputs 
*/
int main(int argc, char *argv[])
{
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


	/*
	static size_t const nb_ins = atoi(argv[1]);
	static size_t const nb_col = atoi(argv[2]);
	static size_t const nb_neu = atoi(argv[3]);
	static size_t const nb_out = atoi(argv[4]);*/

	srand(time(NULL));

	NEURON **network = init__network(nb_ins, nb_col, nb_hne, nb_out);
	/*for (int i = 2 ; i < 6 ; i++)
	{
		printf("%f\n", network[i] -> val);
	}*/

	//printf(argv[0] + "\n");
	//init_inputs_layer(argv[1])*
	for (int i = 0 ; i < argc ; i++)
		printf("Argument %d : %s \n", i+1, argv[i]);

	train(network);
	return 0;
}