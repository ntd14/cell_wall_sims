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

/* the maximum number of FA chunks to be used in the positive and negative directions. this is the limit of how many chunks can be in each FA */
int max_build_steps; /* note this is in each direction so *2 to get total*/
/* the number of fibril agregates to be build */
int num_of_FAs;

/*6 parameters to describe the cellulose chains for poly-elipsoids*/

typedef struct partical_types {
	double R; /* radius of particles */
	double density; /* the desity of the particle type */
	double angle_lh;
	double angle_ld;
	double sd_lh;
	double sd_ld;

} part_defs;

/* init the different particle types above, see source file for values */
part_defs FA1;
part_defs LG1;
part_defs H2O;
#endif /* PAR_DEFS_H_ */
