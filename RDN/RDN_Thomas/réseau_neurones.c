# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>


double signoid(double x)
{
  return 1.0/(1.0 + exp(-x));
}

double derivative(double x)
{
  return x*(1.0-x);
}

double neuronOutput(double inputs[], double weights[], double bias, size_t len)
{
  double res = 0;
  for (size_t i = 0; i < len; i++)
  {
    res += inputs[i]*weights[i];
  }
  return signoid(res+bias);
}

void train()
{
  double inputs[4][2] = { {0,0},
                          {0,1},
                          {1,0},
                          {1,1}
                        };

  double results[4] = {1,0,0,1};

  double n1_Inputs[2];
  double n1_Weights[2];
  double n1_BiasWeights;
  double n1_Error;
  size_t n1_Len = 2;

  double n2_Inputs[2];
  double n2_Weights[2];
  double n2_BiasWeights;
  double n2_Error;
  size_t n2_Len = 2;

  double n3_Inputs[2];
  double n3_Weights[2];
  double n3_BiasWeights;
  double n3_Error;
  size_t n3_Len = 2;

  double n4_Inputs[2];
  double n4_Weights[2];
  double n4_BiasWeights;
  double n4_Error;
  size_t n4_Len = 2;

  double n5_Inputs[4];
  double n5_Weights[4];
  double n5_BiasWeights;
  double n5_Error;
  size_t n5_Len = 4;

  n1_Weights[0] = (double) rand()/(double) RAND_MAX;
  n1_Weights[1] = (double) rand()/(double) RAND_MAX;
  n1_BiasWeights = (double) rand()/(double) RAND_MAX;

  n2_Weights[0] = (double) rand()/(double) RAND_MAX;
  n2_Weights[1] = (double) rand()/(double) RAND_MAX;
  n2_BiasWeights = (double) rand()/(double) RAND_MAX;

  n3_Weights[0] = (double) rand()/(double) RAND_MAX;
  n3_Weights[1] = (double) rand()/(double) RAND_MAX;
  n3_BiasWeights = (double) rand()/(double) RAND_MAX;

  n4_Weights[0] = (double) rand()/(double) RAND_MAX;
  n4_Weights[1] = (double) rand()/(double) RAND_MAX;
  n4_BiasWeights = (double) rand()/(double) RAND_MAX;

  n5_Weights[0] = (double) rand()/(double) RAND_MAX;
  n5_Weights[1] = (double) rand()/(double) RAND_MAX;
  n5_Weights[2] = (double) rand()/(double) RAND_MAX;
  n5_Weights[3] = (double) rand()/(double) RAND_MAX;
  n5_BiasWeights = (double) rand()/(double) RAND_MAX;

  int epoch = 0;
  while (epoch < 5000)
  {
    epoch++;
    for (int i = 0; i < 4; i++)
    {
      //Inputs 1,2,3
      n1_Inputs[0] = inputs[i][0];
      n1_Inputs[1] = inputs[i][1];

      n2_Inputs[0] = inputs[i][0];
      n2_Inputs[1] = inputs[i][1];

      n3_Inputs[0] = inputs[i][0];
      n3_Inputs[1] = inputs[i][1];

      n4_Inputs[0] = inputs[i][0];
      n4_Inputs[1] = inputs[i][1];
      //Inputs 1,2,3

      //Inputs 4
      n5_Inputs[0] = neuronOutput(n1_Inputs, n1_Weights, n1_BiasWeights, n1_Len);
      n5_Inputs[1] = neuronOutput(n2_Inputs, n2_Weights, n2_BiasWeights, n2_Len);
      n5_Inputs[2] = neuronOutput(n3_Inputs, n3_Weights, n3_BiasWeights, n3_Len);
      n5_Inputs[3] = neuronOutput(n4_Inputs, n4_Weights, n4_BiasWeights, n4_Len);
      //Inputs 4

      //Output 4
      double n5_Output = neuronOutput(n5_Inputs, n5_Weights, n5_BiasWeights, n5_Len);
      //Output 4

      //Test
      printf("%f xor %f = %f\n", inputs[i][0], inputs[i][1], n5_Output);
      //Test

      //n4 Error
      n5_Error = derivative(n5_Output) * (results[i] - n5_Output);
      n5_Weights[0] += (n5_Error * n5_Inputs[0]);
      n5_Weights[1] += (n5_Error * n5_Inputs[1]);
      n5_Weights[2] += (n5_Error * n5_Inputs[2]);
      n5_Weights[3] += (n5_Error * n5_Inputs[3]);
      n5_BiasWeights += n5_Error;
      //n4 Error

      //n1,n2,n3 Error
      n1_Error = derivative(n5_Inputs[0]) * n5_Weights[0] * n5_Error;
      n2_Error = derivative(n5_Inputs[1]) * n5_Weights[1] * n5_Error;
      n3_Error = derivative(n5_Inputs[2]) * n5_Weights[2] * n5_Error;
      n4_Error = derivative(n5_Inputs[3]) * n5_Weights[3] * n5_Error;

      n1_Weights[0] += (n1_Error * n1_Inputs[0]);
      n1_Weights[1] += (n1_Error * n1_Inputs[1]);
      n1_BiasWeights += n1_Error;

      n2_Weights[0] += (n2_Error * n2_Inputs[0]);
      n2_Weights[1] += (n2_Error * n2_Inputs[1]);
      n2_BiasWeights += n2_Error;

      n3_Weights[0] += (n3_Error * n3_Inputs[0]);
      n3_Weights[1] += (n3_Error * n3_Inputs[1]);
      n3_BiasWeights += n3_Error;

      n4_Weights[0] += (n4_Error * n4_Inputs[0]);
      n4_Weights[1] += (n4_Error * n4_Inputs[1]);
      n4_BiasWeights += n4_Error;
      //n1,n2,n3 Error
    }
  }
}

void main()
{
  srand(time(NULL));
  train();
}

/*struct
{
  double* weights;
  ...

}

void init()
{
  struct neuron* n1;
  n1 -> weights = malloc(m*sizeof(...));
}*/
