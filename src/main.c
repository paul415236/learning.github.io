/*
 * File: main.c
 * Author: Paul Lin
 * Mailto: paul415236@gmail.com
*/
#ifndef MAIN_H
#include <main.h>
#endif

int main(int argc, char *argv[])
{
	int training_approach;
	if (argc <= 1)
	{
		printf("usage: ./out training_approach \n");
		return S_FAIL;
	}
	else
	{
		training_approach = atoi(argv[1]);
		if (training_approach >= TRAINING_APPROACH_MAX)
		{
			printf("unsupported approach. \n");
			return S_FAIL;
		}

		show_approach(training_approach);
	}

	switch (training_approach)
	{
	case BATCH_GRADIENT_DESCENT:
	case STOCHASTIC_GRADIENT_DESCENT:
		gradient_descent(training_approach);
	break;

	case PERCEPTRON_LEARNING_ALGORITHM:
		pla(training_approach);
	break;

	default:
	break;
	}

    return S_OK;
}
