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
#include "build_init_structure/build_chains.h"

int create_init_state(double* coor_array, int ca_len)
{
	printf("in get init data \n");

	/* intalise the count of particles */
	int li = 0;

	/* distribute the water in the problem space */
	printf("entering sat problem space \n");
	li = sat_problem_space(coor_array, li, H2O, ca_len);
	printf("exited sat problem space, created %i H2O\n", li);
	int li_tmp = li;
	/* call to bchains to create the FAs and HCs */
	printf("entering bchain \n");
	li = bchain(coor_array, FA1, ca_len, li);
	printf("exiting bchain created %i FA1 \n", li-li_tmp);
	li_tmp = li;
	li = bchain(coor_array, HC1, ca_len, li);
	printf("exited bchain created %i HC1 \n", li - li_tmp);

	printf("leaving get_init_data created %i particles \n", li);
	return(li);
}

