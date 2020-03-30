COMPILER := gcc
COMPILER_FLAGS := -g -c

all: test_heap.o

test_heap.o: test_heap.c
	${COMPILER} ${COMPILER_FLAGS} test_heap.c

clean:
	rm -f *.o
