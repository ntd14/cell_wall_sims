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
#include "../par_defs.h"
#include "make_FA_starting_points.h"

/* make a starting point which has a random position inside the problem space */
void make_start_point(double* start_point)
{
	start_point[0] = (double) length_of_problem_space*(rand()/(double) RAND_MAX);
	start_point[1] = (double) depth_of_problem_space*(rand()/(double) RAND_MAX);
	start_point[2] = (double) height_of_problem_space*(rand()/(double) RAND_MAX);
}

/* use above to calc the starting points for each FA */
void starting_points(double* FA_starts, part_defs pl)
{
	int ii, jj;
	double* start_point = make1Darray(3);
	for(ii = 0; ii < pl.num_of; ii++)
	{
		make_start_point(start_point);
		for(jj = 0; jj < 3; jj++)
		{
			/* save the starting points for each FA into the FA_starts vector, defined in the get_init_data function */
			FA_starts[ind2D(ii, jj, pl.num_of, 3)] = start_point[jj];
		}
	}
	free(start_point);
	start_point = NULL;
}
