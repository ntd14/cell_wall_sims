/*
 * get_init_data.h
 *
 *  Created on: 21/05/2015
 *      Author: nick
 */

#ifndef GET_INIT_DATA_H_
#define GET_INIT_DATA_H_

int create_init_state(double * coor_array, int ca_len);

void load_particle_into_struct(struct particle* old_particles, double** init_coors_ptr, part_defs pl, int plist_len);

#endif /* GET_INIT_DATA_H_ */
