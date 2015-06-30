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
	/* call to bchains to create the FAs and HCs */
	printf("entering bchain \n");
	FA1.uid_start = li;
	li = bchain(init_coors, FA1, ca_len, li);
	FA1.uid_end = li - 1;
	printf("exiting bchain created %i FA1 \n", FA1.uid_end - FA1.uid_end);
	HC1.uid_start = li;
	li = bchain(init_coors, HC1, ca_len, li);
	HC1.uid_end = li -1;
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
		old_particles[ii].uid = ii; /* not that sure this is needed, may need to add 1 so no uids are zero, change above start and end points to +1 if this is the case */
		old_particles[ii].x = *init_coors_ptr + ind2D(ii,0, plist_len, 3);
		old_particles[ii].y = *init_coors_ptr + ind2D(ii,1, plist_len, 3);
		old_particles[ii].z = *init_coors_ptr + ind2D(ii,2, plist_len, 3);
		old_particles[ii].ptype = pl;
		old_particles[ii].nlistlen = 0;
		old_particles[ii].nlist = &nlist_array[ind2D(ii, 0, plist_len, max_cons)];
	}
}

/*takes non-chain forming particles, H2O only at this stage, and uses a huristic to get the NN list, will only work before deformation and for particles of the same type */
void create_sat_bonds(struct particle* old_particles, int plist_len, struct particle** nlist_array, part_defs* pl)
{
	int ii, jj, kk, ii1, jj1, kk1, ln;
	int pnum = pl->uid_start;
	int ran = (int)(max_ndist/(2*pl->R))+1;
	printf("Thickness of non-chain particles as NNs: %i \n",ran);
	int sl = (int)(length_of_problem_space/(pl->R*2.0) + 1);
	int sh = (int)(height_of_problem_space/(pl->R*2.0) + 1);
	int sd = (int)(depth_of_problem_space/(pl->R*2.0) + 1);
	for(ii=0; ii < sl; ii++)
	{
		for(jj=0;jj < sh; jj++)
		{
			for(kk=0; kk < sd; kk++)
			{
				ln = 0;
				for(ii1 = -1*ran; ii1 <= ran; ii1++)
				{
					for(jj1 = -1*ran; jj1 <= ran; jj1++)
					{
						for(kk1 = -1*ran; kk1 <= ran; kk1++)
						{
							nlist_array[ind2D(pnum, ln, plist_len, max_cons)] = &old_particles[ind3D(ii+ii1, jj+jj1, kk+kk1, sl, sh, sd)];
							if(ind3D(ii+ii1, jj+jj1, kk+kk1, sl, sh, sd) >= 0 && ind3D(ii+ii1, jj+jj1, kk+kk1, sl, sh, sd) <= plist_len)
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
			}
		}
	}
}

/* Finds the particles which have strong inner chain bonds and stores them in the NN list */
void create_chain_bonds(struct particle* old_particles, int plist_len, struct particle** nlist_array, part_defs* pl)
{
	int ii;
	if(pl->max_build_steps < 1)
	{
		printf("not creating chains as particle type %s has max_build_steps <1 \n", pl->name);
		exit(1);
	}

	double dist = get_dist(*old_particles[pl->uid_start].x, *old_particles[pl->uid_start+1].x, *old_particles[pl->uid_start].y, *old_particles[pl->uid_start+1].y, *old_particles[pl->uid_start].z, *old_particles[pl->uid_start+1].z);

	if(dist < 2.1*pl->R && dist > 1.9*pl->R)
	{
		nlist_array[ind2D(pl->uid_start, old_particles[pl->uid_start].nlistlen, plist_len, max_cons)] = &old_particles[pl->uid_start+1];
		old_particles[pl->uid_start].nlistlen = old_particles[pl->uid_start].nlistlen + 1;
	}

	for(ii = pl->uid_start+1; ii < pl->uid_end-1; ii++)
	{
		dist = get_dist(*old_particles[ii].x, *old_particles[ii-1].x, *old_particles[ii].y, *old_particles[ii-1].y, *old_particles[ii].z, *old_particles[ii-1].z);

		if(dist < 2.1*old_particles[ii].ptype->R && dist > 1.9*old_particles[ii].ptype->R)
		{
			nlist_array[ind2D(ii, old_particles[ii].nlistlen, plist_len, max_cons)] = &old_particles[ii-1];
			old_particles[ii].nlistlen = old_particles[ii].nlistlen + 1;
		}

		dist = get_dist(*old_particles[ii].x, *old_particles[ii+1].x, *old_particles[ii].y, *old_particles[ii+1].y, *old_particles[ii].z, *old_particles[ii+1].z);

		if(dist < 2.1*old_particles[ii].ptype->R && dist > 1.9*old_particles[ii].ptype->R)
		{
			nlist_array[ind2D(ii, old_particles[ii].nlistlen, plist_len, max_cons)] = &old_particles[ii+1];
			old_particles[ii].nlistlen = old_particles[ii].nlistlen + 1;
		}
	}

	dist = get_dist(*old_particles[pl->uid_end].x, *old_particles[pl->uid_end-1].x, *old_particles[pl->uid_end].y, *old_particles[pl->uid_end-1].y, *old_particles[pl->uid_end].z, *old_particles[pl->uid_end-1].z);

	if(dist < 2.1*pl->R && dist > 1.9*pl->R)
	{
		nlist_array[ind2D(pl->uid_end, old_particles[pl->uid_end].nlistlen, plist_len, max_cons)] = &old_particles[pl->uid_end-1];
		old_particles[pl->uid_end].nlistlen = old_particles[pl->uid_end].nlistlen + 1;
	}
}





