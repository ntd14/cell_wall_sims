/*
 * build_chains.c
 *
 *  Created on: 23/06/2015
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../make_arrays.h"
#include "../par_defs.h"
#include "make_FA_starting_points.h"
#include "../normal_dist_gen.h"
#include "calc_point_pos_single_FA.h"

/* build all chains of particle type pl */
int bchain(double* init_pos, part_defs pl)
{
	/* init an array to hold the starting points for all of the chains */
	double* spa = make2Darray(pl.num_of, 3);
	/* get starting points */
	starting_points(spa, pl);
	/* init temp array to store the starting coords for each chain */
	double* tmp_sp = make1Darray(3);
	/* set init values to keep track of the longest chain */
	int len = 2*pl.max_build_steps;
	int len_max = 0;
	int ii;
	/* create each chain in turn */
	for(ii = 0; ii < pl.num_of; ii++)
	{
		tmp_sp[0] = spa[ind2D(ii,0,pl.num_of,3)];
		tmp_sp[1] = spa[ind2D(ii,1,pl.num_of,3)];
		tmp_sp[2] = spa[ind2D(ii,2,pl.num_of,3)];

		/* return the coordinates for each chunk in current chain */
		len = new_point_pos((init_pos+ind3D(0,0,ii, 2*pl.max_build_steps, 3, pl.num_of)), tmp_sp, pl);

		/* update the max length that a created FA has */
		if(len > len_max)
		{
			len_max = len;
		}
	}
	/* return the length of the longest chain */
	return(len_max);
}
