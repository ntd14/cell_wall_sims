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
	double* init_pos = make2Darray(2*max_build_steps, 5);
	int len_FA = new_point_pos(init_pos, tmp_sp, FA1);
	for(ii=0; ii < len_FA; ii++)
	{
		printf("%f, ",init_pos[ind2D(ii, 0, len_FA, 5)]);
		printf("%f, ",init_pos[ind2D(ii, 1, len_FA, 5)]);
		printf("%f, ",init_pos[ind2D(ii, 2, len_FA, 5)]);
		printf("%f, ",init_pos[ind2D(ii, 3, len_FA, 5)]);
		printf("%f, \n",init_pos[ind2D(ii, 4, len_FA, 5)]);
	}

}

