/*
 * par_defs.c
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */
#include "par_defs.h"
#include <math.h>

/* define size of problem space in nm */
int length_of_problem_space = 1000;
int height_of_problem_space = 1000;
int depth_of_problem_space = 1000;

double max_ndist = 13.9;
int max_cons = 28; /* if max_n_dist >14 need 126 connections, if < 14 need 28 connections */

/*see header file for def of each entry*/
part_defs FA1 = {"FA1", 7.0, 1500.0, M_PI/2, M_PI/2, 0, 0, 500, 500}; /* aprox 35% */
part_defs HC1 = {"HC1", 7.0, 1500.0, M_PI/2, M_PI/2, 0, 0, 20, 2000}; /* aprox 20% */
part_defs H2O = {"H2O", 7.0, 1000.0, 0.0, 0.0, 0.0, 0.0, 0, 0}; /* aprox 30%, NOTE number of H2O is manually calculated as:
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	   *(length_of_problem_space/(H2O.R*2) + 1)*(height_of_problem_space/(H2O.R*2) + 1)*(depth_of_problem_space/(H2O.R*2) + 1);*/
part_defs LG1 = {"LG1", 7.0,  500.0, 0.0, 0.0, 0.0, 0.0, 0, 0}; /* aprox 15% */

con_defs FA1FA1strong = {"FA1", "FA1", 14, 100, -1000, 0, 14, 1000};
con_defs FA1FA1weak = {"FA1", "FA1", 14, 100, -1000, 0, 14, 1000};
con_defs HC1HC1strong = {"HC1", "HC1", 14, 100, -1000, 0, 14, 1000};
con_defs HC1HC1weak = {"HC1", "HC1", 14, 100, -1000, 0, 14, 1000};
con_defs H2OH2O = {"H2O", "H2O", 14, 100, -1000, 0, 14, 1000};

con_defs FA1HC1 = {"FA1", "HC1", 14, 100, -1000, 0, 14, 1000};
con_defs FA1H2O = {"FA1", "H2O", 14, 100, -1000, 0, 14, 1000};
con_defs FA1LG1 = {"FA1", "LG1", 14, 100, -1000, 0, 14, 1000};
con_defs HC1H2O = {"HC1", "H2O", 14, 100, -1000, 0, 14, 1000};
con_defs HC1LG1 = {"HC1", "LG1", 14, 100, -1000, 0, 14, 1000};
con_defs H2OLG1 = {"H2O", "LG1", 14, 100, -1000, 0, 14, 1000};
