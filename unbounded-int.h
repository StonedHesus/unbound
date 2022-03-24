//
// Created by Andrei-Paul Ionescu on 21/03/2022.
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

// Prototypes of the function.
int unbounded_int_cmp_unbounded_int(unbounded_int first, unbounded_int second);

// Helper methods.
char convertIntToChar(int value){
    /**
     *
     * @param value, an integer value, which due to the design of the header will always be a digit.
     *
     * Helper method which converts an integer, which we assume to be a digit, into its corresponding character
     * and then it returns it to the caller.
     *
     * @author Andrei-Paul Ionescu
     * @version 0.01
     * @date 23.03.2022
     */

    switch(value){

        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';

        default: ;
    }

    return 'E';
}


int lengthOfString(const char *string){
    /**
     *
     * @param string, a String object( a pointer which directs us to a zone in memory containing a string that is a
     * sequence of char<1 octet> which end by the special character '\0'.
     *
     * Helper method, used so as to compute the length of the String given as the parameter.
     *
     * @author Andrei-Paul Ionescu
     * @version 0.01
     * @date 23.03.2022
     */

    assert(string != NULL);
    int length = 0;

    while(*string != '\0'){

        length += 1;
        string += 1;
    }

    return length;
}

int containsOnlyDigits(const char *string){
    /**
     *
     *
     * @param string, a String object.
     *
     * Helper method which determines whether the string given as input for the method
     * string2unbounded_int(const char * e) is a valid string or not. We consider a valid string a sequence of
     * digits, any other character within the string will cause the string to be labelled as invalid.
     *
     * @author Andrei-Paul Ionescu
     * @version 0.01
     * @date 23.03.2022
     */

    assert(string != NULL);

    while(*string != '\0'){

        if(!isnumber(*string)) return 0;

        string += 1;
    }


    return 1;
}

// Methods of the header.
int unbounded_int_cmp_unbounded_int(unbounded_int first, unbounded_int second){
    /**
     *
     * @param1 first, an unbounded_int.
     * @param2 second, an unbounded_int.
     *
     * This method compares two unbounded_int objects and returns one of the values -1, 0 and 1 depending on whether
     * the two unbounded_int represent two integers who have the property that max(first, second) is first,
     * they are equal or max(first, second) second respectively.
     *
     * @author Andrei-Paul Ionescu
     * @date 24.03.2022
     * @version 0.01
     */

    assert(first.sign != '*' && second.sign != '*');

    if(first.sign == '-' && second.sign == '+'){

        return 1;
    } else if(first.sign == '+' && second.sign == '-'){

        return -1;
    } else if(first.sign == '+' && second.sign == '+'){

        if(first.length > second.length){

            return 1;
        } else if(first.length < second.length){

            return -1;
        } else if(first.length == second.length){

                digit *pointer_towards_the_first    = first.first;
                digit *pointer_towards_the_second   = second.first;


                while(pointer_towards_the_first != NULL){

                    if(pointer_towards_the_first->value - '0' > pointer_towards_the_second->value - '0')
                        return 1;
                    else
                        if(pointer_towards_the_first->value - '0' < pointer_towards_the_second->value - '0')
                            return -1;

                   pointer_towards_the_first = pointer_towards_the_first->next;
                   pointer_towards_the_second = pointer_towards_the_second->next;
                }

                return 0;
            }
    } else if(first.sign == '-' && second.sign == '-'){

        if(first.length > second.length){

            return -1;
        } else if(first.length < second.length){

            return 1;
        } else if(first.length == second.length){

            digit *pointer_towards_the_first    = first.first;
            digit *pointer_towards_the_second   = second.first;

            while(pointer_towards_the_first != NULL){

                if(pointer_towards_the_first->value - '0' > pointer_towards_the_second->value - '0')
                    return -1;
                else
                if(pointer_towards_the_first->value - '0' < pointer_towards_the_second->value - '0')
                    return 1;

                pointer_towards_the_first = pointer_towards_the_first->next;
                pointer_towards_the_second = pointer_towards_the_second->next;
            }

            return 0;
        }
    }

    return -1;
}

char *unbounded_int2string(unbounded_int unboundedInt){
    /**
     *
     * @param unboundedInt, an object of type unboundedInt
     *
     * This here method converts an unboundedInt object into a string.
     *
     *
     *
     * @author Andrei-Paul Ionescu
     * @version 0.01
     * @date 24.03.2022
     */

    // TODO: Add support for the rare case in which user decide to depict positive numbers by giving the sign as well.

    assert(unboundedInt.sign != '*');

    if(unboundedInt.sign == '+'){

        // In the case where the sign of the number is plus we will omit it from the representation of the
        // unbounded_int object as a string object.

        int length_of_unbounded_int = unboundedInt.length;

        char *result = malloc(sizeof(char) * (length_of_unbounded_int + 1));

        if (result == NULL) {

            return NULL;
        }


        digit *pointer = unboundedInt.first;
        char *pointer_to_string = result;

        for(int i = 0 ; i < length_of_unbounded_int ; ++i){

            *pointer_to_string = pointer->value;
            pointer_to_string += 1;
            pointer = pointer->next;
        }


        return result;
    } else if(unboundedInt.sign == '-'){

        int length_of_unbounded_int = unboundedInt.length;

        char *result = malloc(sizeof(char) * (length_of_unbounded_int + 1));

        if (result == NULL) {

            return NULL;
        }



        digit *pointer = unboundedInt.first;
        char *pointer_to_string = result;

        for(int i = 0 ; i < length_of_unbounded_int ; ++i){

            *pointer_to_string = pointer->value;
            pointer_to_string += 1;
            pointer = pointer->next;
        }

        return result;

    }
    return NULL;
}

unbounded_int ll2unbounded_int(long long int integer){

    // TODO: I will have to document myself about how long long int are implemented in C so as to be able to take
    //  advantage of that and thus manipulate more easily the memory.

    unbounded_int *result = malloc(sizeof(unbounded_int));

    if(result == NULL) abort();

    if(integer >= 0){

        result->sign = '+';
    } else{

        result->sign = '-';
    }

    digit *tail = malloc(sizeof(digit));

    // TODO: Alter the manner in which we treat problematic cases so that they will comply with the norm given out
    //  by the professor.
    if(tail == NULL) abort();

    result->length = 0;

    // TODO: Fix the length issue.

    while(integer > 0){

        printf("%c",convertIntToChar((integer%10)));
        tail->value = convertIntToChar((integer%10));
        tail->next = malloc(sizeof(digit));

        if(tail->next == NULL) abort();

        tail = tail->next;
        integer /= 10;
        result->length += 1;
    }

    result->last = tail;

    printf("%zu", result->length);

    digit *head = result->last;


    for(int i = 0 ; i < result->length ; ++i){

        head = head->previous;
    }

    result->first = head;


    return *result;
}

unbounded_int string2unbounded_int(const char *e){
    /**
     *
     * @param e, a String object.
     *
     * The function converts a String object into an unbounded_int object, case the object is unable to be created
     * due to the reason that the String does not contain integers then the function will return a structure containing
     * NULL values for the pointers which indicate the tail and the head of the doubled chained list we so as to
     * represent the number and an '*' for the sign of the structure.
     *
     * @author Andrei-Paul Ionescu
     * @version 0.01
     * @date 23.03.2022
     */

    assert(e != NULL);

    unbounded_int *temporary = malloc(sizeof(unbounded_int));

    if(temporary == NULL) abort();

    if(*e == '-'){

        if(containsOnlyDigits(e + 1) == 0){

            temporary->sign   ='*';
            temporary->length = 0;
            temporary->first  = NULL;
            temporary ->last  = NULL;
            return *temporary;
        }


        temporary->sign = '-';
        temporary->length = lengthOfString(e + 1);


        digit *tail = malloc(sizeof(digit));

        if(tail == NULL) abort();

        int off_set = 1; // Digits are offset by one position due to the apparition of the sign.

        while(*(e + off_set) != '\0'){

            tail->value = *(e + off_set);
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
    } else if(*e == '+'){

        if(containsOnlyDigits(e + 1) == 0){

            temporary->sign   ='*';
            temporary->length = 0;
            temporary->first  = NULL;
            temporary ->last  = NULL;
            return *temporary;
        }

        temporary->sign = '+';
        temporary->length = lengthOfString(e + 1);

        digit *tail = malloc(sizeof(digit));

        if(tail == NULL) abort();

        int off_set = 1; // Digits are offset by one position due to the apparition of the sign.


        while(*(e + off_set) != '\0'){

            tail->value = *(e + off_set) ;
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

        temporary->sign = '+';
        temporary->length = lengthOfString(e+1);
    } else{

        // If no sign is specified we assume that the number is positive and hence its corresponding sign is '+'.

        if(containsOnlyDigits(e) == 0){

            temporary->sign   ='*';
            temporary->length = 0;
            temporary->first  = NULL;
            temporary ->last  = NULL;
            return *temporary;
        }


        temporary->sign   = '+';
        temporary->length = lengthOfString(e);


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
    }

    return *temporary;
}


#endif //UNBOUNDED_INT_UNBOUNDED_INT_H
