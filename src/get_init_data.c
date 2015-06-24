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

void create_init_state()
{
	printf("starting get init data \n");
	int ii, jj, kk;

	/* call to box making function note to truncate a value devide by 10 then type cast to an int eg want 34.32452 to go to box 3, (int)(34.32452/10) = 3
	 * can then call the ind3D function with each value and the number of boxes in each direction to get a box id
	 * Another advantage of this is can use ind3D(x+-1,y+-1,z+-1) to get sorunding box ids and shouldnt ever need to store a list of them
	 * just a nabour list of uids, and poentually a seach short list of uids in further away boxes.
	 */

	/* createing the problem space full of water */
	int num_of_H2Os = (int)(length_of_problem_space/(H2O.R*2) + 1)*
						(int)(height_of_problem_space/(H2O.R*2) + 1)*
						(int)(depth_of_problem_space/(H2O.R*2) + 1);

	/*intit array to store h2o coords*/
	double* init_H2O_coords = make2Darray(num_of_H2Os, 3);

	/*init_H2O_coords houses the init coords of the water. */
	sat_problem_space(init_H2O_coords, H2O, num_of_H2Os);

	/* call to function to store particles in boxes with uids, NOTE uid needs to be passed to and from functions, maybe as int* */

	/* starting to build FAs and HCs*/

	/* init an array to store the centre points of all FA particles, note is "large enough" */
	double* init_posFA = make3Darray(2*FA1.max_build_steps, 3, FA1.num_of);
	int len_FA_max = bchain(init_posFA, FA1);

	/* init a new array that is only as large as is needed */
	double* init_FA_coords = make3Darray(len_FA_max, 3, FA1.num_of);

	/* resize the positions array to be as short as the longest FA */
	reduce3Darray(init_posFA, 2*FA1.max_build_steps, 3, FA1.num_of, init_FA_coords, len_FA_max, 3, FA1.num_of);

	/* init an array to store the centre points of all HC particles, note is "large enough" */
	double* init_posHC = make3Darray(2*HC1.max_build_steps, 3, HC1.num_of);
	int len_HC_max = bchain(init_posHC, HC1);

	/* init a new array that is only as large as is needed */
	double* init_HC_coords = make3Darray(len_HC_max, 3, HC1.num_of);

	/* resize the positions array to be as short as the longest FA */
	reduce3Darray(init_posHC, 2*HC1.max_build_steps, 3, HC1.num_of, init_HC_coords, len_HC_max, 3, HC1.num_of);

	/* make hydrated state from above  */
	/* pass init hydrated state to main function */


	/* call to function to create the particles */
	int total_num_pls = num_of_H2Os + len_FA_max*FA1.num_of + len_HC_max*HC1.num_of;
	struct particle *p_ptr[total_num_pls];

	for(ii = 0; ii < num_of_H2Os; ii++)
	{
		p_ptr[ii] = malloc(sizeof(struct particle));
		p_ptr[ii]->uid = ii;
		p_ptr[ii]->x = &init_H2O_coords[ind2D(ii,0,num_of_H2Os,3)];
		p_ptr[ii]->y = &init_H2O_coords[ind2D(ii,1,num_of_H2Os,3)];
		p_ptr[ii]->z = &init_H2O_coords[ind2D(ii,2,num_of_H2Os,3)];
		p_ptr[ii]->ptype = &H2O;
		p_ptr[ii]->nlistlen = 1;
	}
	printf("%i a\n", ii);
	double tol = 0.0000000001;
	for(kk = 0; kk < FA1.num_of; kk++)
	{
		for(jj = 0; jj < len_FA_max; jj++)
		{
			if(init_FA_coords[ind3D(jj,0,kk,len_FA_max,3,FA1.num_of)] > tol
					&& init_FA_coords[ind3D(jj,1,kk,len_FA_max,3,FA1.num_of)] >tol
					&& init_FA_coords[ind3D(jj,2,kk,len_FA_max,3,FA1.num_of)] >tol)
			{
				p_ptr[ii] = malloc(sizeof(struct particle));
				p_ptr[ii]->uid = ii;
				p_ptr[ii]->x = &init_FA_coords[ind3D(jj,0,kk,len_FA_max,3,FA1.num_of)];
				p_ptr[ii]->y = &init_FA_coords[ind3D(jj,1,kk,len_FA_max,3,FA1.num_of)];
				p_ptr[ii]->z = &init_FA_coords[ind3D(jj,2,kk,len_FA_max,3,FA1.num_of)];
				p_ptr[ii]->ptype = &FA1;
				p_ptr[ii]->nlistlen = 2;
				ii++;
			}
		}
	}
	printf("%i b\n", ii);

	for(kk = 0; kk < HC1.num_of; kk++)
	{
		for(jj = 0; jj < len_HC_max; jj++)
		{
			if(init_HC_coords[ind3D(jj,0,kk,len_HC_max,3,FA1.num_of)] > tol
					&& init_HC_coords[ind3D(jj,1,kk,len_HC_max,3,FA1.num_of)] >tol
					&& init_HC_coords[ind3D(jj,2,kk,len_HC_max,3,FA1.num_of)] >tol)
			{

			p_ptr[ii] = malloc(sizeof(struct particle));
			p_ptr[ii]->uid = ii;
			p_ptr[ii]->x = &init_HC_coords[ind3D(jj,0,kk,len_HC_max,3,FA1.num_of)];
			p_ptr[ii]->y = &init_HC_coords[ind3D(jj,1,kk,len_HC_max,3,FA1.num_of)];
			p_ptr[ii]->z = &init_HC_coords[ind3D(jj,2,kk,len_HC_max,3,FA1.num_of)];
			p_ptr[ii]->ptype = &HC1;
			p_ptr[ii]->nlistlen = 3;
			ii++;
			}
		}
	}
	printf("%i c\n", ii);
	int p_ptr_len = ii;

	struct particle *particles_list[p_ptr_len];

	for(ii=0; ii < p_ptr_len; ii++)
	{
		particles_list[ii] = p_ptr[ii];
	}

	for(ii = 0; ii < p_ptr_len; ii++)
	{
		printf("%f ", *particles_list[ii]->x);
		printf("%f ", *particles_list[ii]->y);
		printf("%f ", *particles_list[ii]->z);
		printf("%i \n", particles_list[ii]->nlistlen);
	}

	FILE *allp = fopen("allp.vtk", "w");
	if (allp == NULL)
	{
		    printf("Error opening file!\n");
		    exit(1);
	}
	fprintf(allp, "x, y, z, type,\n");
	for(ii = 0; ii < p_ptr_len; ii++)
	{
		fprintf(allp, "%f, ",  *particles_list[ii]->x);
		fprintf(allp, "%f, ",  *particles_list[ii]->y);
		fprintf(allp, "%f, ",  *particles_list[ii]->z);
		fprintf(allp, "%i, \n",  particles_list[ii]->nlistlen);

	}
	fclose(allp);

	/* writing the different particle types to files in working dir */
/*	FILE *h2o = fopen("h2o.vtk", "w");
	if (h2o == NULL)
	{
		    printf("Error opening file!\n");
		    exit(1);
	}
	fprintf(h2o, "x, y, z, \n");
	for(ii = 0; ii < num_of_H2Os; ii++)
	{
		fprintf(h2o, "%f, ",  init_H2O_coords[ind2D(ii, 0, num_of_H2Os, 3)]);
		fprintf(h2o, "%f, ",  init_H2O_coords[ind2D(ii, 1, num_of_H2Os, 3)]);
		fprintf(h2o, "%f, \n",  init_H2O_coords[ind2D(ii, 2, num_of_H2Os, 3)]);

	}
	fclose(h2o);

	FILE *fa1 = fopen("fa1.vtk", "w");
	if (fa1 == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	fprintf(fa1, "x, y, z, FA_num \n");
	for(ii = 0; ii < FA1.num_of; ii++)
	{
		for(jj = 0; jj < len_FA_max; jj++)
		{
			fprintf(fa1, "%f, ",  init_FA_coords[ind3D(jj, 0, ii, len_FA_max, 3, FA1.num_of)]);
			fprintf(fa1, "%f, ",  init_FA_coords[ind3D(jj, 1, ii, len_FA_max, 3, FA1.num_of)]);
			fprintf(fa1, "%f, ",  init_FA_coords[ind3D(jj, 2, ii, len_FA_max, 3, FA1.num_of)]);
			fprintf(fa1, "%i, \n", ii);
		}
	}
	fclose(fa1);

	FILE *hc1 = fopen("hc1.vtk", "w");
	if (hc1 == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	fprintf(hc1, "x, y, z, HC_num \n");
	for(ii = 0; ii < HC1.num_of; ii++)
	{
		for(jj = 0; jj < len_HC_max; jj++)
		{
			fprintf(hc1, "%f, ",  init_HC_coords[ind3D(jj, 0, ii, len_HC_max, 3, HC1.num_of)]);
			fprintf(hc1, "%f, ",  init_HC_coords[ind3D(jj, 1, ii, len_HC_max, 3, HC1.num_of)]);
			fprintf(hc1, "%f, ",  init_HC_coords[ind3D(jj, 2, ii, len_HC_max, 3, HC1.num_of)]);
			fprintf(hc1, "%i, \n", ii);
		}
	}
	fclose(hc1);
*/
	printf("finished get_init_data \n");
}

