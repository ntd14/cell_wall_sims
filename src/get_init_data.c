/*
 * get_init_data.c
 *
 *  Created on: 21/05/2015
 *      Author: nick
 */

#include "get_init_data.h"
#include "par_defs.h"

/* if statment to call the aproprate functions from here. num_of_C_chains = 1 will be worked on first */

/*make problem space bigger so that we get random arrangment of FA at the boundaries */
double ext_pspace(int length_of_problem_space, int height_of_problem_space)
{
	int ext_length = 1.2*length_of_problem_space;
	int ext_height = 1.2*height_of_problem_space;
	return ext_length, ext_height;
}

/* make a vector of starting points for the FAs in the extended space*/
double* make_FA_start_points(int ext_length, int init_spacing_of_FA)
{
	double FA_start_points[ext_length/init_spacing_of_FA];
	double start_point = 0;
	int ii = 0;
	while (start_point < ext_length)
	{
		FA_start_points[ii] = start_point;
		++ii;
		start_point = start_point + init_spacing_of_FA;
	}
	return FA_start_points;
}

/* function to generate a vector of angles */
/* function to generate new point poisitons based on C geometry
 * from header and angle from function above */

/*function
 * take in FA_start_points
 * loop
 * call fucntion to generate angles
 * call function to calc new point positions
 * update starting points and save
 * loop end
 * return matrix of end/start points for each FA chunk
 */

/*function to calculate centre points and orenetiaon
 * for the poly-elipsoids using the end points from above
 */


double average()
{
	printf("inside average function \n");
	return(a+b)/2;
}
