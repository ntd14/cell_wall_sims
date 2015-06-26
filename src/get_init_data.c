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
#include "build_init_structure/make_FA_starting_points.h"
#include "build_init_structure/calc_point_pos_single_FA.h"

int create_init_state(double* coor_array, int ca_len)
{
	printf("in get init data \n");
	/* intalise the count of particles */
	int li = 0;

	/* distribute the water in the problem space */
	li = sat_problem_space(coor_array, li, H2O, ca_len);

	/* move to a seperate function */
	/* get the starting points for each chain type */
	double* FA1_starts = make2Darray(FA1.num_of, 3);
	double* HC1_starts = make2Darray(HC1.num_of, 3);
	starting_points(FA1_starts, FA1);
	starting_points(HC1_starts, HC1);

	double* tmfa = make1Darray(3);
	tmfa[0] = FA1_starts[ind2D(0,0,FA1.num_of,3)];
	tmfa[1] = FA1_starts[ind2D(0,1,FA1.num_of,3)];
	tmfa[2] = FA1_starts[ind2D(0,2,FA1.num_of,3)];

	li = new_point_pos(coor_array, tmfa, FA1, li, ca_len);
	/* move above to a seperate function */
/*	int ii;
	for(ii=510;ii<li;ii++)
	{
		printf("%f ", coor_array[ind2D(ii,0,ca_len,4)]);
		printf("%f ", coor_array[ind2D(ii,1,ca_len,4)]);
		printf("%f ", coor_array[ind2D(ii,2,ca_len,4)]);
		printf("%f \n", coor_array[ind2D(ii,3,ca_len,4)]);
	}*/

	printf("leaving get_init_data \n");
	return(li);
}

