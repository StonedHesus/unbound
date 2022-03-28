//
// Created by Andrei-Paul Ionescu on 24/03/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "./unbounded-int.h"

void print_unbounded_int(unbounded_int unboundedInt, int direction);
void print_separator(char separator);

int main(void){

    print_separator('#');
    printf("\n# Tests for ll2unbounded_int:\n");
    printf("\t[1] Creating an unbounded_int via the aid of a long long integer. This here test should output "
           "the values 123456789\n");
    printf("\t\t\tTEST VALUE: ");
    print_unbounded_int(ll2unbounded_int(123456789), 1);
    printf("\n");

    printf("\t[2] In order to ensure that our doubled linked list is set up correctly, this test ought to print "
           "the following value on screen: 987654321.\n");
    printf("\t\t\tTEST VALUE:");
    print_unbounded_int(ll2unbounded_int(123456789), 0);


    printf("\n\n");
    print_separator('#');
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


    printf("\n");
    print_separator('#');
    printf("\n\n");
    printf("# Tests for unbounded_int_sum:\n");
    printf("\t [1] Adding two unbounded_int of the same size and same sign.\n");

    printf("\t\t[i] Given the values 1234 and 1866 the result ought to be 3100.\n");
    printf("\t\t\tTEST VALUE: ");
    print_unbounded_int(unbounded_int_sum(string2unbounded_int("1234"),
                                          string2unbounded_int("1866")),1);

    printf("\n");
    printf("\t\t[ii] Given the values -1234 and -1866 the result ought to be -3100.\n");
    printf("\t\t\tTEST VALUE: ");
    print_unbounded_int(unbounded_int_sum(string2unbounded_int("-1234"),
                                          string2unbounded_int("-1866")),1);


    printf("\n");

    printf("\t [2] Adding two unbounded_int of the same size and different sign.\n");

    printf("\n");

    printf("\t [3] Adding two unbounded_int of the different size and signs which can be different or not.\n");
    printf("\t\t[i] Given the values 123 and 0 the result ought to be 123. "
           "\n\t\t\tTEST VALUE: ");
    print_unbounded_int(unbounded_int_sum(string2unbounded_int("123"),
                                          string2unbounded_int("0")), 1);
    printf("\n");

    printf("\n\t\t[ii] Given the values -123 and 0 the result ought to be -123.\n");
    printf("\t\t\tTEST VALUE: ");
    print_unbounded_int(unbounded_int_sum(string2unbounded_int("-123"),
                                          string2unbounded_int("0")), 1);

    printf("\n");
   print_separator('#');


    return EXIT_SUCCESS;
}

void print_separator(char separator){
    /**
     * @param1 separator, a character which will be when 'drawing' the dividing line.
     *
     * This here method utilise the winsize struct which stores information regarding the current state of the terminal
     * hence when the method ioctl is applied the struct will contain all the detail regarding the current session of
     * the terminal. We utilise the ws_col field so as to print a number of separator which spread equally on the
     * breadth of the screen, further to this I might add a version which changes everytime the user alters the size
     * of the screen, hence responding to events and therefore making the program more robust, dynamic and
     * user-friendly.
     *
     * @author Andrei-Paul Ionescu
     * @date 28.03.2022
     * @version 28.03.2022
     */

    struct winsize winsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsize);

    for(int i = 0 ; i < winsize.ws_col ; ++i){

        printf("%c", separator);
    }

    printf("\n");
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

    if(unboundedInt.sign == '-') printf("%c", unboundedInt.sign);

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

