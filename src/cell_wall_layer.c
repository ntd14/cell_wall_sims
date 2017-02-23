/*
 * cell_wall_layer.c
 *
 *  Created on: 8/01/2016
 *      Author: nick
 */



/*
 * make_CML.c
 *
 *  Created on: 12/10/2015
 *      Author: nick
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./helpers/get_ini_vars.h"
#include "./helpers/lists.h"
#include "./helpers/create_chains.h"
#include "./helpers/add_water.h"
#include "./helpers/search_funcs.h"
#include "cell_wall_layer.h"



/*then add what is currentlty in create_layer to a new function that creates the new points, and deals with water overlaps*/


/*then write create layer to call the above functions and distribute to suitable file structure*/
/* call CML_point to make the isotropic CML */
int create_layer(struct particle* p, struct particle** nlist_array, int num_of_particles, struct point Po, struct point Pi)
{

	int ii;
	int update_pos_counter = num_of_particles;
	int sarray_outer[2]; /* [0] number of points to start on the outer surface x axis, [1] y axis */
	int sarray_inner[2]; /* [0] number of points to start on the inner surface x axis, [1] y axis */

	/*call get_num_starting_points_line for the outer and inner surfaces*/
	get_num_starting_points_line(sarray_outer, Po.MFA, Po.rad, Po.FA_content); /*make generic for Px*/
	get_num_starting_points_line(sarray_inner, Pi.MFA, Pi.rad, Pi.FA_content);

	int npx_maxmin[2]; /* number of starting points in x direction at [0] outer and [1] inner */
	npx_maxmin[0] = (int) sarray_outer[0]*((Po.rad - Pi.rad)/vars.FA_dia) + 0.5;
	npx_maxmin[1] = (int) sarray_inner[0]*((Po.rad - Pi.rad)/vars.FA_dia) + 0.5;
	get_biggest_int(npx_maxmin); /* converting so that [0] is max number of points, [1] is min number */
	int npy_maxmin[2];/* number of starting points in xy direction at 0 outer and [1] inner */
	npy_maxmin[0] = (int) sarray_outer[1]*((Po.rad - Pi.rad)/vars.FA_dia) + 0.5;
	npy_maxmin[1] = (int) sarray_inner[1]*((Po.rad - Pi.rad)/vars.FA_dia) + 0.5;
	get_biggest_int(npy_maxmin); /* converting so that [0] is max number of points, [1] is min number */

	int pv_len_x = (int) (npx_maxmin[1] + ((npx_maxmin[0]-npx_maxmin[1])/2)); /* calc the total number of starting points in x direction */
	int pv_len_y = (int) (npy_maxmin[1] + ((npy_maxmin[0]-npy_maxmin[1])/2)); /* calc the total number of starting points in y direction */

	/*set memory aside to store the vector of x starting points*/
	/* create starting points vectors*/
	double *points_vec_x = calloc(pv_len_x, sizeof(double));
	if(points_vec_x == NULL)
	{
		printf("calloc failed creating points_vec_x in make_CML \n");
		printf("exiting code, possibly due to lack of memory for given perameters \n");
		exit(0);
	}

	/* call gen_starting_points to get all of the starting points over the layer on x axis*/
	gen_starting_points(npx_maxmin[0], npx_maxmin[1], Pi.rad, Po.rad, points_vec_x, pv_len_x);

	/*storing the particles that are started on the x surface*/
	for(ii = 0; ii < pv_len_x; ii++){
		p[update_pos_counter].uid = update_pos_counter;
		p[update_pos_counter].r = points_vec_x[ii];
		p[update_pos_counter].theta = vars.ROI_angle*(rand()/(double) RAND_MAX);
		p[update_pos_counter].h = 0; /*should this have some noise added into it?*/
		p[update_pos_counter].nr = p[update_pos_counter].r;
		p[update_pos_counter].ntheta = p[update_pos_counter].theta;
		p[update_pos_counter].nh = p[update_pos_counter].h;
		p[update_pos_counter].ptype = "FA0";
		p[update_pos_counter].nlistlen = 0;
		p[update_pos_counter].nlist = &nlist_array[update_pos_counter*vars.max_connections];
		update_pos_counter++;
	}
	free(points_vec_x);
	points_vec_x = NULL;

	double* points_vec_y = calloc(pv_len_y, sizeof(double));
	if(points_vec_y == NULL)
	{
		printf("calloc failed creating points_vec_y in make_CML \n");
		printf("exiting code, possibly due to lack of memory for given perameters \n");
		exit(0);
	}


	/* call gen_starting_points to get starting points on y axis*/
	gen_starting_points(npy_maxmin[0], npy_maxmin[1], Pi.rad, Po.rad, points_vec_y, pv_len_y);

	/* storing the particles that are started on the y surface, if statment to deal with the side they start on depending on the MFA */
	for(ii = 0; ii < pv_len_y; ii++){
		p[update_pos_counter].uid = update_pos_counter;
		p[update_pos_counter].r = points_vec_y[ii];
		p[update_pos_counter].h = vars.ROI_height*(rand()/(double) RAND_MAX);
		p[update_pos_counter].ptype = "FA0";
		p[update_pos_counter].nlistlen = 0;
		p[update_pos_counter].nlist = &nlist_array[update_pos_counter*vars.max_connections];

		if((Po.MFA + Pi.MFA)/2 > 0){
			p[update_pos_counter].theta = 0;/*should this have some noise added into it?*/
		}else{
			p[update_pos_counter].theta = vars.ROI_angle; /*should this have some noise added into it?*/
		}

		p[update_pos_counter].nr = p[update_pos_counter].r;
		p[update_pos_counter].ntheta = p[update_pos_counter].theta;
		p[update_pos_counter].nh = p[update_pos_counter].h;

		update_pos_counter++;
	}
	free(points_vec_y);
	points_vec_y = NULL;

	int start_points_firstp = num_of_particles;
	int start_points_lastp = update_pos_counter;

	int start_point = start_points_firstp;
	int end_point = start_points_lastp;
	int used = 1;
	while(used > 0){
		used = add_particles_to_chains(p, nlist_array, start_point, end_point, Po, Pi);
		start_point = start_point + used;
		end_point = end_point + used;
	}

	update_pos_counter = end_point;
	int FAmain_startp = start_points_lastp;
	int FAmain_endp = update_pos_counter;




	/*call to function that adds water in available spaces*/
	/*update_pos_counter = add_water(p, nlist_array, num_of_particles, update_pos_counter, Po, Pi);*/

	int H2O_startp = FAmain_endp;
	int H2O_endp = update_pos_counter;

	/*call to search function which finds all connections and stores them*/

	/*checking starting FA points for connections with eachother*/
	selective_search(p, start_points_firstp, start_points_lastp, start_points_firstp, start_points_lastp);
	/*checking starting FA points for connectiosn with the FA chain particles*/
	selective_search(p, start_points_firstp, start_points_lastp, FAmain_startp, FAmain_endp);
	/*checking FA chain particles for starting points with them selfs*/
	selective_search(p, FAmain_startp, FAmain_endp, FAmain_startp, FAmain_endp);
	/*checking FA chain particles for connections to water*/
	selective_search(p, FAmain_startp, FAmain_endp, H2O_startp, H2O_endp);
	/*checking water for connections with themselfs*/
	selective_search(p, H2O_startp, H2O_endp, H2O_startp, H2O_endp);

	return(update_pos_counter);
}



