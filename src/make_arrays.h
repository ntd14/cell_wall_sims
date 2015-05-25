/*
 * make_arrays.h
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */

#ifndef MAKE_ARRAYS_H_
#define MAKE_ARRAYS_H_

void free1Darray(double* array);
void free2Darray(double** array, int nrow);
void free3Darray(double*** array, int nrow, int ncol);

double* make1Darray(int nrow);
double** make2Darray(int nrow, int ncol);
double*** make3Darray(int nrow, int ncol, int ndep);

#endif /* MAKE_ARRAYS_H_ */
