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

void create_init_state()
{
	double* FA_starting_points = make2Darray(num_of_FAs, 3);
	starting_points(FA_starting_points);
	int ii, jj;
	for(ii = 0; ii < 10; ii++)
	{
		printf("\n");
		for(jj = 0; jj < 3; jj++)
		{
			printf("%f ", FA_starting_points[ind2D(ii,jj,10,3)]);
		}
	}
}
/*make problem space bigger so that we get random arrangment of FA at the boundaries
 * void ext_pspace(int* ext_dims)
 * caller function needs to define int* ext_dims[3]
 */

/* make a vector of starting points for the FAs in the extended space*/
/* caller function needs to define double FA_start_points[ext_length/init_spacing_of_FA]; */

/*function to calculate the geometric centre of the partical*/

/*function to check if currnet partical geometric centre is inside the ROI*/

/* caller function needs to define: double new_pos[num_of_build_steps][5];
 * as well as generate old_s from make_FA_start_points*/


/*main function to tie it all togeather here.*/

