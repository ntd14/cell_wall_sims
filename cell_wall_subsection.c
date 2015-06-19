/*
 * twoD_single_pore.c
 *
 *  Created on: 21/05/2015
 *      Author: nick
 *
 *  This is the main trunk file for the implementation of a single 2D cellulose fibril aggregate
 *  pore filling with lignin.
 */

#include <stdio.h>
#include "src/get_init_data.h"
#include "src/main_worker.h"
#include "src/post_processing.h"

int main(void) /*this may change to take in arguments later*/
{
	create_init_state();
	/* returns init hydrated state */
	/* call to worker functions to minamise hydrated init state energy */
	/* loop:
	 * call to functions to add a bit of lignin
	 * call to worker functions to calculate new min energy state
	 * exit loop when cell wall is fully lignified
	 */
	/* post processing */
	return 0;
}

