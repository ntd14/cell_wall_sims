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
void point_pos(double* cur_point, double* next_point, double theta, double thi, double p_len)
{
	next_point[0] = p_len*cos(theta)*sin(thi)+ cur_point[0];/*p_len*sin(thi)*cos(theta) + cur_point[0];*/
	next_point[1] = p_len*sin(theta)*sin(thi) + cur_point[1];/*p_len*sin(thi)*sin(theta) + cur_point[1];*/
	next_point[2] = p_len*cos(thi) + cur_point[2];
	/* 3D will change these */
}
/* calc next point in negitive direction */
void point_neg(double* cur_point, double* next_point, double theta, double thi, double p_len)
{
	next_point[0] = p_len*cos(theta + M_PI)*sin(thi)+ cur_point[0];/*p_len*sin(thi)*cos(theta + M_PI) + cur_point[0];*/
	next_point[1] = p_len*sin(theta + M_PI)*sin(thi)+ cur_point[1];/*p_len*sin(thi)*sin(theta + M_PI) + cur_point[1];*/
	next_point[2] = p_len*cos(thi) + cur_point[2];
}

int new_point_pos(double* pos, double* start_point, part_defs p_name)
{
	double* vec_of_theta = make1Darray(2*max_build_steps);
	norm_dist(vec_of_theta, 2*max_build_steps, mean_MFA, sd_MFA);
	double* vec_of_thi = make1Darray(2*max_build_steps);
	norm_dist(vec_of_thi, 2*max_build_steps, mean_wall_interaction, sd_wall_interaction);
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
	while(cur_point_pos[0] < length_of_problem_space && cur_point_pos[1] < height_of_problem_space && cur_point_pos[0] > 0 && cur_point_pos[1] > 0 && ii < max_build_steps)
	{
		point_pos(cur_point_pos, next_point_pos, vec_of_theta[ii], vec_of_thi[ii], p_len);

		for(jj = 0; jj < 3; jj++)
		{
			tmp_pos[ind2D(ii, jj, max_build_steps, 5)] = next_point_pos[jj];
		}

		tmp_pos[ind2D(ii, 3, max_build_steps, 5)] = vec_of_theta[ii+1];
		tmp_pos[ind2D(ii, 4, max_build_steps, 5)] = vec_of_thi[ii+1];
		cur_point_pos = next_point_pos;
		ii++;
	}
	int tmp_pos_len = ii;

	/* update here for 3D */
	ii = 0;
	while(cur_point_neg[0] < length_of_problem_space && cur_point_neg[1] < height_of_problem_space && cur_point_neg[0] > 0 && cur_point_neg[1] > 0 && ii < max_build_steps)
	{
		point_neg(cur_point_neg, next_point_neg, vec_of_theta[ii+max_build_steps],vec_of_thi[ii+max_build_steps], p_len);
		for(jj = 0; jj < 3; jj++)
		{
			tmp_neg[ind2D(ii, jj, max_build_steps, 5)] = next_point_neg[jj];
		}
		tmp_neg[ind2D(ii, 3, max_build_steps, 5)] = vec_of_theta[ii+max_build_steps];
		tmp_neg[ind2D(ii, 4, max_build_steps, 5)] = vec_of_thi[ii+max_build_steps];;
		cur_point_neg = next_point_neg;
		ii++;
	}
	int tmp_neg_len = ii;
	int kk = 0;
	for(ii = tmp_neg_len-1; ii >= 0; ii--)
	{
		for(jj = 0; jj < 5; jj++)
		{
			pos[ind2D(kk, jj, 2*max_build_steps, 5)] = tmp_neg[ind2D(ii, jj, max_build_steps, 5)];
		}
		kk++;
	}

	pos[ind2D(tmp_neg_len, 0, 2*max_build_steps, 5)] = start_point[0];
	pos[ind2D(tmp_neg_len, 1, 2*max_build_steps, 5)] = start_point[1];
	pos[ind2D(tmp_neg_len, 2, 2*max_build_steps, 5)] = start_point[2];
	pos[ind2D(tmp_neg_len, 3, 2*max_build_steps, 5)] = vec_of_theta[0];
	pos[ind2D(tmp_neg_len, 4, 2*max_build_steps, 5)] = vec_of_thi[0];

	for(ii = tmp_neg_len+1; ii < tmp_pos_len+tmp_neg_len+1; ii++)
	{
		for(jj = 0; jj < 5; jj++)
		{
			pos[ind2D(ii, jj, 2*max_build_steps, 5)] = tmp_pos[ind2D(ii-tmp_neg_len, jj, max_build_steps, 5)];
		}
	}

	return tmp_neg_len+tmp_pos_len+1;
}
