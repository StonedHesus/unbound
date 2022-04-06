//
// Created by Andrei Paul Ionescu on 26/03/2022.
//

/// Existing libraries.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <ctype.h>

/// Custom libraries.
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
static void readFile(const char *path);
static void prepare(int count, char **args);
static void run(void);
static void read(void);
static void write(void);
static void parseLine(char *line);

// Global variables of the program.
static FILE *input;
static FILE *output;

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

    prepare(count, args);
    run();

//    memory = create_execution_stack();
//    //readFile(args[1]);
//    stack my_stack = create_execution_stack();
//
//
//    add_back(&my_stack, "123");
//     add_back(&my_stack, "321");
//
//
//    print_stack(&my_stack, FRONTWARDS);
//    printf("\n");
//
//    print_unbounded_int(pop_front(&my_stack), 1);
//    printf("\n");
//    print_unbounded_int(pop_front(&my_stack), 1);


//    round_robin *roundRobin = malloc(sizeof(roundRobin));
//
//    if(roundRobin == NULL) exit(0);
//
//    int stored = 0;
//    int option_index = 0;
//    int create = 0;
//
//    for(int i = 1 ; i < count ; ++i){
//
//        printf("%s\n", args[i]);
//
//        if(create == 0){
//
//            roundRobin->command = malloc(sizeof(command));
//            if(roundRobin->command == NULL) exit(0);
//            create = 1;
//        }
//
//
//        if(stored == 1){
//
//            roundRobin->next = malloc(sizeof(roundRobin));
//            round_robin *temporary = roundRobin;
//
//            roundRobin = roundRobin->next;
//            roundRobin->previous = temporary;
//            stored = 0;
//            option_index = 0;
//            create = 0;
//        }
//
//        if(isFileName(args[i])){
//
//            roundRobin->command->target = malloc(sizeof(char *));
//            if(roundRobin->command->target == NULL) exit(1);
//
//            roundRobin->command->target = args[i];
//            stored = 1;
//        } else{
//
//            roundRobin->command->options[option_index] = args[i];
//            option_index += 1;
//        }
//    }



    return EXIT_SUCCESS;
}


// Methods of the .c file.
static void read(void){
    /**
     *
     *
     * @author Andrei-Paul Ionescu
     * @date 04.04.2022
     * @version 0.01
     * @location Home office.
     */


    if(input == stdin){

        char *line = NULL;
        size_t size = 0;
        ssize_t read = 0;

        while(1){

            fprintf(output, ">>>");
            read = getline(&line, &size, input);

            if(strstr(line, "clear") || strstr(line, "clear()"))
                system("clear");

            if(read == -1 || strstr(line, "exit") != NULL || strstr(line, "exit()") != NULL){

                fprintf(output, "\n");
                exit(0);
            }

            parseLine(line);

        }

    }

}

static void write(void){
    /**
     *
     * @author Andrei-Paul Ionescu
     * @date 04.04.2022
     * @version 0.01
     * @location Home Office.
     */

}

static void run(void){
    /**
     *
     *
     * This here method manages the behaviour of the hole interpreter, thus it is dependent on whether or not the
     * environment has been set out properly or not, therefore prior to calling run we strongly advise to use the
     * prepare method.
     *
     * @author Andrei-Paul Ionescu
     * @date 04.04.2022
     * @version 0.01
     * @location Home office.
     */

    read();
    write();
}

static void prepare(int count, char **args){
    /**
     *
     * @param1, the number of pointers which are found in the list args.
     * @param2, a list of pointers
     *
     * This method determines, based on the given input, whether the user of the program specified any particular input
     * or output files or if any other options had been passed to the program, in which case the software is bound to
     * respond according to the user's input or to warn him about fraudulent behaviour which it might cause.
     *
     * @author Andrei-Paul Ionescu
     * @date 04.04.2022
     * @version 0.01
     * @location Home office.
     */

    if(count == 1){

        input   = stdin;
        output  = stdout;
        return;
    }
}

static void parseLine(char *line){
    /**
     *
     *
     * @author Andrei-Paul Ionescu
     * @date 01.04.2022
     * @version 0.01
     * @location BU Licences Sorbonne Campus PMC
     */

    char *token = strtok(line, " ");

    int assign = 0;
    int variable = 0;

    // TODO: ACCOUNT FOR CASES IN WHICH WE DO NOT HAVE WHITESPACES HENCE A TURING MACHINE APPROACH WILL BE BETTER.
    while(token){

       if(strcmp(token, "print") == 0){

           return;
        }

        if(assign == 1 && variable == 1){



            assign   = 0;
            variable = 0;
        }

        if(isalpha(*token)){
            variable = 1;
        } else
            if(strcmp(token, "=") == 0){

            assign = 1;
        }

        token = strtok(NULL, " ");
    }


}

static void readFile(const char *path){
    /**
     *
     *
     * @author Andrei-Paul Ionescu
     * @date 01.04.2022
     * @version 0.01
     * @location BU Licences Sorbonne Campus PMC
     */

    FILE *temporary;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    temporary = fopen(path, "r");

    if(temporary == NULL){

        printf("File error: The file which you wanted to read does not exist! "
               "We advise double checking the path you used.\n");
        exit(1);
    }

    while((read = getline(&line, &len, temporary)) != -1){

        parseLine(line);
    }

    fclose(temporary);
    if (line)
        free(line);
    //exit(EXIT_SUCCESS);
}

static int isFileName(const char *entity){
    /**
     * @param entity, a const char object.
     *
     * Determine whether entity is a file name or not utilising the following criteria, if entity is a file name then
     * it stands to reason that it contains only one '.' which separates the name of the file from its extension.
     *
     * @author Andrei-Paul Ionescu
     * @date 28.03.2022
     * @version 0.02
     */

    int times = 0;

    char *result = strtok(strdup(entity), ".");

    while(result){

        times += 1;
        result = strtok(NULL, ".");
    }

    if(times == 0 || times > 2) return 0;
    else
        return 1;
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
               "extension .unbound or .ub.\n");
        return 0;
    }

    return 1;
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
