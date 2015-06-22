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

void create_init_state()
{
	printf("starting get init data \n");
	int ii, jj;

	/* createing the problem space full of water */
	int num_of_H2Os = (length_of_problem_space/(H2O.R*2) + 1)*(height_of_problem_space/(H2O.R*2) + 1)*(depth_of_problem_space/(H2O.R*2) + 1);

	/*intit array to store h2o coords*/
	double* init_H2O_coords = make2Darray(num_of_H2Os, 3);

	/*init_H2O_coords houses the init coords of the water. */
	sat_problem_space(init_H2O_coords, H2O, num_of_H2Os);

	/* starting to build FAs*/
	double* FA_starting_points = make2Darray(num_of_FAs, 3);

	/* call to randomly scatter FA builder starting points matrix called FA_starting_points*/
	starting_points(FA_starting_points);

	/* init temp array to store the starting point for the current FA */
	double* tmp_sp = make1Darray(3);

	/* init an array to store the centre points of all FA particles, note is "large enough" */
	double* init_pos = make3Darray(2*max_build_steps, 3, num_of_FAs);
	/* seting counters to find the maximum used length  in init_pos */
	int len_FA = 2*max_build_steps;
	int len_FA_max = 0;

	/* create each FA in turn */
	for(ii = 0; ii < num_of_FAs; ii++)
	{
		tmp_sp[0] = FA_starting_points[ind2D(ii,0,num_of_FAs,3)];
		tmp_sp[1] = FA_starting_points[ind2D(ii,1,num_of_FAs,3)];
		tmp_sp[2] = FA_starting_points[ind2D(ii,2,num_of_FAs,3)];

		/* return the coordinates for each FA chunk in curent FA */
		len_FA = new_point_pos((init_pos+ind3D(0,0,ii, 2*max_build_steps, 3, num_of_FAs)), tmp_sp, FA1);

		/* update the max length that a created FA has */
		if(len_FA > len_FA_max)
		{
			len_FA_max = len_FA;
		}
	}

	/* init a new array that is only as large as is needed */
	double* init_FA_coords = make3Darray(len_FA_max, 3, num_of_FAs);

	/* resize the positions/orentations array to be as short as the longest FA */
	reduce3Darray(init_pos, 2*max_build_steps, 3, num_of_FAs, init_FA_coords, len_FA_max, 3, num_of_FAs);
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
	 * FAs are deposited. Also have init_FA_coords which has the coordinates and orentations for each of the FA chunks TO BE deposited
	 * NEXT need to deposit the FAs into the water and remove the displaced water
	 */
/*	for(ii = 0; ii < num_of_FAs; ii++)
	{
		for(jj = 0; jj < len_FA_max; jj++)
		{
			printf("%f, ",  init_FA_coords[ind3D(jj, 0, ii, len_FA_max, 3, num_of_FAs)]);
			printf("%f, ",  init_FA_coords[ind3D(jj, 1, ii, len_FA_max, 3, num_of_FAs)]);
			printf("%f, \n",  init_FA_coords[ind3D(jj, 2, ii, len_FA_max, 3, num_of_FAs)]);
		}
		printf("\n");
	}*/
/*	FILE *f = fopen("file.vtk", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	fprintf(f, "x, y, z, FA_num \n");
	for(ii = 0; ii < num_of_FAs; ii++)
	{
		for(jj = 0; jj < len_FA_max; jj++)
		{
			fprintf(f, "%f, ",  init_FA_coords[ind3D(jj, 0, ii, len_FA_max, 3, num_of_FAs)]);
			fprintf(f, "%f, ",  init_FA_coords[ind3D(jj, 1, ii, len_FA_max, 3, num_of_FAs)]);
			fprintf(f, "%f, ",  init_FA_coords[ind3D(jj, 2, ii, len_FA_max, 3, num_of_FAs)]);
			fprintf(f, "%i, \n", ii);
		}
	}
	fclose(f);*/

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

	/* make hydrated state from above  */
	/* pass init hydrated state to main function */

	printf("finished get_init_data \n");
}

