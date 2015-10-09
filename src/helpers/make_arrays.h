/*
 * make_arrays.h
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */

#ifndef MAKE_ARRAYS_H_
#define MAKE_ARRAYS_H_

int ind2D(int i, int j, int nrow, int ncol);

int ind3D(int i, int j, int k, int nrow, int ncol, int ndep);

double* make1Darray(int len);

double* make2Darray(int nrow, int ncol);

double* reduce2Darray(double* old_array, int new_nrow, int new_ncol);

int* make1Darray_int(int len);

int* make2Darray_int(int nrow, int ncol);


/*void reduce1Darray(double* old_array, int old_len, double* new_array, int new_len);



void reduce3Darray(double* old_array, int old_nrow, int old_ncol, int old_ndep, double* new_array, int new_nrow, int new_ncol, int new_ndep);*/

#endif /* MAKE_ARRAYS_H_ */
