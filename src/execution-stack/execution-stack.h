//
// Created by Andrei-Paul Ionescu on 01/04/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../unbounded-int/unbounded-int.h"

#define FRONTWARDS 1
#define BACKWARDS  0

#ifndef UNBOUNDED_INT_EXECUTION_STACK_H
#define UNBOUNDED_INT_EXECUTION_STACK_H


/// Structures of the header.
typedef struct stack{
    /**
     *
     * A double-chained list without a tail.
     *
     * @author Andrei-Paul Ionescu
     * @version final
     * @date 01.04.2022
     * @location BU Licences Sorbonne Campus PMC
     */

    struct stack *previous;
    unbounded_int unboundedInt;
    struct stack *next;
}stack;


/// Non-static methods of the header.
unbounded_int pop_front(stack *my_stack){
    /**
     *
     *
     * @author Andrei-Paul Ionescu
     * @date 01.04.2022
     * @version 0.01
     * @location BU Licences Sorbonne Campus PMC
     */

    if(my_stack->next == NULL && my_stack->previous == NULL){

        unbounded_int value = my_stack->unboundedInt;
        my_stack = NULL;
        return value;
    }

    assert(my_stack != NULL && my_stack->unboundedInt.sign != '*');

    unbounded_int value = my_stack->unboundedInt;
    *my_stack = *my_stack->next;
    free(my_stack->previous);
    my_stack->previous = NULL;

    return value;
}

void print_stack(stack *my_stack, int direction){
    /**
     *
     *
     * @author Andrei-Paul Ionescu
     * @date 01.04.2022
     * @version 0.01
     * @location BU Licences Sorbonne Campus PMC
     */
    if(direction == FRONTWARDS){

        for(stack *pointer = my_stack ; pointer != NULL ; pointer = pointer->next)
            print_unbounded_int(pointer->unboundedInt, 1, NULL);

        printf("\n");
    }

}

void add_back(stack *my_stack, char *value){
    /**
     *
     *
     * @author Andrei-Paul Ionescu
     * @date 01.04.2022
     * @version 0.01
     * @location BU Licences Sorbonne Campus PMC
     */

    stack *pointer;

    if(my_stack->unboundedInt.sign == '*'){
        // We have an empty stack on our hands.

        my_stack->unboundedInt = string2unbounded_int(value);
    } else{

        for(pointer = my_stack ; pointer->next != NULL ; pointer = pointer->next)
            ;

        pointer->next = malloc(sizeof(stack));
        if(pointer->next == NULL) abort();

        pointer->next->unboundedInt = string2unbounded_int(value);
        pointer->next->next  = NULL;
    }
}

stack create_execution_stack(void){
    /**
     *
     *
     * @author Andrei-Paul Ionescu
     * @date 01.04.2022
     * @version 0.01
     * @location BU Licences Sorbonne Campus PMC
     */

    stack *temporary = malloc(sizeof(stack));

    if(temporary == NULL) abort();

    temporary->next     = NULL;
    temporary->previous = NULL;
    temporary->unboundedInt.sign = '*';

    return *temporary;
}

#endif //UNBOUNDED_INT_EXECUTION_STACK_H
