COMPILER := gcc
COMPILER_FLAGS := -g -c

all: heap.o helper.o

heap.o: heap.c heap.h
	${COMPILER} ${COMPILER_FLAGS} heap.c

helper.o: helper.c helper.h
	${COMPILER} ${COMPILER_FLAGS} helper.c

clean:
	rm -f ./*.o
