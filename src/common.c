/*
 * File: common.c
 * Author: Paul Lin
 * Mailto: paul415236@gmail.com
*/
#ifndef MAIN_H
#include <main.h>
#endif

/*
 * brief set random value to a matrix
*/
RESULT set_int_random(int num, int min, int max, int *src)
{
	srand((unsigned)time(NULL));

	int i;
	for (i = 0; i < num; i++)
	{
		*(src + i) = (rand()%(min+max)) + min;
	}

	return S_OK;
}

/*
 * brief sign
*/
int sign(double v)
{
	if (v > 0.0)		return 1;
	else if (v < 0.0)	return -1;
	else				return 0;

}

RESULT show_approach(int s)
{
	switch (s)
	{
	case BATCH_GRADIENT_DESCENT:
		printf("BATCH_GRADIENT_DESCENT. \n");
	break;
	case STOCHASTIC_GRADIENT_DESCENT:
		printf("STOCHASTIC_GRADIENT_DESCENT. \n");
	break;
	case PERCEPTRON_LEARNING_ALGORITHM:
		printf("PERCEPTRON_LEARNING_ALGORITHM. \n");
	break;

	default:
	break;
	}

    return S_OK;
}

