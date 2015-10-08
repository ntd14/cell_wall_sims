
#include <stdio.h>
#include <stdlib.h>
#include "./src/helpers/get_ini_vars.h"

#include "./src/helpers/interp_funs.h"

int main(void)
{
	printf("entering main \n");

	build_structs();

	printf("finished main \n");


	/* Here will include: */

/* check cartesian<>cylindrical conversion function */

/* build boundary conditions for togur pressure, sourding cells etc, this may need to be ini input info?
 * maybe do four quarters of the cell and the top/bottom, as boundaries each with there own properties in the ini
 * would then have to update the build_structs to include the new values
 * could maybe just have say x number of boundary conditions and give the extreme coords that they cover
 *
 * could take P0 rad and then just have a check somewhere that takes into account the BC if r >P0 rad,
 * rather than any direct particle boundary*/

/* build CML in subseted ROI defined in the ini file*/
	/* CML can just be FAs to start with, will have to work out how to have them randomly orentated, then fill the CML with lignin later */

/* fill inside with H20 particles */

/* take inner most points at each end of the cylinder, ie the tips, what was doing tip growth now creates the FAs */
/* generic function to deal with force applied to each particle. outermost point = 0, linear to intersept, linear to very large inside intersept */
/* run step to stable state */
/* move up/down a bit using the verious randomnesses -- controled by functions with space and time/age dependence -- */
/* when a FA hits the end of the ROI need some logic as to where to start it next time to keep the chem proportions correct */
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




