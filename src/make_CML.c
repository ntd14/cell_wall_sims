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



/* function that gets vec of random starting points
 * then propgates in either direction from each one
 */

/* create a random point inside the ROI */
void CML_point(double* cml_point)
{
	cml_point[0] = (P0.rad - P1.rad)*(rand()/(double) RAND_MAX) + P1.rad;
	cml_point[1] = vars.ROI_angle*(rand()/(double) RAND_MAX);
	cml_point[2] = vars.ROI_height*(rand()/(double) RAND_MAX);
}

/* call CML_point to make the isotropic CML */
void create_CML(struct particle* p)
{
	/* calculate the number of FA0s and H2Os in the CML by there volume fractions */
	/* need to update this to use the interp functions for now just using P0 values */

	/*
	 * calculate the number of FAs and H2Os in the CML-- not the straight foward because they are spheres so dont pack well -- http://www2.latech.edu/~jkanno/packing.pdf --
	 * loop through calling CML_point for each particle and designating it either FA0 of H2O
	 * global search to find all connections
	 * */
	double v1 = M_PI * P0.rad * P0.rad * vars.ROI_height;
	double v2 = M_PI * P1.rad * P1.rad * vars.ROI_height;
	double CML_vol = (v1 - v2) * (vars.ROI_angle)/(2*M_PI);

	double FA0_occupied_vol = CML_vol * P0.FA_content;
	double H2O_occupied_vol = CML_vol * (1 - P0.FA_content);


}

