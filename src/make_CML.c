/*
 * make_CML.c
 *
 *  Created on: 12/10/2015
 *      Author: nick
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./helpers/get_ini_vars.h"

#include "./helpers/cart_and_cyl.h"
#include "./helpers/make_arrays.h"
#include "./helpers/normal_dist_gen.h"

#include "make_CML.h"

/*
 * set x as 1, use MFA and trig to calc the multiplier for y. tan(mfa) = y multiplyer (or maybe 1/multipyer)
 *
 * We know the total virtual length of the two starting sides (x + multiplyer * y),
 * and the volume fraction of each constituent
 * so should be able to estimate the number of starting points from
 * num of starting points of ptype = ( total virtual length / volume proportion ) / particle diameter
 *
 * then calc the starting points on the two sides that they are needed sampling from a uniform dist
 *
 * partition the starting points to the bottom and side based on the MFA
 * (if else statements using the sign of the mfa, and the value, < M_PI uses bottom, > M_PI uses top)
 *
 * num of x starting points of ptype = length of x / total vert length * num of starting points of ptype
 * num of y starting points of ptype = vert length of y / total vert length * num of starting points of ptype
 *
 * x start points pos = sample from uniform dist between 0 and length x by num of x starting points times
 * y start points pos =  sample from uniform dist between 0 and length y by num of y starting points times
*/


/* create a random point inside the ROI */
void CML_point(double* cml_point)
{
	cml_point[0] = P0.rad;/*(P0.rad - P1.rad)*(rand()/(double) RAND_MAX) + P1.rad;*/
	cml_point[1] = vars.ROI_angle*(rand()/(double) RAND_MAX);
	cml_point[2] = 0; /*vars.ROI_height*(rand()/(double) RAND_MAX); */
}

/* call CML_point to make the isotropic CML */
int create_CML(struct particle* p, int num_of_particles)
{

	/* calculate the number of FA0s and H2Os in the CML by there volume fractions */
	/* need to update this to use the interp functions for now just using P0 values */

	/*
	 * calculate the number of FAs and H2Os in the CML-- not the straight foward because they are spheres so dont pack well -- http://www2.latech.edu/~jkanno/packing.pdf --
	 * loop through calling CML_point for each particle and designating it either FA0 of H2O
	 * global search to find all connections
	 * To terminate maybe use a number/proportion of new particles pushed outside the boundary instead of trying to predict the number using a packing function
	 * */
	double v1 = M_PI * P0.rad * P0.rad * vars.ROI_height;
	double v2 = M_PI * P1.rad * P1.rad * vars.ROI_height;
	double CML_vol = (v1 - v2) * (vars.ROI_angle)/(2*M_PI);

	double FA0_occupied_vol = CML_vol * P0.FA_content;
	double H2O_occupied_vol = CML_vol * (1 - P0.FA_content);
	double FA0_p_vol = pow((vars.FA_dia/2), 2) * M_PI;
	double H2O_p_vol = pow((vars.H2O_dia/2), 2) * M_PI;

	/* assume a packing desntiy of say 0.6? */
	int num_of_FA0s = (int) (0.6*FA0_occupied_vol)/FA0_p_vol;
	int num_of_H2Os = (int) (0.6*H2O_occupied_vol)/H2O_p_vol;

	int update_pos_counter = 0;

	/* get init starting points currently assuming a full round cell*/
/*
	int iif = 0;
	int iih = 0;
	double carray[3];

	while(update_pos_counter <= vars.max_particles &&
			(iif < num_of_FA0s ||  iih < num_of_H2Os))
	{
		if(iif < num_of_FA0s)
		{
			CML_point(carray);
			p[update_pos_counter].uid = update_pos_counter;
			p[update_pos_counter].r = carray[0];
			p[update_pos_counter].theta = carray[1];
			p[update_pos_counter].h = carray[2];
			p[update_pos_counter].ptype = "FA0";
			iif++;
			update_pos_counter++;
		}

		if(iih < num_of_H2Os)
		{
			CML_point(carray);
			p[update_pos_counter].uid = update_pos_counter;
			p[update_pos_counter].r = carray[0];
			p[update_pos_counter].theta = carray[1];
			p[update_pos_counter].h = carray[2];
			p[update_pos_counter].ptype = "H2O";
			iih++;
			update_pos_counter++;
		}
*/

/*		if(update_pos_counter%10000 == 0)
		{
			printf("pos update \n");
		}
		if(update_pos_counter >= vars.max_particles)
		{
			printf("WARNING: max particles excedded in the CML layer, %i particles\n", update_pos_counter);
			return(num_of_particles + update_pos_counter);
		}
	} */
	printf("%i particles in CML \n", update_pos_counter);
	return(num_of_particles + update_pos_counter);
}

