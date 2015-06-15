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
	int ii, jj, kk;
	double* tmp_sp = make1Darray(3);
	double* init_pos = make3Darray(2*max_build_steps, 5, num_of_FAs);
	int len_FA = 2*max_build_steps;
	int len_FA_old = 0;
	for(ii = 0; ii < num_of_FAs; ii++)
	{
		tmp_sp[0] = FA_starting_points[ind2D(ii,0,num_of_FAs,3)];
		tmp_sp[1] = FA_starting_points[ind2D(ii,1,num_of_FAs,3)];
		tmp_sp[2] = FA_starting_points[ind2D(ii,2,num_of_FAs,3)];
		len_FA = new_point_pos((init_pos+ind3D(0,0,ii, 2*max_build_steps, 5, num_of_FAs)), tmp_sp, len_FA, FA1);
		if(len_FA > len_FA_old)
		{
			len_FA_old = len_FA;
		}
	}
	len_FA = len_FA -1;
	double* init_coords = make3Darray(len_FA, 5, num_of_FAs);
	for(ii=0; ii < len_FA; ii++)
	{
		for(jj=0; jj < 5; jj++)
		{
			for(kk = 0; kk < num_of_FAs; kk++)
			{
				init_coords[ind3D(ii,jj,kk,len_FA,5,num_of_FAs)] = init_pos[ind3D(ii,jj,kk,2*max_build_steps, 5, num_of_FAs)];
			}
		}
	}

	for(ii = 0; ii < num_of_FAs; ii++)
	{
		for(jj = 0; jj < len_FA; jj++)
		{
			printf("%f, ",  init_coords[ind3D(jj, 0, ii, len_FA, 5, num_of_FAs)]);
			printf("%f, ",  init_coords[ind3D(jj, 1, ii, len_FA, 5, num_of_FAs)]);
			printf("%f, ",  init_coords[ind3D(jj, 2, ii, len_FA, 5, num_of_FAs)]);
			printf("%f, ",  init_coords[ind3D(jj, 3, ii, len_FA, 5, num_of_FAs)]);
			printf("%f, \n",init_coords[ind3D(jj, 4, ii, len_FA, 5, num_of_FAs)]);
		}
		printf("\n");
	}
}

