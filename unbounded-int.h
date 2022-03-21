//
// Created by Andrei Paul Ionescu on 21/03/2022.
//

#include <assert.h>
#include <ctype.h>

#ifndef UNBOUNDED_INT_UNBOUNDED_INT_H
#define UNBOUNDED_INT_UNBOUNDED_INT_H

/// Data structures utilised in the header.
typedef struct digit{

    /// This here struct models a cell in a double chained list, the value which is being stored inside the said cell
    /// being a char value which can be easily converted into an int for further compatibility with C's other primitive
    /// types.

    struct digit *previous;
    char value;
    struct digit *next;

} digit;

typedef struct{

    /// This here struct represents the list itself, with fields storing the head, tail and the sign of the integer
    /// which is going to be stored with the aid of the structure.

    char sign; // Either '+' or '-'.
    size_t length; // The number of digits of our integer, the sign being independent from this.
    digit *first; // Pointer to the header of the list aka our first value.
    digit *last; // Pointer to the tail of the list aka our last value.

}unbounded_int;

// Helper methods.
int lengthOfString(const char *string){

    assert(string != NULL);
    int length = 0;

    while(*string != '\0'){

        length += 1;
        string += 1;
    }

    return length;
}

int containsOnlyDigits(const char *string){

    assert(string != NULL);

    while(*string != '\0'){

        if(!isnumber(*string)) return 0;

        string += 1;
    }


    return 1;
}

// Methods of the header.
unbounded_int ll2unbounded_int(long long int integer){

    // TODO: I will have to document myself about how long long int are implemented in C so as to be able to take
    //  advantage of that and thus manipulate more easily the memory.

    return (unbounded_int){};
}

unbounded_int string2unbounded_int(const char *e){

    assert(e != NULL);

    unbounded_int *temporary = malloc(sizeof(unbounded_int));

    if(temporary == NULL) abort();

    if(containsOnlyDigits(e) == 0){

        temporary->sign   ='*';
        temporary->length = 0;
        temporary->first  = NULL;
        temporary ->last  = NULL;
        return *temporary;
    }

    temporary->length = lengthOfString(e);
    temporary->sign = '+';

    digit *tail = malloc(sizeof(digit));

    if(tail == NULL) abort();


    while(*e != '\0'){

        tail->value = *e;
        tail->next = malloc(sizeof(digit));

        if(tail->next == NULL) abort();

        digit *tmp = tail;
        tail = tail->next;
        tail->previous = tmp;

        e += 1;
    }

    temporary->last  = tail->previous;
    temporary->last->next = NULL;

    digit *head = tail;

    for(int times = 0 ; times < temporary->length ; ++times){

        head = head->previous;
    }

    temporary->first = head;
    temporary->first->previous = NULL;

    return *temporary;
}


#endif //UNBOUNDED_INT_UNBOUNDED_INT_H
