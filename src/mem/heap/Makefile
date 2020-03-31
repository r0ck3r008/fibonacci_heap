COMPILER := gcc
COMPILER_FLAGS := -g -c

all: heap.o helper.o node.o alloc.o

heap.o: heap.c heap.h
	${COMPILER} ${COMPILER_FLAGS} heap.c

helper.o: helper.c helper.h
	${COMPILER} ${COMPILER_FLAGS} helper.c

node.o: node.c node.h
	${COMPILER} ${COMPILER_FLAGS} node.c

alloc.o: alloc.c alloc.h
	${COMPILER} ${COMPILER_FLAGS} alloc.c

clean:
	rm -f *.o
