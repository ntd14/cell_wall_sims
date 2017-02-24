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
	double hdist = sqrt(fabs(pow(p0->r, 2) + pow(p1->r, 2) - 2*p0->r*p1->r*cos(dtheta)));
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

		force = ((24*conptr->met_force)/(conptr->met))*(2*pow((conptr->met)/(dist),13) - (pow((conptr->met)/(dist),7)));

		if(force > fabs(conptr->max_force)){
			force = fabs(conptr->max_force);
		}else if(force < -1*fabs(conptr->max_force)){
			force = -1*fabs(conptr->max_force);
		}

	}else{
		force = 0;
	}
	return(force);
}




void move_to_new_pos(int pstart, int pend, struct particle* p){
	int ii;
	for(ii = pstart; ii < pend; ii++){
		p[ii].r = p[ii].nr;
		p[ii].theta = p[ii].ntheta;
		p[ii].h = p[ii].nh;
	}
}


void update_pos_burnin(int pend, struct particle* p, double time_step, int num_burnin_steps){
	double dist, force, dmove, prad;
	double mass;
	double time = time_step/num_burnin_steps;
	double bc_force;
	double delta_r, delta_theta, delta_h;
	int ii, jj, bb, bc;
	int bs = 0;
	int sbf;
	double fdir[3];
	double pos_vec[3];
	double bc_list[6];
	double tdlim = 1;
	double td = tdlim*2;

	selective_search(p, 0, pend, 0, pend);


	while((td > tdlim) && (bs < num_burnin_steps)){

		td = 0; /* for a auto cutoff it might be better to say, any one particle should move more than x */
		for(ii = 0; ii < pend; ii++){
			fdir[0] = 0;
			fdir[1] = 0;
			fdir[2] = 0;

			if(strcmp(p[ii].ptype, "FA0") == 0){
				mass = vars.FA_mass;
			}else if(strcmp(p[ii].ptype, "LG0") == 0){
				mass = vars.LG_mass;
			}else if(strcmp(p[ii].ptype, "H2O") == 0){
				mass = vars.H2O_mass;
			}else{
				printf("error particle type has no defined mass, using default of water \n");
				mass = vars.H2O_mass;
			}

			for(jj = 0; jj < p[ii].nlistlen; jj++){
				dist = calc_dist(&p[ii], p[ii].nlist[jj]);
				force = calc_force(&p[ii], p[ii].nlist[jj], dist);
				dmove = 0.5*(force/mass)*time*time/dist;

				td = td + fabs(dmove);

				if((p[ii].theta != p[ii].theta) || (p[ii].nlist[jj]->theta != p[ii].nlist[jj]->theta)){
					printf("theta is nan at particle %i \n", ii);
					printf("%f, ", p[ii].theta);
					printf("%f \n", p[ii].nlist[jj]->theta);
				}
				if((p[ii].r - p[ii].nlist[jj]->r) > 0){
					fdir[0] = fdir[0] - dmove*(p[ii].r - p[ii].nlist[jj]->r);
				} else if((p[ii].r - p[ii].nlist[jj]->r) <= 0){
					fdir[0] = fdir[0] + dmove*(p[ii].r - p[ii].nlist[jj]->r);
				} if((p[ii].theta - p[ii].nlist[jj]->theta) > 0){
					fdir[1] = fdir[1] - dmove*(p[ii].theta - p[ii].nlist[jj]->theta);
				} else if((p[ii].theta - p[ii].nlist[jj]->theta) <= 0){
					fdir[1] = fdir[1] + dmove*(p[ii].theta - p[ii].nlist[jj]->theta);
				} if ((p[ii].h - p[ii].nlist[jj]->h) > 0){
					fdir[2] = fdir[2] - dmove*(p[ii].h - p[ii].nlist[jj]->h);
				} else if ((p[ii].h - p[ii].nlist[jj]->h) <= 0) {
					fdir[2] = fdir[2] + dmove*(p[ii].h - p[ii].nlist[jj]->h);
				}
			}



			for(bb=0; bb < vars.num_bounds_used; bb++){
				sbf = -1;
				dmove = 0;

				if(strcmp(p[ii].ptype, "FA0") == 0){
					bc_force = ptr_bounds[bb]->force_FA0;
					prad = vars.FA_dia;
				}else if(strcmp(p[ii].ptype, "LG0") == 0){
					bc_force = ptr_bounds[bb]->force_LG0;
					prad = vars.LG_dia;
				}else if(strcmp(p[ii].ptype, "H2O") == 0){
					bc_force = ptr_bounds[bb]->force_H2O;
					prad = vars.H2O_dia;
				}else{
					printf("error particle type has no defined boundray force, ignoring \n");
					}

				if((ptr_bounds[bb]->r_start != -1) && (p[ii].r < ptr_bounds[bb]->r_start)){
					delta_r = ptr_bounds[bb]->r_start - p[ii].r;
					sbf = 1;

					if(delta_r < prad){
						force = bc_force*(delta_r/prad);
					}else{
						force = bc_force;
					}
					dmove = 0.5*force/mass*time*time;
					fdir[0] = fdir[0] + dmove;

				}if((ptr_bounds[bb]->r_end != -1) && (p[ii].r > ptr_bounds[bb]->r_end)){
					if(delta_r != 0){
						printf("something strange is going on, a particle is defined as below r_start and above r_end at the same time \n");
					}
					delta_r = ptr_bounds[bb]->r_end - p[ii].r;
					sbf = 1;

					if(delta_r < prad){
						force = bc_force*(delta_r/prad);
					}else{
						force = bc_force;
					}
					dmove = 0.5*force/mass*time*time;
					fdir[0] = fdir[0] + dmove;

				}if((ptr_bounds[bb]->theta_start != -1) && (p[ii].theta < ptr_bounds[bb]->theta_start)){
					delta_theta = sqrt(pow(p[ii].r,2) + pow(p[ii].r,2) - 2*p[ii].r*p[ii].r*cos(p[ii].theta - ptr_bounds[bb]->theta_start));
					sbf = 1;

					if(delta_theta < prad){
						force = bc_force*(delta_theta/prad);
					}else{
						force = bc_force;
					}
					dmove = acos((pow(p[ii].r,2) + pow(p[ii].r,2) - pow((0.5*force/mass*time*time), 2))/(2*(0.5*force/mass*time*time)*p[ii].r));
					fdir[1] = fdir[1] + dmove;

				}if((ptr_bounds[bb]->theta_end != -1) && (p[ii].theta > ptr_bounds[bb]->theta_end)){
					if(delta_theta != 0){
						printf("something strange is going on, a particle is defined as below theta_start and above theta_end at the same time \n");
					}
					delta_theta = sqrt(pow(p[ii].r,2) + pow(p[ii].r,2) - 2*p[ii].r*p[ii].r*cos(p[ii].theta - ptr_bounds[bb]->theta_end));
					sbf = 1;

					if(delta_theta < prad){
						force = bc_force*(delta_theta/prad);
					}else{
						force = bc_force;
					}
					dmove = acos((pow(p[ii].r,2) + pow(p[ii].r,2) - pow((0.5*force/mass*time*time), 2))/(2*(0.5*force/mass*time*time)*p[ii].r));
					fdir[1] = fdir[1] + dmove;

				}if((ptr_bounds[bb]->h_start != -1) && (p[ii].h < ptr_bounds[bb]->h_start)){
					delta_h = ptr_bounds[bb]->h_start - p[ii].h;
					sbf = 1;

					if(delta_h < prad){
						force = bc_force*(delta_h/prad);
					}else{
						force = bc_force;
					}
					dmove = 0.5*force/mass*time*time;
					fdir[2] = fdir[2] + dmove;

				}if((ptr_bounds[bb]->h_end != -1) && (p[ii].h > ptr_bounds[bb]->h_end)){
					if(delta_h != 0){
						printf("something strange is going on, a particle is defined as below h_start and above h_end at the same time \n");
					}
					delta_h = ptr_bounds[bb]->h_end - p[ii].h;
					sbf = 1;

					if(delta_h < prad){
						force = bc_force*(delta_h/prad);
					}else{
						force = bc_force;
					}
					dmove = 0.5*force/mass*time*time;
					fdir[2] = fdir[2] + dmove;
				}

			}

			p[ii].r = p[ii].r + fdir[0];
			p[ii].theta = p[ii].theta + fdir[1];
			p[ii].h = p[ii].h + fdir[2];
		}
		bs++;
		/*printf("td = %f \n", td);*/
	}

}

/*			sbf = -1;
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

					if(strcmp(p[ii].ptype, "FA0") == 0){
						bc_force = ptr_bounds[bb]->force_FA0;
						prad = vars.FA_dia;
					}else if(strcmp(p[ii].ptype, "LG0") == 0){
						bc_force = ptr_bounds[bb]->force_LG0;
						prad = vars.LG_dia;
					}else if(strcmp(p[ii].ptype, "H2O") == 0){
						bc_force = ptr_bounds[bb]->force_H2O;
						prad = vars.H2O_dia;
					}else{
						printf("error particle type has no defined boundray force, ignoring \n");
					}
				}

				for(bc=0; bc<6; bc++){
					if((bc_list[bc] == -1)){
					} else if((bc_list[bc] == -2) && (bc == 0)){
						bc_list[bc] = ptr_points[vars.num_points_used -1]->rad - vars.H2O_dia*vars.luman_safe_depth;
					} else if((bc_list[bc] == -2) && (bc == 1)){
						bc_list[bc] = ptr_points[0]->rad;
					} else if((bc_list[bc] == -2) && (bc == 2)){
						bc_list[bc] = 0;
					} else if((bc_list[bc] == -2) && (bc == 3)){
						bc_list[bc] = vars.ROI_angle;
					} else if((bc_list[bc] == -2) && (bc == 4)){
						bc_list[bc] = 0;
					} else if((bc_list[bc] == -2) && (bc == 5)){
						bc_list[bc] = vars.ROI_height;
					} else if(bc_list[bc] < 0){
						printf("error undefined boundary code, check ini file for mistakes in boundary conditions, setting to -1 \n");
						bc_list[bc] = -1;
					}
				}

				for(bc=0; bc<6; bc++){
					if(bc_list[bc] != -1){
						dist = fabs(bc_list[bc] - pos_vec[bc/2]);
						if(dist < prad){
							force = bc_force*(dist/prad);
						}else{
							force = bc_force;
						}
						dmove = (0.5*(force/mass)*time*time);
						td = td + fabs(dmove);
						if((bc_list[bc] == 0)){
							fdir[0] = fdir[0] + dmove;
						} else if((bc_list[bc] == 1)){
							fdir[0] = fdir[0] - dmove;
						} else if((bc_list[bc] == 2)){
							fdir[1] = fdir[1] + dmove;
						} else if((bc_list[bc] == 3)){
							fdir[1] = fdir[1] - dmove;
						}else if((bc_list[bc] == 4)){
							fdir[2] = fdir[2] + dmove;
						} else if((bc_list[bc] == 5)){
							fdir[2] = fdir[2] - dmove;
						}
					}
				}*/
