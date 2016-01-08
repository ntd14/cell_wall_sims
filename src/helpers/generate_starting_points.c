/*
 * generate_starting_points.c
 *
 *  Created on: 3/01/2016
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void gen_uniform(int num_points, double* points_vec){
	int ii;
	for(ii = 0; ii < num_points; ii++){
		points_vec[ii] = (rand()/(double) RAND_MAX);
	}
	printf("uniform %i \n", ii);
}

void gen_tri(int starting_point, int max_points, double* points_vec){
	int ii;
	for(ii = starting_point; ii < max_points; ii++){
		points_vec[ii] = sqrt((rand()/(double) RAND_MAX));
	}
	printf("tri %i \n", ii);
}

void get_biggest_double(double* maxmin){
	double maxmin_out[2];
	if(maxmin[1] > maxmin[0]){
		maxmin_out[0] = maxmin[1];
		maxmin_out[1] = maxmin[0];
	}
	maxmin = maxmin_out;
}
void get_biggest_int(int* maxmin){
	int maxmin_out[2];
	if(maxmin[1] > maxmin[0]){
		maxmin_out[0] = maxmin[1];
		maxmin[1] = maxmin[0];
	}
	maxmin = maxmin_out;
}

void gen_starting_points(int np_inner, int np_outer, double phy_inner, double phy_outer, double* points_vec, int pv_len){
	/*check of np_inner or np_outer is lower, or if the same*/

	int np_maxmin[2];
	np_maxmin[0] = np_inner;
	np_maxmin[1] = np_outer;
	get_biggest_int(np_maxmin);

	double phy_maxmin[2];
	phy_maxmin[0] = np_inner;
	phy_maxmin[1] = np_outer;
	get_biggest_double(phy_maxmin);
	/*call a function to generate random uniform 0-1 numbers and populate points_vec */
	printf("np_min = %i", np_maxmin[1]);
	gen_uniform(np_maxmin[1], points_vec);
	/*call a function to generate a sqrt(random uniform 0-1 distribution) and populate the remaing space in points_vec*/
	gen_tri(np_maxmin[1], np_maxmin[0], points_vec);
	/*transofrm points vec using phy_max and phy_min to give real values*/

	int ii;
	for(ii = 0; ii < pv_len; ii++){
		points_vec[ii] = (phy_maxmin[0] - phy_maxmin[1]) * points_vec[ii] + phy_maxmin[1];
	}
}
