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

double get_interp_val_P(double r, char* interp_var)
{
	printf("in get interp \n");
	int ii = 0;

	point P;
	P = *ptr_points[0];
	while(r <= P.rad)
	{
		ii++;
		P = *ptr_points[ii];

	}
	if(ii >= vars.num_points_used)
	{
		printf("WARNGING: the point used is excluded by the ini file \n");
	}

	point Pouter = *ptr_points[ii-1];
	point Pinner = *ptr_points[ii];

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

	else if(strcmp(interp_var, "depth_SD") == 0)
	{
		Poutervar = Pouter.depth_SD;
		Pinnervar = Pinner.depth_SD;
	}

	else if(strcmp(interp_var, "depth_SD") == 0)
	{
		Poutervar = Pouter.FA_content;
		Pinnervar = Pinner.FA_content;
	}

	else if(strcmp(interp_var, "depth_SD") == 0)
	{
		Poutervar = Pouter.LG_content;
		Pinnervar = Pinner.LG_content;
	}

	else
	{
		printf("WARNING: Call to INTERP_FUNS had invalid property \n");
	}

	double val = Poutervar + (Pinnervar - Poutervar)*(r - Pouter.rad)/(Pinner.rad - Pouter.rad);
	printf("leaving interp \n");

	return(val);
}
