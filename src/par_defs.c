/*
 * par_defs.c
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */
#include "par_defs.h"
#include <math.h>

/* define size of problem space in nm */
int length_of_problem_space = 1000;
int height_of_problem_space = 1000;
int depth_of_problem_space = 1000;

/* the maximum number of FA chunks to be used in the positive and negative directions. this is the limit of how many chunks can be in each FA */
int max_build_steps = 500; /* note this is in each direction so *2 to get total*/
/* the number of fibril agregates to be build */
int num_of_FAs = 33;

/*see header file for def of each entry*/
/*part_defs FA1 = {7.0, 1500.0, -0.2 + M_PI/2, M_PI/2, M_PI/4, 0.1};*/
part_defs FA1 = {7.0,  500.0, 0.0, 0.0, 0.0, 0.0};
part_defs LG1 = {7.0,  500.0, 0.0, 0.0, 0.0, 0.0};
part_defs H2O = {7.0, 1000.0, 0.0, 0.0, 0.0, 0.0};
