/*
 * get_dist_and_check.c
 *
 *  Created on: 30/06/2015
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "make_arrays.h"
#include "par_defs.h"

double get_dist(double x0, double y0, double z0, double x1, double y1, double z1)
{
	double dist = sqrt(pow((x0 - x1),2) + pow((y0 - y1),2) + pow((z0 - z1),2));
	return(dist);
}
