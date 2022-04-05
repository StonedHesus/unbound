//
// Created by Andrei-Paul Ionescu on 21/03/2022.
//

#include <stdio.h>

#ifndef UNBOUNDED_INT_UNBOUNDED_INT_H
#define UNBOUNDED_INT_UNBOUNDED_INT_H

typedef struct unbounded_int *unbounded_int;

extern unbounded_int string2unbounded_int(const char *e);
extern int unbounded_int_cmp_unbounded_int(unbounded_int first, unbounded_int second);
extern unbounded_int unbounded_int_sum(unbounded_int first, unbounded_int second);
extern unbounded_int ll2unbounded_int(long long int integer);
extern unbounded_int unbounded_int_subtraction(unbounded_int first, unbounded_int second);
extern void print_unbounded_int(unbounded_int unboundedInt, int direction, FILE *flot);

#endif //UNBOUNDED_INT_UNBOUNDED_INT_H
