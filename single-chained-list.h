//
// Created by Andrei Paul Ionescu on 19/07/2022.
//

#ifndef UNBOUNDED_INT_SINGLE_CHAINED_LIST_H
#define UNBOUNDED_INT_SINGLE_CHAINED_LIST_H

// Custom aliases for the current objects/data types which are native to the compilation unit.
typedef struct cell cell;

typedef struct list{
    /**
     *  This here structure models a single chained list object which is a collection of cell object which are used
     *  as containers within the list object.
     *
     *  @author Andrei-Paul Ionescu.
     */

    cell *head; // A reference towards the first element of the list.
} list;


extern list construct_empty_list(void);
extern list construct_list(cell head);
extern list construct_list_from_string(const char * string);
extern void add_back(const char * string);
extern void print_from_head(list current_list);

#endif //UNBOUNDED_INT_SINGLE_CHAINED_LIST_H
