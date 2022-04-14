//
// Created by Andrei Paul Ionescu on 26/03/2022.
//

/**
 * This here .c file models the interpreter of the unbound programming language.
 *
 * @version 0.10
 * @author Andrei-Paul Ionescu
 */

/// Existing libraries.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <ctype.h>
#include <errno.h>


/// Custom libraries.
#include "unbounded-int.h"
#include "dictionary.h"
#include "input-manager.h"

// Macro constants of the file.
#define DEFAULT "\033[0m"
#define GREEN "\033[32m"
#define BOLD_GREEN "\033[1m\033[32m"
#define RED "\033[31m"
#define BOLD_RED "\033[1m\033[31m"



// Prototypes of the function used inside this here .c file.

static int checkForInputFile(const char *filename);
static int isFileName(const char *entity);
static void readFile(const char *path);
static void prepare(int count, char **args);
static void run(void);
static void read(void);
static void write(char *line);
static void parseLine(char *line);
static char ** is_a_mathematical_expression(char *line);
static char ** get_operands_of_expression(char *line);
static int is_a_number(char *line);
static int checkForOutputFile(const char *filename);

// Global variables of the program.
static FILE *input;
static FILE *output;
static unsigned int line_number = 1;
static dictionary memory;

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
static int is_a_number(char *line){
    /**
     * @param line, a string object representing a line of text.
     *
     * Determine whether a string represents a digit or not.
     *
     * @since 0.07
     * @version 0.01
     * @author Andrei-Paul Ionescu
     * @date 07.04.2022
     * @location BU Grandes Moulines, forth floor.
     */

    for(char *pointer = line ; *pointer != '\0'; ++pointer){

        if(isdigit(*pointer) == 0)
            return 0;

    }

    return 1;
}
static char ** get_operands_of_expression(char *line){
    /*
     * @param line, a string object representing a line of text.
     *
     * @since 0.07
     * @version final
     * @author Andrei-Paul Ionescu
     * @date 07.04.2022
     * @location BU Grandes Moulines, forth floor.
     */

    char **operators = is_a_mathematical_expression(line);

    if(operators == NULL) return NULL;

    char **operands = malloc(sizeof(char **));
    if(operands == NULL) abort();


    return NULL;
}

static char **is_a_mathematical_expression(char *line){
    /*
     * @param line, a string object representing a line of text.
     *
     * Check whether the line contains a mathematical expression or not.
     *
     * If the line is a mathematical expression then return the operators it contains.
     *
     * @since 0.07
     * @version final
     * @author Andrei-Paul Ionescu
     * @date 07.04.2022
     * @location BU Grandes Moulines, forth floor.
     */

    assert(line);

    char **result = malloc(sizeof(char **));
    unsigned int position = 0;

    if(result == NULL) abort();

    for(const char* pointer = line ; *pointer !='\0' ; pointer += 1){

        if(*pointer == '+'){

            result[position] = malloc(sizeof(char *));
            if(result[position] == NULL) abort();
            result[position++] = "+";
        }

        if(*pointer == '-'){

            result[position] = malloc(sizeof(char *));
            if(result[position] == NULL) abort();
            result[position++] = "-";
        }

        if(*pointer == '/'){

            result[position] = malloc(sizeof(char *));
            if(result[position] == NULL) abort();
            result[position++] = "/";
        }

        if(*pointer == '*'){

            result[position] = malloc(sizeof(char *));
            if(result[position] == NULL) abort();
            result[position++] = "*";
        }
    }

    if(position == 0)
        return NULL;
    else
        return result;
}
static void read(void){
    /**
     *
     *
     * @author Andrei-Paul Ionescu
     * @date 04.04.2022
     * @version 0.02
     * @location Home office.
     */


    if(input == stdin){

        char *line = NULL;
        size_t size = 0;
        ssize_t read = 0;
        int beginning = 0;

        while(1){

            if(beginning == 0){

                fprintf(output, "Unbound 0.0.10 (default, 13th April 2022, 15:33:49)\n");
                fprintf(output, "calc_unbound -- An enhanced unbound shell; type '?' for help.\n\n");

                beginning = 1;
            }

            fprintf(output, "%sIn [%s%d%s%s]: %s", GREEN, BOLD_GREEN, line_number, DEFAULT, GREEN, DEFAULT);
            line_number += 1;
            read = getline(&line, &size, input);

            // Line is not an assignment, hence it can either be a variable or a command.
            if(strstr(line, "print") != NULL){

                strtok(line, " ");
                char * variable = strtok(NULL, " ");

                char *pointer = variable;

                is_a_mathematical_expression(variable);
                while(*pointer != ' ' && *pointer != '\n' && *pointer != '\t')
                    // Remove extra spaces from the suffix of the handle.
                    pointer += 1;

                // Add the string terminator.
                *pointer = '\0';

                if(search_in_dictionary(memory, variable) == 0){

                    printf("ERROR: The variable %s was not defined!\n", variable);
                } else{

                    write(unbounded_int2string(*search_in_dictionary(memory, variable)));
                }
            }


            if(!strstr(line, "=")){
                // If the line is not an assignment then it might be an operation, a number or a command, either of
                // these requires immediate output.

                if(is_a_number(line) == 1){

                    write(line);
                } else{


                    char **result = is_a_mathematical_expression(line);
                    if(result == NULL)
                        system(line);
                    else
                        write(line);
                }
            } else{

                char *key = strtok(line, "=");
                char *pointer = key;

                while(*pointer != ' ')
                   pointer += 1;

                *pointer = '\0';

                char *value = strtok(NULL, " ");

                pointer = value;

                while(*pointer != ' ' && *pointer != '\t' && *pointer != '\n')
                    pointer += 1;



                *pointer = '\0';

                insert_into_dictionary(memory, key, string2unbounded_int(value));
            }

            if(strstr(line, "len")){
                // Return the number of digits of the variable.

                strtok(line, " ");
                char *value = strtok(NULL, " ");
                char *pointer = value;

                while(*pointer != ' ' && *pointer != '\t' && *pointer != '\n')
                    pointer += 1;

                *pointer = '\0';


            }

            if(strstr(line, "cd"))
                //chdir(line);
                // Solve conflict between the library which contains the chdir command and the method implemented
                // by the interpreter.

            if(strstr(line, "clear") || strstr(line, "clear()"))
                system("clear");

            if(read == -1 || strstr(line, "exit") != NULL || strstr(line, "exit()") != NULL){

                fprintf(output, "\n");
                exit(0);
            }

            if(strstr(line, "?")){
                system("clear");
                fprintf(output, "calc_unbound -- An enhanced unbound shell\n");
                fprintf(output, "=========================================\n\n");
                fprintf(output, "calc_unbound offers an interpreter with convenient shell features for the unbound "
                                "language.\n");

            }

            fprintf(output, "\n");
            parseLine(line);
        }

    }

}

// TODO: Make write behaves like printf.

static void write(char *line){
    /**
     *
     * @author Andrei-Paul Ionescu
     * @date 04.04.2022
     * @version 0.01
     * @location Home Office.
     */

    if(output == stdout){

        fprintf(output, "%sOut [%s%d%s%s]: %s%s\n", RED, BOLD_RED, line_number, DEFAULT, RED, DEFAULT, line);
    }
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

    memory = create_dictionary();
    read();


}

static void prepare(int count, char **args){
    /**
     *
     * @param1, the number of pointers which are found in the list args.
     * @param2, a list of pointers.
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
    } else{
        // Commence the round-robin algorithm.

        round_robin roundRobin = create_round_robin();
        command current_process;

        output = stdout;

        // TODO: finish implementing the add_process method and correct the print_round_robin one.


        int file_already_exists    = 0;
        int process_already_exists = 0;
        for(int i = 1 ; i < count ; ++i){

            if(isFileName(args[i]) == 1){

                if(file_already_exists == 0){

                    if(process_already_exists == 0){

                        current_process = new_command(args[i]);
                        process_already_exists = 1;
                    } else{

                        add_target(&current_process, args[i]);
                    }
                    file_already_exists = 1;
                } else{

                    add_process(&roundRobin, current_process);

                    current_process = new_empty_command();
                    file_already_exists = 0;
                    process_already_exists = 1;
                }

            } else{

                if(process_already_exists == 0){

                    current_process = new_empty_command();
                    add_option(&current_process, args[i]);
                    process_already_exists = 1;
                } else{

                    add_option(&current_process, args[i]);
                }
            }
        }


        //print_round_robin(roundRobin);
        print_command(current_process);
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
    assert(entity);

    if(!strstr(entity, ".")) return  0;

    int times = 0;

    char *result = strtok(strdup(entity), ".");

    if(result == NULL) return 0;

    while(result){

        times += 1;
        result = strtok(NULL, ".");
    }

    if(times == 0 || times > 2) return 0;
    else
        return 1;
}

static int checkForOutputFile(const char *filename){
    /**
     * @param filename; a string object which represents the name of a possible output file.
     *
     * This here method determines whether or not the file name passed to the method is a valid output file or not,
     * valid output files end with the extensions .txt, .out.
     *
     * @since 0.09
     * @version final
     * @author Andrei-Paul Ionescu
     * @location Crous cafeteria Grands Moulines.
     */

    assert(filename != NULL);

    const char *first_result  = strstr(filename, ".txt");
    const char *second_result = strstr(filename, ".out");

    if(!first_result && !second_result){

        printf("File format error: all output files must bear the extensions .txt or .out.\n");
        return 0;
    }

    return 1;
}

static int checkForInputFile(const char *filename){
    /**
     * @param filename; a const char( string object whose values we cannot alter) which represents the name of
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


