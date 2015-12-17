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
void get_num_starting_points_line(int* sarray, double mfa, double r){
	double multi[2];
	get_multiplier(multi, mfa);
	 /*calcs the length of the x axis, with a provisor for the mean MFA, ie a mfa of pi/2 will give x length*/
	double lx = arc_length(r, vars.ROI_angle) * multi[0];
	/*calcs the height with a provisor for the mfa, ie a mfa of 0 will give no y length*/
	double ly = vars.ROI_height * multi[1];
	/*calcs the total length to distribute the particales along when corrected for the mfa*/
	double vl = lx + ly;
	/*clacs the number of points based onthe vertual length above, the proportion of the particle type and its diameter*/
	int nsp = (int) (vl/P0.FA_content)/vars.FA_dia;
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
int create_CML(struct particle* p, int num_of_particles)
{
	/*seting the particle counter to the first particle for this seq, should be 0 for CML*/
	int update_pos_counter = num_of_particles;
	int sarray_outer[2];
	int sarray_inner[2];
	int ii;

	/*getting the number of starting points on the inner and outer edges of the region*/
	get_num_starting_points_line(sarray_outer, P0.MFA, P0.rad);
	get_num_starting_points_line(sarray_inner, P1.MFA, P1.rad);
	/*calc the total number of starting points over the regions x and y surfaces*/
	int sarray[2];
	sarray[0] = ((sarray_outer[0] + sarray_inner[0])/2.0) * (P0.rad - P1.rad);
	sarray[1] = ((sarray_outer[1] + sarray_inner[1])/2.0) * (P0.rad - P1.rad);

	printf("num x points %i \n", sarray[0]);
	printf("num y points %i \n", sarray[1]);

	/*storing the particles that are started on the x surface*/
	for(ii = 0; ii < sarray[0]; ii++){
		p[update_pos_counter].uid = update_pos_counter;
		p[update_pos_counter].r = P0.rad;/*needs to be sampled from a linear distribution between the inner and outer points*/
		p[update_pos_counter].theta = vars.ROI_angle*(rand()/(double) RAND_MAX);
		p[update_pos_counter].h = 0; /*should this have some noise added into it?*/
		p[update_pos_counter].ptype = "FA0";
		update_pos_counter++;
	}
	/*storing the particles that are started on the y axis, ifelse deals with which side of the
	 * ROI they start on based on the direction of the MFA*/
	for(ii = 0; ii < sarray_outer[1]; ii++){
		if(P0.MFA > 0){
			p[update_pos_counter].uid = update_pos_counter;
			p[update_pos_counter].r = P0.rad;/*needs to be sampled from a linear distribution between the inner and outer points*/
			p[update_pos_counter].theta = 0;/*should this have some noise added into it?*/
			p[update_pos_counter].h = vars.ROI_height*(rand()/(double) RAND_MAX);
			p[update_pos_counter].ptype = "FA0";
			update_pos_counter++;
		}else{
			p[update_pos_counter].uid = update_pos_counter;
			p[update_pos_counter].r = P0.rad;/*needs to be sampled from a linear distribution between the inner and outer points*/
			p[update_pos_counter].theta = vars.ROI_angle; /*should this have some noise added into it?*/
			p[update_pos_counter].h = vars.ROI_height*(rand()/(double) RAND_MAX);
			p[update_pos_counter].ptype = "FA0";
			update_pos_counter++;
		}
	}

	if(update_pos_counter - num_of_particles != (sarray_outer[0] + sarray_outer[1])){
		printf("warning update_pos_counter = %i while sarray has ", update_pos_counter);
		printf("%i points \n", (sarray_outer[0] + sarray_outer[1]));
	}

	printf("%i particles in CML \n", update_pos_counter);
	return(update_pos_counter);
}

