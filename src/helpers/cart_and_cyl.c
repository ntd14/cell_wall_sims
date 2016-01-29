/*
 * cart_and_cyl.c
 *
 *  Created on: 25/09/2015
 *      Author: nick
 */
#include <stdio.h>
#include <math.h>
#include "cart_and_cyl.h"

/* function to convert cartesian xyz coord array to a cylindrical rtz coord array */
void cart_to_cyl(double* xyz_array, double* rtz_array)
{
	rtz_array[0] = sqrt(pow(xyz_array[0], 2) + pow(xyz_array[1], 2));
	rtz_array[1] = atan(xyz_array[1]/xyz_array[0]); /* Be a bit carefull here, may need some logic to deal with a 360 degree body */
	rtz_array[2] = xyz_array[2];
}

/* reverse of above, function converts cylindrical rtz coord array to cartesian coord array xyz */
void cyl_to_cart(double* rtz_array, double* xyz_array)
{
	xyz_array[0] = rtz_array[0]*cos(rtz_array[1]); /* Be a bit carefull here, may need some logic to deal with a 360 degree body */
	xyz_array[1] = rtz_array[0]*sin(rtz_array[1]);
	xyz_array[2] = rtz_array[2];
}

double arc_length(double r, double angle)
{
	double l = 2*r * M_PI * angle / (2*M_PI);
	return l;
}

double calc_dist_between_points(double* a1, double* a2){ /*a[r], a[theta], a[h]*/
	double td = sqrt(pow(a1[0], 2) + pow(a2[0], 2) - 2*a1[0]*a2[0]*cos(a2[1] - a1[1]));
	double hd = a1[2] - a2[2];
	double dist = sqrt(pow(td, 2) + pow(hd, 2));
	return(dist);
}
