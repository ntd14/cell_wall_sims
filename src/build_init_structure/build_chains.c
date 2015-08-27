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
int bchain(double* coor_array, part_defs pl, int alen, int li)
{
	printf("in bchain \n");
	/* init an array to hold the starting points for all of the chains */
	double* spa = make2Darray(pl.num_of, 3);

	/* get starting points */
	starting_points(spa, pl);
	/* init temp array to store the starting coords for each chain */
	double* tmp_sp = make1Darray(3);

	int ii;
	/* create each chain in turn */
	for(ii = 0; ii < pl.num_of; ii++)
	{
		tmp_sp[0] = spa[ind2D(ii,0,pl.num_of,3)];
		tmp_sp[1] = spa[ind2D(ii,1,pl.num_of,3)];
		tmp_sp[2] = spa[ind2D(ii,2,pl.num_of,3)];

		li = new_point_pos(coor_array, tmp_sp, pl, li, alen);
	}
	free(tmp_sp);
	tmp_sp = NULL;
	free(spa);
	spa = NULL;
	printf("leaving bchain \n");
	return(li);
}

 int bchain_sur(double* coor_array, part_defs pl, part_defs pl_centre, int alen, int li)
 {
	 double dchange = pl_centre.R + pl.R;
	 double achange = 2*M_PI/pl.max_build_steps;
	 double xo;
	 double yo;
	 double zo;
	 double xn0;
	 double yn0;
	 double zn0;
	 double xn1;
	 double yn1;
	 double zn1;
	 int bcp;
	 int ii;

	 for(bcp = pl_centre.uid_start; bcp < pl_centre.uid_end+1; bcp++)
	 {
		 xo = coor_array[ind2D(bcp, 0, alen, 3)];
		 yo = coor_array[ind2D(bcp, 1, alen, 3)];
		 zo = coor_array[ind2D(bcp, 2, alen, 3)];

		 for(ii = 0; ii < pl.max_build_steps; ii++)
		 {
			 xn0 = dchange*cos(ii*achange);
			 yn0 = dchange*sin(ii*achange);
			 zn0 = 0;

			 xn1 = xn0;
			 yn1 = yn0*cos(pl.angle_depth) - zn0*sin(pl.angle_depth);
			 zn1 = yn0*sin(pl.angle_depth) + zn0*cos(pl.angle_depth);

			 xn0 = xn1*cos(pl.angle_MFA) - zn1*sin(pl.angle_MFA);
			 yn0 = yn1;
			 zn0 = xn1*sin(pl.angle_MFA) + zn1*cos(pl.angle_MFA);

			 coor_array[ind2D(li, 0, alen, 3)] = xo + xn0;
			 coor_array[ind2D(li, 1, alen, 3)] = yo + yn0;
			 coor_array[ind2D(li, 2, alen, 3)] = zo + zn0;
			 li++;
		 }
	 }
	 return(li);
 }
