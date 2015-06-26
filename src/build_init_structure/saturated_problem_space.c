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

int sat_problem_space(double* pos, int li, part_defs pl, int len)
{
	int ii, jj, kk;
	for(ii=0; ii < (int)(length_of_problem_space/(pl.R*2.0) + 1); ii++)
	{
		for(jj=0;jj < (int)(height_of_problem_space/(pl.R*2.0) + 1); jj++)
		{
			for(kk=0; kk < (int)(depth_of_problem_space/(pl.R*2.0) + 1); kk++)
			{
				pos[ind2D(li, 0, len, 4)] = ii*pl.R*2.0;
				pos[ind2D(li, 1, len, 4)] = jj*pl.R*2.0;
				pos[ind2D(li, 2, len, 4)] = kk*pl.R*2.0;
				pos[ind2D(li, 3, len, 4)] = (double)li;
				li++;
			}
		}
	}
	return(li);
}
