/*
 * interp_funs.c
 *
 *  Created on: 17/09/2015
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "interp_funs.h"
#include "get_ini_vars.h"

/* build a generic function to interpolate properties between the points in the ini file. curently set to 10 (0 - 9) but could generalise? */

double get_interp_val_P(double r, char* interp_var)
{
	double val;
	val = 1;
/* while r >=P.rad cycle through point structs
 * 		val = (P-1).val + (P.val - (P-1).val)*(r - (P-1).rad)/(P.rad - (P-1).rad)
 */
	return(val);
}
