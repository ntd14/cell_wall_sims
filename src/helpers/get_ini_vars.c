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


void build_structs()
{
	test_ini_import();

	printf("starting building structs from ini file \n");

	vars_import();

	char* list_points[] = {"P0", "P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8", "P9"};
	point* ptr_points[] = {&P0, &P1, &P2, &P3, &P4, &P5, &P6, &P7, &P8, &P9};
	char* list_cons[] = {"FA0FA0con", "FA0LG0con", "FA0H2Ocon", "LG0LG0con", "LG0H2Ocon", "H2OH2Ocon"};
	con* ptr_cons[] = {&FA0FA0con, &FA0LG0con, &FA0H2Ocon, &LG0LG0con, &LG0H2Ocon, &H2OH2Ocon};

	pc_lists* ptr_pclists = &pclists;

	ptr_pclists->ptr_points = ptr_points;
	ptr_pclists->list_points = list_points;
	ptr_pclists->ptr_cons = ptr_cons;
	ptr_pclists->list_cons = list_cons;

	printf("%s \n", list_points[1]);

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

	printf("finished building structs from ini file \n");
}


