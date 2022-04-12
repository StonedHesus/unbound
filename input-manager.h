//
// Created by Andrei-Paul Ionescu on 11/04/2022.
//

#ifndef UNBOUNDED_INT_INPUT_MANAGER_H
#define UNBOUNDED_INT_INPUT_MANAGER_H

typedef struct command command;
typedef struct round_robin round_robin;

// Structures of the library.
struct command{

    unsigned int number_of_options;
    const char **options;
    const char *target;
};

struct round_robin{

    struct round_robin *next;
    command *command;
    struct round_robin *previous;
};

extern void print_command(command command);
extern void print_round_robin(round_robin roundRobin);
extern round_robin create_round_robin();
extern void add_process(round_robin current_roundRobin,command new_process);
extern void move_pointer(round_robin current_roundRobin);
extern command new_command(const char* target);
extern void add_option(command existing_command, char * option);

#endif //UNBOUNDED_INT_INPUT_MANAGER_H
