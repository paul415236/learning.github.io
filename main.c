#ifndef MAIN_H
#include <main.h>
#endif

#define NUM_OF_SAMPLES  1000


int main()
{
    int i, j, k;
    int training_times = 500;

    double x_1[NUM_OF_SAMPLES], x_2[NUM_OF_SAMPLES], y[NUM_OF_SAMPLES];


    srand((unsigned)time(NULL));
    for (i = 0; i < NUM_OF_SAMPLES; i++)
    {
        x_1[i] = (double)(rand()%50)*1.1;
        x_2[i] = (double)(rand()%10)*1.1;
        y[i] = (double)(x_1[i]*1.32 + x_2[i]*0.17);
    }

    // weight
    double theta[3] = {0.1, 0.1, 0.1};
    // learning rate
    double alpha = 0.0000001;

#define BATCH_GRADIENT_DESCENT (0)
#define STOCHASTIC_GRADIENT_DESCENT (1)
    double new_theta[3];
    for (k = training_times; k > 0; k--)
    {
        for (i = 0; i < 3; i++)
        {
            double sum = 0.0;
            for (j = 0; j < NUM_OF_SAMPLES; j++)
            {
                if (i == 0)
                    sum += ((theta[0] + theta[1]*x_1[j] + theta[2]*x_2[j]) - y[j]);
                else if (i == 1)
                    sum += ((theta[0] + theta[1]*x_1[j] + theta[2]*x_2[j]) - y[j])*x_1[j];
                else if (i == 2)
                    sum += ((theta[0] + theta[1]*x_1[j] + theta[2]*x_2[j]) - y[j])*x_2[j];

            }

            #if BATCH_GRADIENT_DESCENT
            new_theta[i] = theta[i] - alpha*sum;
            #elif STOCHASTIC_GRADIENT_DESCENT
            theta[i] -= alpha*sum;
            #endif
        }

        // update
        #if BATCH_GRADIENT_DESCENT
        for (i = 0; i < 3; i++)
            theta[i] = new_theta[i];
        #endif

        //printf("%.1f %.1f \n", theta[0], theta[1]);

        double error = 0.0;
        for (j = 0; j < NUM_OF_SAMPLES; j++)
            error += (y[j]-(theta[0] + theta[1]*x_1[j] + theta[2]*x_2[j]));

        printf("error = %.1f \n", error);
    }


    printf("theta = %.1f %.1f %.1f \n", theta[0], theta[1], theta[2]);


    return 0;
}
