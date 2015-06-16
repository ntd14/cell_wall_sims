/*
 * make_arrays.h
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */

#ifndef MAKE_ARRAYS_H_
#define MAKE_ARRAYS_H_

int ind2D(int i, int j, int nrow, int ncol);

int ind3D(int i,int j,int k, int nrow, int ncol, int ndep);

double* make1Darray(int len);

double* make2Darray(int nrow, int ncol);

double* make3Darray(int nrow, int ncol, int ndep);

double* reduce1Darray(double* array, int new_len, int old_len);

double* reduce2Darray(double* array, int old_nrow, int old_ncol, int new_nrow, int new_ncol);

void reduce3Darray(double* old_array, int old_nrow, int old_ncol, int old_ndep, double* new_array, int new_nrow, int new_ncol, int new_ndep);

#endif /* MAKE_ARRAYS_H_ */
