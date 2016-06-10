/*
 * lists.h
 *
 *  Created on: 24/09/2015
 *      Author: nick
 */

#ifndef LISTS_H_
#define LISTS_H_



char* list_points[10];
point* ptr_points[10];
char* list_cons[6];
con* ptr_cons[6];
char* list_bounds[6];
bound* ptr_bounds[6];

point* point_ptr_name(char name[10]);
con* con_ptr_name(char name[10]);
bound* bound_ptr_name(char name[10]);


#endif /* LISTS_H_ */
