/*
 * lists.c
 *
 *  Created on: 24/09/2015
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_ini_vars.h"
#include "lists.h"

/* IF YOU CHANGE THESE REMEBER TO UPDATE THE LENGTHS IN THE HEADER FILE */

char* list_points[10] = {"P0", "P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8", "P9"};

point* ptr_points[10] = {&P0, &P1, &P2, &P3, &P4, &P5, &P6, &P7, &P8, &P9};

char* list_cons[6] = {"FA0FA0con", "FA0LG0con", "FA0H2Ocon", "LG0LG0con", "LG0H2Ocon", "H2OH2Ocon"};

con* ptr_cons[6] = {&FA0FA0con, &FA0LG0con, &FA0H2Ocon, &LG0LG0con, &LG0H2Ocon, &H2OH2Ocon};

char* list_bounds[6] = {"B_top", "B_bot", "B0", "B1", "B2", "B3"};

bound* ptr_bounds[6] = {&B_top, &B_bot, &B0, &B1, &B2, &B3};



point* point_ptr_name(char name[10]){
	int ii = 0;
	char pname[10];
	strcpy(pname, list_points[ii]);

	while((strcmp(pname, name) != 0) & (ii < vars.num_points_used - 1)){
		ii++;
		strcpy(pname, list_points[ii]);
	}

	if(ii >= vars.num_points_used){
		printf("no point found \n");
		exit(0);
	}
	point* pptr = ptr_points[ii];
	return(pptr);
}


con* con_ptr_name(char name[10]){
	int ii = 0;
	char pname[10];
	strcpy(pname, list_cons[ii]);

	while((strcmp(pname, name) != 0) & (ii < vars.num_cons_used - 1)){
		ii++;
		strcpy(pname, list_cons[ii]);
	}

	if(ii >= vars.num_cons_used){
		printf("no connection found  \n");
		exit(0);
	}
	con* cptr = ptr_cons[ii];
	return(cptr);
}


bound* bound_ptr_name(char name[10]){
	int ii = 0;
	char pname[10];
	strcpy(pname, list_bounds[ii]);

	while((strcmp(pname, name) != 0) & (ii < vars.num_bounds_used - 1)){
		ii++;
		strcpy(pname, list_bounds[ii]);
	}

	if(ii >= vars.num_bounds_used){
		printf("no bound found \n");
		exit(0);
	}
	bound* bptr = ptr_bounds[ii];
	return(bptr);
}
