/*
 * make_FA_starting_points.c
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */


#include "make_FA_starting_points.h"
#include "../par_defs.h"
/* make a vector of starting points for the FAs in the extended space*/
/* caller function needs to define double FA_start_points[ext_length/init_spacing_of_FA]; */
int make_FA_start_points(int* ext_dims, double* FA_start_points, int array_len)
{
	double start_point = 0.0;
	FA_start_points[0] = start_point;
	int ii = 0;
	while (start_point < ext_dims[0]) /* later will have to add in the other direction */
	{
		ii++;
		start_point = start_point + (double) init_spacing_of_FA;
		FA_start_points[ii] = start_point;
	}
	ii++;
	return ii;
}
