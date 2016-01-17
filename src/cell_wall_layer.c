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

/* calcs the proportion of points to go the the x and y axis for a unit length */
void get_multiplier(double* multi, double mfa){
	if(vars.ROI_angle > M_PI){
		multi[0] = 1;
		multi[1] = 0;
	}else{
		multi[0] = tan(M_PI/2 - mfa) / (tan(M_PI/2 - mfa) + tan(mfa));
		multi[1] = tan(mfa) / (tan(M_PI/2 - mfa) + tan(mfa));
		printf("multi x = %f, ", multi[0]);
		printf("multi y = %f \n", multi[1]);
	}
}

/*calcs the number of starting points on the x and y axis*/
void get_num_starting_points_line(int* sarray, double mfa, double r, double content){
	double multi[2];
	get_multiplier(multi, mfa);
	 /*calcs the length of the x axis, with a provisor for the mean MFA, ie a mfa of pi/2 will give x length*/
	double lx = arc_length(r, vars.ROI_angle) * multi[0];
	/*calcs the height with a provisor for the mfa, ie a mfa of 0 will give no y length*/
	double ly = vars.ROI_height * multi[1];
	/*calcs the total length to distribute the particales along when corrected for the mfa*/
	double vl = lx + ly;
	/*clacs the number of points based on the vertual length above, the proportion of the particle type and its diameter*/
	int nsp = (int) (vl/content)/vars.FA_dia;
	/*calcs and returns the number of particles to be started on x and y axes*/
	sarray[0] = nsp*multi[0];
	sarray[1] = nsp*multi[1];
}

int add_particles_to_chains(struct particle* p, int start_point, int end_point, struct point Po, struct point Pi){

	int used = 0;
	int update_pos_counter = end_point;
	int ii;
	double start_coords_rtz[3];
	double start_coords_xyz[3];
	double new_coords_rtz[3];
	double new_coords_xyz[3];
	double mfa;
	double mfa_sd;
	double depth_sd;
	double cmfa;
	double cdepth;

	for(ii = start_point; ii < end_point; ii++){
		if((p[ii].theta >= 0) & (p[ii].theta <= vars.ROI_angle) & (p[ii].h >= 0) & (p[ii].h <= vars.ROI_height)){
			start_coords_rtz[0] = p[ii].r;
			start_coords_rtz[1] = p[ii].theta;
			start_coords_rtz[2] = p[ii].h;
			cyl_to_cart(start_coords_rtz, start_coords_xyz); /* convert to cart coords */

			/*call the interp function using r between the two points to get the mfa, mfa_sd and depth_sd*/
			mfa = get_interp_val_P(start_coords_rtz[0], Po.rad, Pi.rad, Po.MFA, Pi.MFA);
			mfa_sd = get_interp_val_P(start_coords_rtz[0], Po.rad, Pi.rad, Po.MFA_SD, Pi.MFA_SD);
			depth_sd = get_interp_val_P(start_coords_rtz[0], Po.rad, Pi.rad, Po.depth_SD, Pi.depth_SD);

			/* call random normal dist function for above to get vals for this chain and step*/
			cmfa = norm_dist_single(mfa, mfa_sd);
			cdepth = norm_dist_single(0, depth_sd);

			/* calc new pos in the cart coords*/
			new_coords_xyz[0] = vars.FA_dia*(sin(cmfa)*cos(cdepth)) + start_coords_xyz[0];
			new_coords_xyz[1] = vars.FA_dia*(sin(cmfa)*sin(cdepth)) + start_coords_xyz[1];
			new_coords_xyz[2] = vars.FA_dia*cos(cmfa) + start_coords_xyz[2];

			/* convert new point back to cyl coords*/
			cart_to_cyl(new_coords_xyz, new_coords_rtz);
			/* add new point to the particles struct */
			p[update_pos_counter].uid = update_pos_counter;
			p[update_pos_counter].ptype = "FA0";
			p[update_pos_counter].r = new_coords_rtz[0];
			p[update_pos_counter].theta = new_coords_rtz[1];
			p[update_pos_counter].h = new_coords_rtz[2];
			update_pos_counter++;
			used++;
		}
	}
	return(used);
}

/*
 * function to take in the inner and outer particle numbers, generate a random number,
 * and apply it to y = mx + c where x is the random number, m is the gradiant between the
 * inner and outer particle numbers and c is the inner rad.
 * return y, the rad of the particle to be generated
 * */

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
	printf("sarray_outer[0] = %i \n", sarray_outer[0]);
	printf("sarray_inner[0] = %i \n", sarray_inner[0]);
	int npy_maxmin[2];/* number of starting points in xy direction at 0 outer and [1] inner */
	npy_maxmin[0] = (int) sarray_outer[1]*((Po.rad - Pi.rad)/vars.FA_dia) + 0.5;
	npy_maxmin[1] = (int) sarray_inner[1]*((Po.rad - Pi.rad)/vars.FA_dia) + 0.5;
	get_biggest_int(npy_maxmin); /* converting so that [0] is max number of points, [1] is min number */

	int pv_len_x = (int) (npx_maxmin[1] + ((npx_maxmin[0]-npx_maxmin[1])/2)); /* calc the total number of starting points in x direction */
	int pv_len_y = (int) (npy_maxmin[1] + ((npy_maxmin[0]-npy_maxmin[1])/2)); /* calc the total number of starting points in y direction */
	printf("npx_maxmin[0] = %i \n", npx_maxmin[0]);
	printf("npx_maxmin[1] = %i \n", npx_maxmin[1]);
	/*set memory aside to store the vector of x starting points*/
	/* create starting points vectors*/
	printf("pv_len_x = %i \n", pv_len_x);
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
	printf("used %i \n", used);
	printf("start_points %i \n", start_point);
	printf("end_points %i \n", end_point);
	update_pos_counter = end_point;
	/* propogate starting points to chains, probably do this in a seperate function?*/

	/*take the starting point, num_of_particles and the end point update_pos_counter and loop between them,
	 * adding one particle to each of the starting points, record the first and last in this sequence
	 * loop between the new start and end of the particles, checking that they are in the ROI and adding
	 * a new particle with a position defined by the previous */

	printf("%i particles in CML \n", update_pos_counter);
	return(update_pos_counter);
}



