//
// Created by Andrei-Paul Ionescu on 26/04/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include "syntax-tree.h"

#define BUFFER 1000000000 // The language does not deal with numbers which have more digits than this value.

/////////////////////////////
//// Version 0.0.1 /////////
///////////////////////////

/**
 * This compilation unit contains the data structure and methods for managing and instantiating that data structure,
 * which will in turn allow us to properly parse mathematical expressions.
 */

struct node{

    struct node *left;
    char * key;
    struct node *right;
};

struct tree{

    struct node root;
};

static char ** extract_numbers(char * expression){
    /**
     * @param expression; a string containing a mathematical expression.
     *
     * @since 0.0.1
     * @version 0.0.1
     * @author Andrei-Paul Ionescu
     */

    assert(expression != NULL);

    char * current_word = malloc(sizeof(char) * BUFFER);
    int index = 0;
    int results_index = 0;

    for(char * pointer = expression ; *pointer != '\0' ; ++pointer){

        if(isdigit(*pointer)){


        } else{
            // We reached a character which is either a space, a bracket or an operator therefore the number has been
            // properly read and all that is left is to store it into memory.


        }
    }

    return NULL;
}

Tree construct_tree(char * expression){
    /**
     * @param expression; a string containing a mathematical expression.
     *
     * This constructor converts the string expression into a binary tree whose root is the operator with the utmost
     * important precedence in the expression.
     *
     * @since 0.0.1
     * @version 0.0.1
     * @author Andrei-Paul Ionescu
     */

    assert(expression != NULL);

    Tree *temporary = malloc(sizeof(Tree));

    if(temporary == NULL) {

        printf("ERROR: Tree object could not be instantiated.\n");
        abort();
    }



    return *temporary;
}
