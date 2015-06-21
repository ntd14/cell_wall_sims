/*
 * saturated_problem_space.c
 *
 *  Created on: 21/06/2015
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include "../make_arrays.h"
#include "../par_defs.h"

void sat_problem_space(double* pos, part_defs particle, int len)
	{
		printf("entering sat_problem_space \n");
		int ii, jj, kk;
		/* sat_problem_space(init_H2O_coords, part_defs H2O, num_of_H2Os);
		 * check partical is spherical, and print warning if not
		 * start at 000
		 * add length neg in x
		 * add height neg in y
		 * add depth neg in z
		 * put first point
		 *
		 * loop
		 * add length neg + pos in x
		 * 	loop
		 * 		add height neg + pos in y
		 * 		loop
		 * 			add depth neg + pos in z
		 * 			put point
		 */
		printf("exiting sat_problem_space \n");
	}
