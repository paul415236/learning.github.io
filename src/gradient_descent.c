/*
 * File: gradient_descent.c
 * Author: Paul Lin
 * Mailto: paul415236@gmail.com
*/

#ifndef MAIN_H
#include <main.h>
#endif

#define LOCALLY_WEIGHTED	(1)

RESULT gradient_descent(int approach)
{
	int i, j, k;

	/* parameters */
	double alpha = 0.00001;		// learning rate
	#if TERMINATE_BY_TRAINING_TIMES
	int training_times = 2000;		// training_times
	#elif TERMINATE_BY_ERROR_CONVERGE
	double converge_error = 10.0;	// acceptable error to be terminated
	#endif

	/* set input data */
	int x[2][NUM_OF_SAMPLES];
	set_int_random(NUM_OF_SAMPLES, 0, 50, x[0]);	// square footage of the house
	set_int_random(NUM_OF_SAMPLES, 1, 20, x[1]);	// how old is the house

	/* set output data */
	int y[NUM_OF_SAMPLES];
	for (i = 0; i < NUM_OF_SAMPLES; i++)
		y[i] = (int)(x[0][i]*35/x[1][i]);			// price of the house


	/* weight */
	double theta[3] = { 0.1, 0.1, 0.1 };
	// handler for result record
	FILE *file_weight;
	if ((file_weight = fopen("weights.txt", "w")) == NULL)
	{
		printf("open weights.txt fail. \n");
		fclose(file_weight);
		return S_FAIL;
	}

 	/* locally weighted linear regression */
	#if LOCALLY_WEIGHTED
	int evaluate_x = 30; // assume we are looking for a 30 square footage of house
	double bandwidth = 0.5;
	#endif

	unsigned int iteration = 0;

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

				#if LOCALLY_WEIGHTED
				double local_w = exp((double)((-1.0*(x[0][k]-evaluate_x)*(x[0][k]-evaluate_x))/2*(bandwidth*bandwidth)));
				sum *= local_w;
				#endif
			}

			if (approach == BATCH_GRADIENT_DESCENT)
				new_theta[j] = theta[j] - alpha*sum;
			else if (approach == STOCHASTIC_GRADIENT_DESCENT)
				theta[j] -= alpha*sum;
		}

		if (approach == BATCH_GRADIENT_DESCENT)
		{
			for (j = 0; j < 3; j++)
				theta[j] = new_theta[j];
		}

		double error = 0.0;
		for (j = 0; j < NUM_OF_SAMPLES; j++)
		{
			#if LOCALLY_WEIGHTED
			double local_w = exp((double)((-1.0*(x[0][j]-evaluate_x)*(x[0][j]-evaluate_x))/2*(bandwidth*bandwidth)));
			error += (y[j]-(theta[0] + theta[1]*x[0][j] + theta[2]*x[1][j]))*local_w;
			#else
			error += (y[j]-(theta[0] + theta[1]*x[0][j] + theta[2]*x[1][j]));
			#endif
		}

		printf("(%d) error = %.1f\n", iteration, error);
		#if TERMINATE_BY_ERROR_CONVERGE
		if (error <= converge_error)
			break;
		#endif
	}

	printf("theta = %.1f %.1f %.1f \n", theta[0], theta[1], theta[2]);
	for (i = 0; i < 3; i++)
		fprintf(file_weight, "%f\n", theta[i]);


	fclose(file_weight);

	return S_OK;
}



