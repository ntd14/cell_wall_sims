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
	li = 0;
	for(ii=0; ii < (int)(length_of_problem_space/(pl.R*2.0) + 1); ii++)
	{
		for(jj=0;jj < (int)(height_of_problem_space/(pl.R*2.0) + 1); jj++)
		{
			for(kk=0; kk < (int)(depth_of_problem_space/(pl.R*2.0) + 1); kk++)
			{
				pos[ind2D(li, 0, len, 3)] = ii*pl.R*2.0;
				pos[ind2D(li, 1, len, 3)] = jj*pl.R*2.0;
				pos[ind2D(li, 2, len, 3)] = kk*pl.R*2.0;
				li++;
			}
		}
	}
	printf("exiting sat_problem_space \n");
}
