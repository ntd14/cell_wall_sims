
#include <stdio.h>
#include <stdlib.h>
#include "./src/helpers/get_ini_vars.h"

#include "./src/helpers/cart_and_cyl.h"

int main(void)
{
	printf("entering main \n");

	build_structs();

	struct particle* old_particles = calloc(vars.max_particles,sizeof(struct particle));
	if(old_particles == NULL)
	{
		printf("calloc failed when init particle* old_particles in cell_wall_subsection \n");
	}



	/* Here will include: */

/* check cartesian<>cylindrical conversion function */

/* Can I just calculate a new x position from the angle in cart then convert that to a theta val? */

/* need some way to convert the conventional MFA into an MFA applied to the angle coord in cylindrical system */
/* calc total circunfrence given r at a point
 * calc the change in x in the cart system
 * deta theta = delta x / cir * 2*M_PI Might be able to calc this once for each point, along with the given SD at that point
 * change in depth and height coords are equel the change in cart coords -- check this --*/

	/* have a point in cyl
	 * convert to cart
	 * calc new point cart pos
	 * convert new point to cyl
	 */


/* Now have the BCs, still need to write a check to see if a given particle is outside the boundary or not*/

/* calc coords of subseted ROI defined in the ini file */

/* build CML*/
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
	printf("finished main \n");

	free(old_particles);
	old_particles = NULL;

	return 0;
}

/* structs */

/* uid */
/* Ptype */
/* coords */
/* conns */
/* creation time */




