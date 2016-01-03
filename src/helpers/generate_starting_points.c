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

void get_biggest_double(double max, double min){
	int max_in = max;
	int min_in = min;
	if(min_in > max_in){
		max = min_in;
		min = max_in;
	}
}
void get_biggest_int(int* maxmin){
	int max_in = maxmin[0];
	int min_in = maxmin[1];
	if(min_in > max_in){
		maxmin[0] = min_in;
		maxmin[1] = max_in;
	}
}

void gen_starting_points(int np_inner, int np_outer, double phy_inner, double phy_outer, double* points_vec, int pv_len){
	/*check of np_inner or np_outer is lower, or if the same*/
	double phy_max = phy_inner;
	double phy_min = phy_outer;

	int* np_maxmin[2];
	np_maxmin[0] = np_inner;
	np_maxmin[1] = np_outer;
	get_biggest_int(np_maxmin);

	get_biggest_double(phy_max, phy_min);
	/*call a function to generate random uniform 0-1 numbers and populate points_vec */
	printf("np_min = %i", np_maxmin[1]);
	gen_uniform(np_maxmin[1], points_vec);
	/*call a function to generate a sqrt(random uniform 0-1 distribution) and populate the remaing space in points_vec*/
	gen_tri(np_maxmin[1], np_maxmin[0], points_vec);
	/*transofrm points vec using phy_max and phy_min to give real values*/

	int ii;
	for(ii = 0; ii < pv_len; ii++){
		points_vec[ii] = (phy_max - phy_min) * points_vec[ii] + phy_min;
	}
}
