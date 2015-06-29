/*
 * calc_point_pos_single_FA.c
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../normal_dist_gen.h"
#include "../par_defs.h"
#include "calc_point_pos_single_FA.h"
#include "../make_arrays.h"

/* calc next point in positive direction */
void point_pos(double* cur_point, double* next_point, double theta, double thi, double p_len)
{
	next_point[0] = p_len*cos(theta)*sin(thi)+ cur_point[0];
	next_point[1] = p_len*sin(theta)*sin(thi) + cur_point[1];
	next_point[2] = p_len*cos(thi) + cur_point[2];
	/* 3D will change these */
}
/* calc next point in negitive direction */
void point_neg(double* cur_point, double* next_point, double theta, double thi, double p_len)
{
	next_point[0] = p_len*cos(theta + M_PI)*sin(thi)+ cur_point[0];
	next_point[1] = p_len*sin(theta + M_PI)*sin(thi)+ cur_point[1];
	next_point[2] = p_len*cos(thi) + cur_point[2];
}

int new_point_pos(double* pos, double* start_point, part_defs pl, int li, int alen)
{
	double* vec_of_theta = norm_dist(2*pl.max_build_steps, pl.angle_lh, pl.sd_lh); /* note because norm_dist produces 2 random numbers
																	this is 2x more cpu efficant than calling each time,
																	trade of is that it uses more memory*/
	double* vec_of_thi = norm_dist(2*pl.max_build_steps, pl.angle_ld, pl.sd_ld);

	double p_len = 2*pl.R;
	int ii, jj, ll;
	double* tmp_pos = make2Darray(pl.max_build_steps, 3);
	double* tmp_neg = make2Darray(pl.max_build_steps, 3);

	double* cur_point_pos = make1Darray(3);
	double* cur_point_neg = make1Darray(3);
	double* next_point_pos = make1Darray(3);
	double* next_point_neg = make1Darray(3);

	for(ii=0; ii <3; ii++)
	{
		cur_point_pos[ii] = start_point[ii];
		cur_point_neg[ii] = start_point[ii];
	}
	ii = 0;
	while(cur_point_pos[0] < length_of_problem_space-2*pl.R && cur_point_pos[1] < height_of_problem_space-2*pl.R && cur_point_pos[2] < depth_of_problem_space-2*pl.R
			&& cur_point_pos[0] > 2*pl.R && cur_point_pos[1] > 2*pl.R && cur_point_pos[2] > 2*pl.R
			&& ii < pl.max_build_steps)
	{
		point_pos(cur_point_pos, next_point_pos, vec_of_theta[ii], vec_of_thi[ii], p_len);

		for(jj = 0; jj < 3; jj++)
		{
			tmp_pos[ind2D(ii, jj, pl.max_build_steps, 3)] = next_point_pos[jj];
		}
		for(ll=0; ll <3; ll++)
		{
			cur_point_pos[ll] = next_point_pos[ll];
		}
		ii++;
	}
	int tmp_pos_len = ii;

	/* update here for 3D */
	ii = 0;
	while(cur_point_neg[0] < length_of_problem_space-2*pl.R && cur_point_neg[1] < height_of_problem_space-2*pl.R && cur_point_neg[2] < depth_of_problem_space-2*pl.R
			&& cur_point_neg[0] > 2*pl.R && cur_point_neg[1] > 2*pl.R && cur_point_neg[2] > 2*pl.R
			&& ii < pl.max_build_steps)
	{
		point_neg(cur_point_neg, next_point_neg, vec_of_theta[ii+pl.max_build_steps],vec_of_thi[ii+pl.max_build_steps], p_len);
		for(jj = 0; jj < 3; jj++)
		{
			tmp_neg[ind2D(ii, jj, pl.max_build_steps, 3)] = next_point_neg[jj];
		}
		for(ll=0; ll <3; ll++)
		{
			cur_point_neg[ll] = next_point_neg[ll];
		}
		ii++;
	}
	int tmp_neg_len = ii;
	int kk = 0;

	for(ii = tmp_neg_len-1; ii >= 0; ii--)
	{
		for(jj = 0; jj < 3; jj++)
		{
			pos[ind2D(kk + li, jj, alen, 3)] = tmp_neg[ind2D(ii, jj, pl.max_build_steps, 3)];
		}
		kk++;
	}

	pos[ind2D(tmp_neg_len + li, 0, alen, 3)] = start_point[0];
	pos[ind2D(tmp_neg_len + li, 1, alen, 3)] = start_point[1];
	pos[ind2D(tmp_neg_len + li, 2, alen, 3)] = start_point[2];

	for(ii = 0; ii < tmp_pos_len; ii++)
	{
		for(jj = 0; jj < 3; jj++)
		{
			pos[ind2D(ii+tmp_neg_len+1 + li, jj, alen, 3)] = tmp_pos[ind2D(ii, jj, pl.max_build_steps, 3)];
		}
	}

	free(cur_point_pos);
	cur_point_pos  = NULL;
	free(cur_point_neg);
	cur_point_neg  = NULL;
	free(next_point_pos);
	next_point_pos  = NULL;
	free(next_point_neg);
	next_point_neg  = NULL;

	free(vec_of_theta);
	vec_of_theta = NULL;
	free(vec_of_thi);
	vec_of_thi  = NULL;
	free(tmp_pos);
	tmp_pos = NULL;
	free(tmp_neg);
	tmp_neg  = NULL;


	return li+tmp_neg_len + 1 + tmp_pos_len;
}
