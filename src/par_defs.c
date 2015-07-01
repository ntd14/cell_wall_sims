/*
 * par_defs.c
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */
#include "par_defs.h"
#include <math.h>

/* define size of problem space in nm */
int length_of_problem_space = 100;
int height_of_problem_space = 100;
int depth_of_problem_space = 100;

double max_ndist = 5;
int max_cons = 500;

/*see header file for def of each entry*/
part_defs FA1 = {"FA1", 3.22625, 1500.0, M_PI/2, M_PI/2, 0, 0, 500, 500}; /* aprox 35% */
part_defs FA2 = {"FA2", 2.0, 1500.0, 0, 0, 0, 0, 8, 0}; /* Note these chains run around the FA1 core use r = Rsin(π/n)/[1 - sin(π/n)] and R = r[1 - sin(π/n)]/sin(π/n)
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 * to pick the FA1 and FA2 radii as well as the chain length for FA2, calculator here http://www.had2know.com/academics/outer-circular-ring-radii-formulas-calculator.html*/
part_defs HC1 = {"HC1", 3.22625, 1500.0, M_PI/2, M_PI/2, 0, 0, 20, 2000};/* aprox 20% */
part_defs HC2 = {"HC2", 2.0, 1500.0, 0, 0, 0, 0, 0, 8, 0}; /* see FA2 comment */
part_defs H2O = {"H2O", 4.0, 1000.0, 0, 0, 0, 0, 0, 0}; /* aprox 30%, leave number of particles unknown it is calculated later */

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
