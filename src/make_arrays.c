/*
 * make_arrays.c
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */
#include <stdlib.h>
#include <stdio.h>
#include "make_arrays.h"
 /* needs checks added in, realloc functions, free function and  conversion functions to lapack*/

int ind2D(int i, int j, int nrow, int ncol)
{
	int ind = nrow*j + i;
	return ind;
}

int ind3D(int i,int j,int k, int nrow, int ncol, int ndep)
{
	int ind = nrow*ncol*k + nrow*j + i;
	return ind;
}


double* make1Darray(int len)
{
	double* array = (double *)malloc(len*sizeof(double));
	if(array == NULL)
	{
		printf("make1Darray failed in malloc");
	}
	return array;
}

double* make2Darray(int nrow, int ncol)
{
	int len = nrow*ncol;
	double* array = (double *)malloc(len*sizeof(double));
	if(array == NULL)
	{
		printf("make2Darray failed in malloc");
	}
	return array;
}

double* make3Darray(int nrow, int ncol, int ndep)
{
	int len = nrow*ncol*ndep;
	double* array = (double *)malloc(len*sizeof(double));
	if(array == NULL)
	{
		printf("make3Darray failed in malloc");
	}
	return array;
}

void reduce1Darray(double* old_array, int old_len, double* new_array, int new_len)
{
	int ii;
	for(ii = 0; ii < new_len; ii++)
	{
			new_array[ii] = old_array[ii];
	}
	free(old_array);
}


double* reduce2Darray(double* array, int old_nrow, int old_ncol, int new_nrow, int new_ncol)
{
	/*split array into seperate 1D vectors of nrow and ncol length then call make2D array */
	double* tmp_array = make2Darray(new_nrow, new_ncol);
	int ii, jj;
	for(ii = 0; ii < new_nrow; ii++)
	{
		for(jj = 0; ii < new_ncol; jj++)
		{
			tmp_array[ind2D(ii, jj, new_nrow, new_ncol)] = array[ind2D(ii, jj, old_nrow, old_ncol)];
		}
	}
	free(array);
	return tmp_array;
}

void reduce3Darray(double* old_array, int old_nrow, int old_ncol, int old_ndep, double* new_array, int new_nrow, int new_ncol, int new_ndep)
{
	/*split array into seperate 1D vectors of nrow and ncol length then call make2D array */
	int ii, jj, kk;
	for(ii=0; ii < new_nrow; ii++)
		{
			for(jj=0; jj < new_ncol; jj++)
			{
				for(kk = 0; kk < new_ndep; kk++)
				{
					new_array[ind3D(ii,jj,kk,new_nrow,new_ncol,new_ndep)] = old_array[ind3D(ii,jj,kk,old_nrow, old_ncol, old_ndep)];
				}
			}
		}
	free(old_array);
}







