#include <stdio.h>
#include <stdlib.h>
#include "unbounded-int.h"

int main() {

    //printf("%d", containsOnlyDigits("12a3"));

//    unbounded_int test = string2unbounded_int("-123");
//
//    digit *pointer = test.first;
//
//    printf("%zu\n", test.length);
//
//
//    char *second_test = unbounded_int2string(test);
//
//
//    printf("%s", second_test);
//
//    printf("\n\t%s", unbounded_int2string(string2unbounded_int("123")));
//
//    long long int test_value = 192;
//
//    unbounded_int instantiation_from_lli = ll2unbounded_int(test_value);
//
//    //printf("\n%c", instantiation_from_lli.last->previous->previous->previous->value);
//    printf("\n\t\t%s", unbounded_int2string(string2unbounded_int("-3100")));


    unbounded_int unboundedInt = ll2unbounded_int(-12345);

    printf("%c", unboundedInt.last->previous->value);

    //print_unbounded_int(unboundedInt, 1, NULL);
    return EXIT_SUCCESS;
}
