# include "neuron_bias.h"

void train(char *argv[])
{
	double inputs[4][2] = {
		{0,1},
		{0,0},
		{1,0},
		{1,1}
	}; 

	double results[4] = {1,0,1,0};
	neuron **network = init__network();
	/*
	struct neuron *inputs_layer = init_inputs_layer();
	struct neuron *hidden_layer = init__layer(inputs_layer);
	struct neuron *output_layer = init__layer(hidden_layer);
	*/
	/*
	struct neuron *n_1 = init_neuron(2);
	struct neuron *n_2 = init_neuron(2);
	struct neuron *n_3 = init_neuron(2);
	struct neuron *n_f = init_neuron(3);
	*/
	int epoch = 0;
	double dev_f = 0;
	double dev_3 = 0;
	double dev_2 = 0;
	double dev_1 = 0;
	double nf_output = 0;
	while (epoch < 100) //&& (epoch < 200 || nf_output < 0.8 ))
	{
		epoch++;
		for (int i = 0 ; i < 4 ; i++)
		{
			for (int j = 0 ; j < 2 ; j ++)
				(inputs_layer + j) -> val = inputs[i][j];
			/*
			n_1 -> inputs [0] = inputs[i][0];
			n_1 -> inputs [1] = inputs[i][1];

			n_2 -> inputs [0] = inputs[i][0];
			n_2 -> inputs [1] = inputs[i][1];

			n_3 -> inputs [0] = inputs[i][0];
			n_3 -> inputs [1] = inputs[i][1];
			*/
			for (int j = 0 ; j < 3 ; j++)
				hidden_layer[j] -> val = n_output(
					hidden_layer -> inputs,
					(hidden_layer + j) -> weights,
					hidden_layer -> len);

			output_layer -> val = n_output(
				output_layer -> inputs, 
				output_layer -> weights, 
				output_layer -> len);
			/*
			n_1 -> val = n_output(n_1 -> inputs, n_1 -> weights, n_1 -> len);
			n_2 -> val = n_output(n_2 -> inputs, n_2 -> weights, n_2 -> len);
			n_3 -> val = n_output(n_3 -> inputs, n_3 -> weights, n_3 -> len);
			n_f -> val = n_output(n_f -> inputs, n_f -> weights, n_f -> len);
			*/
			/*
			n_f -> inputs[0] = n_output(n_1 -> inputs, n_1 -> weights, n_1 -> len);
			n_f -> inputs[1] = n_output(n_2 -> inputs, n_2 -> weights, n_2 -> len);
			n_f -> inputs[2] = n_output(n_3 -> inputs, n_3 -> weights, n_3 -> len);
			//nf_output = n_output(n_f -> inputs, n_f -> weights, n_f -> len);
			*/
			printf("%f xor %f = %f\n", inputs[i][0], inputs[i][1], output_layer -> val);

			output_layer -> error = results[i] - output_layer -> val;
			/*dev_f = derivative(nf_output);
			dev_3 = derivative(n_3 -> val);
			dev_2 = derivative(n_2 -> val);
			dev_1 = derivative(n_1 -> val);*/
			for (int j = 0 ; j < 3 ; j++)
			{
				hidden_layer[j] -> error = 
				output_layer -> error *
				(output_layer -> weights)[j] * 
				derivative(hidden_layer[j] -> val);
			}
			/*
			n_3 -> error = dev_3 * n_f -> weights[2] * n_f -> error;
			n_2 -> error = dev_2 * n_f -> weights[1] * n_f -> error;
			n_1 -> error = dev_1 * n_f -> weights[0] * n_f -> error;
			/*
			n_f -> error = derivative(nf_output) * (results[i] - nf_output);
			n_3 -> error = derivative(n_f -> inputs[2]) * n_f -> weights[2] * n_f -> error;
			n_2 -> error = derivative(n_f -> inputs[1]) * n_f -> weights[1] * n_f -> error;
			n_1 -> error = derivative(n_f -> inputs[0]) * n_f -> weights[0] * n_f -> error;
			*/
			/*n_f -> weights[0] += n_f -> error * n_f -> inputs[0];
			n_f -> weights[1] += n_f -> error * n_f -> inputs[1];
			n_f -> weights[2] += n_f -> error * n_f -> inputs[2];*/

			for (int j = 0 ; j < 3 ; j++)
			{
				output_layer -> weights[j] += output_layer -> error * output_layer -> inputs[j]
			}
			/*
			n_f -> weights[0] += n_1 -> inputs[0] * n_f -> error;
			n_f -> weights[1] += n_2 -> inputs[1] * n_f -> error;
			n_f -> weights[2] += n_3 -> inputs[2] * n_f -> error;

			/*n_3 -> weights[0] += n_3 -> error * n_3 -> inputs[0];
			n_3 -> weights[1] += n_3 -> error * n_3 -> inputs[1];*/
			for (int k = 0 ; k < 3 ; k++)
			{
				for (int j = 0 ; j < 2 ; j++)
				{
					hidden_layer[k] -> weights[j] += 0.5 * 
					hidden_layer[k] -> inputs[j] -> val * 
					hidden_layer[k] -> error;
				}
			}
			/*
			n_3 -> weights[0] += 0.1 * n_3 -> inputs[0] * n_3 -> error;
			n_3 -> weights[1] += 0.1 * n_3 -> inputs[1] * n_3 -> error;

			/*n_2 -> weights[0] += (n_2 -> error * n_2 -> inputs[0]);
			n_2 -> weights[1] += (n_2 -> error * n_2 -> inputs[1]);*/
			/*
			n_2 -> weights[0] += 0.1 * n_2 -> inputs[0] * n_2 -> error;
			n_2 -> weights[1] += 0.1 * n_2 -> inputs[1] * n_2 -> error;

			/*n_1 -> weights[0] += n_1 -> error * n_1 -> inputs[0];
			n_1 -> weights[1] += n_1 -> error * n_1 -> inputs[1];*/
			/*
			n_1 -> weights[0] += 0.1 * n_1 -> inputs[0] * n_1 -> error;
			n_1 -> weights[1] += 0.1 * n_1 -> inputs[1] * n_1 -> error;
			*/
		}
		printf("%d\n", epoch);
	}
	/* 
	kill_neuron(n_1);
	kill_neuron(n_2);
	kill_neuron(n_3);
	kill_neuron(n_f);
	*/
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	//printf(argv[0] + "\n");
	//init_inputs_layer(argv[1])
	for (size_t i = 0 ; i < argc ; i++)
	{
		printf("Argument %ld : %s \n", i+1, argv[i]);
	}



	train(argv);
	return 0;
}