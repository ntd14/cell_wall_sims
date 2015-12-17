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
void get_multiplier(double* multi){
	if(vars.ROI_angle > M_PI){
		multi[0] = 1;
		multi[1] = 0;
	}else{
		multi[0] = tan(M_PI/2 - P0.MFA) / (tan(M_PI/2 - P0.MFA) + tan(P0.MFA));
		multi[1] = tan(P0.MFA) / (tan(M_PI/2 - P0.MFA) + tan(P0.MFA));
		printf("multi x = %f, ", multi[0]);
		printf("multi y = %f \n", multi[1]);
	}
}

/*calcs the number of starting points on the x and y axis*/
void get_num_starting_points(int* sarray){
	double multi[2];
	get_multiplier(multi);
	 /*calcs the length of the x axis, with a provisor for the mean MFA, ie a mfa of pi/2 will give x length*/
	double lx = arc_length(P0.rad, vars.ROI_angle) * multi[0];
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

/* call CML_point to make the isotropic CML */
int create_CML(struct particle* p, int num_of_particles)
{
	/*seting the particle counter to the first particle for this seq, should be 0 for CML*/
	int update_pos_counter = num_of_particles;
	int sarray[2];
	int ii;

	get_num_starting_points(sarray);

	printf("num x points %i \n", sarray[0]);
	printf("num y points %i \n", sarray[1]);

	/*storing the particles that are started on the x axis*/
	for(ii = 0; ii < sarray[0]; ii++){
		p[update_pos_counter].uid = update_pos_counter;
		p[update_pos_counter].r = P0.rad;
		p[update_pos_counter].theta = vars.ROI_angle*(rand()/(double) RAND_MAX);
		p[update_pos_counter].h = 0;
		p[update_pos_counter].ptype = "FA0";
		update_pos_counter++;
	}
	/*storing the particles that are started on the y axis, ifelse deals with which side of the
	 * ROI they start on based on the direction of the MFA*/
	for(ii = 0; ii < sarray[1]; ii++){
		if(P0.MFA > 0){
			p[update_pos_counter].uid = update_pos_counter;
			p[update_pos_counter].r = P0.rad;
			p[update_pos_counter].theta = 0;
			p[update_pos_counter].h = vars.ROI_height*(rand()/(double) RAND_MAX);
			p[update_pos_counter].ptype = "FA0";
			update_pos_counter++;
		}else{
			p[update_pos_counter].uid = update_pos_counter;
			p[update_pos_counter].r = P0.rad;
			p[update_pos_counter].theta = vars.ROI_angle;
			p[update_pos_counter].h = vars.ROI_height*(rand()/(double) RAND_MAX);
			p[update_pos_counter].ptype = "FA0";
			update_pos_counter++;
		}
	}

	if(update_pos_counter - num_of_particles != (sarray[0] + sarray[1])){
		printf("warning update_pos_counter = %i while sarray has ", update_pos_counter);
		printf("%i points \n", (sarray[0] + sarray[1]));
	}

	printf("%i particles in CML \n", update_pos_counter);
	return(update_pos_counter);
}

