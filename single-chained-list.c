//
// Created by Andrei Paul Ionescu on 19/07/2022.
//

// Headers belonging to the standard C library.
#include <stdlib.h>
#include <stdio.h>

// Custom headers for this particular project.
#include "single-chained-list.h"

// Data structures defined for this particular compilation unit.
struct cell{
    /**
     *  This here structure models a cell object which is utilised as containers for the list data type.
     *
     *  @author Andrei-Paul Ionescu.
     */

    const char * content; // The content of the current cell.
    struct cell *next; // A reference towards the next block in the list object.
};

// Static/global variables.
static cell *current;

// Methods of the header.
extern void print_from_head(list current_list){
    /**
     * @param current_list; a list object.
     *
     * This here method prints the content of the list commencing with the head and terminating with the last value for
     * which the next field of the cell is non nil.
     *
     * @return none; this function does not return anything back to the caller.
     *
     * @author Andrei-Paul Ionescu.
     */

    cell *pointer = current_list.head;

    while(pointer != NULL){

        printf("%s\n", pointer->content);
        pointer = pointer->next;
    }
}

extern void add_back(const char * string){
    /**
     * @param string; a literal string object.
     *
     * This method adds a new cell object which contains the value indicated by the string parameter to the end of the
     * list, this operation is performed with the aid of the current pointer, which is initialised as a global static
     * pointer variable.
     *
     * @return none; this function does not return anything back to the caller.
     *
     * @author Andrei-Paul Ionescu.
     */

    // Instantiate a new cell object.
    cell *temporary = malloc(sizeof(cell));

    // Address any potential errors which might arise when allocating the space for the cell object.
    if(temporary == NULL){

        printf("[!] You ran out of space and therefore the program is unabled to continue execution!");
        abort();
    }

    // Set the values for the content field and the next field respectively.
    temporary->content = string;
    temporary->next = NULL;

    // Update the current pointer.
    if(current == NULL) // The list is empty.
        current = temporary;
    else{

        current->next = temporary;
        current = current->next;
    }
}

extern list construct_list_from_string(const char * string){
    /**
     * @param string; a literal string object.
     *
     * This here method constructs a new list object which after the action is completed it returns it to the caller,
     * whilst also dealing with the creation of a cell object which will hold the current string.
     *
     * @return a list object.
     *
     * @author Andrei-Paul Ionescu.
     */

    // Reserve the memory required to store a list object.
    list *temporary = malloc(sizeof(list));

    // Address the error which might arise if the system runs out of available space or any other internal errors
    // caused the malloc function to fail reserving the space.
    if(temporary == NULL){

        printf("[!] You ran out of space and therefore the program is unabled to continue execution!");
        abort();
    }

    // Create a new cell object and assign to its content field the value passed to the function by the user.
    cell *tmp = malloc(sizeof(cell));

    // Again, address the error which might arise if the system runs out of available space or any other internal errors
    // caused the malloc function to fail reserving the space.
    if(tmp == NULL){

        printf("[!] You ran out of space and therefore the program is unabled to continue execution!");
        abort();
    }

    // Assign the string to the newly instantiated cell and then assigned the reference towards that cell to the new
    // list object, then return the list to the caller.
    tmp->content = string;
    tmp->next = NULL;
    temporary->head = tmp;

    // Update the current pointer so that it points to the next available position.
    current = temporary->head;

    return *temporary;
}

extern list construct_list(cell head){
    /**
     * @param head; a cell object which the user provides and which will automatically become the head of the current list.
     *
     * This here method constructs a new list object from the current given cell which serves the role of the head of
     * the newly instantiated list.
     *
     * @return the newly created list object.
     *
     * @author Andrei-Paul Ionescu.
     */

    // Reserve the memory required to store a list object.
    list *temporary = malloc(sizeof(list));

    // Respond to the error which might arise if the system runs out of available space or any other internal errors
    // caused the malloc function to fail reserving the space.
    if(temporary == NULL){

        printf("[!] You ran out of space and therefore the program is unabled to continue execution!");
        abort();
    }

    // Assign the cell object passed to the function by the caller to the head field of the current list object.
    temporary->head = &head;

    // Update the current pointer.
    current = temporary->head;

    return *temporary;
}

extern list construct_empty_list(void){
    /**
     * @param none; this function takes no formal arguments upon invocation.
     *
     * This function initialises a new empty list object and it returns it to the caller.
     *
     * @return a list object.
     *
     * @author Andrei-Paul Ionescu.
     */

    list *temporary = malloc(sizeof(list)); // Initialise a memory zone which is capable of holding a list object.

    if(temporary == NULL){
        // If there was an error when reserving the memory for the list then warn the user and abort the program.

        printf("[!] You ran out of space and therefore the program is unabled to continue execution!");
        abort();
    }

    temporary->head = NULL; // Since the list is empty, we will indicate this by making the head point to NULL.

    return *temporary;
}

