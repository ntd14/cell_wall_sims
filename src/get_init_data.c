/*
 * get_init_data.c
 *
 *  Created on: 21/05/2015
 *      Author: nick
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "get_init_data.h"
#include "par_defs.h"

/* if statment to call the aproprate functions from here. num_of_C_chains = 1 will be worked on first */

/*make problem space bigger so that we get random arrangment of FA at the boundaries */
/*caller function needs to define int* ext_dims[3]*/
void ext_pspace(int length_of_problem_space, int height_of_problem_space, int depth_of_problem_space, int* ext_dims)
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
		ii++;
		start_point = start_point + init_spacing_of_FA;
		FA_start_points[ii] = start_point;
	}
}



/* function to generate a vector of angles */
/* function to generate new point poisitons based on
 * FA geometry (R_C*C_length_pos + R_C*C_length_neg)
 * from header and angle from function above
 *
 * double C_L = R_C*C_length_pos + R_C*C_length_neg;
 * double mfac = call to angle function
 * x_new = C_L*sin(mfac) + x_old
 * y_new = C_L*cos(mfac) + y_old
 *
 * */
void new_point_pos(double* new_pos, double* old_s, int num_of_build_steps)
{
	double new_s[num_of_build_steps][2];
	double C_L = R_C*C_length_pos + R_C*C_length_neg; /*length of poly-elip */
	double mfac[num_of_build_steps];   /*init vector of angles for current FA */
	norm_dist(mfac, num_of_build_steps, mean_MFA , sd_MFA); /*get angles for all of the current FA */
	int ii;
	for(ii = 0; ii<num_of_build_steps; ii++)
	{
		new_s[ii][0] = C_L*sin(mfac[ii]) + old_s[ii][0];
		new_s[ii][1] = C_L*cos(mfac[ii]) + old_s[ii][1];
		/*call to function to calc geometric centre*/
		new_pos[ii][0] = new_s[ii][0] - old_s[ii][0];
		new_pos[ii][1] = new_s[ii][1] - old_s[ii][1];
		new_pos[ii][2] = 0;
		new_pos[ii][3] = R_C;
		new_pos[ii][4] = C_length_pos;
		new_pos[ii][5] = C_width_pos;
		new_pos[ii][6] = C_depth_pos;
		new_pos[ii][7] = C_length_neg;
		new_pos[ii][8] = C_width_neg;
		new_pos[ii][9] = C_depth_neg;
		new_pos[ii][10] = mfac[ii];
		new_pos[ii][11] = 0;
	}
	/*call to norm_dist_gen to get angle to travel along
	 * double mfac = call to angle function
	 * new_s[1,ii] = C_L*sin(mfac[ii]) + old_s[1,ii]
	 * new_s[2,ii] = C_L*cos(mfac[ii]) + old_s[2,ii]
	 * test if old or new points are in ROI, if they are:
	 * 		call function to calc the geometric centre of the
	 * 		poly-elipsoid with the endpoints old_s and new_s
	 * 		save geometric centres as new_pos
	 * else test if have exited ROI, then kill loop
	 * save new_s as old_s and del new_s
	 */
}

/*old_t is the top position from the previous time step
 * new_pos is the centre of the poly-elipsoid - might need an external function to do this at some stage,
 * 					as geometries get more complicated will be harder
 * num_of_build_steps is the number of FA clumps to produce in each chain
 *
 * */

/*function
 * take in FA_start_points
 * loop
 * call fucntion to generate angles
 * call function to calc new point positions
 * update starting points
 * if inside problem region > save points
 * loop end
 * return matrix of end/start points for each FA chunk
 */

/*function to calculate centre points and orenetiaon
 * for the poly-elipsoids using the end points from above
 * [[x1, y1, x1, R1, a1, b1, c1, theta1, thi1, gamma1]
 *  [x2, y2, z2, R2, a2, b2, c2, theta2, thi2, gamma2]]
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
