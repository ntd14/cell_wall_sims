/*
 * global_search.c
 *
 *  Created on: 18/08/2015
 *      Author: nick
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "par_defs.h"
#include "global_search.h"

void search_all_upper(struct particle* old_particles, int plist_len)
{
	int ii, jj;
	for(ii = 0; ii < plist_len; ii++)
	{
		for(jj = ii+1; jj < plist_len; jj++)
		{
			double x = abs(*old_particles[ii].x - *old_particles[jj].x);
			if(x < max_ndist)
			{
				double y = abs(*old_particles[ii].y - *old_particles[jj].y);
				if(y < max_ndist)
				{
					double z = abs(*old_particles[ii].z - *old_particles[jj].z);
					if(z < max_ndist)
					{
						old_particles[ii].nlistlen = old_particles[ii].nlistlen + 1;
						/* update list of NNs */
						old_particles[ii].nlist[old_particles[ii].nlistlen-1] = &old_particles[jj];
						old_particles[jj].nlistlen = old_particles[jj].nlistlen + 1;
						/* update list of NNs */
						old_particles[jj].nlist[old_particles[jj].nlistlen-1] = &old_particles[ii];

					}
				}
			}
		}
	}
	/* search all particles above current to check if they are in contact
	 * if in contact store in nlist of current particle, and update nlistlen
	 * go to upper particle and update nlist and nlistlen
	 * return  to current particle and iteratate up*/
}
