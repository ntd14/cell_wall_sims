/*
 * make_arrays.c
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */
#include <stdlib.h>
#include "make_arrays.h"
 /* needs checks added in as well as conversion functions to lapack*/

void free1Darray(double* array)
{
	free(array);
}

void free2Darray(double** array, int nrow)
{
	int ii;
	for(ii=0; ii < nrow; ii++)
	{
		free(array[ii]);
	}
}

void free3Darray(double*** array, int nrow, int ncol)
{
	int ii;
	int jj;
	for(ii=0;ii<nrow;ii++)
	{
		for(jj=0; jj<nrow; jj++)
		{
			free(array[ii][jj]);
		}
	}
}

double * make1Darray(int nrow)
{
	double* theArray = malloc(nrow*sizeof(double));
    return theArray;
}

double** make2Darray(int nrow, int ncol)
{
	double** theArray;
	int ii;
	theArray = (double**) malloc(nrow*sizeof(double*));
	for (ii = 0; ii < nrow; ii++)
		theArray[ii] = (double*) malloc(ncol*sizeof(double));
    return theArray;
}

double*** make3Darray(int nrow, int ncol, int ndep)
{
	double*** theArray;
	int ii;
	int jj;
	theArray = (double***) malloc(nrow*sizeof(double**));
	for (ii = 0; ii < nrow; ii++)
	{
		theArray[ii] = (double**) malloc(ncol*sizeof(double*));
		for(jj = 0; jj < ncol; jj++)
		{
			theArray[ii][jj] = (double*) malloc(ncol*sizeof(double));
		}
	}
    return theArray;
}
