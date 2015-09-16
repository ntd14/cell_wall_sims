
#include <stdio.h>
#include <stdlib.h>
#include "./src/helpers/iniparser.h" /* from http://ndevilla.free.fr/iniparser/html/index.html*/

int main(void)
{
	printf("entering main \n");
	const char * properties = "properties.ini";
	dictionary* d = iniparser_load(properties);
	const char * ROI_angle_lab = "vars:ROI_angle";
	double ROI_angle = iniparser_getdouble(d, ROI_angle_lab, 99999999999);
	printf("ini ROI_angle in rads: %f ", ROI_angle);
	iniparser_freedict(d);

	/* Here will include:
 */
/* call to some ini file with user adjustable varables */
/* load the varables to a useable format */
/* build a generic function to interpolate properties between the points in the ini file. curently set to 9 but could generalise? */
/* write cartesian<>cylindrical conversion function */
/* setup a cylindrical coord system */
/* subset to the region defined in the ini */
/* build CML */
/* build boundary conditions for togur pressure etc */
/* fill inside with H20 particles */
/* take inner most points at each end of the cylinder, ie the tips, what was doing tip growth now creates the FAs */
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




