/*
 * par_defs.h
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */

#ifndef PAR_DEFS_H_
#define PAR_DEFS_H_

/* define size of problem space in nm */
int length_of_problem_space;
int height_of_problem_space;
int depth_of_problem_space;

/* define properties of the FAs, mean_MFA is the trend line angle what the FAs follow */
double mean_MFA;
/* mean_wall_interaction is the radial trend line the FAs follow, this goverens how much interaction there is between "shells" of FAs */
double mean_wall_interaction;
/* sd_MFA is the stadard devation of the diribution that direction of each FA chunk follows */
double sd_MFA;
/* sd_wall_interaction is the sd of the distibution that the radial direction of the FAs are sampled from */
double sd_wall_interaction;

/* cellulose fibril agregate properties */
/* num_of_C_chains is the number of particles which are used to model each fibril agregite in the cross section */
/* int num_of_C_chains; CUREENTLY NOT USED */
/* the maximum number of FA chunks to be used in the positive and negative directions. this is the limit of how many chunks can be in each FA */
int max_build_steps; /* note this is in each direction so *2 to get total*/
/* the number of fibril agregates to be build */
int num_of_FAs;

/*6 parameters to describe the cellulose chains for poly-elipsoids*/

typedef struct partical_types {
	double R_ratio; /* this is the number all of the dims are multiplied by to get their absolute value */
	double length_pos; /* length of the particle in the positive x direction, when alligned with the problem space coords */
	double length_neg; /* length in the -x dir */
	double height_pos ; /* as above for height (y) */
	double height_neg;
	double depth_pos; /*as above for depth (z) */
	double depth_neg;
	double density; /* the desity of the particle type */

} part_defs;

/* init the different particle types above, see source file for values */
part_defs FA1;
part_defs LG1;
part_defs H2O;
#endif /* PAR_DEFS_H_ */
