/*
 * cell_wall_layer.c
 *
 *  Created on: 8/01/2016
 *      Author: nick
 */



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
#include "./helpers/generate_starting_points.h"
#include "./helpers/interp_funs.h"

#include "cell_wall_layer.h"


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

int add_particles_to_chains(struct particle* p, int start_point, int end_point, struct point Po, struct point Pi){

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

			update_pos_counter++;
			used++;
		}
	}
	return(used);
}

/*Need global search function*/
void global_search(struct particle* p, int start_particles, int end_particles){
	int ii, jj;
	for(ii = start_particles; ii < end_particles; ii++){
		for(jj = ii + 1; jj < end_particles; jj++){
			/*check if p[ii] and p [jj] are close enough to store eachother*/
			/*if they are store the pointer to the other one in the p struct*/
		}
	}
}



/*function to add water to the cell wall. */
int add_water(struct particle* p, int start_particles, int end_particles, struct point Po, struct point Pi){
	int ptot = end_particles;
		/*split ro - ri into h2o.dia +1 chuncks starting at the outer wall, calc the change in theta at that rad to give a movement of 1 dia
		 * split height into h2o.dia +1 chunks starting at the bottom ring, work up to h
		 * once one shell is complete move in 1 rad, recalc the change in theta and do the next shell*/
	int num_of_shells = (int) (Po.rad - Pi.rad)/vars.H2O_dia + 1;
	int num_of_height_chunks = (int) vars.ROI_height / vars.H2O_dia + 1;
	int ii, jj, kk, ll, used;
	int num_particles_at_rad;
	double particle_theta;
	double tmp_coords[3];
	double closest_r = vars.H2O_dia;
	double closest_h = vars.H2O_dia;
	for(ii = 0; ii < num_of_shells; ii++){
		num_particles_at_rad = (int) (arc_length((Po.rad - vars.H2O_dia*ii), vars.ROI_angle) / vars.H2O_dia) + 1;
		particle_theta = (vars.ROI_angle/(num_particles_at_rad - 1));
		for(jj = 0; jj < num_of_height_chunks; jj++){
			for(kk = 0; kk < num_particles_at_rad; kk++){
				/*create tmp particle*/
				tmp_coords[0] = Po.rad - vars.H2O_dia*ii;
				tmp_coords[1] = particle_theta*kk;
				tmp_coords[2] = vars.H2O_dia*jj;
				/*check if tmp particle can be used, if yes add, if no delete*/
				ll = start_particles;
				used = 0;
				while((ll < end_particles) && (used == 0)){
					if((fabs(tmp_coords[0] - p[ll].r) < closest_r) &&
							(fabs(tmp_coords[1] - p[ll].theta) < particle_theta) &&
							(fabs(tmp_coords[2] - p[ll].h) < closest_h)){
						used = 1;
					}
					ll++;
				}
				if(used == 0){
					p[ptot].uid = ptot;
					p[ptot].r = tmp_coords[0];
					p[ptot].theta = tmp_coords[1];
					p[ptot].h = tmp_coords[2]; /*should this have some noise added into it?*/
					p[ptot].ptype = "H2O";
					ptot++;
				}
			}
		}
	}

	return(ptot);
}


/*then add what is currentlty in create_layer to a new function that creates the new points, and deals with water overlaps*/


/*then write create layer to call the above functions and distribute to suitable file structure*/
/* call CML_point to make the isotropic CML */
int create_layer(struct particle* p, int num_of_particles, struct point Po, struct point Pi)
{
	int ii;
	int update_pos_counter = num_of_particles;
	int sarray_outer[2]; /* [0] number of points to start on the outer surface x axis, [1] y axis */
	int sarray_inner[2]; /* [0] number of points to start on the inner surface x axis, [1] y axis */

	/*call get_num_starting_points_line for the outer and inner surfaces*/
	get_num_starting_points_line(sarray_outer, Po.MFA, Po.rad, Po.FA_content); /*make generic for Px*/
	get_num_starting_points_line(sarray_inner, Pi.MFA, Pi.rad, Pi.FA_content);

	int npx_maxmin[2]; /* number of starting points in x direction at [0] outer and [1] inner */
	npx_maxmin[0] = (int) sarray_outer[0]*((Po.rad - Pi.rad)/vars.FA_dia) + 0.5;
	npx_maxmin[1] = (int) sarray_inner[0]*((Po.rad - Pi.rad)/vars.FA_dia) + 0.5;
	get_biggest_int(npx_maxmin); /* converting so that [0] is max number of points, [1] is min number */
	int npy_maxmin[2];/* number of starting points in xy direction at 0 outer and [1] inner */
	npy_maxmin[0] = (int) sarray_outer[1]*((Po.rad - Pi.rad)/vars.FA_dia) + 0.5;
	npy_maxmin[1] = (int) sarray_inner[1]*((Po.rad - Pi.rad)/vars.FA_dia) + 0.5;
	get_biggest_int(npy_maxmin); /* converting so that [0] is max number of points, [1] is min number */

	int pv_len_x = (int) (npx_maxmin[1] + ((npx_maxmin[0]-npx_maxmin[1])/2)); /* calc the total number of starting points in x direction */
	int pv_len_y = (int) (npy_maxmin[1] + ((npy_maxmin[0]-npy_maxmin[1])/2)); /* calc the total number of starting points in y direction */

	/*set memory aside to store the vector of x starting points*/
	/* create starting points vectors*/
	double *points_vec_x = calloc(pv_len_x, sizeof(double));
	if(points_vec_x == NULL)
	{
		printf("calloc failed creating points_vec_x in make_CML \n");
		printf("exiting code, possibly due to lack of memory for given perameters \n");
		exit(0);
	}

	/* call gen_starting_points to get all of the starting points over the layer on x axis*/
	gen_starting_points(npx_maxmin[0], npx_maxmin[1], Pi.rad, Po.rad, points_vec_x, pv_len_x);

	/*storing the particles that are started on the x surface*/
	for(ii = 0; ii < pv_len_x; ii++){
		p[update_pos_counter].uid = update_pos_counter;
		p[update_pos_counter].r = points_vec_x[ii];
		p[update_pos_counter].theta = vars.ROI_angle*(rand()/(double) RAND_MAX);
		p[update_pos_counter].h = 0; /*should this have some noise added into it?*/
		p[update_pos_counter].ptype = "FA0";
		update_pos_counter++;
	}
	free(points_vec_x);
	points_vec_x = NULL;


	double* points_vec_y = calloc(pv_len_y, sizeof(double));
	if(points_vec_y == NULL)
	{
		printf("calloc failed creating points_vec_y in make_CML \n");
		printf("exiting code, possibly due to lack of memory for given perameters \n");
		exit(0);
	}


	/* call gen_starting_points to get starting points on y axis*/
	gen_starting_points(npy_maxmin[0], npy_maxmin[1], Pi.rad, Po.rad, points_vec_y, pv_len_y);

	/* storing the particles that are started on the y surface, if statment to deal with the side they start on depending on the MFA */
	for(ii = 0; ii < pv_len_y; ii++){
		p[update_pos_counter].uid = update_pos_counter;
		p[update_pos_counter].r = points_vec_y[ii];
		p[update_pos_counter].h = vars.ROI_height*(rand()/(double) RAND_MAX);
		p[update_pos_counter].ptype = "FA0";

		if((Po.MFA + Pi.MFA)/2 > 0){
			p[update_pos_counter].theta = 0;/*should this have some noise added into it?*/
		}else{
			p[update_pos_counter].theta = vars.ROI_angle; /*should this have some noise added into it?*/
		}
		update_pos_counter++;
	}
	free(points_vec_y);
	points_vec_y = NULL;

	int start_point = num_of_particles;
	int end_point = update_pos_counter;
	int used = 1;
	while(used > 0){
		used = add_particles_to_chains(p, start_point, end_point, Po, Pi);
		start_point = start_point + used;
		end_point = end_point + used;
	}

	update_pos_counter = end_point;

	/*call to function that adds water in available spaces*/
	update_pos_counter = add_water(p, num_of_particles, update_pos_counter, Po, Pi);

	/*call to search function which finds all connections and stores them*/

	return(update_pos_counter);
}



