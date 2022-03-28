//
// Created by Andrei Paul Ionescu on 26/03/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "unbounded-int.h"

typedef struct command{

    const char **options;
    const char *target;
} command;

typedef struct round_robin{


    struct round_robin *next;
    command *command;
    struct round_robin *previous;
} round_robin;


// Prototypes of the function used inside this here .c file.
static void print_command(command command);
static void print_round_robin(round_robin roundRobin);
static int checkFileName(const char *filename);
static int isFileName(const char *entity);

int main(int count, char **args){
    /**
     *
     * @param1 number, the number of elements stored in the array of string args.
     * @param2 args, an array of string object.
     *
     * This here program contains the interpreter of the unbounded int allowing us to have a minimal mathematical
     * interpreter which only works on integers.
     *
     * @author Andrei-Paul Ionescu
     * @version 0.01
     * @data 26.03.2022
     */

    round_robin *roundRobin = malloc(sizeof(roundRobin));

    if(roundRobin == NULL) exit(0);

    int stored = 0;

    for(int i = 1 ; i < count ; ++i){

        roundRobin->command = malloc(sizeof(command));
        if(roundRobin->command == NULL) exit(0);

        if(stored == 1){

            roundRobin->next = malloc(sizeof(roundRobin));
            round_robin *temporary = roundRobin;

            roundRobin = roundRobin->next;
            roundRobin->previous = temporary;
        }
    }

    //print_round_robin(*roundRobin);

    checkFileName("test.ub");

    if(isFileName("test.ub.ub") == EXIT_SUCCESS) printf("\nThe function does work");

    return EXIT_SUCCESS;
}


// Methods of the .c file.
static int isFileName(const char *entity){
    /**
     * @param entity, a const char object.
     *
     * Determine whether entity is a file name or not utilising the following criteria, if entity is a file name then
     * it stands to reason that it contains only one '.' which separates the name of the file from its extension.
     *
     * @author Andrei-Paul Ionescu
     * @date 28.03.2022
     * @version 0.01
     */

    int times = 0;

    char *result = (char *)entity;

    while(result != NULL){

        result = strstr(result, ".");

        if(!result) {

            result = NULL;
        } else{

            printf("%s", result);
            times += 1;
        }
    }

    printf("%d", times);
    if(times == 0 || times > 2) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

static int checkFileName(const char *filename){
    /**
     * @param filename, a const char( string object whose values we cannot alter) which represents the name of
     * a possible input file.
     *
     * This here method determines whether or not the input file passed to the interpret ends with one of the
     * allowed extension thus marking it as a file containing unbound code.
     *
     * @author Andrei-Paul Ionescu
     * @date 28.03.2022
     * @version final
     */

    assert(filename != NULL);

    const char *first_result  = strstr(filename, ".unbound");
    const char *second_result = strstr(filename, ".ub");
    if(!first_result && !second_result){

        printf("File format error: all files containing code written in unbound must finish with the "
               "extension .unbound or .ub\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static void print_round_robin(round_robin roundRobin){

    round_robin *current = &roundRobin;

    do{

        print_command(*current->command);
        current = current->next;
    }while(current != &roundRobin);
}

static void print_command(command command){

    for(const char *option = command.options[0]; option != NULL ; option += 1){

        printf("%s", option);
    }
}
