/*
 * get_ini_vars.h
 *
 *  Created on: 17/09/2015
 *      Author: nick
 */

#ifndef GET_INI_VARS_H_
#define GET_INI_VARS_H_

typedef struct var {
	double ROI_angle;
	double ROI_height;
	double H2O_dia;
	double FA_dia;
	double LG_dia;
	int FA_steps_PT;
	int LG_steps_PT;
	int LG_start_time;
} var;
var vars;

typedef struct point {
	double rad;
	double MFA;
	double MFA_SD;
	double depth_SD;
	double FA_content;
	double LG_content;
} point;

point P0;
point P1;
point P2;
point P3;
point P4;
point P5;
point P6;
point P7;
point P8;
point P9;

typedef struct con {
	double dist;
	double met;
	double met_force;
	double max_force;
} con;

con FA0FA0con;
con FA0LG0con;
con FA0H2Ocon;
con LG0LG0con;
con LG0H2Ocon;
con H2OH2Ocon;

void build_structs();

#endif /* GET_INI_VARS_H_ */
