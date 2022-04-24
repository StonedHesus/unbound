//
// Created by Andrei-Paul Ionescu on 05/04/2022.
//


#include "unbounded-int.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/**
 *
 * @version 0.0.9
 * @author Andrei-Paul Ionescu
 */



/// Data structures utilised in the header.
typedef struct digit{

    /// This here struct models a cell in a double chained list, the value which is being stored inside the said cell
    /// being a char value which can be easily converted into an int for further compatibility with C's other primitive
    /// types.

    struct digit *previous;
    char value;
    struct digit *next;

} digit;


// Helper methods.
static int lengthOfString(const char *string){
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

static int containsOnlyDigits(const char *string){
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
     * @version 0.0.1
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
unbounded_int unbounded_int_multiplication(unbounded_int first, unbounded_int second){
    /**
     * @param first; an unbounded_int object.
     * @param second; an unbounded_int object.
     *
     *  This method performs the multiplication of the two unbounded_int objects and returns their result.
     *
     *  @since 0.0.9
     *  @version 0.0.1
     *  @author Andrei-Paul Ionescu
     *  @location Home office.
     */

    assert(first.sign != '*' && second.sign != '*');

    /// TODO: Solve the weird behaviour behind this test, hint: it might have to do with compare function.
    if(unbounded_int_cmp_unbounded_int(first, string2unbounded_int("0")) == 0
    || unbounded_int_cmp_unbounded_int(second, string2unbounded_int("0")) == 0)
        return string2unbounded_int("0");
    else {
        // Basic multiplication algorithm goes here.
    }

    return (unbounded_int){};
}


void destroy_unbounded_int(unbounded_int unboundedInt){
    /**
     * @param unboundedInt; an unbounded_int object.
     *
     * Liberate all the memory which is occupied by an unbounded_int object.
     *
     *
     * @since 0.0.8
     * @version 0.0.1
     * @author Andrei-Paul Ionescu
     * @date 07.04.2022
     * @location in the car, on the way to university.
     */

    digit *pointer = unboundedInt.first;
    digit *next;

    for(int index = 0 ; index < unboundedInt.length ; ++index){

        next = pointer->next;

        free(pointer->next);
        free(pointer->previous);
        pointer = next;
    }

    free(unboundedInt.first);
    free(unboundedInt.last);
    free(&unboundedInt);
}

void print_unbounded_int(unbounded_int unboundedInt, int direction, FILE *flot){
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

            if(flot != NULL)
                fprintf(flot, "%c", pointer->value);

            printf("%c", pointer->value);
            pointer = pointer->next;
        }
    }

    if(direction == 0){

        digit *pointer = unboundedInt.last;

        for(int index = unboundedInt.length ; index > 0 ; --index){

            if(flot != NULL)
                fprintf(flot, "%c", pointer->value);

            printf("%c", pointer->value);
            pointer = pointer->previous;
        }
    }

}

/// TODO: Fix the tossing around of values between the subtraction method and addition one.

unbounded_int unbounded_int_subtraction(unbounded_int first, unbounded_int second, ...){
    /**
     *
     * @param1 first, an unbounded_int.
     * @param2 second, an unbounded_int.
     *
     * This here method computes the difference betwixt first and second, which are unbounded_int objects and it
     * returns a new unbounded_int which contains the result of this operation.
     *
     * @author Andrei-Paul Ionescu
     * @date 28.03.2022
     * @version 28.03.2022
     */

    va_list vaList;

    int calledFromAPreviousMethod = va_arg(vaList, int);

    if (calledFromAPreviousMethod != 1){

    if(first.sign == '-' && second.sign == '+'){

        second.sign = '-';
        return unbounded_int_sum(first, second);
    }

    if(first.sign == '+' && second.sign == '-'){

        second.sign ='+';
        return unbounded_int_sum(first, second);
    }

    }


    long long int result = 0;

    if(first.length >= second.length){


        int lend = 0;
        int position = 1;

        digit *pointer_towards_digit_of_first_unbounded_int = first.last;
        digit *pointer_towards_digit_of_second_unbounded_int  = second.last;

        for(int index = 0 ; index < second.length; ++index){

            if(pointer_towards_digit_of_first_unbounded_int->value >=
               pointer_towards_digit_of_second_unbounded_int->value){


                result += position * ((pointer_towards_digit_of_first_unbounded_int->value - lend) -
                                      pointer_towards_digit_of_second_unbounded_int->value);

                lend = 0;
            }
            else{

                lend = 1;

                result += position * ((pointer_towards_digit_of_first_unbounded_int->value)*10 -
                                      pointer_towards_digit_of_second_unbounded_int->value);
            }

            position *= 10;
            pointer_towards_digit_of_first_unbounded_int = pointer_towards_digit_of_first_unbounded_int->next;
            pointer_towards_digit_of_second_unbounded_int = pointer_towards_digit_of_second_unbounded_int->next;
        }

        for(size_t index = second.length ; index < first.length; ++index){

            result += position * ((pointer_towards_digit_of_first_unbounded_int->value) - lend);


            position *= 10;
            lend = 0;

            pointer_towards_digit_of_first_unbounded_int = pointer_towards_digit_of_first_unbounded_int->next;
        }

    } else{


        int lend = 0;

        for(int index = 0 ; index < first.length ; ++index){


        }
    }

    return ll2unbounded_int(result);
}
unbounded_int unbounded_int_sum(unbounded_int first, unbounded_int second){
    /**
     *
     * @param1 first, an unbounded_int.
     * @param2 second, an unbounded_int.
     *
     *
     * This here method computes the sum of two unbounded_int and returns a new unbounded_int which contains the result
     * of the said operation.
     *
     * @author Andrei-Paul Ionescu
     * @date 26.03.2022
     * @version 0.01
     */

    // Determine which number is the shortest and use its length so as to iterate thru the digits of the numbers so as
    // perform the addition operation.

    // TODO: Fix the subtract method's behaviour for thus far it is quite faulty.

    if(first.sign == '+' && second.sign == '-'){

        return unbounded_int_subtraction(first, second, 1);
    }

    if(first.sign == '-' && second.sign == '+'){

        return unbounded_int_subtraction(second, first, 1);
    }

    digit *pointer_towards_digit_of_the_first_number = first.last;
    digit *pointer_towards_digit_of_the_second_number = second.last;
    long long int addition_result = 0;
    long long int remainder = 0;
    int position = 1;

    if(first.length >= second.length){

        for(int index = 0 ; index < second.length ; ++index){


            addition_result += (((pointer_towards_digit_of_the_first_number->value - '0') +
                                 (pointer_towards_digit_of_the_second_number->value - '0')) % 10)*position;
            addition_result += remainder*position;

            remainder =  ((pointer_towards_digit_of_the_first_number->value - '0') +
                          (pointer_towards_digit_of_the_second_number->value - '0')) / 10;



            pointer_towards_digit_of_the_first_number = pointer_towards_digit_of_the_first_number->previous;
            pointer_towards_digit_of_the_second_number = pointer_towards_digit_of_the_second_number->previous;
            position *= 10;
        }

        // Add the remaining digits from the longest number, in this case first.
        for(int index = second.length ; index < first.length ; ++index){


            addition_result += ((pointer_towards_digit_of_the_first_number->value - '0') * position) +
                               remainder*position;

            remainder = (pointer_towards_digit_of_the_first_number->value - '0')/10;
            pointer_towards_digit_of_the_first_number = pointer_towards_digit_of_the_first_number->previous;
            position *= 10;
        }

    } else{

        for(int index = 0 ; index < first.length ; ++index){


            addition_result += (((pointer_towards_digit_of_the_first_number->value - '0') +
                                 (pointer_towards_digit_of_the_second_number->value - '0')) % 10)*position;
            addition_result += remainder*position;

            remainder =  ((pointer_towards_digit_of_the_first_number->value - '0') +
                          (pointer_towards_digit_of_the_second_number->value - '0')) / 10;



            pointer_towards_digit_of_the_first_number = pointer_towards_digit_of_the_first_number->previous;
            pointer_towards_digit_of_the_second_number = pointer_towards_digit_of_the_second_number->previous;
            position *= 10;
        }

        // Add the remaining digits from the longest number, in this case second.

        for(int index = first.length ; index < second.length ; ++index){


            addition_result += ((pointer_towards_digit_of_the_second_number->value - '0') * position) +
                               remainder*position;

            remainder = (pointer_towards_digit_of_the_second_number->value - '0')/10;
            pointer_towards_digit_of_the_second_number = pointer_towards_digit_of_the_second_number->previous;
            position *= 10;
        }
    }


    if(first.sign == '-' && second.sign == '-') addition_result *= -1;

    return ll2unbounded_int(addition_result);
}
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
    /**
     *
     * @param1 integer, a long long int whose going to be converted into an unbounded_int object.
     *
     * This here method takes as argument a long long int value which it converts into an unbounded_int object.
     *
     *
     * @author Andrei-Paul Ionescu
     * @date 28.03.2022
     * @version 0.02
     */

    unbounded_int *result = malloc(sizeof(unbounded_int));

    if(result == NULL) abort();

    if(integer >= 0){

        result->sign = '+'; // I might replace the sign by macro constants.
    } else{

        result->sign = '-';
        integer *= -1;
    }


    digit *head = malloc(sizeof(digit));
    if(head == NULL) abort();


    while(integer > 0){

        head->value = (char)((integer % 10) +'0');
        head->previous  = malloc(sizeof(digit));
        if(head->previous == NULL) abort();

        digit *temporary = head;
        head = head->previous;
        head->next = temporary;

        integer /= 10;
        result->length += 1;
    }


    result->first = head->next;
    result->first->previous = NULL;

    digit *tail = result->first;

    for(int index = 0 ; index < result->length - 1 ; ++index){

        tail = tail->next;
    }

    result->last = tail;
    result->last->next = NULL;
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

