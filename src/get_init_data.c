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
#include "build_init_structure/make_FA_starting_points.h"
#include "build_init_structure/calc_point_pos_single_FA.h"
#include "build_init_structure/saturated_problem_space.h"
#include "build_init_structure/build_chains.h"

void create_init_state()
{
	printf("starting get init data \n");
	int ii, jj;

	/* createing the problem space full of water */
	int num_of_H2Os = (int)(length_of_problem_space/(H2O.R*2) + 1)*
						(int)(height_of_problem_space/(H2O.R*2) + 1)*
						(int)(depth_of_problem_space/(H2O.R*2) + 1);

	/*intit array to store h2o coords*/
	double* init_H2O_coords = make2Darray(num_of_H2Os, 3);

	/*init_H2O_coords houses the init coords of the water. */
	sat_problem_space(init_H2O_coords, H2O, num_of_H2Os);

	/* starting to build FAs and HCs*/

	/* call to function to create FAs
	 * call to function to create HCs
	 */
/*	double* FA_starting_points = make2Darray(FA1.num_of, 3);*/

	/* call to randomly scatter FA builder starting points matrix called FA_starting_points*/
/*	starting_points(FA_starting_points, FA1); */

	/* init temp array to store the starting point for the current FA */
/*	double* tmp_spFA = make1Darray(3); */

	/* init an array to store the centre points of all FA particles, note is "large enough" */
	double* init_posFA = make3Darray(2*FA1.max_build_steps, 3, FA1.num_of);
	int len_FA_max = bchain(init_posFA, FA1);
	/* seting counters to find the maximum used length  in init_pos */
/*	int len_FA = 2*FA1.max_build_steps;
	int len_FA_max = 0;*/

	/* create each FA in turn */
/*	for(ii = 0; ii < FA1.num_of; ii++)
	{
		tmp_spFA[0] = FA_starting_points[ind2D(ii,0,FA1.num_of,3)];
		tmp_spFA[1] = FA_starting_points[ind2D(ii,1,FA1.num_of,3)];
		tmp_spFA[2] = FA_starting_points[ind2D(ii,2,FA1.num_of,3)];*/

		/* return the coordinates for each FA chunk in curent FA */
	/*	len_FA = new_point_pos((init_posFA+ind3D(0,0,ii, 2*FA1.max_build_steps, 3, FA1.num_of)), tmp_spFA, FA1);*/

		/* update the max length that a created FA has */
	/*	if(len_FA > len_FA_max)
		{
			len_FA_max = len_FA;
		}
	}
*/
	/* init a new array that is only as large as is needed */
	double* init_FA_coords = make3Darray(len_FA_max, 3, FA1.num_of);

	/* resize the positions array to be as short as the longest FA */
	reduce3Darray(init_posFA, 2*FA1.max_build_steps, 3, FA1.num_of, init_FA_coords, len_FA_max, 3, FA1.num_of);

	/* starting to build HCs*/
	double* HC_starting_points = make2Darray(HC1.num_of, 3);

	/* call to randomly scatter HC builder starting points matrix called HC_starting_points*/
	starting_points(HC_starting_points, HC1);

	/* init temp array to store the starting point for the current HC */
	double* tmp_spHC = make1Darray(3);

	/* init an array to store the centre points of all HC particles, note is "large enough" */
	double* init_posHC = make3Darray(2*HC1.max_build_steps, 3, HC1.num_of);
	/* seting counters to find the maximum used length  in init_pos */
	int len_HC = 2*HC1.max_build_steps;
	int len_HC_max = 0;

	/* create each HC in turn */
	for(ii = 0; ii < HC1.num_of; ii++)
	{
		tmp_spHC[0] = HC_starting_points[ind2D(ii,0,HC1.num_of,3)];
		tmp_spHC[1] = HC_starting_points[ind2D(ii,1,HC1.num_of,3)];
		tmp_spHC[2] = HC_starting_points[ind2D(ii,2,HC1.num_of,3)];

		/* return the coordinates for each HC chunk in curent HC */
		len_HC = new_point_pos((init_posHC+ind3D(0,0,ii, 2*HC1.max_build_steps, 3, HC1.num_of)), tmp_spHC, HC1);

		/* update the max length that a created HC has */
		if(len_HC > len_HC_max)
		{
			len_HC_max = len_HC;
		}
	}

	/* init a new array that is only as large as is needed */
	double* init_HC_coords = make3Darray(len_HC_max, 3, HC1.num_of);

	/* resize the positions array to be as short as the longest FA */
	reduce3Darray(init_posHC, 2*HC1.max_build_steps, 3, HC1.num_of, init_HC_coords, len_HC_max, 3, HC1.num_of);



	/* NOTE here somewhere could implement the ability to have multiple chains inside each FA chunk
	 * along with HCs etc inside the chains. Will try to code the project so that this is posable in the future
	 */
	/* NOTE could include HCs bridging FAs here as descrete particles, but using a signifcantly long attraction force to other FAs
	 * should similate their presents implicetly. Draw the geometry with the forces to visuallise. Should even account for
	 * the slip stick mechanisum of clemens, with one or two H bonds holding the FAs from parting, but lots holding from shear.
	 * NOTE johns book pg 41-42 length of xylose 100-200 repeate units he stats xylose is most important. B-D 1,4'xylopyranose backbone units,
	 * is predominantly O-acetyl-4-O-methylglucuronoxylan
	 */

	/* at this point have init_H2O_coords which has the 3d coordinates for all of the water particles in the problem space before
	 * FAs are deposited. Also have init_FA_coords which has the coordinates for each of the FA chunks TO BE deposited
	 * NEXT need to deposit the FAs into the water and remove the displaced water
	 */

/*	FILE *f = fopen("file.vtk", "w");
	if (f == NULL)
	{
		    printf("Error opening file!\n");
		    exit(1);
	}
	fprintf(f, "x, y, z, \n");
	for(ii = 0; ii < num_of_H2Os; ii++)
	{
		fprintf(f, "%f, ",  init_H2O_coords[ind2D(ii, 0, num_of_H2Os, 3)]);
		fprintf(f, "%f, ",  init_H2O_coords[ind2D(ii, 1, num_of_H2Os, 3)]);
		fprintf(f, "%f, \n",  init_H2O_coords[ind2D(ii, 2, num_of_H2Os, 3)]);

	}
	fclose(f);*/
	FILE *f = fopen("file.vtk", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	fprintf(f, "x, y, z, FA_num \n");
	for(ii = 0; ii < FA1.num_of; ii++)
	{
		for(jj = 0; jj < len_FA_max; jj++)
		{
			fprintf(f, "%f, ",  init_FA_coords[ind3D(jj, 0, ii, len_FA_max, 3, FA1.num_of)]);
			fprintf(f, "%f, ",  init_FA_coords[ind3D(jj, 1, ii, len_FA_max, 3, FA1.num_of)]);
			fprintf(f, "%f, ",  init_FA_coords[ind3D(jj, 2, ii, len_FA_max, 3, FA1.num_of)]);
			fprintf(f, "%i, \n", ii);
		}
	}
	fclose(f);

/*	FILE *f = fopen("file.vtk", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	fprintf(f, "x, y, z, HC_num \n");
	for(ii = 0; ii < HC1.num_of; ii++)
	{
		for(jj = 0; jj < len_HC_max; jj++)
		{
			fprintf(f, "%f, ",  init_HC_coords[ind3D(jj, 0, ii, len_HC_max, 3, HC1.num_of)]);
			fprintf(f, "%f, ",  init_HC_coords[ind3D(jj, 1, ii, len_HC_max, 3, HC1.num_of)]);
			fprintf(f, "%f, ",  init_HC_coords[ind3D(jj, 2, ii, len_HC_max, 3, HC1.num_of)]);
			fprintf(f, "%i, \n", ii);
		}
	}
	fclose(f);*/

	/* make hydrated state from above  */
	/* pass init hydrated state to main function */

	printf("finished get_init_data \n");
}

