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

/*
 * function to take in the inner and outer particle numbers, generate a random number,
 * and apply it to y = mx + c where x is the random number, m is the gradiant between the
 * inner and outer particle numbers and c is the inner rad.
 * return y, the rad of the particle to be generated
 * */

/* call CML_point to make the isotropic CML */
int create_layer(struct particle* p, int num_of_particles)
{
	int ii;
	int update_pos_counter = num_of_particles;
	int sarray_outer[2]; /* [0] number of points to start on the outer surface x axis, [1] y axis */
	int sarray_inner[2]; /* [0] number of points to start on the inner surface x axis, [1] y axis */

	/*call get_num_starting_points_line for the outer and inner surfaces*/
	get_num_starting_points_line(sarray_outer, P0.MFA, P0.rad, P0.FA_content); /*make generic for Px*/
	get_num_starting_points_line(sarray_inner, P1.MFA, P1.rad, P1.FA_content);

	int npx_maxmin[2]; /* number of starting points in x direction at 0 outer and 1 inner */
	npx_maxmin[0] = (int) sarray_outer[0]*((P0.rad - P1.rad)/vars.FA_dia) + 0.5;
	npx_maxmin[1] = (int) sarray_inner[0]*((P0.rad - P1.rad)/vars.FA_dia) + 0.5;
	get_biggest_int(npx_maxmin); /* converting so that 0 is max number of points, 1 is min number */
	int npy_maxmin[2];/* number of starting points in xy direction at 0 outer and 1 inner */
	npy_maxmin[0] = sarray_outer[1]*((P0.rad - P1.rad)/vars.FA_dia) + 0.5;;
	npy_maxmin[1] = sarray_inner[1]*((P0.rad - P1.rad)/vars.FA_dia) + 0.5;;
	get_biggest_int(npx_maxmin); /* converting so that 0 is max number of points, 1 is min number */

	int pv_len_x = (int) (npx_maxmin[1] + ((npx_maxmin[0]-npx_maxmin[1])/2)); /* calc the total number of starting points in x direction */
	int pv_len_y = (int) (npy_maxmin[1] + ((npy_maxmin[0]-npy_maxmin[1])/2)); /* calc the total number of starting points in y direction */

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
	gen_starting_points(npx_maxmin[0], npx_maxmin[1], P1.rad, P0.rad, points_vec_x, pv_len_x);

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
	gen_starting_points(npy_maxmin[0], npy_maxmin[1], P1.rad, P0.rad, points_vec_y, pv_len_y);

	/* storing the particles that are started on the y surface, if statment to deal with the side they start on depending on the MFA */
	for(ii = 0; ii < pv_len_y; ii++){
		p[update_pos_counter].uid = update_pos_counter;
		p[update_pos_counter].r = points_vec_y[ii];/*needs to be sampled from a linear distribution between the inner and outer points*/
		p[update_pos_counter].h = vars.ROI_height*(rand()/(double) RAND_MAX);
		p[update_pos_counter].ptype = "FA0";

		if(P0.MFA > 0){
			p[update_pos_counter].theta = 0;/*should this have some noise added into it?*/
		}else{
			p[update_pos_counter].theta = vars.ROI_angle; /*should this have some noise added into it?*/
		}
		update_pos_counter++;
	}
	free(points_vec_y);
	points_vec_y = NULL;

	/* propogate starting points to chains, probably do this in a seperate function?*/

	printf("%i particles in CML \n", update_pos_counter);
	return(update_pos_counter);
}

