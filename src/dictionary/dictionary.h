//
// Created by Andrei-Paul Ionescu on 05/04/2022.
//



#ifndef UNBOUNDED_INT_DICTIONARY_H
#define UNBOUNDED_INT_DICTIONARY_H


typedef struct dictionary *dictionary;

extern dictionary create_dictionary(void);
extern void destroy_dictionary(dictionary dictionary);
extern void insert_into_dictionary(dictionary dictionary, const char *key, unbounded_int value);
extern unbounded_int *search_in_dictionary(dictionary dictionary, const char *key);
extern void delete_from_dictionary(dictionary dictionary, const char *key);

#endif //UNBOUNDED_INT_DICTIONARY_H
