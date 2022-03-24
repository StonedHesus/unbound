//
// Created by Andrei-Paul Ionescu on 24/03/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include "./unbounded-int.h"

void print_unbounded_int(unbounded_int unboundedInt, int direction);

int main(void){

    printf("# Tests for ll2unbounded_int:\n");
    printf("[1] Creating an unbounded_int via the aid of a long long integer. This here test should output "
           "the values 123456789\n");
    printf("\t\t\tTEST VALUE: ");
    print_unbounded_int(ll2unbounded_int(123456789), 1);
    printf("\n");

    printf("[2] In order to ensure that our doubled linked list is set up correctly, this test ought to print "
           "the following value on screen: 987654321.\n");
    printf("\t\t\tTEST VALUE:");
    print_unbounded_int(ll2unbounded_int(123456789), 0);


    printf("\n\n###################################################################");
    printf("\n\n");
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
    printf("\t\t[iii] If the objects both have positive sign and the first one is the same length as the second then "
           "this test "
           "should yield the value 0 if they are equal, -1 if the second is bigger or 1 \n\t\t\tif "
           "the first is the max between the two numbers. "
           "\n\t\t\tTEST VALUE: %d\n",
           unbounded_int_cmp_unbounded_int(string2unbounded_int("123"),
                                           string2unbounded_int("123")));

    printf("\t\t[iv] If the objects both have negative sign and the first one is longer than the second then this test "
           "should yield the value -1. \n\t\t\tTEST VALUE: %d\n",
           unbounded_int_cmp_unbounded_int(string2unbounded_int("-1223"),
                                           string2unbounded_int("-123")));

    printf("\t\t[v] If the objects both have negative sign and the second one is longer than the first then this test "
           "should yield the value 1. \n\t\t\tTEST VALUE: %d\n",
           unbounded_int_cmp_unbounded_int(string2unbounded_int("-122"),
                                           string2unbounded_int("-1233")));

    printf("\t\t[vi] If the objects both have negative sign and the first one is the same length as the second then "
           "this test "
           "should yield the value 0 if they are equal, -1 if the second is bigger or 1 if "
           "\t\t\tthe first is the max between the two numbers. "
           "\n\t\t\tTEST VALUE: %d\n",
           unbounded_int_cmp_unbounded_int(string2unbounded_int("-103"),
                                           string2unbounded_int("-123")));





    return EXIT_SUCCESS;
}

void print_unbounded_int(unbounded_int unboundedInt, int direction){
    /**
     *
     * @param1, an unbounded_int object.
     *
     * Prints an unbounded_int object from head tail if direction is 1 or from tail to head if direction is 0
     * to the stdout.
     *
     * @author Andrei-Paul Ionescu
     * @date 24.03.2022
     * @version final
     */

    assert(unboundedInt.sign != '*' && (direction != 1 || direction != 0));

    if(direction == 1){

        digit *pointer = unboundedInt.first;

        for(int index = 0 ; index < unboundedInt.length ; ++index){

            printf("%c", pointer->value);
            pointer = pointer->next;
        }
    }

    if(direction == 0){

        digit *pointer = unboundedInt.last;

        for(int index = unboundedInt.length ; index > 0 ; --index){

            printf("%c", pointer->value);
            pointer = pointer->previous;
        }
    }

}

