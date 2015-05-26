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
/* make a vector of starting points for the FAs in the extended space*/
/* caller function needs to define double FA_start_points[ext_length/init_spacing_of_FA]; */
void make_start_point(double* start_point)
{
	start_point[0] = (double) length_of_problem_space*(rand()/(double) RAND_MAX);
	start_point[1] = (double) height_of_problem_space*(rand()/(double) RAND_MAX);
	start_point[2] = (double) depth_of_problem_space*(rand()/(double) RAND_MAX);
	int ii;
	for(ii = 0; ii < 3; ii++)
	{
		printf("%f ", start_point[ii]);
	}
	printf("\n");
}

void starting_points(double* FA_starts)
{
	int ii, jj;
	for(ii = 0; ii < num_of_FAs; ii++)
	{
		double* start_point = make1Darray(3);
		make_start_point(start_point);
		for(jj = 0; jj < 3; jj++)
		{
			FA_starts[ind2D(ii, jj, num_of_FAs, 3)] = start_point[jj];
		}
	}
}
