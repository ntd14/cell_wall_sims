/*
 * lists.c
 *
 *  Created on: 24/09/2015
 *      Author: nick
 */

#include "get_ini_vars.h"

/* IF YOU CHANGE THESE REMEBER TO UPDATE THE LENGTHS IN THE HEADER FILE */

char* list_points[10] = {"P0", "P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8", "P9"};

point* ptr_points[10] = {&P0, &P1, &P2, &P3, &P4, &P5, &P6, &P7, &P8, &P9};

char* list_cons[6] = {"FA0FA0con", "FA0LG0con", "FA0H2Ocon", "LG0LG0con", "LG0H2Ocon", "H2OH2Ocon"};

con* ptr_cons[6] = {&FA0FA0con, &FA0LG0con, &FA0H2Ocon, &LG0LG0con, &LG0H2Ocon, &H2OH2Ocon};

char* list_bounds[9] = {"B_top", "B_bot", "B_theta_min", "B_theta_max", "B_luman", "B_per0", "B_per1", "B_per2", "B_per3"};

bound* ptr_bounds[9] = {&B_top, &B_bot, &B_theta_min, &B_theta_max, &B_luman, &B_per0, &B_per1, &B_per2, &B_per3};
