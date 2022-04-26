//
// Created by Andrei-Paul Ionescu on 26/04/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include "binary-tree.h"

/////////////////////////////
//// Version 0.0.1 /////////
///////////////////////////

struct node{

    struct node *left;
    char * key;
    struct node *right;
};

struct tree{

    struct node root;
};

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



    return (Tree){};
}
