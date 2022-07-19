//
// Created by Andrei Paul Ionescu on 25/06/2022.
//

#ifndef UNBOUNDED_INT_CONTROL_FLOW_H
#define UNBOUNDED_INT_CONTROL_FLOW_H

// For loops in unbound are similar to the python one, and thus they use the range method.
extern void for_loop(long starting_value, long bound, long step);
// Unbound also supports for in loops which take a collection of entities which are to be retrieved, if possible
// from a collection/set which should correspond in construction with the entities which are requested to be
// extracted from the said set.
extern void for_in_loop(char ** entities, char ** collection);

#endif //UNBOUNDED_INT_CONTROL_FLOW_H
