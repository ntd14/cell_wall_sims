/*
 * get_init_data.c
 *
 *  Created on: 21/05/2015
 *      Author: nick
 */
#include <stdlib.h>
#include "get_init_data.h"
#include "par_defs.h"

/* if statment to call the aproprate functions from here. num_of_C_chains = 1 will be worked on first */

/*make problem space bigger so that we get random arrangment of FA at the boundaries */
/*caller function needs to define int* ext_dims[3]*/
void ext_pspace(int length_of_problem_space, int height_of_problem_space,
		int depth_of_problem_space, int* ext_dims)
{
	ext_dims[0] = 1.2*length_of_problem_space;
	ext_dims[1] = 1.2*height_of_problem_space;
	ext_dims[2] = 1.2*depth_of_problem_space;
}

/* make a vector of starting points for the FAs in the extended space*/
/* caller function needs to define double FA_start_points[ext_length/init_spacing_of_FA]; */
void make_FA_start_points(int ext_length, int init_spacing_of_FA, double* FA_start_points)
{
	double start_point = 0;
	FA_start_points[0] = start_point;
	int ii = 0;
	while (start_point < ext_length) /* later will have to add in the other direction */
	{
		++ii;
		start_point = start_point + init_spacing_of_FA;
		FA_start_points[ii] = start_point;
	}
}

/* uniform random numbers to normal random numbers mean of zero sd of 1.
generate two uniform numbers and from those you get
two normally distributed numbers. Return one, save the other
for the next request of a random number.

float x1, x2, w, y1, y2;
while ( w >= 1.0 )
{
    x1 = 2.0 * ranf() - 1.0;
    x2 = 2.0 * ranf() - 1.0;
    w = x1 * x1 + x2 * x2;
}
w = sqrt( (-2.0 * log( w ) ) / w );
y1 = x1 * w;
y2 = x2 * w;
 *
to get a normal distribution near what we want:
y = y1*(sd we want) + (mean we want)
 */

/* function to generate a vector of angles */
/* function to generate new point poisitons based on
 * FA geometry (R_C*C_length_pos + R_C*C_length_neg)
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
 * [[x1, y1, x1, R1, a1, b1, c1, theta1, thi1, gamma1]
 *  [x2, y2, z2, R1, a1, b1, c1, theta2, thi2, gamma2]]
 *  x y and z are the global centre positions
 *  R is the length ratio constant, a, b, c are the length ratios.
 *  and theta thi and gamma are the orentation
 *  Note a number of these may be removed if we assume particals are identical.
 */

/*return the init state to the main function */

double average()
{
	printf("inside average function \n");
	return(a+b)/2;
}
