# include "neuron_bias_2.h"

void train(NEURON **network)//char *argv[])
{
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
			for (size_t j = 0 ; j < 2 ; j++)
				network[j] -> val = inputs[i][j];

			for (size_t j = 2 ; j < 5 ; j++)
			{
				network[j] -> val = n_output(
					network[network[j]->inputs],
					network[j] -> weights,
					network[j] -> len);
			}

			for (size_t j = 5 ; j < 6 ; j++)
			{
				network[j] -> val = n_output(
					network[network[j]->inputs],
					network[j] -> weights,
					network[j] -> len);
			}

			printf("%f xor %f = %f\n", inputs[i][0], inputs[i][1], network[5] -> val);
			//propagation of errors
			//printf("test 0\n");
			for (size_t j = 5 ; j > 4 ; j--)
				network[j] ->  error = results[i] - (network[j] -> val);
			//printf("test 1\n");

			for (size_t j = 4 ; j > 1 ; j--)
			{	
				double sum = 0;
				for (size_t c = 5 ; c < 6 ; c++)
					sum += (network[c] -> error) * ((network[c] -> weights)[j-2]);
				network[j] -> error = sum * derivative(network[j] -> val);
			}
			//printf("test 2\n");

			//update of weigth
			for (size_t j = 2 ; j < 6 ; j++)
			{
				size_t l = network[j] -> len;
				for (size_t k = 0 ; k < l ; k++)
				{
					(network[j] -> weights[k]) += (0.2 *  //learning alpha
						(network[j] -> error) *
						(network[(network[j] -> inputs) + k] -> val));  
				}
			}
			//printf("test 3\n");
		}

		printf("%d\n", epoch);
		epoch++;
	} while (epoch < 2);
	/* 
	kill_neuron(n_1);
	kill_neuron(n_2);
	kill_neuron(n_3);
	kill_neuron(n_f);
	*/
}

int main()//int argc, char *argv[])
{
	srand(time(NULL));
	//NEURON* network[6];
	//init__network(network);
	NEURON **network = init__network();
	for (int i = 2 ; i < 6 ; i++)
	{
		printf("%f\n", network[i] -> val);
	}
	//printf(argv[0] + "\n");
	//init_inputs_layer(argv[1])
	/*
	for (int i = 0 ; i < argc ; i++)
	{
		printf("Argument %d : %s \n", i+1, argv[i]);
	}

*/

	train(network);//argv);
	for (int i = 2 ; i < 6 ; i++)
	{
		printf("%f\n", network[i] -> val);
	}
	return 0;
}