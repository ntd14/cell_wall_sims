/*
 * par_defs.h
 *
 *  Created on: 22/05/2015
 *      Author: nick
 */

#ifndef PAR_DEFS_H_
#define PAR_DEFS_H_

/* All parameters to define the problem are stored here */

/* these are the physical space in nm that is modeled, currently assumes a cartesian R2 or R3 space */
int length_of_problem_space = 1000;
int height_of_problem_space = 1000;
int depth_of_problem_space = 0;

/* the MFA parameters, sd_MFA is the standard devation of the trendline directions BETWEEN MFs,
 * MFA_sd is the standard devation of the normal distrib that is selected from during the growth of the MF
 * all in radians
 */

double mean_MFA = 0.175;
double sd_MFA = 0.035;
double MFA_sd = 0.01;
double init_spacing_of_FA = 20; /*nm*/

/* cellulose fibril agregate properties,
 * num_of_C_chains is the number of particals which are used to model each fibril agregit
 * num_of_ags is the number of fibril agregits in the model
 */
int num_of_C_chains = 1;
int num_of_ags = 2;
/*6 parameters to describe the cellulose chains for poly-elipsoids*/
double R_C = 10;
double C_width_pos = 0.2;
double C_width_neg = 0.2;
double C_depth_pos = 0;
double C_depth_neg = 0;
double C_length_pos = 2;
double C_length_neg = 2;
double C_density = 1500; /*kg/m^3*/
/*parameters to define the contact models*/

/* lignin properties
 * num_lignin_clumps is the number of lignin particals to be used
 */
int num_lignin_clumps = 10;
/*6 parameters to describe the lignin clumps as poly-elipsoids*/
double L_width_pos = 1;
double L_width_neg = 1;
double L_depth_pos = 1;
double L_depth_neg = 1;
double L_length_pos = 1;
double L_length_neg = 1;
double L_density = 500; /* kg/m^3 */
/*parameters to define the contact models*/


/* trial varables remove later */
double a = 1;
double b = 3.3;

#endif /* PAR_DEFS_H_ */
