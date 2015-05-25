/*
 * get_init_data.c
 *
 *  Created on: 21/05/2015
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include "par_defs.h"
#include "build_init_structure/build_ext_space.h"
#include "build_init_structure/make_FA_starting_points.h"
#include "build_init_structure/calc_point_pos_single_FA.h"

void create_init_state()
{
	int ext_dims[3];
	ext_pspace(ext_dims);
	int ii = 0;
	while(ii < 3)
	{
		printf("%i ", ext_dims[ii]);
		ii++;
	}
	int FAstart_len =  ext_dims[0]/init_spacing_of_FA + init_spacing_of_FA;
	double* FA_start_points = malloc(FAstart_len * sizeof(double));
	/*malloc check */
	int FA_end_len = 0;
	FA_end_len = make_FA_start_points(ext_dims, FA_start_points, FA_end_len);
	FA_start_points = realloc(FA_start_points, FA_end_len*sizeof(double));
	/*realloc check*/
	ii = 0;
	while(ii < FA_end_len)
	{
		printf("\n %g ", FA_start_points[ii]);
		ii++;
	}
/* call to calc_point_pos_single_FA.h > then create all of the init chains, still dont know how */
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

