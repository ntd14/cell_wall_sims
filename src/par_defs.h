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

double max_ndist;
int max_cons;

typedef struct partical_types {
	char* name;
	double R; /* radius of particles */
	double density; /* the desity of the particle type */
	double angle_lh; /* MFA */
	double angle_ld; /* angle of travel in depth direction, this is for mixing in radial direction */
	double sd_lh; /* MFA standard devation, sd between each particle position in distribution with mean MFA */
	double sd_ld; /* standard devation for the depth/radial interaction */
	int max_build_steps; /* the maximum number of chunks to be used in the positive and negative directions. this is the limit of how many chunks can be in each FA */
	int num_of; /* number of chains of that particle to create */
	int uid_start;
	int uid_end;

} part_defs;

/* init the different particle types above, see source file for values */
part_defs FA1;
part_defs HC1;
part_defs LG1;
part_defs H2O;


typedef struct connection_types {
	char* p1_name; /* name of one particle in connection */
	char* p2_name; /* name of second particle in connection */
	double mint; /* min distance over which tension acts  */
	double maxt; /* max distance over which tension acts */
	double forcet; /* tensile force */
	double minc;
	double maxc;
	double forcec;
} con_defs;

con_defs FA1FA1strong;
con_defs FA1FA1weak;
con_defs HC1HC1strong;
con_defs HC1HC1weak;
con_defs H2OH2O;

con_defs FA1HC1;
con_defs FA1H2O;
con_defs FA1LG1;
con_defs HC1H2O;
con_defs HC1LG1;
con_defs H2OLG1;


struct particle {
	int uid;
	double* x;
	double* y;
	double* z;
	part_defs* ptype;
	int nlistlen;
	int* nlist; /* need to check if the length needs to be defined at compile time */
	con_defs* nltype;
};


#endif /* PAR_DEFS_H_ */
