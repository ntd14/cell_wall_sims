/*
 * calc_point_pos_single_FA.c
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */


#include <math.h>
#include <stdio.h>
#include "../normal_dist_gen.h"
#include "../par_defs.h"
#include "calc_point_pos_single_FA.h"
#include "../make_arrays.h"

/* calc next point in positive direction */
void point_pos(double* cur_point, double* next_point, double angle1, double angle2, double p_len)
{
	next_point[0] = p_len*sin(angle1) + cur_point[0];
	next_point[1] = p_len*cos(angle2) + cur_point[1];
	next_point[2] = 0;
	next_point[3] = angle1;
	next_point[4] = angle2;
	/* 3D will change these */
}
/* calc next point in negitive direction */
void point_neg(double* cur_point, double* next_point, double angle1, double angle2, double p_len)
{
	next_point[0] = p_len*sin(angle1 + M_PI) + cur_point[0];
	next_point[1] = p_len*cos(angle1 + M_PI) + cur_point[1];
	next_point[2] = 0;
	next_point[3] = angle1;
	next_point[4] = angle2;
}


int new_point_pos(double* pos, double* start_point, part_defs p_name)
{
	double angle2 = 0;
	double* vec_of_angles = make1Darray(2*max_build_steps);
	norm_dist(vec_of_angles, 2*max_build_steps, mean_MFA, sd_MFA);
	double p_len = p_name.length_pos + p_name.length_neg;
	int ii, jj;
	double* tmp_pos = make2Darray(max_build_steps, 5);
	double* tmp_neg = make2Darray(max_build_steps, 5);
	double* cur_point_pos = make1Darray(5);
	double* cur_point_neg = make1Darray(5);
	double* next_point_pos = make1Darray(5);
	double* next_point_neg = make1Darray(5);
	for(ii=0; ii <3; ii++)
	{
		cur_point_pos[ii] = start_point[ii];
		cur_point_neg[ii] = start_point[ii];
	}
	/* update here for 3D*/
	ii = 0;
	while(cur_point_pos[0] < length_of_problem_space && cur_point_pos[1] < height_of_problem_space)
	{
		point_pos(cur_point_pos, next_point_pos, vec_of_angles[ii], angle2, p_len);
		for(jj = 0; jj < 5; jj++)
		{
			tmp_pos[ind2D(ii, jj, max_build_steps, 5)] = next_point_pos[jj];
		}
		cur_point_pos = next_point_pos;
		ii++;
	}
	int tmp_pos_len = ii;

	/* update here for 3D*/
	ii = 0;
	while(cur_point_pos[0] > 0 && cur_point_pos[1] > 0)
	{
		point_neg(cur_point_neg, next_point_neg, vec_of_angles[ii+max_build_steps], angle2, p_len);
		for(jj = 0; jj < 5; jj++)
		{
			tmp_neg[ind2D(ii, jj, max_build_steps, 5)] = next_point_neg[jj];
		}
		cur_point_neg = next_point_neg;
		ii++;
	}
	int tmp_neg_len = ii;
	double* tmp_array = make2Darray(tmp_pos_len+tmp_neg_len+1, 5);
	int kk = 0;
	for(ii = tmp_neg_len-1; ii >= 0; ii--)
	{
		for(jj = 0; jj < 5; jj++)
		{
			tmp_array[ind2D(kk, jj, tmp_pos_len+tmp_neg_len+1, 5)] = tmp_neg[ind2D(ii, jj, tmp_pos_len, 5)];
		 	jj++;
		}
		kk++;
	}

	tmp_array[ind2D(tmp_neg_len, 0, tmp_pos_len+tmp_neg_len+1, 5)] = start_point[0];
	tmp_array[ind2D(tmp_neg_len, 1, tmp_pos_len+tmp_neg_len+1, 5)] = start_point[1];
	tmp_array[ind2D(tmp_neg_len, 2, tmp_pos_len+tmp_neg_len+1, 5)] = start_point[2];
	tmp_array[ind2D(tmp_neg_len, 3, tmp_pos_len+tmp_neg_len+1, 5)] = vec_of_angles[0];
	tmp_array[ind2D(tmp_neg_len, 4, tmp_pos_len+tmp_neg_len+1, 5)] = vec_of_angles[1];

	for(ii = tmp_neg_len+1; ii < tmp_pos_len+tmp_neg_len+1; ii++)
	{
		for(jj = 0; jj < 5; jj++)
		{
			tmp_array[ind2D(ii, jj, tmp_pos_len+tmp_neg_len+1, 5)] = tmp_pos[ind2D(ii, jj, tmp_pos_len, 5)];
		 	jj++;
		}
	}
	pos = tmp_array;
	return tmp_pos_len+tmp_neg_len+1;
}
