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
	printf("entering main \n");
	/* calc the number of H2O particles to be used */
	H2O.num_of = (length_of_problem_space/(H2O.R*2) + 1)*(height_of_problem_space/(H2O.R*2) + 1)*(depth_of_problem_space/(H2O.R*2) + 1);
	/* calc total potentiual number of particles */
	int total_num_pls = H2O.num_of + 2*FA1.max_build_steps*FA1.num_of + 2*HC1.max_build_steps*HC1.num_of;

	/* init 2D array of coords */
	double* init_coors = make2Darray(total_num_pls, 3);

	/* call function to fill with init coords */
	printf("entering init data \n");

	int plist_len = create_init_state(init_coors, total_num_pls);
	printf("exiting init data \n");
	printf("%i \n", plist_len);

	/* resize the init_coors array to only hold the particles created */
	init_coors = reduce2Darray(init_coors, plist_len, 3);

	/* init a new array of strcuts to hold each particle that was created */
	struct particle* old_particles = calloc(plist_len,sizeof(struct particle));
	if(old_particles == NULL)
	{
		printf("calloc failed when init particle* old_particles in cell_wall_subsection \n");
	}
	/* init an array to hold updated particle positions. Do this here so that memory is partitioned */
	struct particle* new_particles = calloc(plist_len,sizeof(struct particle));
	if(new_particles == NULL)
	{
		printf("calloc failed when init particle* new_particles in cell_wall_subsection \n");
	}

	/* setup a pointer to the pointer of the coordiante array */
	double** init_coors_ptr = &init_coors;
	/* pass old_particles the particle type and total number of particles to the load particles function
	 * Note the &init_coors_ptr means take the value of the pointer to the pointer to the init coors array and pass it in*/
	load_particle_into_struct(old_particles, init_coors_ptr, &H2O, plist_len);
	load_particle_into_struct(old_particles, init_coors_ptr, &FA1, plist_len);
	load_particle_into_struct(old_particles, init_coors_ptr, &HC1, plist_len);

	create_NN_lists(old_particles, plist_len);

	/* build NN lists */
/*	int ii;
	for(ii=0;ii<plist_len;ii++)
	{
		printf("%i ", old_particles[ii].uid);
		printf("%f ", *old_particles[ii].x);
		printf("%f ", *old_particles[ii].y);
		printf("%f \n", *old_particles[ii].z);
	}*/


	/* at this point have an array of structs "all_particles" in there init positions, before any work is done*/


/*	FILE *allp = fopen("allp.vtk", "w");
	if (allp == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	fprintf(allp, "x, y, z, type \n");
	for(ii = 0; ii < plist_len; ii++)
	{
		fprintf(allp, "%f, ", all_particles[ii].x);
		fprintf(allp, "%f, ", all_particles[ii].y);
		fprintf(allp, "%f, ", all_particles[ii].z);
		fprintf(allp, "%i, \n",all_particles[ii].nlistlen);
	}
	fclose(allp);*/

	free(old_particles);
	old_particles = NULL;
	free(new_particles);
	new_particles = NULL;
	free(init_coors);
	init_coors = NULL;
	printf("end of main \n");
	return 0;
}

