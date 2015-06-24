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

int box_len = 10; /*NOTE the problem space dims must be devidable to ints by the box sizes*/
int box_hei = 10;
int box_dep = 10;

/*see header file for def of each entry*/
part_defs FA1 = {7.0, 1500.0, M_PI/2, M_PI/2, M_PI/4, 0.1, 500, 15}; /* aprox 35% */
part_defs HC1 = {7.0, 1500.0, M_PI/2, M_PI/2, M_PI/4, M_PI/4, 10, 30}; /* aprox 20% */
part_defs H2O = {7.0, 1000.0, 0.0, 0.0, 0.0, 0.0, 0, 0}; /* aprox 30% */
part_defs LG1 = {7.0,  500.0, 0.0, 0.0, 0.0, 0.0, 0, 0}; /* aprox 15% */


