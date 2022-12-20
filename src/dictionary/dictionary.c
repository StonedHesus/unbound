//
// Created by Andrei-Paul Ionescu on 05/04/2022.
//
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../unbounded-int/unbounded-int.h"
#include "dictionary.h"

/**
 * The dictionary.c file is made up of all the functions which enables one to create and maintain a dictionary.
 *
 *
 * @version 0.06
 * @author Andrei-Paul Ionescu
 */

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

    // The element object contains a pointer towards a new element due to the sole fact that
    // the collisions in our hash table are solved with the aid of chaining.
    struct element *next;
    char *key; // The key of the tuple, which is a string object.
    unbounded_int value; // The value of the tuple which is an unbounded_int object.
} element;

struct dictionary{
    /**
     * The dictionary object.
     *
     * @since 0.01
     * @version final
     * @author Andrei-Paul Ionescu.
     * @date 05.04.2022
     * @location BU Grandes Moulines, forth floor.
     */

    unsigned int number_of_elements; // Number of elements in the dictionary.
    int size;   // The size of the dictionary.
    element **elements; // The table which contains the elements of the dictionary.

};

/// Macro constants of the header.
#define INITIAL_SIZE 1024
#define GROWTH_FACTOR 2
#define MAJORIZATION_CONSTANT 97
#define LOAD_FACTOR 1

/// Prototypes of the file.
static dictionary _create_dictionary(int size);
static unsigned long _hash(const char *s);
static void grow(dictionary old_dictionary);
void insert_into_dictionary(dictionary dictionary, const char *key, unbounded_int value);
void destroy_dictionary(dictionary dictionary);
unbounded_int *search_in_dictionary(dictionary dictionary, const char *key);

// Helper methods of the file.
static unsigned long _hash(const char *s){
    /**
     *
     *
     * @since 0.01
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

static dictionary _create_dictionary(int size){
    /**
     *  @param1 size, an integer which depicts the desired size for our dictionary.
     *
     *  This here method is a helper method of the header, meaning that it can only be accessed by the components of
     *  the header file. The method creates a dictionary object of size 'size'.
     *
     *  @since 0.01
     *  @version final
     *  @author Andrei-Paul Ionescu
     *  @date 05.04.2022
     *  @location BU Grandes Moulines, forth floor.
     */

    dictionary dict = malloc(sizeof(dictionary));

    if(dict == NULL) abort();


    dict->size = size;
    dict->elements = 0;
    dict->elements = malloc(sizeof(element *) * size);

    if(dict->elements == NULL) abort();

    for(int i = 0 ; i < size ; ++i) dict->elements[i] = NULL;

    return dict;
}

// Methods of the file.
unbounded_int *search_in_dictionary(dictionary dictionary, const char *key){

    assert(key != NULL);

    for(element *pointer = dictionary->elements[_hash(key) % dictionary->size]; pointer;
    pointer = pointer->next){

        if(!strcmp(pointer->key, key)){

            return &pointer->value;
        }
    }


    return 0;
}

static void grow(dictionary old_dictionary){
    /**
     * @param *old_dictionary, a pointer to the memory zone where a dictionary object is stored.
     *
     * This method doubles the size of the dictionary and recopies the elements in accordance with the hash rule,
     * finally, after all this steps are completed the program swaps the temporary value which contains the new
     * dictionary for the old one, and then liberates the auxiliary memory used, this way we mutate the existing
     * variable and thus we do not have to worry about returning or passing values.
     *
     * @since 0.03
     * @version 0.01
     * @author Andrei-Paul Ionescu
     * @date 07.04.2022
     * @location BU Grandes Moulines, forth floor.
     */

    dictionary new_dictionary;
    dictionary swap;
    element *element;

    new_dictionary = _create_dictionary(old_dictionary->size * GROWTH_FACTOR);

    for(int i = 0 ; i < old_dictionary->size ; ++i){
        for(element = old_dictionary->elements[i]; element ; element = element->next){

            insert_into_dictionary(new_dictionary, element->key, element->value);
            // TODO: Swap this for a new hashing which is done in report with the specifications of the new dictionary.
        }
    }

    swap =  old_dictionary;
    *old_dictionary = *new_dictionary;
    new_dictionary = swap;

    destroy_dictionary(new_dictionary);
}

void delete_from_dictionary(dictionary dictionary, const char *key){
    /**
     * @param dictionary; a dictionary object.
     * @param key; a string of characters representing a key.
     *
     * This method eliminates the key if it is found inside the dictionary.
     *
     * @since 0.06
     * @version final
     * @author Andrei-Paul Ionescu
     * @location BU Grandes Moulines, forth floor.
     */
    assert(key);


    element to_be_deleted;

    for(element **previous = &(dictionary->elements[_hash(key) % dictionary->size]) ; *previous != 0 ;
        previous = &((*previous)->next)){

        if(!strcmp((*previous)->key, key)){

            //to_be_deleted = previous;
            *previous = to_be_deleted.next;

            free(to_be_deleted.key);
            free(to_be_deleted.next);
            return;
        }
    }

}

void insert_into_dictionary(dictionary dictionary, const char *key, unbounded_int value){
    /**
     * @param dictionary; a dictionary object
     * @param key; a pointer to a constant string of characters.
     * @param value; an unbounded_int object.
     *
     * This method inserts into the dictionary dictionary a new couple key-value, where the values for key and and value
     * are specified inside the call to the function.
     *
     * @since 0.03
     * @version final
     * @author Andrei-Paul Ionescu
     * @date 07.04.2022
     * @location in the car, on the way to university.
     */

    //&& value.sign != '*'
    // FIX ERROR WITH string2unbound_int method.
    assert(key != NULL );

    element *temporary;
    unsigned long hash_value;

    temporary = malloc(sizeof(element));

    if(temporary == NULL) abort();

    temporary->key = strdup(key);
    temporary->value = value;

    hash_value = _hash(key) % dictionary->size;

    /// TODO: FIX THE SIZE OF THE DICTIONARY BUG.

    temporary->next = dictionary->elements[hash_value];
    dictionary->elements[hash_value] = temporary;
    dictionary->number_of_elements += 1;

//    if(dictionary.number_of_elements >= dictionary.size * LOAD_FACTOR)
//        grow(&dictionary);
}

void destroy_dictionary(dictionary dictionary){
    /**
     * @param1 dictionary, a dictionary object.
     *
     * Liberate the memory reserved by the dictionary object dictionary.
     *
     * @since 0.02
     * @version final
     * @date 06.04.2022
     * @location BU Grandes Moulines, forth floor.
     */

    element *next;

    for(int index = 0 ; index < dictionary->size ; ++index){
        for(element *element = dictionary->elements[index]; element != NULL ; element = next){

            next = element->next;

            free(element->key);
            free(element);
        }

    }

    free(dictionary->elements);

}

dictionary create_dictionary(void) {
    /**
     * Create a new dictionary of size INITIAL_SIZE.
     *
     * @since 0.01
     * @version final
     * @author Andrei-Paul Ionescu
     * @date 05.04.2022
     * @location BU Grandes Moulines, forth floor.
     */

    return _create_dictionary(INITIAL_SIZE);
}
