/*
 * cart_and_cyl.h
 *
 *  Created on: 25/09/2015
 *      Author: nick
 */

#ifndef CART_AND_CYL_H_
#define CART_AND_CYL_H_

void cart_to_cyl(double* xyz_array, double* rtz_array);

void cyl_to_cart(double* rtz_array, double* xyz_array);

double arc_length(double d, double angle);

#endif /* CART_AND_CYL_H_ */
