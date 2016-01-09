/*
 * interp_funs.c
 *
 *  Created on: 17/09/2015
 *      Author: nick
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "get_ini_vars.h"
#include "interp_funs.h"
#include "lists.h"

/* function to interpolate properties between the points in the ini file */


double get_interp_val_P(double r, double r_outer, double r_inner, double Poutervar, double Pinnervar)
{

	double val = Poutervar + (Pinnervar - Poutervar)*(r - r_outer)/(r_inner - r_outer);

	return(val);
}
