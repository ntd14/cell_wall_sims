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

/*6 parameters to describe the cellulose chains for poly-elipsoids*/

typedef struct partical_types {
	double R; /* radius of particles */
	double density; /* the desity of the particle type */
	double angle_lh; /* MFA */
	double angle_ld; /* angle of travel in depth direction, this is for mixing in radial direction */
	double sd_lh; /* MFA standard devation, sd between each particle position in distribution with mean MFA */
	double sd_ld; /* standard devation for the depth/radial interaction */
	int max_build_steps; /* the maximum number of FA chunks to be used in the positive and negative directions. this is the limit of how many chunks can be in each FA */
	int num_of; /* number of chains of that particle to create */

} part_defs;

/* init the different particle types above, see source file for values */
part_defs FA1;
part_defs HC1;
part_defs LG1;
part_defs H2O;
#endif /* PAR_DEFS_H_ */
