# include "neuron.h"

void train()
{
	double inputs[4][2] = {
		{0,1},
		{0,0},
		{1,0},
		{1,1}
	}; 

	double results[4] = {1,0,1,0};

	struct neuron *n_1 = init_neuron(2);
	struct neuron *n_2 = init_neuron(2);
	struct neuron *n_3 = init_neuron(2);
	struct neuron *n_f = init_neuron(3);
	double nf_output = 0;

	int epoch = 0;
	double derivativ = 0;
	while (epoch < 1000) //&& (epoch < 200 || nf_output < 0.8 ))
	{
		epoch++;
		for (int i = 0 ; i < 4 ; i++)
		{
			n_1 -> inputs [0] = inputs[i][0];
			n_1 -> inputs [1] = inputs[i][1];

			n_2 -> inputs [0] = inputs[i][0];
			n_2 -> inputs [1] = inputs[i][1];

			n_3 -> inputs [0] = inputs[i][0];
			n_3 -> inputs [1] = inputs[i][1];

			n_f -> inputs[0] = n_output(n_1 -> inputs, n_1 -> weights, n_1 -> bias, n_1 -> len);
			n_f -> inputs[1] = n_output(n_2 -> inputs, n_2 -> weights, n_2 -> bias, n_2 -> len);
			n_f -> inputs[2] = n_output(n_3 -> inputs, n_3 -> weights, n_3 -> bias, n_3 -> len);

			nf_output = n_output(n_f -> inputs, n_f -> weights, n_f -> bias, n_f -> len);
			printf("%f xor %f = %f\n", inputs[i][0], inputs[i][1], nf_output);

			n_f -> error = derivative(nf_output) * (results[i] - nf_output);
			n_f -> weights[0] += n_f -> error * n_f -> inputs[0];
			n_f -> weights[1] += n_f -> error * n_f -> inputs[1];
			n_f -> weights[2] += n_f -> error * n_f -> inputs[2];
			/*n_f -> error = (results[i] - nf_output);
			derivativ = derivative(nf_output);
			n_f -> weights[0] += derivativ * n_f -> error * n_f -> inputs[0];
			n_f -> weights[1] += derivativ * n_f -> error * n_f -> inputs[1];
			n_f -> weights[2] += derivativ * n_f -> error * n_f -> inputs[2];*/
			n_f -> bias += n_f -> error;

			n_3 -> error = derivative(n_f -> inputs[2]) * n_f -> weights[2] * n_f -> error;
			n_3 -> weights[0] += n_3 -> error * n_3 -> inputs[0];
			n_3 -> weights[1] += n_3 -> error * n_3 -> inputs[1];
			/*n_3 -> error = n_f -> weights[2] * n_f -> error;
			derivativ = derivative(n_f -> inputs[2]);
			n_3 -> weights[0] += derivativ * n_3 -> error * n_3 -> inputs[0];
			n_3 -> weights[1] += derivativ * n_3 -> error * n_3 -> inputs[1];*/
			n_3 -> bias += n_3 -> error;

			n_2 -> error = derivative(n_f -> inputs[1]) * n_f -> weights[1] * n_f -> error;
			n_2 -> weights[0] += (n_2 -> error * n_2 -> inputs[0]);
			n_2 -> weights[1] += (n_2 -> error * n_2 -> inputs[1]);
			/*n_2 -> error = n_f -> weights[1] * n_f -> error;
			derivativ = derivative(n_f -> inputs[1]);
			n_2 -> weights[0] += derivativ * n_2 -> error * n_2 -> inputs[0];
			n_2 -> weights[1] += derivativ * n_2 -> error * n_2 -> inputs[1];*/
			n_2 -> bias += n_2 -> error;

			n_1 -> error = derivative(n_f -> inputs[0]) * n_f -> weights[0] * n_f -> error;
			n_1 -> weights[0] += n_1 -> error * n_1 -> inputs[0];
			n_1 -> weights[1] += n_1 -> error * n_1 -> inputs[1];
			/*n_1 -> error = n_f -> weights[0] * n_f -> error;
			derivativ = derivative(n_f -> inputs[0]);
			n_1 -> weights[0] += derivativ * n_1 -> error * n_1 -> inputs[0];
			n_1 -> weights[1] += derivativ * n_1 -> error * n_1 -> inputs[1];*/
			n_1 -> bias += n_1 -> error;
		}
		printf("%d\n", epoch);
	} 
	kill_neuron(n_1);
	kill_neuron(n_2);
	kill_neuron(n_3);
	kill_neuron(n_f);
}

int main()
{
	srand(time(NULL));
	train();
	return 0;
}