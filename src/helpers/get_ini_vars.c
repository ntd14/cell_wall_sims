/*
 * get_ini_vars.c
 *
 *  Created on: 17/09/2015
 *      Author: nick
 */
#include <stdio.h>
#include <string.h>
#include "iniparser.h" /* from http://ndevilla.free.fr/iniparser/html/index.html*/
#include "get_ini_vars.h"
#include "lists.h"

void test_ini_import()
{
	const char * properties = "properties.ini";
	dictionary* d = iniparser_load(properties);
	const char * TEST_VAR_lab = "vars:TEST_VAR";
	int TEST_VAR = iniparser_getint(d, TEST_VAR_lab, 0);
	if(TEST_VAR == 1){
		printf("ini test pass \n");
	}
	else {
		printf("\n #### WARNING #### \n");
		printf("ini test failed with val: %d \n\n", TEST_VAR);
	}
	iniparser_freedict(d);
}

void vars_import()
{
	const char* properties = "properties.ini";
	dictionary* d = iniparser_load(properties);
	char tmp1[30];

	strcpy(tmp1, "vars:ROI_angle");
	vars.ROI_angle = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, "vars:H2O_dia");
	vars.H2O_dia = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, "vars:FA_dia");
	vars.FA_dia = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, "vars:LG_dia");
	vars.LG_dia = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, "vars:FA_steps_PT");
	vars.FA_steps_PT = iniparser_getint(d, tmp1, 0);

	strcpy(tmp1, "vars:LG_steps_PT");
	vars.LG_steps_PT = iniparser_getint(d, tmp1, 0);

	strcpy(tmp1, "vars:LG_start_time");
	vars.LG_start_time = iniparser_getint(d, tmp1, 0);

	strcpy(tmp1, "vars:num_points_used");
	vars.num_points_used = iniparser_getint(d, tmp1, 0);

	strcpy(tmp1, "vars:num_cons_used");
	vars.num_cons_used = iniparser_getint(d, tmp1, 0);

	strcpy(tmp1, "vars:max_particles");
	vars.max_particles = iniparser_getint(d, tmp1, 0);

	strcpy(tmp1, "vars:num_bounds_used");
	vars.num_bounds_used = iniparser_getint(d, tmp1, 0);

	iniparser_freedict(d);

}

void point_import(char* p, point* P)
{
	const char* properties = "properties.ini";
	dictionary* d = iniparser_load(properties);
	char tmp1[30];
	char tmp2[30];

	strcpy(tmp1, p);
	P->name = tmp1;

	strcpy(tmp2, ":rad");
	strcat(tmp1, tmp2);
	P->rad = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, p);
	strcpy(tmp2, ":MFA");
	strcat(tmp1, tmp2);
	P->MFA = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, p);
	strcpy(tmp2, ":MFA_SD");
	strcat(tmp1, tmp2);
	P->MFA_SD = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, p);
	strcpy(tmp2, ":depth_SD");
	strcat(tmp1, tmp2);
	P->depth_SD = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, p);
	strcpy(tmp2, ":max_FA_length");
	strcat(tmp1, tmp2);
	P->max_FA_length = iniparser_getint(d, tmp1, 0);

	strcpy(tmp1, p);
	strcpy(tmp2, ":FA_content");
	strcat(tmp1, tmp2);
	P->FA_content = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, p);
	strcpy(tmp2, ":LG_content");
	strcat(tmp1, tmp2);
	P->LG_content = iniparser_getdouble(d, tmp1, 0);

	iniparser_freedict(d);

}

void con_import(char* c, con* C)
{
	const char* properties = "properties.ini";
	dictionary* d = iniparser_load(properties);
	char tmp1[30];
	char tmp2[30];

	strcpy(tmp1, c);
	C->name = tmp1;

	strcpy(tmp2, ":dist");
	strcat(tmp1, tmp2);
	C->dist = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, c);
	strcpy(tmp2, ":met");
	strcat(tmp1, tmp2);
	C->met = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, c);
	strcpy(tmp2, ":met_force");
	strcat(tmp1, tmp2);
	C->met_force = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, c);
	strcpy(tmp2, ":max_force");
	strcat(tmp1, tmp2);
	C->max_force = iniparser_getdouble(d, tmp1, 0);

	iniparser_freedict(d);

}

void bound_import(char* b, bound* B)
{
	const char* properties = "properties.ini";
	dictionary* d = iniparser_load(properties);
	char tmp1[30];
	char tmp2[30];

	strcpy(tmp1, b);
	B->name = tmp1;

	strcpy(tmp1, b);
	strcpy(tmp2, ":r_start");
	strcat(tmp1, tmp2);
	B->r_start = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, b);
	strcpy(tmp2, ":r_end");
	strcat(tmp1, tmp2);
	B->r_end = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, b);
	strcpy(tmp2, ":force_FA0");
	strcat(tmp1, tmp2);
	B->force_FA0 = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, b);
	strcpy(tmp2, ":force_LG0");
	strcat(tmp1, tmp2);
	B->force_LG0 = iniparser_getdouble(d, tmp1, 0);

	strcpy(tmp1, b);
	strcpy(tmp2, ":force_H2O");
	strcat(tmp1, tmp2);
	B->force_H2O = iniparser_getdouble(d, tmp1, 0);

	iniparser_freedict(d);

}

void build_structs()
{
	test_ini_import();

	printf("starting building structs from ini file \n");

	vars_import();

	char p[3];
	int ii;
	for(ii=0; ii < vars.num_points_used; ii++)
	{
		strcpy(p, list_points[ii]);
		point_import(p, ptr_points[ii]);
	}
	char c[10];
	for(ii=0; ii < vars.num_cons_used; ii++)
	{
		strcpy(c, list_cons[ii]);
		con_import(c, ptr_cons[ii]);
	}

	char b[10];
	for(ii=0; ii < vars.num_bounds_used; ii++)
	{
		strcpy(b, list_bounds[ii]);
		bound_import(b, ptr_bounds[ii]);
	}

	printf("finished building structs from ini file \n");
}


