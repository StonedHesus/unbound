//
// Created by Andrei-Paul Ionescu on 24/03/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "unbounded-int.h"
#include "dictionary.h"

// Macro constants.

#define BOLD_TEXT "\033[1m"
#define NORMAL_TEXT "\033[0m"

// Prototypes of the .c file.
void print_separator(char separator);
void print_new_line(int times);

// Global variables of the program.
FILE *flot;


int main(void){
    /**
     *
     * This here program consists of a series of predefined tests which have two particular usages:
     *      i) They ensure that after development the functionalities of the unbounded-int methods are working according
     *  to the desired specifications.
     *      ii) They enable the developer to easily spot backwards compatibility issues or other types of problems which
     *  might arise due to the addition of new methods and functionalities to the program.
     *
     *  The program outputs information both to the STDIN (terminal) and to a separate file entitled test-results.txt,
     *  in this said file we store only the section whose tests have passed without triggering any errors, such as
     *  segmentation error, whilst the whole bunk of the file including the error messages could be perceived only by
     *  with the terminal.
     *
     * @version 0.0.4
     * @author Andrei-Paul Ionescu
     * @date 03.04.2022
     * @location BU ENS Paris-Saclay
     */

    flot = fopen("test-results.txt", "w");

    print_separator('#');
    printf("\n%s[*]Tests for dictionary object:%s\n", BOLD_TEXT, NORMAL_TEXT);
    fprintf(flot, "\n# Tests for dictionary object:\n");

    printf("\t[1] Creating a dictionary and adding the pair(\"my_first_variable\", 1234) where 1234 is an unbounded_int"
           "object should cause no problem and thus no error\n\t    to be triggered if it does then there is some issue"
           " with the code.\n");
    fprintf(flot, "\t[1] Creating a dictionary and adding the pair(\"my_first_variable\", 1234) where 1234 is an unbounded_int"
                  "object should cause no problem and thus no error to be triggered if it does then there is some issue "
                  "with the code.\n");

    dictionary my_dictionary = create_dictionary();
    insert_into_dictionary(my_dictionary, "my_first_variable", string2unbounded_int("1234"));

    printf("\t[2] Searching for the newly added unbounded_int object, whose value is 1234 ought to yield that object"
           "from within the dictionary.\n");
    printf("\t\tTEST VALUE: ");

    print_unbounded_int(*search_in_dictionary(my_dictionary, "my_first_variable"), 1, flot);

    fprintf(flot, "\t[2] Searching for the newly added unbounded_int object, whose value is 1234 ought to yield that object"
                  "from within the dictionary..\n");
    fprintf(flot, "\t\tTEST VALUE: ");

    print_new_line(1);

    fclose(flot);

    /// The tests for this particular method are deprecated since the method is now a static one which can only be
    /// accessed from within the unbounded-int compilation unit.

//    flot = fopen("test-results.txt", "w");
//
//    print_separator('#');
//    printf("\n# Tests for create_empty_unbounded_int_object:\n");
//    fprintf(flot, "\n# Tests for create_empty_unbounded_int_object:\n");
//
//    printf("\t[1] Creating an empty unbounded_int object with 20 digits and the default of 1 should result in the value"
//           "11111111111111111111, to appear on the screen, if not then the function's behaviour is faulty and hence this"
//           "matter should be addressed immediately.\n");
//    fprintf(flot, "\t[1] Creating an empty unbounded_int object with 20 digits and the default of 1 should result in the value"
//                  "11111111111111111111, to appear on the screen, if not then the function's behaviour is faulty and hence this"
//                  "matter should be addressed immediately.\n");
//
//    printf("\t\t\tTEST VALUE: ");
//    fprintf(flot, "\t\t\tTEST VALUE: ");
//    print_unbounded_int(create_empty_unbounded_int_object(20, 1), 1, flot);
//    print_new_line(1);
//
//    fclose(flot);


    flot = fopen("test-results.txt", "a");

    print_separator('#');
    printf("\n%s[*] Tests for ll2unbounded_int:%s\n", BOLD_TEXT, NORMAL_TEXT);
    fprintf(flot, "\n# Tests for ll2unbounded_int:\n");

    printf("\t[1] Creating an unbounded_int via the aid of a long long integer. This here test should output "
           "the values 123456789\n");
    fprintf(flot, "\t[1] Creating an unbounded_int via the aid of a long long integer. This here test should output "
           "the values 123456789\n");

    printf("\t\t\tTEST VALUE: ");
    fprintf(flot, "\t\t\tTEST VALUE: ");
    print_unbounded_int(ll2unbounded_int(123456789), 1, flot);
    print_new_line(1);

    printf("\t[2] In order to ensure that our doubled linked list is set up correctly, this test ought to print "
           "the following value on screen: 987654321.\n");
    fprintf(flot, "\t[2] In order to ensure that our doubled linked list is set up correctly, this test ought to print "
           "the following value on screen: 987654321.\n");

    printf("\t\t\tTEST VALUE: ");
    fprintf(flot, "\t\t\tTEST VALUE: ");
    print_unbounded_int(ll2unbounded_int(123456789), 0, flot);

    print_new_line(1);

    printf("\t[3]  Creating a negative unbounded_int via the aid of a long long integer. This here test should output "
           "the following value on screen: -12345.\n");
    fprintf(flot, "\t[3]  Creating a negative unbounded_int via the aid of a long long integer. This here test should output "
                  "the following value on screen: -12345.\n");

    printf("\t\t\tTEST VALUE :");
    fprintf(flot, "\t\t\tTEST VALUE: ");

    print_unbounded_int(ll2unbounded_int(-12345), 1, flot);

    print_new_line(2);
    print_separator('#');
    print_new_line(2);

    fclose(flot);

    flot = fopen("test-results.txt", "a");

    printf("%s[*] Tests for unbounded_int_cmp_unbounded_int:%s\n", BOLD_TEXT, NORMAL_TEXT);
    fprintf(flot, "# Tests for unbounded_int_cmp_unbounded_int:\n");

    printf("\t[1] Comparing two unbounded_int object of same sign:\n");
    fprintf(flot, "\t[1] Comparing two unbounded_int object of same sign:\n");

    printf("\t\t[i] If the objects both have positive sign and the first one is longer than the second then this test "
           "should yield the value 1. \n\t\t\tTEST VALUE: %d\n",
           unbounded_int_cmp_unbounded_int(string2unbounded_int("1223"),
                                           string2unbounded_int("123")));
    fprintf(flot, "\t\t[i] If the objects both have positive sign and the first one is longer than the second then this test "
           "should yield the value 1. \n\t\t\tTEST VALUE: %d\n",
           unbounded_int_cmp_unbounded_int(string2unbounded_int("1223"),
                                           string2unbounded_int("123")));

    printf("\t\t[ii] If the objects both have positive sign and the second one is longer than the first then this test "
           "should yield the value -1. \n\t\t\tTEST VALUE: %d\n",
           unbounded_int_cmp_unbounded_int(string2unbounded_int("123"),
                                           string2unbounded_int("1223")));

    fprintf(flot, "\t\t[ii] If the objects both have positive sign and the second one is longer than the first then this test "
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

    fprintf(flot, "\t\t[iii] If the objects both have positive sign and the first one is the same length as the second then "
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
    fprintf(flot, "\t\t[iv] If the objects both have negative sign and the first one is longer than the second then this test "
           "should yield the value -1. \n\t\t\tTEST VALUE: %d\n",
           unbounded_int_cmp_unbounded_int(string2unbounded_int("-1223"),
                                           string2unbounded_int("-123")));

    printf("\t\t[v] If the objects both have negative sign and the second one is longer than the first then this test "
           "should yield the value 1. \n\t\t\tTEST VALUE: %d\n",
           unbounded_int_cmp_unbounded_int(string2unbounded_int("-122"),
                                           string2unbounded_int("-1233")));

    fprintf(flot, "\t\t[v] If the objects both have negative sign and the second one is longer than the first then this test "
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

    fprintf(flot, "\t\t[vi] If the objects both have negative sign and the first one is the same length as the second then "
           "this test "
           "should yield the value 0 if they are equal, -1 if the second is bigger or 1 if "
           "\t\t\tthe first is the max between the two numbers. "
           "\n\t\t\tTEST VALUE: %d\n",
           unbounded_int_cmp_unbounded_int(string2unbounded_int("-103"),
                                           string2unbounded_int("-123")));


    print_new_line(1);
    print_separator('#');
    print_new_line(2);

    fclose(flot);

    flot = fopen("test-results.txt", "a");

    printf("%s[*] Tests for unbounded_int_sum:%s\n", BOLD_TEXT, NORMAL_TEXT);
    fprintf(flot, "# Tests for unbounded_int_sum:\n");

    printf("\t [1] Adding two unbounded_int of the same size and same sign.\n");
    fprintf(flot, "\t [1] Adding two unbounded_int of the same size and same sign.\n");

    printf("\t\t[i] Given the values 1234 and 1866 the result ought to be 3100.\n");
    fprintf(flot, "\t\t[i] Given the values 1234 and 1866 the result ought to be 3100.\n");

    printf("\t\t\tTEST VALUE: ");
    fprintf(flot, "\t\t\tTEST VALUE: ");
    print_unbounded_int(unbounded_int_sum(string2unbounded_int("1234"),
                                          string2unbounded_int("1866")),1, flot);

    print_new_line(1);
    printf("\t\t[ii] Given the values -1234 and -1866 the result ought to be -3100.\n");
    fprintf(flot, "\t\t[ii] Given the values -1234 and -1866 the result ought to be -3100.\n");

    printf("\t\t\tTEST VALUE: ");
    fprintf(flot, "\t\t\tTEST VALUE: ");

    print_unbounded_int(unbounded_int_sum(string2unbounded_int("-1234"),
                                          string2unbounded_int("-1866")),1, flot);

    print_new_line(1);

    printf("\t [2] Adding two unbounded_int of the same size and different sign.\n");
    fprintf(flot, "\t [2] Adding two unbounded_int of the same size and different sign.\n");

    printf("\t\t[i] Given the values 123 and -123 the program ought to yield the value 0.");
    fprintf(flot, "\t\t[i] Given the values 123 and -123 the program ought to yield the value 0.");

    printf("\n\t\t\tTEST VALUE: ");
    fprintf(flot, "\n\t\t\tTEST VALUE: ");

    print_unbounded_int(unbounded_int_sum(string2unbounded_int("123"),
                                          string2unbounded_int("-123")) ,1, flot);


    printf("\n\t\t[ii] Given the values -123 and 123 the program ought to yield the value 0.");
    fprintf(flot, "\n\t\t[ii] Given the values -123 and 123 the program ought to yield the value 0.");

    printf("\n\t\t\tTEST VALUE: ");
    fprintf(flot, "\n\t\t\tTEST VALUE: ");

    print_unbounded_int(unbounded_int_sum(string2unbounded_int("-123"),
                                          string2unbounded_int("123")) ,1, flot);

    printf("\n\t\t[iii] Given the values -123 and 120 the program ought to yield the value -3.");
    fprintf(flot, "\n\t\t[iii] Given the values -123 and 120 the program ought to yield the value -3.");

    printf("\n\t\t\tTEST VALUE: ");
    fprintf(flot, "\n\t\t\tTEST VALUE: ");

    print_unbounded_int(unbounded_int_sum(string2unbounded_int("-123"),
                                          string2unbounded_int("120")) ,1, flot);

    printf("\n\t\t[ii] Given the values 120 and -123 the program ought to yield the value -3.");
    fprintf(flot, "\n\t\t[ii] Given the values 120 and -123 the program ought to yield the value -3.");

    printf("\n\t\t\tTEST VALUE: ");
    fprintf(flot, "\n\t\t\tTEST VALUE: ");

    print_unbounded_int(unbounded_int_sum(string2unbounded_int("120"),
                                          string2unbounded_int("-123")) ,1, flot);

    print_new_line(2);

    printf("\t [3] Adding two unbounded_int of the different size and signs which can be different or not.\n");
    fprintf(flot, "\t [3] Adding two unbounded_int of the different size and signs which can be different or not.\n");

    printf("\t\t[i] Given the values 123 and 0 the result ought to be 123. "
           "\n\t\t\tTEST VALUE: ");
    fprintf(flot, "\t\t[i] Given the values 123 and 0 the result ought to be 123. "
           "\n\t\t\tTEST VALUE: ");
    print_unbounded_int(unbounded_int_sum(string2unbounded_int("123"),
                                          string2unbounded_int("0")), 1, flot);
    print_new_line(1);

    printf("\n\t\t[ii] Given the values -123 and 0 the result ought to be -123.\n");
    fprintf(flot, "\n\t\t[ii] Given the values -123 and 0 the result ought to be -123.\n");

    printf("\t\t\tTEST VALUE: ");
    fprintf(flot, "\t\t\tTEST VALUE: ");
    print_unbounded_int(unbounded_int_sum(string2unbounded_int("-123"),
                                          string2unbounded_int("0")), 1, flot);

    printf("\n\t\t[iii] Given the values 1000 and 999 the program ought to yield the value 1999.");
    fprintf(flot, "\n\t\t[iii] Given the values 1000 and 999 the program ought to yield the value 1999.");

    printf("\n\t\t\tTEST VALUE: ");
    fprintf(flot, "\n\t\t\tTEST VALUE: ");

    print_unbounded_int(unbounded_int_sum(string2unbounded_int("1000"),
                                          string2unbounded_int("999")) ,1, flot);


    print_new_line(1);
    print_separator('#');

    fclose(flot);

    flot = fopen("test-results.txt", "a");

    printf("%s[*] Tests for unbounded_int_multiplication:\n%s", BOLD_TEXT, NORMAL_TEXT);
    fprintf(flot, "# Tests for unbounded_int_multiplication:\n");

    printf("\t[1] Multiplying a number by zero will yield zero as a result.\n");
    fprintf(flot, "\t[1] Multiplying a number by zero will yield zero as a result.\n");

    printf("\t\t\tTEST VALUES : ");
    fprintf(flot, "\t\t\tTEST VALUES: ");
    print_unbounded_int(unbounded_int_multiplication(string2unbounded_int("12345"),
                                                     string2unbounded_int("0")), 0, flot);

    printf(", ");
    fprintf(flot, ", ");

    print_unbounded_int(unbounded_int_multiplication(string2unbounded_int("0"),
                                                     string2unbounded_int("-12345")), 0, flot);


    print_new_line(2);

    printf("\t[2] Multiplying a number by one will yield the same number as a result.\n");
    fprintf(flot, "\t[2] Multiplying a number by one will yield the same number as a result.\n");

    printf("\t\t\t 1234 X 1 = ");
    fprintf(flot, "\t\t\t 1234 X 1 = ");

    print_unbounded_int(unbounded_int_multiplication(string2unbounded_int("1234"),
                                                     string2unbounded_int("1")), 0, flot);

    print_new_line(1);

    printf("\t\t\t -1 X 1234 = ");
    fprintf(flot, "\t\t\t -1 X 1234 = ");

    print_unbounded_int(unbounded_int_multiplication(string2unbounded_int("-1"),
                                                     string2unbounded_int("1234")), 0, flot);

    print_new_line(2);

    fclose(flot);

    return EXIT_SUCCESS;
}

void print_new_line(int times){
    /**
     * @param1 times, an integer which represents the number of newlines we want.
     *
     * @author Andrei-Paul Ionescu
     * @date 03.04.2022
     * @location BU ENS Paris-Saclay
     * @version final
     */

    while(times > 0){

        printf("\n");
        fprintf(flot, "\n");

        times -=1;
    }
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
     * @version final
     */

    struct winsize winsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsize);

    for(int i = 0 ; i < winsize.ws_col ; ++i){

        printf("%c", separator);
        fprintf(flot, "%c", separator);
    }

    printf("\n");
}



