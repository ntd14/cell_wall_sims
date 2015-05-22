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
int length_of_problem_space = 100;
int height_of_problem_space = 100;
/* int depth_of_area = 0; will be included later */

/* the MFA parameters, sd_MFA is the standard devation of the trendline directions BETWEEN MFs,
 * MFA_sd is the standard devation of the normal distrib that is selected from during the growth of the MF
 * all in radians
 */
double mean_MFA = 0.175;
double sd_MFA = 0.35;
double MFA_sd = 0.01;

/* cellulose fibril agregate properties,
 * num_of_C_chains is the number of particals which are used to model each fibril agregit
 * num_of_ags is the number of fibril agregits in the model
 */
int num_of_C_chains = 1;
int num_of_ags = 2;
/*6 parameters to describe the cellulose chains for poly-elipsoids*/
/* longest direction is goverened by getting to grid points and is calculated later
 * C_length_ratio is the ratio between the pos and neg radiouses in the length to be calced later
 * all in nm
 */
int C_width_pos = 5;
int C_width_neg = 5;
int C_depth_pos = 5;
int C_depth_neg = 5;
double C_length_ratio = 1;
/*parameters to define the contact models*/

/* lignin properties
 * num_lignin_clumps is the number of lignin particals to be used
 */
int num_lignin_clumps = 10;
/*6 parameters to describe the lignin clumps as poly-elipsoids*/
int L_width_pos = 10;
int L_width_neg = 10;
int L_depth_pos = 10;
int L_depth_neg = 10;
int L_length_pos = 10;
int L_length_neg = 10;
/*parameters to define the contact models*/



/* trial varables remove later */
double a = 1;
double b = 3.3;

#endif /* PAR_DEFS_H_ */
