# Define the compiler which is used to build the project and the flags which are to be applied to the compiler.
CC=gcc
CFLAGS=		-Wall -g -pedantic

# Define a variable which stores all the executable files which are going to be built after the execution of the
# makefile.
ALL= test calc_unbounded_int

# Build the executable components.
all: $(ALL)

# Build the test executable.
test: test.o unbounded-int.o dictionary.o

# Build the executable for the parser/ interpreter.
calc_unbounded_int: calc_unbounded_int.o dictionary.o unbounded-int.o input-manager.o

# Build the object files for the current project, whilst respecting their dependencies and their linkage properties.

input-manager.o: input-manager.c input-manager.h # Define the rule which builds the input-manager module.
dictionary.o: dictionary.c dictionary.h # Define the rule which builds the dictionary module.
unbounded-int.o: unbounded-int.c unbounded-int.h # Define the rule which builds the unbounded-int library.
io.o: io.c io.h # Define the rule which builds the input-output library.
calc_unbounded_int.o: calc_unbounded_int.c unbounded-int.h input-manager.h dictionary.h # Define the rule which builds the interpreter.
test.o: test.c unbounded-int.h dictionary.h # Define the rule which constructs the test object file.
control-flow.o: control-flow.c control-flow.h # Define the rule which constructs the control-flow object file.
single-chained-list.o: single-chained-list.c single-chained-list.h # Define the rule which constructs the single-chained-list object file.

# This here bit defines two custom commands which are to be used so as to clean the developing environment.
clean:
	rm -rf *~
cleanall:
	rm  -rf *~  *.o  $(ALL)