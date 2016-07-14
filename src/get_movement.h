/*
 * get_movement.h
 *
 *  Created on: 24/02/2016
 *      Author: nick
 */

#ifndef SRC_GET_MOVEMENT_H_
#define SRC_GET_MOVEMENT_H_


void update_pos_burnin(int pstart, int pend, struct particle* p, double time_step, int num_burnin_steps, double inner_edge);

#endif /* SRC_GET_MOVEMENT_H_ */
