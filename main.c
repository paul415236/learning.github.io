#ifndef MAIN_H
#include <main.h>
#endif

#define NUM_OF_SAMPLES  (100)

#define TERMINATE_BY_TRAINING_TIMES	(0)
#define TERMINATE_BY_ERROR_CONVERGE	(1)

int main(int argc, char *argv[])
{
	// learning rate
	double alpha = 0.0000002;
	#if TERMINATE_BY_TRAINING_TIMES
	// training_times
	int training_times = 2000;
	#elif TERMINATE_BY_ERROR_CONVERGE
	double converge_error = 10.0;
	#endif

	/*if (argc < 2)
	{
		printf("usage: ./out learning_rate training_times \n");
		return S_FAIL;
	}*/

	int training_approach = BATCH_GRADIENT_DESCENT;

	int i, j, k;

	// input training data
	int x[2][NUM_OF_SAMPLES];
	// target output
	int y[NUM_OF_SAMPLES];
	// weight
	double theta[3] = {0.1, 0.1, 0.1};


	// square footage of the house
	set_int_random(NUM_OF_SAMPLES, 0, 50, x[0]);
	// how old is the house
	set_int_random(NUM_OF_SAMPLES, 1, 20, x[1]);
	// price 
	for (i = 0; i < NUM_OF_SAMPLES; i++)
		y[i] = (int)(x[0][i]*35/x[1][i]);


	unsigned int count = 0;
	switch (training_approach)
	{
	case BATCH_GRADIENT_DESCENT:
	case STOCHASTIC_GRADIENT_DESCENT:
	#if TERMINATE_BY_TRAINING_TIMES
		for (i = training_times; i > 0; i--)
	#elif TERMINATE_BY_ERROR_CONVERGE
		while (TRUE)
	#endif
		{
			count ++;

			double new_theta[3];
			for (j = 0; j < 3; j++)
			{
				double sum = 0.0;
				for (k = 0; k < NUM_OF_SAMPLES; k++)
				{
					if (j == 0)
						sum += ((theta[0] + theta[1]*x[0][k] + theta[2]*x[1][k]) - y[k]);
					else if (j == 1)
						sum += ((theta[0] + theta[1]*x[0][k] + theta[2]*x[1][k]) - y[k])*x[0][k];
					else
						sum += ((theta[0] + theta[1]*x[0][k] + theta[2]*x[1][k]) - y[k])*x[1][k];
				}

				if (training_approach == BATCH_GRADIENT_DESCENT)
					new_theta[j] = theta[j] - alpha*sum;
				else // STOCHASTIC_GRADIENT_DESCENT
					theta[j] -= alpha*sum;
			}

			if (training_approach == BATCH_GRADIENT_DESCENT)
			{
				for (j = 0; j < 3; j++)
					 theta[j] = new_theta[j];
			}

			double error = 0.0;
			for (j = 0; j < NUM_OF_SAMPLES; j++)
				error += (y[j]-(theta[0] + theta[1]*x[0][j] + theta[2]*x[1][j]));

			//if (i == 1)
			printf("error = %.1f, count = %d \n", error, count);
			#if TERMINATE_BY_ERROR_CONVERGE
			if (error <= converge_error)
				break;
			#endif
		}

		printf("theta = %.1f %.1f %.1f \n", theta[0], theta[1], theta[2]);

	break;

	default:
		printf("unknow training_approach. ");
	break;
	}


    return S_OK;
}
