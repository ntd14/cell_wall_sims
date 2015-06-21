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
#include "build_init_structure/saturated_problem_space.h"

void create_init_state()
{
	printf("starting get init data \n");
	int ii, jj;
	int num_of_H2Os = (length_of_problem_space/(H2O.R_ratio*(H2O.length_pos+H2O.length_neg)) - 1) /* because we dont want water on the boundaries, this would just add computation */
			*(height_of_problem_space/(H2O.R_ratio*(H2O.height_pos+H2O.height_neg)) - 1)
			*(depth_of_problem_space/(H2O.R_ratio*(H2O.depth_pos+H2O.depth_neg)) - 1);
	double* init_H2O_coords = make2Darray(num_of_H2Os, 3); /* note the call we make here assumes H20 is spherical would need to change the function to relax this*/
	sat_problem_space(init_H2O_coords, H2O, num_of_H2Os);

	double* FA_starting_points = make2Darray(num_of_FAs, 3);
	starting_points(FA_starting_points);
	double* tmp_sp = make1Darray(3);
	double* init_pos = make3Darray(2*max_build_steps, 5, num_of_FAs);
	int len_FA = 2*max_build_steps;
	int len_FA_max = 0;
	for(ii = 0; ii < num_of_FAs; ii++)
	{
		tmp_sp[0] = FA_starting_points[ind2D(ii,0,num_of_FAs,3)];
		tmp_sp[1] = FA_starting_points[ind2D(ii,1,num_of_FAs,3)];
		tmp_sp[2] = FA_starting_points[ind2D(ii,2,num_of_FAs,3)];
		len_FA = new_point_pos((init_pos+ind3D(0,0,ii, 2*max_build_steps, 5, num_of_FAs)), tmp_sp, FA1);
		if(len_FA > len_FA_max)
		{
			len_FA_max = len_FA;
		}
	}
	double* init_FA_coords = make3Darray(len_FA_max, 5, num_of_FAs);
	reduce3Darray(init_pos, 2*max_build_steps, 5, num_of_FAs, init_FA_coords, len_FA_max, 5, num_of_FAs);
/*	for(ii = 0; ii < num_of_FAs; ii++)
	{
		for(jj = 0; jj < len_FA_max; jj++)
		{
			printf("%f, ",  init_FA_coords[ind3D(jj, 0, ii, len_FA_max, 5, num_of_FAs)]);
			printf("%f, ",  init_FA_coords[ind3D(jj, 1, ii, len_FA_max, 5, num_of_FAs)]);
			printf("%f, ",  init_FA_coords[ind3D(jj, 2, ii, len_FA_max, 5, num_of_FAs)]);
			printf("%f, ",  init_FA_coords[ind3D(jj, 3, ii, len_FA_max, 5, num_of_FAs)]);
			printf("%f, \n",init_FA_coords[ind3D(jj, 4, ii, len_FA_max, 5, num_of_FAs)]);
		}
		printf("\n");
	}*/
	FILE *f = fopen("file.vtk", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	fprintf(f, "x, y, z, theta, thi, FA_num \n");
	for(ii = 0; ii < num_of_FAs; ii++)
	{
		for(jj = 0; jj < len_FA_max; jj++)
		{
			fprintf(f, "%f, ",  init_FA_coords[ind3D(jj, 0, ii, len_FA_max, 5, num_of_FAs)]);
			fprintf(f, "%f, ",  init_FA_coords[ind3D(jj, 1, ii, len_FA_max, 5, num_of_FAs)]);
			fprintf(f, "%f, ",  init_FA_coords[ind3D(jj, 2, ii, len_FA_max, 5, num_of_FAs)]);
			fprintf(f, "%f, ",  init_FA_coords[ind3D(jj, 3, ii, len_FA_max, 5, num_of_FAs)]);
			fprintf(f, "%f, ",  init_FA_coords[ind3D(jj, 4, ii, len_FA_max, 5, num_of_FAs)]);
			fprintf(f, "%i, \n", ii);
		}
	}
	fclose(f);
	/* call to a set of functions to distribute water particles among the FAs*/
	/* pass init hydrated state to main function */

	printf("finished get_init_data \n");
}

