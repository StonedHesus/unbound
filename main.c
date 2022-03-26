#include <stdio.h>
#include <stdlib.h>
#include "unbounded-int.h"

int main() {

    //printf("%d", containsOnlyDigits("12a3"));

    unbounded_int test = string2unbounded_int("-123");

    digit *pointer = test.first;

    printf("%zu\n", test.length);


    char *second_test = unbounded_int2string(test);


    printf("%s", second_test);

    printf("\n\t%s", unbounded_int2string(string2unbounded_int("123")));

    long long int test_value = 19;

    unbounded_int instantiation_from_lli = ll2unbounded_int(test_value);

    printf("\n%c", instantiation_from_lli.first->next->value);

    return EXIT_SUCCESS;
}
