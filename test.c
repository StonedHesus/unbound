//
// Created by Andrei-Paul Ionescu on 24/03/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include "./unbounded-int.h"

int main(void){

    printf("# Tests for unbounded_int_cmp_unbounded_int:\n");
    printf("\t[1] Comparing two unbounded_int object of same sign:\n");
    printf("\t\t[i] If the objects both have positive sign and the first one is longer than the second then this test "
           "should yield the value 1. \n\t\t\tTEST VALUE: %d\n",
           unbounded_int_cmp_unbounded_int(string2unbounded_int("1223"),
                                           string2unbounded_int("123")));
    printf("\t\t[ii] If the objects both have positive sign and the second one is longer than the first then this test "
           "should yield the value -1. \n\t\t\tTEST VALUE: %d\n",
           unbounded_int_cmp_unbounded_int(string2unbounded_int("123"),
                                           string2unbounded_int("1223")));
    printf("\t\t[iii] If the objects both have positive sign and the first one is the same length as the first then "
           "this test "
           "should yield the value 0 if they are equal, -1 if the second is bigger or 1 if "
           "\t\t\tthe first is the max between the two numbers. "
           "\n\t\t\tTEST VALUE: %d\n",
           unbounded_int_cmp_unbounded_int(string2unbounded_int("123"),
                                           string2unbounded_int("123")));




    return EXIT_SUCCESS;
}

