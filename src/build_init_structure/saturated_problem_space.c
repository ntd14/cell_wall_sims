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

int sat_problem_space(double* init_coors, int li, part_defs pl, int alen)
{
	printf("in sat problem space \n");

	int ii, jj, kk;
	for(ii=0; ii < (int)(length_of_problem_space/(pl.R*2.0) + 1); ii++)
	{
		for(jj=0;jj < (int)(height_of_problem_space/(pl.R*2.0) + 1); jj++)
		{
			for(kk=0; kk < (int)(depth_of_problem_space/(pl.R*2.0) + 1) ; kk++)
			{
				init_coors[ind2D(li, 0, alen, 3)] = ii*pl.R*2.0;
				init_coors[ind2D(li, 1, alen, 3)] = jj*pl.R*2.0;
				init_coors[ind2D(li, 2, alen, 3)] = kk*pl.R*2.0;
				li++;
			}
		}
	}
	printf("leaving sat problem space\n");
	return(li);
}
