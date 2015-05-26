/*
 * par_defs.c
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */
#include "par_defs.h"

int length_of_problem_space = 1000;
int height_of_problem_space = 1000;
int depth_of_problem_space = 0;

/* the MFA parameters, sd_MFA is the standard devation of the trendline directions BETWEEN MFs,
 * MFA_sd is the standard devation of the normal distrib that is selected from during the growth of the MF
 * all in radians
 */

double mean_MFA = 0.175;
double sd_MFA = 0.035;
double MFA_sd = 0.01;

/* cellulose fibril agregate properties,
 * num_of_C_chains is the number of particals which are used to model each fibril agregit
 * num_of_ags is the number of fibril agregits in the model
 */
int num_of_C_chains = 1;
int num_of_ags = 2;
int max_build_steps = 200; /* note this is in each direction so *2 to get total*/
int num_of_FAs = 10;
/*6 parameters to describe the cellulose chains for poly-elipsoids*/


part_defs FA1 = {10.0, 0.2, 0.2, 0.2, 0.2, 2.0, 2.0, 1500.0};
part_defs LG1 = {10.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,  500.0};
