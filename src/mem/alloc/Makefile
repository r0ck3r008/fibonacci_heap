COMPILER := gcc
COMPILER_FLAGS := -g -c

all: alloc.o

alloc.o: alloc.c alloc.h
	${COMPILER} ${COMPILER_FLAGS} alloc.c

clean:
	rm -f *.o
