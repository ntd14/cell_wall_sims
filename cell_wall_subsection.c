
#include <stdio.h>
#include <stdlib.h>
#include "./src/helpers/get_ini_vars.h"
#include "./src/cell_wall_layer.h"
#include "./src/get_movement.h"
#include "./src/helpers/cart_and_cyl.h"

int main(void)
{
	printf("entering main \n");

	build_structs();

	struct particle* particles = calloc(vars.max_particles, sizeof(struct particle));
	if(particles == NULL)
	{
		printf("calloc failed creating particles in cell_wall_subsection, try and reduce max_particles in ini file \n");
		printf("exiting code due to lack of memory for given perameters \n");
		exit(0);
	}

	/*calloc a block of memory for max connections worth of particles created here*/

	struct particle** nlist_array = calloc((vars.max_connections*vars.max_particles), sizeof(struct particle*));
	if(particles == NULL)
	{
		printf("calloc failed creating nlist_array in cell_wall_subsection, try and reduce max_particles and/or max_connections in ini file \n");
		printf("exiting code due to lack of memory for given perameters \n");
		exit(0);
	}

	printf("build particles struct, creating CML \n");
	int num_of_particles = 0;
	/* should water be added before or after the FAs? could make whole domain fill with water before starting, but this will use a lot more memory */
	/* set up a boundary condition at the current P_inner radius that has an outward force equle to the amount of force needed to displace the water from the cell, uer defiend */
	num_of_particles = create_layer(particles, nlist_array, num_of_particles, P0, P1); /*have to thing about the cml, maybe this should have its own function that uses create layers functions*/
	/* could create cml in normal way, then go through and change some of the water to pectan, but would have to add a pectan particle type*/
	printf("exiting P0 P1 with %i particles created \n", num_of_particles);

	update_pos_burnin(0, num_of_particles, particles, 0.000001, 5);

	/*with the FAs allow a good amount of overlap with the connections to give the distributions in exp measruments of the thickneses,
	 * ie to other FAs an FA may only appear as say 10nm wide, so when they combine they are 20nm, or something like that
	 * where as to water/lignin they appear as 14nm, so when two combine they are viewed by water/lignin as 20nm, but alone as 14nm*/

	/* to do the water for the rest of the layers, add uniformly make FAs fixed delete when big overlap, move where little overlap*/
	/* to do lignification, randomly find water particles in the lignification zone, add a bit of noise, create lignin particle */

	printf("total num_of_particles = %i \n", num_of_particles);

	int ii, jj;
	FILE *allp = fopen("allp.js", "w");
		if (allp == NULL)
		{
			   printf("Error opening file!\n");
			   exit(1);
		}

		fprintf(allp, "var data = [];\n");
		for(ii = 0; ii < num_of_particles; ii++)
		{
			fprintf(allp, "data[%i] = new Object(); ", ii);
			fprintf(allp, "data[%i].uid = %i; ", ii, particles[ii].uid);
			fprintf(allp, "data[%i].ptype = '%s'; ", ii, particles[ii].ptype);
			fprintf(allp, "data[%i].r = %f; ", ii, particles[ii].r);
			fprintf(allp, "data[%i].theta = %f; ",ii, particles[ii].theta);
			fprintf(allp, "data[%i].h = %f; ", ii, particles[ii].h);
			fprintf(allp, "data[%i].nlistlen = %i; ", ii, particles[ii].nlistlen);

			fprintf(allp, "data[%i].nlist = [", ii);
			jj = 0;
			while(jj < (particles[ii].nlistlen - 1)){
					fprintf(allp, "%i, ", (*particles[ii].nlist[jj]).uid);
					jj++;
			}
			if(jj == (particles[ii].nlistlen - 1)){
				fprintf(allp, "%i", (*particles[ii].nlist[jj]).uid);
			}
			fprintf(allp, "];");

			fprintf(allp, "\n");
		}
		fclose(allp);

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

	free(nlist_array);
	nlist_array = NULL;
	free(particles);
	particles = NULL;

	return 0;
}




