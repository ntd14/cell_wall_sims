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
	double* tmp_sp = make1Darray(3);
	tmp_sp[0] = FA_starting_points[ind2D(0,0,10,3)];
	tmp_sp[1] = FA_starting_points[ind2D(0,1,10,3)];
	tmp_sp[2] = FA_starting_points[ind2D(0,2,10,3)];
	double* init_pos = make3Darray(2*max_build_steps, 5, 2);
	int len_FA = 2*max_build_steps;
	len_FA = new_point_pos((init_pos+ind3D(0,0,0, 2*max_build_steps, 5, 2)), tmp_sp, len_FA, FA1);
	len_FA = new_point_pos((init_pos+ind3D(0,0,1, 2*max_build_steps, 5, 2)), tmp_sp, len_FA, FA1);

	for(ii=0; ii < 2*max_build_steps; ii++)
	{
		printf("%f, ",  init_pos[ind3D(ii, 0, 0, 2*max_build_steps, 5, 2)]);
		printf("%f, ",  init_pos[ind3D(ii, 1, 0, 2*max_build_steps, 5, 2)]);
		printf("%f, ",  init_pos[ind3D(ii, 2, 0, 2*max_build_steps, 5, 2)]);
		printf("%f, ",  init_pos[ind3D(ii, 3, 0, 2*max_build_steps, 5, 2)]);
		printf("%f, \n",init_pos[ind3D(ii, 4, 0, 2*max_build_steps, 5, 2)]);
	}
	printf("\n");
	for(ii=0; ii < 2*max_build_steps; ii++)
	{
		printf("%f, ",  init_pos[ind3D(ii, 0, 1, 2*max_build_steps, 5, 2)]);
		printf("%f, ",  init_pos[ind3D(ii, 1, 1, 2*max_build_steps, 5, 2)]);
		printf("%f, ",  init_pos[ind3D(ii, 2, 1, 2*max_build_steps, 5, 2)]);
		printf("%f, ",  init_pos[ind3D(ii, 3, 1, 2*max_build_steps, 5, 2)]);
		printf("%f, \n",init_pos[ind3D(ii, 4, 1, 2*max_build_steps, 5, 2)]);
	}
}

