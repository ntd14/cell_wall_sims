/*
 * particle_forces.c
 *
 *  Created on: 29/01/2016
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "./get_ini_vars.h"
#include "./lists.h"
#include "./cart_and_cyl.h"
#include "particle_forces.h"


/*this file should hold the functions for calcultating the force on a particle from the sourrounding particles as well as the boundaries*/

void get_bound_properties(struct particle* p_single, struct bound* b, double force_dist[2]){
	if(strcmp(p_single->ptype, "FA0") == 0){
		force_dist[0] = b->force_FA0;
		force_dist[1] = b->dist_FA0;
	}else if(strcmp(p_single->ptype, "LG0") == 0){
		force_dist[0] = b->force_LG0;
		force_dist[1] = b->dist_LG0;
	}else if(strcmp(p_single->ptype, "H2O") == 0){
		force_dist[0] = b->force_H2O;
		force_dist[1] = b->dist_H2O;
	}else{
		printf("could not find aproprate boundary type for particle type, exiting\n");
		exit(0);
	}
}


void calc_new_pos(struct particle* p, int pstart, int pend ){
	int ii, jj, outflag;
	double dist;
	double force_dist[2];
	double p0[3], p1[3];
	for(ii = pstart; ii < pend; ii++);{
		for(jj = 0; jj < vars.num_bounds_used; jj++){
			get_bound_properties(&p[ii], ptr_bounds[jj], force_dist);
			p0[0] = p[ii].r;
			p0[1] = p[ii].theta;
			p0[2] = p[ii].h;
			outflag = 1;
			if(strcmp(ptr_bounds[jj]->name, "B_top") == 0){
				if(p[ii].h > vars.ROI_height){
					outflag = 0;
				}else{
					p1[0] = p[ii].r;
					p1[1] = p[ii].theta;
					p1[2] = vars.ROI_height;
				}

			}else if(strcmp(ptr_bounds[jj]->name, "B_bot") == 0){
				if(p[ii].h < 0){
					outflag = 0;
				}else{
					p1[0] = p[ii].r;
					p1[1] = p[ii].theta;
					p1[2] = 0;
				}
			}else if(strcmp(ptr_bounds[jj]->name, "B_theta_min") == 0){
				if(p[ii].theta < 0){
					outflag = 0;
				}else{
					p1[0] = p[ii].r;
					p1[1] = 0;
					p1[2] = p[ii].h;
				}
			}else if(strcmp(ptr_bounds[jj]->name, "B_theta_max") == 0){
				if(p[ii].theta > vars.ROI_angle){
					outflag = 0;
				}else{
					p1[0] = p[ii].r;
					p1[1] = vars.ROI_angle;
					p1[2] = p[ii].h;
				}

			}else if(strcmp(ptr_bounds[jj]->name, "B_luman") == 0){
				/*need to calc this depending on the progress though building the cell wall*/
			}else{
				if(p[ii].r > P0.rad){
					outflag = 0;
				}else{
					p1[0] = P0.rad;
					if((p[ii].theta >= ptr_bounds[jj]->theta_start) & (p[ii].theta <= ptr_bounds[jj]->theta_end)){
						p1[1] = p[ii].theta;
					}else if(p[ii].theta > ptr_bounds[jj]->theta_end){
						p1[1] = ptr_bounds[jj]->theta_end;
					}else if(p[ii].theta < ptr_bounds[jj]->theta_start){
						p1[1] = ptr_bounds[jj]->theta_start;
					}else{
						printf("error implementing boundary condition \n");
					}
					p1[2] = p[ii].h;
				}
			}
			if(outflag != 0){
				dist = calc_dist_between_points(p0, p1);
				/*calc force vector using linear interp*/
				/*update overall force vector*/
			}else{
				/*calc force vector assuming max force */
				/*update overall force vector*/
			}
		}
		/*loop through the particles nlist
		 * with each one calc the updated force vector*/

		/*from complete force vector update position and save as new_**/
	}
}

/* take in a particle*/
/* check for BC interactions + calc and store forces and directions
 * loop through all connected particles
 * get particle and hence connection type
 * calc and store the direction and force of each on the central particle can probably do this acumulativly
 * find the overall force on the central particle
 * find the new position given the imposed force
 * store the new coords in the new_* varables inside the particle structure*/


/*move new_* to * position vars*/
void update_selected_pos(struct particle* p, int pstart, int pend){
	int ii;
	for(ii = pstart; ii < pend; ii++){
		p[ii].r = p[ii].new_r;
		p[ii].theta = p[ii].new_theta;
		p[ii].h = p[ii].new_h;

	}
}
