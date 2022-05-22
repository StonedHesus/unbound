//
// Created by Andrei-Paul Ionescu on 21/03/2022.
//

#include <stdio.h>

#ifndef UNBOUNDED_INT_UNBOUNDED_INT_H
#define UNBOUNDED_INT_UNBOUNDED_INT_H

typedef struct digit digit;

typedef struct unbounded_int{

    /// This here struct represents the list itself, with fields storing the head, tail and the sign of the integer
    /// which is going to be stored with the aid of the structure.

    char sign; // Either '+' or '-'.
    size_t length; // The number of digits of our integer, the sign being independent from this.
    digit *first; // Pointer to the header of the list aka our first value.
    digit *last; // Pointer to the tail of the list aka our last value.

} unbounded_int;

extern unbounded_int string2unbounded_int(const char *e);
extern int unbounded_int_cmp_unbounded_int(unbounded_int first, unbounded_int second);
extern unbounded_int unbounded_int_sum(unbounded_int first, unbounded_int second);
extern unbounded_int ll2unbounded_int(long long int integer);
extern unbounded_int unbounded_int_subtraction(unbounded_int first, unbounded_int second);
extern unbounded_int unbounded_int_multiplication(unbounded_int first, unbounded_int second);
extern void print_unbounded_int(unbounded_int unboundedInt, int direction, FILE *flot);
extern void destroy_unbounded_int(unbounded_int unboundedInt);
extern char *unbounded_int2string(unbounded_int unboundedInt);
extern unbounded_int unbounded_int_division(unbounded_int first, unbounded_int second);


#endif //UNBOUNDED_INT_UNBOUNDED_INT_H
