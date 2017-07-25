#ifndef MAIN_H
#include <main.h>
#endif

#define NUM_OF_SAMPLES  (100)	// number of samples each input entry

#define TERMINATE_BY_TRAINING_TIMES	(0) // terminate the date training according to interation of training
#define TERMINATE_BY_ERROR_CONVERGE	(1) // terminate the data training according to error

int main(int argc, char *argv[])
{
	int i, j, k;

	/* parameters */
	double alpha = 0.0000002;		// learning rate
	#if TERMINATE_BY_TRAINING_TIMES
	int training_times = 2000;		// training_times
	#elif TERMINATE_BY_ERROR_CONVERGE
	double converge_error = 10.0;	// acceptable error to be terminated
	#endif

	/*if (argc < 2)
	{
		printf("usage: ./out learning_rate training_times \n");
		return S_FAIL;
	}*/

	/* algorithm to be implemented */
	//int training_approach = BATCH_GRADIENT_DESCENT;
	int training_approach =	PERCEPTRON_LEARNING_ALGORITHM;

	/* input data */
	int x[2][NUM_OF_SAMPLES];	// input training data
	/* output data */
	int y[NUM_OF_SAMPLES],
		h[NUM_OF_SAMPLES];

	// weight
	double theta[3] = {0.1, 0.1, 0.1};
	/* pocket algorithm */
	double pocket_theta[3] = { 0.0, 0.0, 0.0 };	// keeps the best weights in pocket
	int min_error = NUM_OF_SAMPLES;				// current minimum error
	int max_training_times = NUM_OF_SAMPLES*10; // threshold to apply pocket algorithm

	set_int_random(NUM_OF_SAMPLES, 0, 50, x[0]);	// square footage of the house
	set_int_random(NUM_OF_SAMPLES, 1, 20, x[1]);	// how old is the house
	// price
	int max = 0;
	for (i = 0; i < NUM_OF_SAMPLES; i++)
	{
		y[i] = (int)(x[0][i]*35/x[1][i]);
		if (y[i] > max)
			max = y[i];
	}

	for (i = 0; i < NUM_OF_SAMPLES; i++)
	{
		if (y[i] > max*0.6)
			h[i] = 1;	// expensive
		else
			h[i] = -1;
	}


	unsigned int iteration = 0;
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
			iteration ++;

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
			printf("(%d) error = %.1f\n", iteration, error);
			#if TERMINATE_BY_ERROR_CONVERGE
			if (error <= converge_error)
				break;
			#endif
		}

		printf("theta = %.1f %.1f %.1f \n", theta[0], theta[1], theta[2]);

	break; // case BATCH_GRADIENT_DESCENT:

	case PERCEPTRON_LEARNING_ALGORITHM:
		while (TRUE)
		{
			iteration ++;

			int re_train = FALSE;
			int error = 0;
			for (i = 0; i < NUM_OF_SAMPLES; i++)
			{
				double v = sign(theta[0] + theta[1]*x[0][i] + theta[2]*x[1][i]);
				if (sign(v) != h[i])
				{
					re_train = TRUE;

					theta[0] += h[i];
					theta[1] += h[i]*x[0][i];
					theta[2] += h[i]*x[1][i];

					error ++;
				}
			}

			if (error < min_error)
			{
				pocket_theta[0] = theta[0];
				pocket_theta[1] = theta[1];
				pocket_theta[2] = theta[2];
				min_error = error;
			}

			printf("(%d) error = %d \n", iteration, error);
			if (!re_train)
				break;
			else if (iteration > max_training_times)
			{
				printf("unable to converge with no mistakes, break with minimum error. \n");
				theta[0] = pocket_theta[0];
				theta[1] = pocket_theta[1];
				theta[2] = pocket_theta[2];
				error = min_error;
				printf("(%d) error = %d \n", iteration + 1, error);
				break;
			}
		}

		printf("theta = %.1f %.1f %.1f \n", theta[0], theta[1], theta[2]);

	break; // case PERCEPTRON_LEARNING_ALGORITHM:

	default:
		printf("unknow training_approach. ");
	break;
	}


    return S_OK;
}
