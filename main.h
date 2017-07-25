#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* bool */
#ifndef TRUE
#define TRUE	(1)
#endif
#ifndef FALSE
#define FALSE	(0)
#endif

typedef enum
{
	S_UNKNOWN = 0x00,

	S_OK,
	S_FAIL
} RESULT;

typedef enum
{
	BATCH_GRADIENT_DESCENT = 0x00,
	STOCHASTIC_GRADIENT_DESCENT,
	PERCEPTRON_LEARNING_ALGORITHM,


	TRAINING_APPROACH_MAX
} TRAINING_APPROACH;

/* set random values to certain matrix */
RESULT set_int_random(int , int , int , int *);
/* sign */
int sign(double);

#endif
