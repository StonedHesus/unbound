//
// Created by Andrei Paul Ionescu on 25/06/2022.
//
// Standard/ vanilla C libraries.
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// Custom libraries.
#include "control-flow.h"
//#include "dictionary.h"

// Structures used in this here compilation unit which are meant to not be accessible to external users.
typedef struct command_block{
    /**
     * This here structure models a block of instructions which are bound to be executed after each iteration thru the
     * loop, regardless of the type of the loop.
     *
     * @author Andrei-Paul Ionescu
     */
    // A collection of string objects which stores the lines of commands which are to be found in the block.
    char ** instructions;
    // An integer value of thirty-two bits which represents the number of strings which are to be found in the upper definition.
    long number_of_instruction_lines;
    // Each command_block disposes of a dictionary in which it holds are the automatic variables which belong to the block's scope.
   // dictionary automatic_values_of_block_scope;
} command_block;

// Prototypes of the routines which are used solely in this compilation unit.
static void execute_command_block(command_block *);

// Implementation of the helper methods.
static void execute_command_block(command_block *current_command){
    /**
     * @param *current_command; a pointer to a current_command object.
     *
     * This here method executes the set of instructions which are to be found within the block, if no instructions
     * are specified then that will cause a premature exit from the method.
     *
     * @author Andrei-Paul Ionescu.
     */

    // If there are no commands to be executed for the current block then exit the function.
    if(current_command->instructions == NULL)
        return ;

    // If there are commands then iterate thru them and invoke the parse line method so as to determine what is to be
    // done with each individual line.
    for(long index = 0 ; index < current_command->number_of_instruction_lines ; ++index)
        printf("%s \n", current_command->instructions[index]);
}

static void test(){

    command_block *test_block = malloc(sizeof(command_block));
    assert(test_block != NULL);
    test_block->instructions = malloc(sizeof(char *) * 2);
    test_block->number_of_instruction_lines = 2;
    assert(test_block->instructions != NULL);
    for(long i = 0 ; i < 2 ; ++i)
        strcpy(test_block->instructions[i], "a = sum(operator in expression distributed over +)");
    execute_command_block(test_block);
}

int main(void){

    test();
    return EXIT_SUCCESS;
}
