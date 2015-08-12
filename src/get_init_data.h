/*
 * get_init_data.h
 *
 *  Created on: 21/05/2015
 *      Author: nick
 */

#ifndef GET_INIT_DATA_H_
#define GET_INIT_DATA_H_

int create_init_state(double * coor_array, int ca_len);

void load_particle_into_struct(struct particle* old_particles, double** init_coors_ptr, part_defs* pl, int plist_len, struct particle** nlist_array);

void create_sat_bonds(struct particle* old_particles, int plist_len, part_defs* pl);

void create_chain_bonds(struct particle* old_particles, int plist_len, struct particle** nlist_array, part_defs* pl);

void create_chain_surface(struct particle* old_particles, int plist_len, struct particle** nlist_array, part_defs* pl, part_defs* pl_centre);

#endif /* GET_INIT_DATA_H_ */
