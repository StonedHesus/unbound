# Define the compiler which is used to build the project and the flags which are to be applied to the compiler.
CC=zig cc
CFLAGS=		-Wall -g -pedantic

init:
	@mkdir -p build

test: test.o unbound.o dictionary.o
test.o: test/test.c src/unbound/unbound.h src/dictionary/dictionary.h
	zig cc -c test/test.c
calc_unbounded_int: calc_unbounded_int.o dictionary.o unbound.o input-manager.o
unbound.o: src/unbound/unbound.c src/unbound/unbound.h 
	zig cc -c src/unbound/unbound.c
input-manager.o: src/input-manager/input-manager.c src/input-manager/input-manager.h 
	zig cc -c src/input-manager/input-manager.c
dictionary.o: src/dictionary/dictionary.c src/dictionary/dictionary.h
	zig cc -c src/dictionary/dictionary.c
io.o: src/io/io.c src/io/io.h 
	zig cc -c src/io/io.c
calc_unbounded_int.o: src/interpreter/calc_unbounded_int.c src/unbound/unbound.h src/input-manager/input-manager.h src/dictionary/dictionary.h 
	zig cc -c src/interpreter/calc_unbounded_int.c
control-flow.o: src/control-flow/control-flow.c src/control-flow/control-flow.h 
	zig cc -c src/control-flow/control-flow.c.c
single-chained-list.o: src/single-chained-list/single-chained-list.c src/single-chained-list/single-chained-list.h 
	zig cc -c src/single-chained-list/single-chained-list.c
#ALL= test calc_unbounded_int
## Build the executable components.
#all: $(ALL)
clean: init
	rm -rf build 
