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
}

void gen_tri(int starting_point, int max_points, double* points_vec){
	int ii;
	for(ii = starting_point; ii < max_points; ii++){
		points_vec[ii] = sqrt((rand()/(double) RAND_MAX));
	}
}

void gen_starting_points(int np_inner, int np_outer, double phy_inner, double phy_outer, double* points_vec, int pv_len){
	/*check of np_inner or np_outer is lower, or if the same*/
	double phy_max;
	double phy_min;
	int np_max;
	int np_min;
	if(np_inner > np_outer){
		np_max = np_inner;
		np_min = np_outer;
	}else{
		np_max = np_outer;
		np_min = np_inner;
	}
	if(phy_inner > phy_outer){
		phy_max = phy_inner;
		phy_min = phy_outer;
	}else{
		phy_max = phy_outer;
		phy_min = phy_inner;
	}
	/*call a function to generate random uniform 0-1 numbers and populate points_vec */
	gen_uniform(np_min, points_vec);
	/*call a function to generate a sqrt(random uniform 0-1 distribution) and populate the remaing space in points_vec*/
	gen_tri(np_min, np_max, points_vec);
	/*transofrm points vec using phy_max and phy_min to give real values*/
	int ii;
	for(ii = 0; ii < pv_len; ii++){
		points_vec[ii] = (phy_max - phy_min) * points_vec[ii] + phy_min;
	}
}
