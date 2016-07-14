#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "./helpers/interp_funs.h"
#include "./helpers/get_ini_vars.h"
#include "./helpers/lists.h"
#include "./helpers/search_funcs.h"
#include "get_movement.h"

double calc_dist(struct particle* p0, struct particle* p1){
	/* calc the distance between p0 and p1 */
	double dtheta = fabs(p0->theta - p1->theta);
	double dh = fabs(p0->h - p1->h);
	double hdist = sqrt(pow(p0->r, 2) + pow(p1->r, 2) - 2*p0->r*p1->r*cos(dtheta));
	double dist = sqrt(pow(hdist, 2) + pow(dh ,2));
	return(dist);
}

double calc_force(struct particle* p0, struct particle* p1, double dist){
	double force;
	char cons1[10], cons2[10];
	strcpy(cons1, p0->ptype);
	strcpy(cons2, p1->ptype);
	strcat(cons1, cons2);
	strcat(cons1, "con");
	con* conptr = con_ptr_name(cons1);

	if(dist < conptr->dist){

		force = 4*conptr->max_force*(pow((conptr->max_force)/(dist),12) - (pow((conptr->max_force)/(dist),6))); /*VERY DUBIOUS AS DIRECTLY SUB FORCE AND ENERGY*/

		/*assume energy = - work, ie no energy is lost as heat, 1st law thermo
		 * Work = force*displacment*/
	}else{
		force = 0;
	}
	return(force);
}


void calc_rel_pos(struct particle* p0, struct particle* p1, double* fdir, double time){
	double dist_bp = calc_dist(p0, p1);
	double force = calc_force(p0, p1, dist_bp);
	if(force != 0){
		/* note at this stage F=ma it is assumed the mass for all particles is 1.
		 * so the forces when implemented in the ini will need to account for this,
		 * as in force normalised to mass*/
		/*Should use Lennard-Jones potential for interpartical models, see wiki*/
		double speed = force*time;
		double con_speed = time/dist_bp;
		double norm_speed = speed/con_speed;
		fdir[0] = fdir[0] + (p0->r - p1->r)*norm_speed;
		fdir[1] = fdir[1] + (p0->theta - p1->theta)*norm_speed;
		fdir[2] = fdir[2] + (p0->h - p1->h)*norm_speed;
	}
}

double get_new_locations(int pstart, int pend, struct particle* p, double burn_in_timestep){
	int ii, jj;
	double dist_e = 0;
	double fdir[3];
	struct particle p1;
	for(ii = pstart; ii < pend; ii++){
		fdir[0] = 0;
		fdir[1] = 0;
		fdir[2] = 0;
		for(jj = 0; jj < p[ii].nlistlen; jj++){
			calc_rel_pos(&p[ii], p[ii].nlist[jj], fdir, burn_in_timestep);
		}

		p[ii].nr = p[ii].r + fdir[0];
		p[ii].ntheta = p[ii].theta + fdir[1];
		p[ii].nh = p[ii].h + fdir[2];
		p1.r = p[ii].nr;
		p1.theta = p[ii].ntheta;
		p1.h = p[ii].nh;
		dist_e = dist_e + calc_dist(&p[ii], &p1); /* NOTE this doesnt work because dist_e is directionless, so when two oposing particles pull on the particle the calc says it moved twice, when really it didnt move */
	}
	return(dist_e);
}

void move_to_new_pos(int pstart, int pend, struct particle* p){
	int ii;
	for(ii = pstart; ii < pend; ii++){
		p[ii].r = p[ii].nr;
		p[ii].theta = p[ii].ntheta;
		p[ii].h = p[ii].nh;
	}
}


void update_pos_burnin(int pstart, int pend, struct particle* p, double time_step, int num_burnin_steps, double inner_edge){
	double dist, speed, energy, dmove;
	double mass = 1; /*a lot of this function needs to have the ini updated around how it works*/
	double Emax = 20; /*set this within the energy calc as the -1*max_force*/
	double time = time_step/num_burnin_steps;
	double bc_energy;
	int ii, jj, bb, bc;
	int bs = 0;
	int sbf;
	double fdir[3];
	double pos_vec[3];
	double bc_list[6];
	double tdlim = 5;
	double td = tdlim*2;

	while((td > tdlim) && (bs < num_burnin_steps)){
		td = 0; /* for a auto cutoff it might be better to say, any one particle should move more than x */
		for(ii = pstart; ii < pend; ii++){
			fdir[0] = 0;
			fdir[1] = 0;
			fdir[2] = 0;
				for(jj = 0; jj < p[ii].nlistlen; jj++){
					dist = calc_dist(&p[ii], p[ii].nlist[jj]);
					energy = calc_force(&p[ii], p[ii].nlist[jj], dist);
					if(energy > Emax){
						energy = Emax;
					}
					speed = sqrt(fabs(2*energy/mass));
					dmove = (speed*time)/dist;
					td = td + dmove*dist;
					fdir[0] = fdir[0] + dmove*(p[ii].r - p[ii].nlist[jj]->r);
					fdir[1] = fdir[1] + dmove*(p[ii].theta - p[ii].nlist[jj]->theta);
					fdir[2] = fdir[2] + dmove*(p[ii].h - p[ii].nlist[jj]->h);
				}

				pos_vec[0] = p[ii].r;
				pos_vec[1] = p[ii].theta;
				pos_vec[2] = p[ii].h;

				for(bb=0; bb < vars.num_bounds_used; bb++){
					bc_list[0] = ptr_bounds[bb]->r_start;
					bc_list[1] = ptr_bounds[bb]->r_end;
					bc_list[2] = ptr_bounds[bb]->theta_start;
					bc_list[3] = ptr_bounds[bb]->theta_end;
					bc_list[4] = ptr_bounds[bb]->h_start;
					bc_list[5] = ptr_bounds[bb]->h_end;


					for(bc=0; bc<6; bc++){
						if((bc_list[bc] == -1)){
						} else if((bc_list[bc] == -2) && (bc == 0)){
							bc_list[bc] = inner_edge;
						} else if(bc_list[bc] < 0){
							printf("error undefined boundary code, check ini file for mistakes in boundary conditions, setting to -1 \n");
							bc_list[bc] = -1;
						}
					}
					sbf = -1;
					for(bc=0; bc<6; bc++){
						if(bc_list[bc] != -1){
							if((bc % 2 == 0) && ((bc_list[bc] - pos_vec[bc/2]) > 0)){
								sbf = 1;
							}else if((bc % 2 == 1) && ((bc_list[bc] - pos_vec[bc/2]) < 0)){
								sbf = 1;
							}
						}
					}

					if(sbf == 1){
						if(strcmp(p[ii].ptype, "FA0") == 0){
							bc_energy = ptr_bounds[bb]->force_FA0; /* change using linear interp ? */
						}else if(strcmp(p[ii].ptype, "LG0") == 0){
							bc_energy = ptr_bounds[bb]->force_LG0;
						}else if(strcmp(p[ii].ptype, "H2O") == 0){
							bc_energy = ptr_bounds[bb]->force_H2O;
						}else{
							printf("error particle type has no defined boundray force, ignoring \n");
						}
						for(bc=0; bc<6; bc++){
							if(bc_list[bc] != -1){
								dist = fabs(bc_list[bc] - pos_vec[bc/2]);
								energy = bc_energy*dist;
								if(energy > Emax){
									energy = Emax;
									printf("emax ");
								}
								speed = sqrt(fabs(2*(energy)/mass));
								dmove = (speed*time)/dist;
								td = td + dmove*dist;
								fdir[bc/2] = fdir[bc/2] - dmove*(pos_vec[bc/2] - bc_list[bc]);
							}
						}
					}

				}


			p[ii].r = p[ii].r + fdir[0];
			p[ii].theta = p[ii].theta + fdir[1];
			p[ii].h = p[ii].h + fdir[2];
		}
		printf("%f \n", td);
		bs++;
	}
	selective_search(p, pstart, pend, pstart, pend);
}

