#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "./helpers/interp_funs.h"
#include "./helpers/get_ini_vars.h"
#include "./helpers/lists.h"
#include "get_movement.h"

double calc_dist(struct particle* p0, struct particle* p1){
	/* calc the distance between p0 and p1 */
	double dtheta = abs(p0->theta - p1->theta);
	double dh = abs(p0->h - p1->h);
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
	if(dist < conptr->met){
		force = get_interp_val_P(dist, conptr->met, 0, conptr->met_force, conptr->max_force);
	}else if((dist >= conptr->met) && (dist <= conptr->dist)){
		force = get_interp_val_P(dist, conptr->dist, conptr->met, conptr->met_force, 0);
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


void update_pos_burnin(int pstart, int pend, struct particle* p, double time_step, int num_burnin_steps){
	double burnin_time_step = time_step/num_burnin_steps;
	int ii = 0;
	double dist_e;
	do{
		dist_e = 0;
		dist_e = get_new_locations(pstart, pend, p, burnin_time_step);
		printf("%f \n", dist_e);
		move_to_new_pos(pstart, pend, p);
		ii++;
	}while(ii < num_burnin_steps); /* && dist_e > some minimum */
}

/*Note should the forces be negative when two particles overlap?, or the other way around*/
