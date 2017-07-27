/*
 * File: main.h
 * Author: Paul Lin
 * Mailto: paul415236@gmail.com
*/
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

/* bool */
#ifndef TRUE
#define TRUE	(1)
#endif
#ifndef FALSE
#define FALSE	(0)
#endif

#define NUM_OF_SAMPLES	(100)
#define TERMINATE_BY_TRAINING_TIMES (0) // terminate the date training according to interation of training
#define TERMINATE_BY_ERROR_CONVERGE (1) // terminate the data training according to error


typedef enum
{
	S_UNKNOWN = 0x00,

	S_OK,
	S_FAIL
} RESULT;

typedef enum
{
	BATCH_GRADIENT_DESCENT = 0,
	STOCHASTIC_GRADIENT_DESCENT,
	PERCEPTRON_LEARNING_ALGORITHM,


	TRAINING_APPROACH_MAX
} TRAINING_APPROACH;

/* set random values to certain matrix */
RESULT set_int_random(int , int , int , int *);
/* sign */
int sign(double);
/* show training approach */
RESULT show_approach(int);

/* gradient descent*/
RESULT gradient_descent(int);

/* perceptron learning algorithm */
RESULT pla(int);
#endif
