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

/* build a generic function to interpolate properties between the points in the ini file. curently set to 10 (0 - 9) but could generalise? */

double get_interp_val_P(double r, char* interp_var)
{
	printf("in get interp \n");
	int ii = 0;

	point P;
	P = ptr_points[0];

	printf("%f, \n", P.rad);
	while(r <= P.rad)
	{
		ii++;
		P = ptr_points[ii];
		printf("%f \n", P.rad);
	}

	point Pouter = ptr_points[ii-1];
	point Pinner = ptr_points[ii];

	double Poutervar;
	double Pinnervar;

	if(strcmp(interp_var, "MFA") == 0)
	{
		Poutervar = Pouter.MFA;
		Pinnervar = Pinner.MFA;
	}
	else if(strcmp(interp_var, "MFA_SD") == 0)
	{
		Poutervar = Pouter.MFA_SD;
		Pinnervar = Pinner.MFA_SD;
	}

	double val = Poutervar + (Pinnervar - Poutervar)*(r - Pouter.rad)/(Pinner.rad - Pouter.rad);
	printf("leaving interp \n");

	return(val);
}
