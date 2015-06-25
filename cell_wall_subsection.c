/*
 * twoD_single_pore.c
 *
 *  Created on: 21/05/2015
 *      Author: nick
 *
 *  This is the main trunk file for the implementation of a single 2D cellulose fibril aggregate
 *  pore filling with lignin.
 */

#include <stdio.h>
#include <stdlib.h>
#include "src/par_defs.h"
#include "src/make_arrays.h"
#include "src/get_init_data.h"
#include "src/main_worker.h"
#include "src/post_processing.h"


int main(void) /*this may change to take in arguments later*/
{
	printf("starting get init data \n");
	int num_of_H2Os = (int)(length_of_problem_space/(H2O.R*2) + 1)*
						(int)(height_of_problem_space/(H2O.R*2) + 1)*
						(int)(depth_of_problem_space/(H2O.R*2) + 1);
	double* init_H2O_coords = make2Darray(num_of_H2Os, 3);
	double* init_posFA = make3Darray(2*FA1.max_build_steps, 3, FA1.num_of);
	double* init_posHC = make3Darray(2*HC1.max_build_steps, 3, HC1.num_of);
	int total_num_pls = num_of_H2Os + 2*FA1.max_build_steps*FA1.num_of + 2*HC1.max_build_steps*HC1.num_of;
	/*struct particle p_ptr[total_num_pls];*/

	struct particle* p_ptr = (struct particle*)calloc(total_num_pls,sizeof(struct particle));
	if(p_ptr == NULL)
	{
		printf("calloc failed when init partical* p_ptr in cell_wall_subsection \n");
	}
	int plist_len = create_init_state(num_of_H2Os, init_H2O_coords, init_posFA, init_posHC, total_num_pls, p_ptr);
	printf("%i \n", plist_len);
	int ii;
	struct particle* all_particles = (struct particle*)calloc(total_num_pls,sizeof(struct particle));
	if(all_particles == NULL)
	{
		printf("calloc failed when init partical* all_particles in cell_wall_subsection \n");
	}

	for(ii = 0;ii<plist_len;ii++)
	{
		all_particles[ii] = p_ptr[ii];
	}
	free(p_ptr);
	p_ptr = NULL;
/*	for(ii = 0; ii < plist_len;ii++)
	{
		printf("%f ", *all_particles[ii].x);
		printf("%f ", *all_particles[ii].y);
		printf("%f \n", *all_particles[ii].z);
	}*/
	printf("finished get_init_data \n");
	printf("starting write to file \n");

	FILE *allp = fopen("allp.vtk", "w");
	if (allp == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	fprintf(allp, "x, y, z, type \n");
	for(ii = 0; ii < plist_len; ii++)
	{
		fprintf(allp, "%f, ", *all_particles[ii].x);
		fprintf(allp, "%f, ", *all_particles[ii].y);
		fprintf(allp, "%f, ", *all_particles[ii].z);
		fprintf(allp, "%i, \n",all_particles[ii].nlistlen);
	}
	fclose(allp);
	printf("write to file finished");

/* at this stage have a array of pointers (all_particles) to structs of type particle for each particle in its pre inital state, ie water, FA and HC only, no work done on system */
	return 0;
}

