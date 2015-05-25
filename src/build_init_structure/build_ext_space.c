/*
 * build_ext_space.c
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */
#include "build_ext_space.h"
#include "../par_defs.h"
/*make problem space bigger so that we get random arrangment of FA at the boundaries */

void ext_pspace(int* ext_dims)
{
	ext_dims[0] = 1.2*length_of_problem_space;
	ext_dims[1] = 1.2*height_of_problem_space;
	ext_dims[2] = 1.2*depth_of_problem_space;
}
