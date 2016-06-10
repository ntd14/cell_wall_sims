/*
 * search_funcs.c
 *
 *  Created on: 28/01/2016
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "./get_ini_vars.h"
#include "./lists.h"

void selective_search(struct particle* p, int sp1, int ep1, int sp2, int ep2){
	int ii, jj, jjst;
	double bd, rdist, hdist, tdist, dtheta;
	con* cptr;
	char cons1[10];
	char cons2[10];

	for(ii = sp1; ii < ep1; ii++){
		if((sp1 == sp2) & (ep1 == ep2)){
			jjst = ii+1;
		}else{
			jjst = sp2;
		}
		/*get particle type*/
		for(jj = jjst; jj < ep2; jj++){
			strcpy(cons1, p[ii].ptype);
			strcpy(cons2, p[jj].ptype);
			strcat(cons1, cons2);
			strcat(cons1, "con");
			/*call function that gets bonding dist from connection name*/
			cptr = con_ptr_name(cons1);
			bd = cptr->dist;
			/*get dist between the two particles*/
			rdist = fabs(p[ii].r - p[jj].r);
			if(rdist <= bd){
				hdist = fabs(p[ii].h - p[jj].h);
				if(hdist <= bd){
					/*convert theta to tdist*/
					dtheta = fabs(p[ii].theta - p[jj].theta);
					tdist = sqrt(pow(p[ii].r ,2) + pow(p[jj].r, 2) - 2*p[ii].r*p[jj].r*cos(dtheta));
					if(tdist <= bd){
						if((p[ii].nlistlen > vars.max_connections) || (p[jj].nlistlen > vars.max_connections)){
							printf("max connections exceeded, try increaseing max_connections but dont exceed ram capacity\n");
							printf("exiting code now \n");
							exit(0);
						}

						p[ii].nlist[p[ii].nlistlen] = &p[jj];
						p[jj].nlist[p[jj].nlistlen] = &p[ii];

						p[ii].nlistlen = p[ii].nlistlen + 1;
						p[jj].nlistlen = p[jj].nlistlen + 1;
					}
				}
			}
		}
	}
}
