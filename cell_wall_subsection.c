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
	int ii;

	/* calc total potentiual number of particles */
	int total_num_pls = H2O.num_of + 2*FA1.max_build_steps*FA1.num_of + 2*HC1.max_build_steps*HC1.num_of;

	/*init a block of mem for the structure that will be filled, note the predetermined max size. */
	struct particle* p_ptr = calloc(total_num_pls,sizeof(struct particle));
	if(p_ptr == NULL)
	{
		printf("calloc failed when init partical* p_ptr in cell_wall_subsection \n");
	}

	/* filling the p_ptr struct with all of the inital particle states and returning the number of particles acually created*/
	int plist_len = create_init_state(H2O.num_of, total_num_pls, p_ptr);
	printf("Number of particles: %i \n", plist_len);

	/* init a new array of strcuts to hold each particle that was created */
	struct particle* all_particles = calloc(plist_len,sizeof(struct particle));
	if(all_particles == NULL)
	{
		printf("calloc failed when init partical* all_particles in cell_wall_subsection \n");
	}

	/* fill the new particle strut array with the created particles Note this substatually reduces the mem used to hold the particle states as is not padded to max num*/
	for(ii = 0;ii<plist_len;ii++)
	{
		all_particles[ii] = p_ptr[ii];
	}

	/* free up the mem from the old structs and set the pointer to NULL*/
	free(p_ptr);
	p_ptr = NULL;
	/* at this point have an array of structs "all_particles" in there init positions, before any work is done*/




/*	for(ii = 0; ii < plist_len;ii++)
	{
		printf("%f ", all_particles[ii].x);
		printf("%f ", all_particles[ii].y);
		printf("%f ", all_particles[ii].z);
		printf("%i \n", all_particles[ii].nlistlen);
	}
	printf("finished get_init_data \n");
	printf("starting write to file \n");*/

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

	printf("write to file finished");
	return 0;
}

