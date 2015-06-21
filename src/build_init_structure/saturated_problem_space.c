/*
 * saturated_problem_space.c
 *
 *  Created on: 21/06/2015
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include "../make_arrays.h"
#include "../par_defs.h"

void sat_problem_space(double* pos, part_defs pl, int len)
	{
		printf("entering sat_problem_space \n");
		int ii, jj, kk, li;
		if(pl.length_pos != pl.length_neg || pl.length_pos != pl.depth_pos || pl.length_pos != pl.depth_neg || pl.length_pos != pl.height_neg || pl.length_pos != pl.height_pos)
		{
			printf("\n warning particle is not a sphere \n");
		}
		li = 0;
		for(ii=0; ii < (length_of_problem_space/(H2O.R_ratio*(H2O.length_pos+H2O.length_neg)) - 1); ii++)
		{
			for(jj=0;jj < (height_of_problem_space/(H2O.R_ratio*(H2O.height_pos+H2O.height_neg)) - 1); jj++)
			{
				for(kk=0; kk < (depth_of_problem_space/(H2O.R_ratio*(H2O.depth_pos+H2O.depth_neg)) - 1); kk++)
				{
					pos[ind2D(li,0,len,3)] = (ii+1)*pl.R_ratio*(pl.length_neg + pl.length_pos);
					pos[ind2D(li,1,len,3)] = (jj+1)*pl.R_ratio*(pl.height_neg + pl.height_pos);
					pos[ind2D(li,2,len,3)] = (kk+1)*pl.R_ratio*(pl.depth_neg + pl.depth_pos);
					li++;
				}
			}
		}
		printf("exiting sat_problem_space \n");
	}
