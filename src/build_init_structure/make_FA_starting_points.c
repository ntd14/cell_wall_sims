/*
 * make_FA_starting_points.c
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../make_arrays.h"
#include "make_FA_starting_points.h"
#include "../par_defs.h"

/* make a starting point which has a random position inside the problem space */
void make_start_point(double* start_point)
{
	start_point[0] = (double) length_of_problem_space*(rand()/(double) RAND_MAX);
	start_point[1] = (double) height_of_problem_space*(rand()/(double) RAND_MAX);
	start_point[2] = (double) depth_of_problem_space*(rand()/(double) RAND_MAX);
}

/* use above to calc the starting points for each FA */
void starting_points(double* FA_starts)
{
	int ii, jj;
	for(ii = 0; ii < num_of_FAs; ii++)
	{
		double* start_point = make1Darray(3);
		make_start_point(start_point);
		for(jj = 0; jj < 3; jj++)
		{
			/* save the starting points for each FA into the FA_starts vector, defined in the get_init_data function */
			FA_starts[ind2D(ii, jj, num_of_FAs, 3)] = start_point[jj];
		}
	}
}
