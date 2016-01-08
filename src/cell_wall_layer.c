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
int create_layer(struct particle* p, int num_of_particles)
{
	int sarray_outer[2]; /* [0] number of points to start on the outer surface x axis, [1] y axis */
	int sarray_inner[2]; /* [0] number of points to start on the inner surface x axis, [1] y axis */
	/*call get_num_starting_points_line for the outer and inner surfaces*/
	/* create starting points vector*/
	/*call gen_starting_points to get all of the starting points over the layer on x axis*/
	/* call gen_starting_points to get starting points on y axis*/

	/* propogate the starting points throuhg the layer*/
	return(num_of_particles);
}

