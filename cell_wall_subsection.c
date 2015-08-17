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
	int ii;
	/* calc the number of H2O particles to be used */
	H2O.num_of = (length_of_problem_space/(H2O.R*2) + 1)*(height_of_problem_space/(H2O.R*2) + 1)*(depth_of_problem_space/(H2O.R*2) + 1);
	/* calc total potentiual number of particles, needs updateding if have multiple particles in each chain cross section */

	FA2.num_of = 2*FA1.max_build_steps*FA1.num_of;
	HC2.num_of = 2*HC1.max_build_steps*HC1.num_of;

	int total_num_pls = H2O.num_of + 2*FA1.max_build_steps*FA1.num_of + FA2.num_of*FA2.max_build_steps
			+ 2*HC1.max_build_steps*HC1.num_of + HC2.num_of*HC2.max_build_steps;

	/* init 2D array of coords */
	double* init_coors = make2Darray(total_num_pls, 3);

	/* call function to fill with init coords */
	printf("entering init data \n");

	int plist_len = create_init_state(init_coors, total_num_pls);
	printf("exiting init data \n");
	printf("num of particles %i \n", plist_len);

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
	if(max_cons < 9)
	{
		printf("WARNING: very low max_cons \n");
	}

	struct particle** nlist_array = calloc(plist_len*max_cons,sizeof(struct particle*));
	if(nlist_array == NULL)
	{
		printf("calloc failed when init particle** nlist_array in cell_wall_subsection \n");
	}
	for(ii = 0; ii < plist_len*max_cons; ii++)
	{
		nlist_array[ii] = NULL;
	}
	/* setup a pointer to the pointer of the coordiante array */
	double** init_coors_ptr = &init_coors;
	/* pass old_particles the particle type and total number of particles to the load particles function
	 * Note the &init_coors_ptr means take the value of the pointer to the pointer to the init coors array and pass it in*/
	printf("starting calls to load_particle_into_struct \n");
	load_particle_into_struct(old_particles, init_coors_ptr, &H2O, plist_len, nlist_array);
	load_particle_into_struct(old_particles, init_coors_ptr, &FA1, plist_len, nlist_array);
	load_particle_into_struct(old_particles, init_coors_ptr, &FA2, plist_len, nlist_array);
	load_particle_into_struct(old_particles, init_coors_ptr, &HC1, plist_len, nlist_array);
	load_particle_into_struct(old_particles, init_coors_ptr, &HC2, plist_len, nlist_array);
	printf("finished calls to load_particle_into_struct \n");

	printf("calling create_sat_bonds \n");
	create_sat_bonds(old_particles, plist_len, &H2O);
	printf("finished create_sat_bonds \n");
	/* create the bonds that exist between elements of a chain, will need updating when chains can have multiple elments in the cross section */
	printf("starting calls to create_chain_bonds \n");
	create_chain_bonds(old_particles, plist_len, &FA1); /* creates the strong bonds between chains */
	create_chain_bonds(old_particles, plist_len, &HC1); /* creates the strong bonds between chains */
	printf("finished calls to create_chain_bonds \n");

	int jj;
	FILE *allp = fopen("allp.csv", "w");
	if (allp == NULL)
	{
		   printf("Error opening file!\n");
		   exit(1);
	}

	fprintf(allp, "uid, x, y, z, type, nlistlen, nlist \n");
	for(ii = 0; ii < plist_len; ii++)
	{
		fprintf(allp, "%i, ", old_particles[ii].uid);
		fprintf(allp, "%f, ", *old_particles[ii].x);
		fprintf(allp, "%f, ", *old_particles[ii].y);
		fprintf(allp, "%f, ", *old_particles[ii].z);
		fprintf(allp, "%s, ", old_particles[ii].ptype->name);
		fprintf(allp, "%i, ", old_particles[ii].nlistlen);
/*		if(old_particles[ii].nlistlen > 0)
		{
			for(jj = 0; jj < old_particles[ii].nlistlen -1; jj++)
			{
				fprintf(allp, "%i; ", (*old_particles[ii].nlist[jj]).uid);
			}
			fprintf(allp, "%i ", (*old_particles[ii].nlist[jj]).uid);
		}*/
		fprintf(allp, "\n");
	}
	fclose(allp);




	/*maybe get a new vector of centre points by taking the ones that have been created and translating to new pos.
	 * Then can label them as a new particle type
	 */
	/* build NN lists this should be generic so can be used every time a full problem space search is needed*/

/*	for(ii=0;ii<plist_len;ii++)
	{
		printf("%i ", old_particles[ii].uid);
		printf("%f ", *old_particles[ii].x);
		printf("%f ", *old_particles[ii].y);
		printf("%f ", *old_particles[ii].z);
		printf("%i ", old_particles[ii].nlistlen);

		if(old_particles[ii].nlistlen > 0)
		{
			printf("%i \n", old_particles[ii].nlist[0]->uid);
		}
		else
		{
			printf("NNNNNNNNN \n");
		}
	}


	 at this point have an array of structs "all_particles" in there init positions, before any work is done*/


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

	free(nlist_array);
	nlist_array = NULL;
	free(old_particles);
	old_particles = NULL;
	free(new_particles);
	new_particles = NULL;
	free(init_coors);
	init_coors = NULL;
	printf("end of main \n");
	return 0;
}

