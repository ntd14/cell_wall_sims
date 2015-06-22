/*
 * par_defs.c
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */
#include "par_defs.h"
#include <math.h>

/* define size of problem space in nm */
int length_of_problem_space = 1000;
int height_of_problem_space = 1000;
int depth_of_problem_space = 1000;

/* define properties of the FAs, mean_MFA is the trend line angle what the FAs follow */
double mean_MFA = -0.2 + M_PI/2;
/* mean_wall_interaction is the radial trend line the FAs follow, this goverens how much interaction there is between "shells" of FAs */
double mean_wall_interaction = M_PI/2;
/* sd_MFA is the stadard devation of the diribution that direction of each FA chunk follows */
double sd_MFA = M_PI/4;
/* sd_wall_interaction is the sd of the distibution that the radial direction of the FAs are sampled from */
double sd_wall_interaction = 0.1;

/* cellulose fibril agregate properties */
/* num_of_C_chains is the number of particals which are used to model each fibril agregite in the cross section */
/*int num_of_C_chains = 1; CURENTLY NOT USED */
/* the maximum number of FA chunks to be used in the positive and negative directions. this is the limit of how many chunks can be in each FA */
int max_build_steps = 500; /* note this is in each direction so *2 to get total*/
/* the number of fibril agregates to be build */
int num_of_FAs = 33;

/*6 parameters to describe the cellulose chains for poly-elipsoids, see header file for def of each entry*/
part_defs FA1 = {10.0, 1500.0};
part_defs LG1 = {10.0,  500.0};
part_defs H2O = {10.0, 1000.0};
