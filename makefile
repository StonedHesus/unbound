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

input-manager.o: src/input-manager/input-manager.c src/input-manager/input-manager.h # Define the rule which builds the input-manager module.
dictionary.o: src/dictionary/dictionary.c src/dictionary/dictionary.h # Define the rule which builds the dictionary module.
unbounded-int.o: src/unbounded-int/unbounded-int.c src/unbounded-int/unbounded-int.h # Define the rule which builds the unbounded-int library.
io.o: src/io/io.c src/io/io.h # Define the rule which builds the input-output library.
calc_unbounded_int.o: src/interpreter/calc_unbounded_int.c src/unbounded-int/unbounded-int.h src/input-manager/input-manager.h src/dictionary/dictionary.h # Define the rule which builds the interpreter.
test.o: tests/test.c src/unbounded-int/unbounded-int.h src/dictionary/dictionary.h # Define the rule which constructs the test object file.
control-flow.o: src/control-flow/control-flow.c src/control-flow/control-flow.h # Define the rule which constructs the control-flow object file.
single-chained-list.o: src/single-chained-list/single-chained-list.c src/single-chained-list/single-chained-list.h # Define the rule which constructs the single-chained-list object file.

# This here bit defines two custom commands which are to be used so as to clean the developing environment.
clean:
	rm -rf *~
cleanall:
	rm  -rf *~  *.o  $(ALL)