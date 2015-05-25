/*
 * calc_point_pos_single_FA.c
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */


#include <math.h>
#include "normal_dist_gen.h"
#include "../par_defs.h"
#include "calc_point_pos_single_FA.h"


void calc_geo_centre(double* gc, double* new_s, double* old_s, part_defs p_name)
{
	gc[0] = new_s[0] - old_s[0];
	gc[1] = new_s[1] - old_s[1];
	gc[2] = 0;
	/*needs updating to calc for generalised P-Es */
}

void inside_ROI(double* gc, int left_ROI)
{
	/*how to do this? */
}
/* caller function needs to define: double new_pos[num_of_build_steps][5];
 * as well as generate old_s from make_FA_start_points*/
void new_point_pos(double** new_pos, double start_point, part_defs p_name)
{
	double old_s[3] = {start_point, 0, 0};
	double new_s[3];
	double particle_length = p_name.R_ratio*p_name.length_pos + p_name.R_ratio*p_name.length_neg; /*length of poly-elip */
	double mfac[max_build_steps];   /*init vector of angles for current FA */
	norm_dist(mfac, max_build_steps, mean_MFA , sd_MFA); /*get angles for all of the current FA */
	int ii;
	int left_ROI = 0;
	while(left_ROI < 2 && ii < max_build_steps)
	{
		new_s[0] = particle_length*sin(mfac[ii]) + old_s[0];
		new_s[1] = particle_length*cos(mfac[ii]) + old_s[1];
		new_s[2] = old_s[2]; /*add here for 3D*/
		double geo_c[3];
		calc_geo_centre(geo_c, new_s, old_s, p_name); /*call to function to calc geometric centre*/
		inside_ROI(geo_c, left_ROI);/*call to function to see if centre is inside the ROI*/
		if(left_ROI < 2)
		{
			new_pos[ii][0] = new_s[0] - old_s[0];
			new_pos[ii][1] = new_s[1] - old_s[1];
			new_pos[ii][2] = 0; /* change this for 3D */
			new_pos[ii][3] = mfac[ii];
			new_pos[ii][4] = 0; /* change this for 3D */
			/*redefining old_s for the next time step */
			old_s[0] = new_s[0];
			old_s[1] = new_s[1];
			old_s[2] = 0; /*change for 3D*/
			ii++;
		}
	}
}
