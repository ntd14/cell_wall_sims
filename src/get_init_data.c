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


int create_init_state(int num_of_H2Os, int total_num_pls, struct particle* p_ptr)
{
	printf("in get init data \n");
	int ii, jj, kk;

	double* init_H2O_coords = make2Darray(num_of_H2Os, 3);

	double* init_posFA  = calloc(2*FA1.max_build_steps*3*FA1.num_of,sizeof(double));
	if(init_posFA == NULL)
	{
		printf("make2Darray failed in calloc");
	}
	/*double* init_posFA = make3Darray(2*FA1.max_build_steps, 3, FA1.num_of);*/
	double* init_posHC = make3Darray(2*HC1.max_build_steps, 3, HC1.num_of);

	/* create all of the coords for the water particles */
	sat_problem_space(init_H2O_coords, H2O, num_of_H2Os);
	/* make the 3d arrays for the coordinates of chains */
	bchain(init_posFA, FA1);
	bchain(init_posHC, HC1);
	/* moving all of the coordinates from above into the structure setup */

	for(ii = 0; ii < num_of_H2Os; ii++)
	{
		p_ptr[ii].uid = ii;
		p_ptr[ii].x = init_H2O_coords[ind2D(ii,0,num_of_H2Os,3)];
		p_ptr[ii].y = init_H2O_coords[ind2D(ii,1,num_of_H2Os,3)];
		p_ptr[ii].z = init_H2O_coords[ind2D(ii,2,num_of_H2Os,3)];
		p_ptr[ii].ptype = H2O;
		p_ptr[ii].nlistlen = 0;
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
				p_ptr[ii].nlistlen = 0;
				p_ptr[ii].uid = ii;
				p_ptr[ii].x = init_posFA[ind3D(jj,0,kk,2*FA1.max_build_steps,3,FA1.num_of)];
				p_ptr[ii].y = init_posFA[ind3D(jj,1,kk,2*FA1.max_build_steps,3,FA1.num_of)];
				p_ptr[ii].z = init_posFA[ind3D(jj,2,kk,2*FA1.max_build_steps,3,FA1.num_of)];
				p_ptr[ii].ptype = FA1;

				if(jj != 0)
				{
					p_ptr[ii-1].nlistlen = 1;
					p_ptr[ii-1].nlist[0] = &p_ptr[ii].uid;
					p_ptr[ii-1].nltype[0] = &FA1FA1strong;
				}
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
				p_ptr[ii].nlistlen = 0;
				p_ptr[ii].uid = ii;
				p_ptr[ii].x = init_posHC[ind3D(jj,0,kk,2*HC1.max_build_steps,3,HC1.num_of)];
				p_ptr[ii].y = init_posHC[ind3D(jj,1,kk,2*HC1.max_build_steps,3,HC1.num_of)];
				p_ptr[ii].z = init_posHC[ind3D(jj,2,kk,2*HC1.max_build_steps,3,HC1.num_of)];
				p_ptr[ii].ptype = HC1;
				if(jj != 0)
				{
					p_ptr[ii-1].nlistlen = 1;
					p_ptr[ii-1].nlist[0] = &p_ptr[ii].uid;
					p_ptr[ii-1].nltype[0] = &HC1HC1strong;
				}
				ii++;
			}
		}
	}
	int plist_len = ii;

/*	for(kk = 0; kk < FA1.num_of; kk++)
	{
		for(jj = 0; jj < 2*FA1.max_build_steps; jj++)
		{
			if(init_posFA[ind3D(jj,0,kk,2*FA1.max_build_steps,3,FA1.num_of)] > tol
					&& init_posFA[ind3D(jj,1,kk,2*FA1.max_build_steps,3,FA1.num_of)] >tol
					&& init_posFA[ind3D(jj,2,kk,2*FA1.max_build_steps,3,FA1.num_of)] >tol)
			{

				printf("%f ", init_posFA[ind3D(jj,0,kk,2*FA1.max_build_steps,3,FA1.num_of)]);
				printf("%f ", init_posFA[ind3D(jj,1,kk,2*FA1.max_build_steps,3,FA1.num_of)]);
				printf("%f \n", init_posFA[ind3D(jj,2,kk,2*FA1.max_build_steps,3,FA1.num_of)]);

			}
		}
	}*/

/*	for(ii = 0; ii < plist_len; ii++)
	{*/
		/* pass function ii and plist_len, this is the uid
		 * inside function get coords and ptype
		 * search upward for coords inside +- max_ndist
		 * IF inside range store uid in array as p_ptr[ii].nlist
		 * also store particale type in array of con_defs* as p_ptr[ii].nltype
		 *
		 * maybe do slist using 3*max_ndist or something
		 */
	/*}*/

	printf("leaving get_init_data \n");
	return(plist_len);
}

