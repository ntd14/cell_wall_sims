/*
 * par_defs.h
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */

#ifndef PAR_DEFS_H_
#define PAR_DEFS_H_

int length_of_problem_space;
int height_of_problem_space;
int depth_of_problem_space;

/* the MFA parameters, sd_MFA is the standard devation of the trendline directions BETWEEN MFs,
 * MFA_sd is the standard devation of the normal distrib that is selected from during the growth of the MF
 * all in radians
 */

double mean_MFA;
double sd_MFA;
double MFA_sd;
int init_spacing_of_FA; /*nm*/

/* cellulose fibril agregate properties,
 * num_of_C_chains is the number of particals which are used to model each fibril agregit
 * num_of_ags is the number of fibril agregits in the model
 */
int num_of_C_chains;
int num_of_ags;
int max_build_steps;
/*6 parameters to describe the cellulose chains for poly-elipsoids*/

typedef struct partical_types {
	double R_ratio;
	double width_pos;
	double width_neg;
	double depth_pos ;
	double depth_neg;
	double length_pos;
	double length_neg;
	double density;

} part_defs;

part_defs FA1;
part_defs LG1;
#endif /* PAR_DEFS_H_ */
