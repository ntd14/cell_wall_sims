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

void calc_geo_centre(double* gc, double* new_s, double* old_s, part_defs p_name)
{
	gc[0] = new_s[0] - old_s[0];
	gc[1] = new_s[1] - old_s[1];
	gc[2] = 0;
	/*needs updating to calc for generalised P-Es */
}
/* calc next point in positive direction */
void point_pos(double* cur_point, double* next_point, double* angle, double p_len)
{

}
/* calc next point in negitive direction */
void point_neg(double* cur_point, double*, next_point, double* angle, double p_len)
{

}

/* caller function needs to define: double new_pos[num_of_build_steps][5];
 * as well as generate old_s from make_FA_start_points*/
void new_point_pos(double* pos, double start_point, part_defs p_name)
{
	/* call norm dist to get vecotor of angle of length 2*max_build_steps
	 * calc particle length, p_len
	 * init next_point
	 * int ii;
	 * init tmp_pos length max_build_steps width 5
	 * init tmp_neg length max_build_steps width 5
	 * while xpos and ypos are inside ROI
	 * 		call point_pos
	 * 		store in tmp_pos
	 * 		track num of entries p_i
	 * while xneg yneg are inside ROI
	 * 		call point_neg
	 * 		store in tmp_neg
	 * 		track num of entries n_i
	 * init array of length p_i+n_i and width 5
	 * reverse for loop adding last tmp_neg entry first
	 * for loop adding tmp_pos to end of tmp_neg
	 * nested fors to put tmp array into pos.
	 */
}
