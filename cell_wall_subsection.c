/*
 * twoD_single_pore.c
 *
 *  Created on: 21/05/2015
 *      Author: nick
 *
 *  This is the main trunk file for the implementation.
 */

#include <stdio.h>
#include <stdlib.h>


int main(void) /*this may change to take in arguments later*/
{
	printf("entering main \n");
	int ii;
/*
 * Here will include:
 * \
/* call to some ini file with user adjustable varables */
/* setup a cylindrical coord system */
/* write cartesian<>cylindrical conversion function */
/* subset to the region defined in the ini */
/* build CML, isotropic, with from ini */
/* build boundary conditions for togur pressure etc */
/* fill inside with H20 particles */
/* take inner most points at each end of the cylinder, ie the tips, */
/* what was doing tip growth now creates the FAs */
/* run step to stable state */
/* move up/down a bit using the verious randomnesses -- controled by functions with space and time/age dependence -- */
/* run step to stable */
/* loop it until built */
/* somehow set rate */
/* if close enough, FAs link to form big FAs */
/* at some point start lignification */
	return 0;
}

/* structs */

/* uid */
/* Ptype */
/* coords */
/* conns */
/* creation time */

/* ptype1 */
/* ptype2 */
/* function of force */




