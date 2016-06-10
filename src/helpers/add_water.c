/*
 * add_water.c
 *
 *  Created on: 28/01/2016
 *      Author: nick
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./get_ini_vars.h"
#include "./cart_and_cyl.h"

/*function to add water to the cell wall. */
int add_water(struct particle* p, struct particle** nlist_array, int start_particles, int end_particles, struct point Po, struct point Pi){
	int ptot = end_particles;
		/*split ro - ri into h2o.dia +1 chuncks starting at the outer wall, calc the change in theta at that rad to give a movement of 1 dia
		 * split height into h2o.dia +1 chunks starting at the bottom ring, work up to h
		 * once one shell is complete move in 1 rad, recalc the change in theta and do the next shell*/
	int num_of_shells = (int) (Po.rad - Pi.rad)/vars.H2O_dia + 1;
	int num_of_height_chunks = (int) vars.ROI_height / vars.H2O_dia + 1;
	int ii, jj, kk, ll, used;
	int num_particles_at_rad;
	double particle_theta;
	double tmp_coords[3];
	double closest_r = vars.H2O_dia;
	double closest_h = vars.H2O_dia;
	for(ii = 0; ii < num_of_shells; ii++){
		num_particles_at_rad = (int) (arc_length((Po.rad - vars.H2O_dia*ii), vars.ROI_angle) / vars.H2O_dia) + 1;
		particle_theta = (vars.ROI_angle/(num_particles_at_rad - 1));
		for(jj = 0; jj < num_of_height_chunks; jj++){
			for(kk = 0; kk < num_particles_at_rad; kk++){
				/*create tmp particle*/
				tmp_coords[0] = Po.rad - vars.H2O_dia*ii;
				tmp_coords[1] = particle_theta*kk;
				tmp_coords[2] = vars.H2O_dia*jj;
				/*check if tmp particle can be used, if yes add, if no delete*/
				ll = start_particles;
				used = 0;
				while((ll < end_particles) && (used == 0)){
					if((fabs(tmp_coords[0] - p[ll].r) < closest_r) &&
							(fabs(tmp_coords[1] - p[ll].theta) < particle_theta) &&
							(fabs(tmp_coords[2] - p[ll].h) < closest_h)){
						used = 1;
					}
					ll++;
				}
				if(used == 0){
					p[ptot].uid = ptot;
					p[ptot].r = tmp_coords[0];
					p[ptot].theta = tmp_coords[1];
					p[ptot].h = tmp_coords[2]; /*should this have some noise added into it?*/
					p[ptot].ptype = "H2O";
					p[ptot].nlistlen = 0;
					p[ptot].nlist = &nlist_array[ptot*vars.max_connections];
					p[ptot].nr = p[ptot].r;
					p[ptot].ntheta = p[ptot].theta;
					p[ptot].nh = p[ptot].h;
					ptot++;
				}
			}
		}
	}

	return(ptot);
}
