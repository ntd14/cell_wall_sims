/*
 * get_init_data.c
 *
 *  Created on: 21/05/2015
 *      Author: nick
 */

#include <stdio.h>
#include "par_defs.h"
#include "build_init_structure/build_ext_space.h"
#include "build_init_structure/make_FA_starting_points.h"
#include "build_init_structure/calc_point_pos_single_FA.h"

void create_init_state()
{
	int ext_dims[3];
	ext_pspace(ext_dims);
	int ii;
	while(ii < 3)
	{
		printf("%i ", ext_dims[ii]);
		ii++;
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

