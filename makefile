CC=gcc
CFLAGS=		-Wall -g -pedantic

ALL= test calc_unbounded_int

all: $(ALL)

test: test.o unbounded-int.o dictionary.o

calc_unbounded_int: calc_unbounded_int.o dictionary.o unbounded-int.o input-manager.o

input-manager.o: input-manager.c input-manager.h
dictionary.o: dictionary.c dictionary.h
unbounded-int.o: unbounded-int.c unbounded-int.h

calc_unbounded_int.o: calc_unbounded_int.c unbounded-int.h input-manager.h dictionary.h
test.o: test.c unbounded-int.h dictionary.h

clean:
	rm -rf *~
cleanall:
	rm  -rf *~  *.o  $(ALL)