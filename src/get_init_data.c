/*
 * get_init_data.c
 *
 *  Created on: 21/05/2015
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include "make_arrays.h"
#include "par_defs.h"
#include "build_init_structure/make_FA_starting_points.h"
#include "build_init_structure/calc_point_pos_single_FA.h"

void create_init_state()
{
	double* FA_starting_points = make2Darray(num_of_FAs, 3);
	starting_points(FA_starting_points);
	int ii, jj;
	printf("starting points");
	for(ii = 0; ii < 10; ii++)
	{
		printf("\n");
		for(jj = 0; jj < 3; jj++)
		{
			printf("%f ", FA_starting_points[ind2D(ii,jj,10,3)]);
		}
	}
	printf("\n");

}

