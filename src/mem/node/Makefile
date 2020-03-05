COMPILER := gcc
COMPILER_FLAGS := -g -c

all: node.o

node.o: node.c node.h
	${COMPILER} ${COMPILER_FLAGS} node.c

clean:
	rm -f ./*.o
