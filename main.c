#include <stdio.h>
#include <stdlib.h>
#include "unbounded-int.h"

int main() {

    //printf("%d", containsOnlyDigits("12a3"));

    unbounded_int test = string2unbounded_int("123");

    digit *pointer = test.first;

    printf("%c", test.first->value);

    return EXIT_SUCCESS;
}
