/*
 * get_init_data.c
 *
 *  Created on: 21/06/2015
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "make_arrays.h"
#include "par_defs.h"
#include "get_dist_and_check.h"
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
	H2O.uid_end = li -1;
	printf("exited sat problem space, created %i H2O\n", H2O.uid_end - H2O.uid_start);
	printf("entering bchain \n");
	FA1.uid_start = li;
	li = bchain(init_coors, FA1, ca_len, li);
	FA1.uid_end = li - 1;

	FA2.uid_start = li;
	li = bchain_sur(init_coors, FA2, FA1, ca_len, li);
	FA2.uid_end = li - 1;

	printf("exiting bchain created %i FA1 \n", FA1.uid_end - FA1.uid_end);
	HC1.uid_start = li;
	li = bchain(init_coors, HC1, ca_len, li);
	HC1.uid_end = li -1;

	HC2.uid_start = li;
	li = bchain_sur(init_coors, HC2, HC1, ca_len, li);
	HC2.uid_end = li - 1;

	printf("exited bchain created %i HC1 \n", HC1.uid_end - HC1.uid_start);

	printf("leaving get_init_data created %i particles \n", li);
	return(li);
}

/*reciving the value of the pointer to the pointer to the init coors array then taking what it points to
 * (the pointer to the init coors arrray) and adding the aproprate index on to it. This stores the value of the pointer to the
 * approprate coord in the struct.*/
void load_particle_into_struct(struct particle* old_particles, double** init_coors_ptr, part_defs* pl, int plist_len, struct particle** nlist_array)
{
	int ii;
	for(ii = pl->uid_start; ii <= pl->uid_end; ii++)
	{
		old_particles[ii].uid = ii;
		old_particles[ii].x = *init_coors_ptr + ind2D(ii,0, plist_len, 3);
		old_particles[ii].y = *init_coors_ptr + ind2D(ii,1, plist_len, 3);
		old_particles[ii].z = *init_coors_ptr + ind2D(ii,2, plist_len, 3);
		old_particles[ii].ptype = pl;
		old_particles[ii].nlistlen = 0;
		old_particles[ii].nlist = &nlist_array[ind2D(ii, 0, plist_len, max_cons)];
	}
}

/*################## NOTE HERE ############### */
/* ALL FUNCTIONS BELOW THIS POINT ARE NOT USED  AND HAVE BEEN COMMENTED FROM THE HEADER FILE*/

/*takes non-chain forming particles, H2O only at this stage, and uses a huristic to get the NN list, will only work before deformation and for particles of the same type */
void create_sat_bonds(struct particle* old_particles, int plist_len, part_defs* pl)
{
	int ii, jj, kk, ii1, jj1, kk1, ln;
	int ran = (int)(max_ndist/(2*pl->R))+1; /* set the distance inside which to keep particles */
	printf("Thickness of non-chain particles as NNs: %i \n",ran);
	/* get the number of particles along each side */
	int sl = (int)(length_of_problem_space/(pl->R*2.0) + 1);
	int sh = (int)(height_of_problem_space/(pl->R*2.0) + 1);
	int sd = (int)(depth_of_problem_space/(pl->R*2.0) + 1);
	/* first three loops to iterate through the number of particles along each side */
	for(ii=0; ii < sl; ii++)
	{
		for(jj=0;jj < sh; jj++)
		{
			for(kk=0; kk < sd; kk++)
			{
				/*setting the number of particles connections to zero */
				ln = 0;
				/* for loops to cycle through all souronding particles NOTE needs to be changed so that it deals with the boundarys */
				for(ii1 = -1*ran; ii1 <= ran; ii1++)
				{
					for(jj1 = -1*ran; jj1 <= ran; jj1++)
					{
						for(kk1 = -1*ran; kk1 <= ran; kk1++)
						{
							/* store the particle connections in the nlist_array */
							if(ii+ii1 >= 0 && ii+ii1 < sl && jj+jj1 >= 0 && jj+jj1 < sh && kk+kk1 >= 0 && kk+kk1 < sd
									&& ind3D(ii+ii1, jj+jj1, kk+kk1, sl, sh, sd) >= pl->uid_start && ind3D(ii+ii1, jj+jj1, kk+kk1, sl, sh, sd)<=pl->uid_end)
							{
								old_particles[ind3D(ii, jj, kk, sl, sh, sd)].nlist[ln] = &old_particles[ind3D(ii+ii1, jj+jj1, kk+kk1, sl, sh, sd)];

								/* check that the max number of connections is not exceeded */
								if(ind3D(ii+ii1, jj+jj1, kk+kk1, sl, sh, sd) <= plist_len)
								{
									ln++;
								}
								if(ln >= max_cons)
								{
									printf("WARNING: can not track requested connections, increase max_cons or decrease max_ndist \n");
									break;
								}
							}
						}
					}
					old_particles[ind3D(ii, jj, kk, sl, sh, sd)].nlistlen = ln;
				}
			}
		}
	}
}

/* Finds the particles which have strong inner chain bonds and stores them in the NN list */
void create_chain_bonds(struct particle* old_particles, int plist_len, part_defs* pl)
{
	int ii;
	/* check the particle type in question forms chains */
	if(pl->max_build_steps < 1)
	{
		printf("not creating chains as particle type %s has max_build_steps <1 \n", pl->name);
		exit(1);
	}
	/* calc the distance between the first and second element */
	double dist = get_dist(*old_particles[pl->uid_start].x, *old_particles[pl->uid_start+1].x, *old_particles[pl->uid_start].y, *old_particles[pl->uid_start+1].y, *old_particles[pl->uid_start].z, *old_particles[pl->uid_start+1].z);

	/* if 1 diameter appart store the second particle as a particle connection in the first */
	if(dist < 4*pl->R)
	{
		/*old_particles[ind2D(pl->uid_start, old_particles[pl->uid_start].nlistlen, plist_len, max_cons)].nlist[0] = &old_particles[pl->uid_start+1];*/
		/* update the number of connections on the current particle */
		old_particles[pl->uid_start].nlistlen = old_particles[pl->uid_start].nlistlen + 1;
	}
	/* loop over all particles of the given type, note the + and - 1 in as we store both the next and previous particles */
	for(ii = pl->uid_start+1; ii < pl->uid_end-1; ii++)
	{
		/* getting distance between the previous particle and current */
		dist = get_dist(*old_particles[ii].x, *old_particles[ii-1].x, *old_particles[ii].y, *old_particles[ii-1].y, *old_particles[ii].z, *old_particles[ii-1].z);
		printf("%f \n", dist);
		/* check if the previous particle in the sequence is the previous particle in the sequence */
		if(dist < 4*old_particles[ii].ptype->R)
		{
			/*old_particles[ind2D(ii, old_particles[ii].nlistlen, plist_len, max_cons)].nlist[0] = &old_particles[ii-1];*/
			old_particles[ii].nlistlen = old_particles[ii].nlistlen + 1;
		}
		/* get the distance to the next particle */
		dist = get_dist(*old_particles[ii].x, *old_particles[ii+1].x, *old_particles[ii].y, *old_particles[ii+1].y, *old_particles[ii].z, *old_particles[ii+1].z);
		/* check if the next particle is the next one in the sequence */
		if(dist < 4*old_particles[ii].ptype->R)
		{
			/*old_particles[ind2D(ii, old_particles[ii].nlistlen, plist_len, max_cons)].nlist[1] = &old_particles[ii+1];*/
			old_particles[ii].nlistlen = old_particles[ii].nlistlen + 1;
		}
	}
	/* get distance from the last particle in the sequence to the second to last */
	/*dist = get_dist(*old_particles[pl->uid_end].x, *old_particles[pl->uid_end-1].x, *old_particles[pl->uid_end].y, *old_particles[pl->uid_end-1].y, *old_particles[pl->uid_end].z, *old_particles[pl->uid_end-1].z);*/
	/* check if the second to last particle in the sequence is attached to the last particle */
	if(dist < 2.1*pl->R && dist > 1.9*pl->R)
	{
		/*old_particles[ind2D(pl->uid_end, old_particles[pl->uid_end].nlistlen, plist_len, max_cons)].nlist[0] = &old_particles[pl->uid_end-1];*/
		old_particles[pl->uid_end].nlistlen = old_particles[pl->uid_end].nlistlen + 1;
	}
}

void create_chain_surface(struct particle* old_particles, int plist_len, struct particle** nlist_array, part_defs* pl, part_defs* pl_centre)
{
	/*int ii, sid;
	int cp_num = 0;*/

	/* check the particle type in question forms chains */
	if(pl->max_build_steps < 1)
	{
		printf("not creating chains as particle type %s has max_build_steps <1 \n", pl->name);
		exit(1);
	}
	/* pl_centre.start conects to pl.start through to pl.start + pl.max build steps */
	/* pl_centre.start + 1 connects to pl.start + pl.max build steps to pl.start + 2*pl.max build steps */

	/* pl.start +1 connects to pl.start, pl.start + 2, pl.start + pl.max build steps, and -pl.max build steps*/

/*	for(ii = pl_centre->uid_start; ii < pl_centre->uid_end-1; ii++)*/
	/*	{*/
	/*	sid = ii + pl->uid_start;*/
		/* old_particle[ii]->ptype needs assinment generated from pl_centre and pl */
		/* old_particle[ii]->nlist needs assinment generated from the sid list */
		/* old_particle[sid]->ptype and nlist need to be added for the centre particle attachment */
		/* call to function that cycles through the surounding particles, max build steps is the number of the particles in the chain around each pc_centre  */

	/*}*/

	/* cycle through the centre particles, for each one, should be able to get the index for the surounding particles
	 * Get index for first surface particle
	 * store that and the rest of the surface particles in that loop, the loop below and above as sourding paricles to teh centre
	 * go to the fist particle in the loop. store the coorosponding up and down particles and the next one in the list
	 * loop over 1:end -1 and store the previous, next, up down and central particles
	 * go to last particle and store the previous, up, down and central particles.
	 * go to the enxt particle in the central list, check it is connected.
	 *
	 * probably write a function to get all the particle
	 */

}

/* to get an updated NN list, take the current particles NN list then go to each of the particles on the list and get their NN lists.
 * Scan their NN lists for particles that are in contact with the first, and add any that are to the first particles NN list.
 */


