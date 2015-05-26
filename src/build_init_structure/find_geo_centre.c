/*
 * find_geo_centre.c
 *
 *  Created on: 26/05/2015
 *      Author: nick
 */


void calc_geo_centre(double* gc, double* new_s, double* old_s, part_defs p_name)
{
	gc[0] = new_s[0] - old_s[0];
	gc[1] = new_s[1] - old_s[1];
	gc[2] = 0;
	/*needs updating to calc for generalised P-Es */
}

void find_init_pos(double* init_pos, double* end_point_pos, int FA_steps, part_defs p_name)
{
	double* tmp_gc = make1Darray(3);
	double* old_s = make1Darray(3);
	double* new_s = make1Darray(3);
	int ii, jj;
	for(ii = 0; ii < FA_steps; ii++)
	{
		for(jj = 0; jj < 3; jj++)
		{
			old_s[jj] = end_point_pos[ind2D(ii, jj, FA_steps+1, 5)];
			new_s[jj] = end_point_pos[ind2D(ii+1, jj, FA_steps+1, 5)];
		}
		calc_geo_centre(tmp_gc, new_s, old_s, p_name);

		init_pos[ind2D(ii,0, FA_steps, 5)] = tmp_gc[0];
		init_pos[ind2D(ii,1, FA_steps, 5)] = tmp_gc[1];
		init_pos[ind2D(ii,2, FA_steps, 5)] = tmp_gc[2];
	}
}
