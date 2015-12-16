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


double get_multiplier(void){ /* needs more work */
	double multi;
	if(vars.ROI_angle > M_PI){
		multi = 0;
	}else{
		multi = tan(P0.MFA); /*might have to work out how to deal with this if tan assumes first quadrant*/
		printf("multi = %f \n", multi);
	}
	return(multi);
}

void get_num_starting_points(int* sarray){
	double multi = get_multiplier();
	double l = arc_length(P0.rad, vars.ROI_angle);
	double vl = l + multi * vars.ROI_height;
	double nsp = (vl/P0.FA_content)/vars.FA_dia;
	sarray[0] = (int) l / vl * nsp;
	sarray[1] = (int) (vars.ROI_height * multi)/ vl * nsp;
}

/* call CML_point to make the isotropic CML */
int create_CML(struct particle* p, int num_of_particles)
{
	int update_pos_counter = 0;
	int sp_counter = 0;
	int sarray[2];
	int ii;
	get_num_starting_points(sarray);

	double* starting_points = calloc((sarray[0] + sarray[1]), sizeof(double));
	if(starting_points == NULL)
	{
		printf("calloc failed creating starting points array in make_CML \n");
		printf("exiting code \n");
		exit(0);
	}

	printf("%i \n", sarray[0]);
	printf("%i \n", sarray[1]);

	for(ii = 0; ii < sarray[0]; ii++){
		starting_points[update_pos_counter] = vars.ROI_angle*(rand()/(double) RAND_MAX);
		sp_counter++;
	}
	for(ii = 0; ii < sarray[1]; ii++){
		starting_points[update_pos_counter] = vars.ROI_height*(rand()/(double) RAND_MAX);
		sp_counter++;
	}

	if(sp_counter != (sarray[0] + sarray[1])){
		printf("warning update_pos_counter = %i while sarray has ", update_pos_counter);
		printf("%i points \n", (sarray[0] + sarray[1]));
	}

	/*create function to tern the starting points vector into particles */

	printf("%i particles in CML \n", update_pos_counter);
	free(starting_points);
	starting_points = NULL;
	return(num_of_particles + update_pos_counter);
}

