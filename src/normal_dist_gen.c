/*
 * normal_dist_gen.c
 *
 *  Created on: 24/05/2015
 *      Author: nick
 *      */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* uniform random numbers to normal random numbers mean of zero sd of 1.
generate two uniform numbers and from those you get
two normally distributed numbers. */

void norm_dist(double* vec_of_nums, int length_of_vec, double mean, double sd)
{
	double x1, x2, w;
	int ii;
    x1 = 2.0 * rand()/RAND_MAX - 1.0;
    x2 = 2.0 * rand()/RAND_MAX - 1.0;
    w = x1 * x1 + x2 * x2;
    for (ii = 0; ii <= length_of_vec; ii+=2)
    {
    	while ( w >= 1.0 )
    	{
    		x1 = 2.0 * (double) rand()/RAND_MAX - 1.0;
    		x2 = 2.0 * (double) rand()/RAND_MAX - 1.0;
    		w = x1 * x1 + x2 * x2;
    	}
    	w = sqrt( (-2.0 * log( w ) ) / w );

    	vec_of_nums[ii] = (x1 * w)*sd + mean;
    	if(ii < length_of_vec)
    	{
    		vec_of_nums[ii+1] = (x2 * w)*sd + mean;
    	}
    }
}
/*

 *
to get a normal distribution near what we want:
y = y1*(sd we want) + (mean we want)
 */
