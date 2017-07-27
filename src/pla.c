/*
 * File: pla.c
 * Author: Paul Lin
 * Mailto: paul415236@gmail.com
*/
#ifndef MAIN_H
#include <main.h>
#endif

RESULT pla(int approach)
{
	int i, j, k;
	/* input data */
	int x[2][NUM_OF_SAMPLES];   // input training data
	set_int_random(NUM_OF_SAMPLES, 0, 50, x[0]);    // square footage of the house

	/* output data */
	int y[NUM_OF_SAMPLES],
		h[NUM_OF_SAMPLES];
	set_int_random(NUM_OF_SAMPLES, 1, 20, x[1]);    // how old is the house
	int max = 0;
	for (i = 0; i < NUM_OF_SAMPLES; i++)
	{
		y[i] = (int)(x[0][i]*35/x[1][i]); // price
		if (y[i] > max)
			max = y[i];
	}

	for (i = 0; i < NUM_OF_SAMPLES; i++)
	{
		if (y[i] > max*0.45)
			h[i] = 1;   // expensive
		else
			h[i] = -1;
	}


	// weight
	double theta[3] = {0.1, 0.1, 0.1};

	/* pocket algorithm */
	double pocket_theta[3] = { 0.0, 0.0, 0.0 }; // keeps the best weights in pocket
	int min_error = NUM_OF_SAMPLES;             // current minimum error
	int max_training_times = NUM_OF_SAMPLES*10; // threshold to apply pocket algorithm

	// record result
	FILE *file_weight;
	if ((file_weight = fopen("weights.txt", "w")) == NULL)
	{
		printf("open weights.txt fail. \n");
		fclose(file_weight);
		return S_FAIL;
	}

	unsigned int iteration = 0;
	while(TRUE)
	{
		iteration ++;

		int error = 0;
		for (i = 0; i < NUM_OF_SAMPLES; i++)
		{
			double v = theta[0] + theta[1]*x[0][i] + theta[2]*x[1][i];

			if (sign(v) != h[i])
			{
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
		if (error == 0)
			break;
		else if (iteration > max_training_times)
		{
			printf("unable to be convergent without mistakes, implement pocket alg. \n");
			theta[0] = pocket_theta[0];
			theta[1] = pocket_theta[1];
			theta[2] = pocket_theta[2];
			error = min_error;
			printf("(%d) error = %d \n", iteration + 1, error);
			break;
		}

	}

	printf("theta = %.1f %.1f %.1f \n", theta[0], theta[1], theta[2]);
	fprintf(file_weight, "%f\n", theta[0]);
	fprintf(file_weight, "%f\n", theta[1]);
	fprintf(file_weight, "%f\n", theta[2]);

	fclose(file_weight);

	return S_OK;
}
