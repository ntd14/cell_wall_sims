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


int create_init_state(int num_of_H2Os, double* init_H2O_coords, double* init_posFA, double* init_posHC, int total_num_pls, struct particle* p_ptr)
{
	printf("in get init data \n");
	int ii, jj, kk;
	/* create all of the coords for the water particles */
	sat_problem_space(init_H2O_coords, H2O, num_of_H2Os);
	/* make the 3d arrays for the coordinates of chains */
	bchain(init_posFA, FA1);
	bchain(init_posHC, HC1);
	/* moving all of the coordinates from above into the structure setup */

	for(ii = 0; ii < num_of_H2Os; ii++)
	{
		p_ptr[ii].uid = ii;
		p_ptr[ii].x = &init_H2O_coords[ind2D(ii,0,num_of_H2Os,3)];
		p_ptr[ii].y = &init_H2O_coords[ind2D(ii,1,num_of_H2Os,3)];
		p_ptr[ii].z = &init_H2O_coords[ind2D(ii,2,num_of_H2Os,3)];
		p_ptr[ii].ptype = &H2O;
		/* need to some how create a vector of NN particles, and the length of that vector */

		/* call function takes in int x, y, z and array for box ids, and num of layers returns array of bids
		tx = (int)(*p_ptr[ii].x/box_len);
		ty = (int)(*p_ptr[ii].y/box_hei);
		tz = (int)(*p_ptr[ii].z/box_dep);
		bid = ind3D(tx,ty,tz,length_of_problem_space/box_len,height_of_problem_space/box_hei,depth_of_problem_space/box_dep);
		printf("%i \n", bid);*/
	}

	double tol = 0.0000000001;
	for(kk = 0; kk < FA1.num_of; kk++)
	{
		for(jj = 0; jj < 2*FA1.max_build_steps; jj++)
		{
			if(init_posFA[ind3D(jj,0,kk,2*FA1.max_build_steps,3,FA1.num_of)] > tol
					&& init_posFA[ind3D(jj,1,kk,2*FA1.max_build_steps,3,FA1.num_of)] >tol
					&& init_posFA[ind3D(jj,2,kk,2*FA1.max_build_steps,3,FA1.num_of)] >tol)
			{
				p_ptr[ii].uid = ii;
				p_ptr[ii].x = &init_posFA[ind3D(jj,0,kk,2*FA1.max_build_steps,3,FA1.num_of)];
				p_ptr[ii].y = &init_posFA[ind3D(jj,1,kk,2*FA1.max_build_steps,3,FA1.num_of)];
				p_ptr[ii].z = &init_posFA[ind3D(jj,2,kk,2*FA1.max_build_steps,3,FA1.num_of)];
				p_ptr[ii].ptype = &FA1;
				/* need to some how create a vector of NN particles, and the length of that vector */
				ii++;
			}
		}
	}

	for(kk = 0; kk < HC1.num_of; kk++)
	{
		for(jj = 0; jj < 2*HC1.max_build_steps; jj++)
		{
			if(init_posHC[ind3D(jj,0,kk,2*HC1.max_build_steps,3,HC1.num_of)] > tol
					&& init_posHC[ind3D(jj,1,kk,2*HC1.max_build_steps,3,HC1.num_of)] >tol
					&& init_posHC[ind3D(jj,2,kk,2*HC1.max_build_steps,3,HC1.num_of)] >tol)
			{
			p_ptr[ii].uid = ii;
			p_ptr[ii].x = &init_posHC[ind3D(jj,0,kk,2*HC1.max_build_steps,3,HC1.num_of)];
			p_ptr[ii].y = &init_posHC[ind3D(jj,1,kk,2*HC1.max_build_steps,3,HC1.num_of)];
			p_ptr[ii].z = &init_posHC[ind3D(jj,2,kk,2*HC1.max_build_steps,3,HC1.num_of)];
			p_ptr[ii].ptype = &HC1;
			/* need to some how create a vector of NN particles, and the length of that vector */
			ii++;
			}
		}
	}
	/* from here calc and store Slist and Nlists */
	/* storing the number of particles and passing it out to the main function */
	int plist_len = ii;
	printf("leaving get_init_data \n");
	return(plist_len);
}

