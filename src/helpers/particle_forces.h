/*
 * particle_forces.h
 *
 *  Created on: 29/01/2016
 *      Author: nick
 */

#ifndef PARTICLE_FORCES_H_
#define PARTICLE_FORCES_H_

void calc_new_pos(struct particle* p, int pstart, int pend);
void update_selected_pos(struct particle* p, int pstart, int pend);

#endif /* PARTICLE_FORCES_H_ */
