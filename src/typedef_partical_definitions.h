/*
 * typedef_partical_definitions.h
 *
 *  Created on: 25/05/2015
 *      Author: nick
 */

#ifndef TYPEDEF_PARTICAL_DEFINITIONS_H_
#define TYPEDEF_PARTICAL_DEFINITIONS_H_

typedef struct partical_types {
	double R_ratio;
	double width_pos;
	double width_neg;
	double depth_pos ;
	double depth_neg;
	double length_pos;
	double length_neg;
	double density;

} part_defs;

part_defs FA1 = {10.0, 0.2, 0.2, 0.0, 0.0, 2.0, 2.0, 1500.0};
part_defs LA1 = {10.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,  500.0};

#endif /* TYPEDEF_PARTICAL_DEFINITIONS_H_ */
