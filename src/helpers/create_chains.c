/*
 * create_chains.c
 *
 *  Created on: 28/01/2016
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./get_ini_vars.h"
#include "./lists.h"
#include "./cart_and_cyl.h"
#include "./normal_dist_gen.h"
#include "./interp_funs.h"
#include "./create_chains.h"

void gen_uniform(int num_points, double* points_vec){
	int ii;
	for(ii = 0; ii < num_points; ii++){
		points_vec[ii] = (rand()/(double) RAND_MAX);
	}
}

void gen_tri(int starting_point, int max_points, double* points_vec){
	int ii;
	max_points = (int) starting_point + (max_points - starting_point)/2;
	for(ii = starting_point; ii < max_points; ii++){
		points_vec[ii] = sqrt((rand()/(double) RAND_MAX));
	}
}

void get_biggest_double(double* maxmin){
	double maxmin_out[2];
	if(maxmin[1] > maxmin[0]){
		maxmin_out[0] = maxmin[1];
		maxmin_out[1] = maxmin[0];
		maxmin[0] = maxmin_out[0];
		maxmin[1] = maxmin_out[1];
	}
}
void get_biggest_int(int* maxmin){
	int maxmin_out[2];
	if(maxmin[1] > maxmin[0]){
		maxmin_out[0] = maxmin[1];
		maxmin_out[1] = maxmin[0];
		maxmin[0] = maxmin_out[0];
		maxmin[1] = maxmin_out[1];
	}

}

void gen_starting_points(int np_inner, int np_outer, double phy_inner, double phy_outer, double* points_vec, int pv_len){
	/*check of np_inner or np_outer is lower, or if the same*/

	int np_maxmin[2];
	np_maxmin[0] = np_inner;
	np_maxmin[1] = np_outer;
	get_biggest_int(np_maxmin);

	double phy_maxmin[2];
	phy_maxmin[0] = phy_inner;
	phy_maxmin[1] = phy_outer;
	get_biggest_double(phy_maxmin);
	/*call a function to generate random uniform 0-1 numbers and populate points_vec */
	gen_uniform(np_maxmin[1], points_vec);
	/*call a function to generate a sqrt(random uniform 0-1 distribution) and populate the remaing space in points_vec*/
	gen_tri(np_maxmin[1], np_maxmin[0], points_vec);
	/*transofrm points vec using phy_max and phy_min to give real values*/

	int ii;
	for(ii = 0; ii < pv_len; ii++){
		points_vec[ii] = (phy_maxmin[0] - phy_maxmin[1]) * points_vec[ii] + phy_maxmin[1];
	}
}

/*calcs the number of starting points on the x and y axis*/
void get_num_starting_points_line(int* sarray, double mfa, double r, double content){

	/* calc height of y * tan (mfa)  this gives the extra length in the x direction that y start points need to compensate for*/
	/* calc the ratio of extra distance to total distance and devide the total number of points, giving the number of points to start on the y axis */
	/*calcs the length of the x axis, with a provisor for the mean MFA, ie a mfa of pi/2 will give x length*/
	double lx = arc_length(r, vars.ROI_angle);
	/*calcs the height with a provisor for the mfa, ie a mfa of 0 will give no y length*/
	double tmp_theta = atan((vars.ROI_height*tan(fabs(mfa)))/r);
	double lx_extra = arc_length(r, tmp_theta); /*might need to convert this to theta then calc the arc length*/
	/*calcs the total length to distribute the particales along when corrected for the mfa*/
	double vl = lx + lx_extra;
	/*clacs the number of points based on the vertual length above, the proportion of the particle type and its diameter*/
	double nsp = (vl*content)/vars.FA_dia;
	/*calcs and returns the number of particles to be started on x and y axes*/
	sarray[0] = (int) nsp*(lx/vl);
	sarray[1] = (int) nsp*(lx_extra/vl);
}

int add_particles_to_chains(struct particle* p, struct particle** nlist_array, int start_point, int end_point, struct point Po, struct point Pi){

	int used = 0;
	int update_pos_counter = end_point;
	int ii;
	double mfa;
	double mfa_sd;
	double depth_sd;
	double cmfa;
	double cdepth;

	double new_r;
	double old_r;
	double tmp_c;
	double delta_theta;
	double new_theta;
	double new_h;

	for(ii = start_point; ii < end_point; ii++){
		if((p[ii].theta >= 0) & (p[ii].theta <= vars.ROI_angle) & (p[ii].h >= 0) & (p[ii].h <= vars.ROI_height)){

			/*call the interp function using r between the two points to get the mfa, mfa_sd and depth_sd*/
			mfa = get_interp_val_P(p[ii].r, Po.rad, Pi.rad, Po.MFA, Pi.MFA);
			mfa_sd = get_interp_val_P(p[ii].r, Po.rad, Pi.rad, Po.MFA_SD, Pi.MFA_SD);

			depth_sd = get_interp_val_P(p[ii].r, Po.rad, Pi.rad, Po.depth_SD, Pi.depth_SD);

			/* call random normal dist function for above to get vals for this chain and step*/
			cmfa = norm_dist_single(mfa, mfa_sd);
			cdepth = norm_dist_single(0, depth_sd); /*need some corection in here so that the mfs dont leave the cell*/

			/* calc new pos in the cart coords*/

			old_r = p[ii].r;
			new_r = old_r + vars.FA_dia*sin(cdepth);
			tmp_c = vars.FA_dia*sin(cmfa);
			delta_theta = acos((pow(old_r, 2) + pow(new_r, 2) - pow(tmp_c, 2) )/(2*old_r*new_r));
			if(cmfa < 0){
				delta_theta = -1*delta_theta;
			}
			new_theta = p[ii].theta + delta_theta;
			new_h = p[ii].h + vars.FA_dia*cos(cmfa)*cos(cdepth);


			/* add new point to the particles struct */
			p[update_pos_counter].uid = update_pos_counter;
			p[update_pos_counter].ptype = "FA0";
			p[update_pos_counter].r = new_r;
			p[update_pos_counter].theta = new_theta;
			p[update_pos_counter].h = new_h;
			p[update_pos_counter].nlist = &nlist_array[update_pos_counter*vars.max_connections];
			p[update_pos_counter].nr = p[update_pos_counter].r;
			p[update_pos_counter].ntheta = p[update_pos_counter].theta;
			p[update_pos_counter].nh = p[update_pos_counter].h;

			update_pos_counter++;
			used++;
		}
	}
	return(used);
}
