/*
 * create_chains.h
 *
 *  Created on: 28/01/2016
 *      Author: nick
 */

#ifndef SRC_HELPERS_CREATE_CHAINS_H_
#define SRC_HELPERS_CREATE_CHAINS_H_

void get_num_starting_points_line(int* sarray, double mfa, double r, double content);
int add_particles_to_chains(struct particle* p, struct particle** nlist_array, int start_point, int end_point, struct point Po, struct point Pi);
void gen_starting_points(int np_inner, int np_outer, double phy_inner, double phy_outer, double* points_vec, int pv_len);
void get_biggest_double(double* maxmin);
void get_biggest_int(int* maxmin);

#endif /* SRC_HELPERS_CREATE_CHAINS_H_ */
