//
// Created by Andrei Paul Ionescu on 05/04/2022.
//

#include <stdlib.h>
#include <string.h>
#include "unbounded-int.h"

#ifndef UNBOUNDED_INT_DICTIONARY_H
#define UNBOUNDED_INT_DICTIONARY_H

/// Structures used in the header.
typedef struct element{
    /**
     * A key, value tuple.
     *
     * @version final
     * @author Andrei-Paul Ionescu.
     * @date 05.04.2022
     * @location BU Grandes Moulines, forth floor.
     */

    const char *key;
    unbounded_int value;
} element;

typedef struct dictionary{
    /**
     * The dictionary object.
     *
     * @version final
     * @author Andrei-Paul Ionescu.
     * @date 05.04.2022
     * @location BU Grandes Moulines, forth floor.
     */

    unsigned int number_of_elements;
    size_t size;
    element **elements;

}dictionary;

/// Macro constants of the header.
#define INITIAL_SIZE 1024
#define GROWTH_FACTOR 2
#define MAJORIZATION_CONSTANT 97


/// Prototypes of the header.
static dictionary _create_dictionary(int size);
dictionary create_dictionary(void);

// Helper methods of the header.
static dictionary _create_dictionary(int size){
    /**
     *  @param1 size, an integer which depicts the desired size for our dictionary.
     *
     *  This here method is a helper method of the header, meaning that it can only be accessed by the components of
     *  the header file. The method creates a dictionary object of size 'size'.
     *
     *  @version final
     *  @author Andrei-Paul Ionescu
     *  @date 05.04.2022
     *  @location BU Grandes Moulines, forth floor.
     */

    dictionary *dict = malloc(sizeof(dictionary));

    if(dict == NULL) abort();

    dict->size = size;
    dict->elements = 0;
    dict->elements = malloc(sizeof(element) * size);

    if(dict->elements == NULL) abort();

    for(int i = 0 ; i < size ; ++i) dict->elements[i] = 0;

    return *dict;
}


static unsigned int hash_code(int key){

    return -1;
}

// Methods of the header.
dictionary create_dictionary(void) {
    /**
     * Create a new dictionary of size INITIAL_SIZE.
     *
     * @version final
     * @author Andrei-Paul Ionescu
     * @date 05.04.2022
     * @location BU Grandes Moulines, forth floor.
     */

    return _create_dictionary(INITIAL_SIZE);
}

unsigned long hash(const char *s){
    /**
     *
     *
     * @version final
     * @author Andrei-Paul Ionescu
     * @date 05.04.2022
     * @location BU Grandes Moulines, forth floor.
     */

    unsigned long h = 0;

    for(unsigned const char *pointer = (unsigned const char *)s; *pointer; pointer += 1)
        h = h * MAJORIZATION_CONSTANT + *pointer;

    return h;
}

#endif //UNBOUNDED_INT_DICTIONARY_H
