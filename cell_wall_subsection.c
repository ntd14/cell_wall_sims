/*
 * twoD_single_pore.c
 *
 *  Created on: 21/05/2015
 *      Author: nick
 *
 *  This is the main trunk file for the implementation of a single 2D cellulose fibril aggregate
 *  pore filling with lignin.
 */

#include <stdio.h>
#include "src/get_init_data.h"
#include "src/build_init_structure.h"
#include "src/main_worker.h"
#include "src/post_processing.h"
#include "src/normal_dist_gen.h"

int main(void) /*this may change to take in arguments later*/
{
	printf("call to call_to_init.c \n");
	double out = average();
	printf("average %g \n", out);
	/*init state matrix is returned*/
	double x, y;
	x = 1;
	y = 2;
	printf("call to build_init_structre.c \n");
	printf("sum %g \n", sum(x,y));
	printf("call to function to do all the work, main_worker.c \n");
	printf("multiply %g \n", mply(x,y));
	printf("call to post_processing.c \n");
	printf("subtract %g \n", subtract(x,y));

	int length_of_vec = 100;
	double vec_of_nums[length_of_vec];
	double mean = 0.175;
	double sd = 0.035;
	norm_dist(vec_of_nums, length_of_vec, mean, sd);
	int ii;
	for(ii = 0; ii <= length_of_vec; ii++)
	{
		printf("%g \n", vec_of_nums[ii]);
	}

	return 0;
}
