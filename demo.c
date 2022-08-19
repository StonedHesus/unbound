//
// Created by Andrei Paul Ionescu on 19/07/2022.
//

#include <stdio.h>
#include <stdlib.h>

#include "single-chained-list.h"

int main(void){

    list my_list = construct_empty_list();
    add_back("Test");
    add_back("Testing");
    print_from_head(my_list);

    return EXIT_SUCCESS;
}
