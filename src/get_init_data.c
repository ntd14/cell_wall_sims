/*
 * get_init_data.c
 *
 *  Created on: 21/06/2015
 *      Author: nick
 */


/*
 * get_init_data.c
 *
 *  Created on: 21/05/2015
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include "make_arrays.h"
#include "par_defs.h"
#include "build_init_structure/saturated_problem_space.h"
#include "build_init_structure/build_chains.h"

int create_init_state(double* 	init_coors, int ca_len)
{
	printf("in get init data \n");

	/* intalise the count of particles */
	int li = 0;
	/* distribute the water in the problem space */
	printf("entering sat problem space \n");
	H2O.uid_start = li;
	li = sat_problem_space(init_coors, li, H2O, ca_len);
	H2O.uid_end = li;
	printf("exited sat problem space, created %i H2O\n", H2O.uid_end - H2O.uid_start);
	/* call to bchains to create the FAs and HCs */
	printf("entering bchain \n");
	FA1.uid_start = li;
	li = bchain(init_coors, FA1, ca_len, li);
	FA1.uid_end = li;
	printf("exiting bchain created %i FA1 \n", FA1.uid_end - FA1.uid_end);
	HC1.uid_start = li;
	li = bchain(init_coors, HC1, ca_len, li);
	HC1.uid_end = li;
	printf("exited bchain created %i HC1 \n", HC1.uid_end - HC1.uid_start);

	printf("leaving get_init_data created %i particles \n", li);
	return(li);
}

/*reciving the value of the pointer to the pointer to the init coors array then taking what it points to
 * (the pointer to the init coors arrray) and adding the aproprate index on to it. This stores the value of the pointer to the
 * approprate coord in the struct.*/
void load_particle_into_struct(struct particle* old_particles, double** init_coors_ptr, part_defs pl, int plist_len)
{
	int ii;
	for(ii = pl.uid_start; ii < pl.uid_end; ii++)
	{
		old_particles[ii].x = *init_coors_ptr + ind2D(ii,0, plist_len, 3);
		old_particles[ii].y = *init_coors_ptr + ind2D(ii,1, plist_len, 3);
		old_particles[ii].z = *init_coors_ptr + ind2D(ii,2, plist_len, 3);
		old_particles[ii].uid = ii;
		old_particles[ii].ptype = &pl;
	}
}

