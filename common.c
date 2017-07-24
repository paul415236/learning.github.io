#ifndef MAIN_H
#include <main.h>


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


#endif
