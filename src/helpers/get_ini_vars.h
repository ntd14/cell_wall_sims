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
	int num_points_used;
	int num_cons_used;
	int num_bounds_used;
	int max_particles;
	int max_connections;
} var;
struct var vars;

typedef struct point {
	char* name;
	double rad;
	double MFA;
	double MFA_SD;
	double depth_SD;
	double FA_content;
	int max_FA_length;
	double LG_content;
} point;

struct point P0;
struct point P1;
struct point P2;
struct point P3;
struct point P4;
struct point P5;
struct point P6;
struct point P7;
struct point P8;
struct point P9;

typedef struct con {
	char* name;
	double dist;
	double met;
	double met_force;
	double max_force;
} con;

struct con FA0FA0con;
struct con FA0LG0con;
struct con FA0H2Ocon;
struct con LG0LG0con;
struct con LG0H2Ocon;
struct con H2OH2Ocon;

typedef struct bound {
	char* name;
	double r_start;
	double r_end;
	double force_FA0;
	double force_LG0;
	double force_H2O;
} bound;

struct bound B_top;
struct bound B_bot;
struct bound B0;
struct bound B1;
struct bound B2;
struct bound B3;

struct particle {
	int uid;
	double r;
	double theta;
	double h;
	double nr;
	double ntheta;
	double nh;
	char* ptype;
	int nlistlen;
	struct particle** nlist;
};


void build_structs();

#endif /* GET_INI_VARS_H_ */
