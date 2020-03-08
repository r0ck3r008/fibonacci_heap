COMPILER := gcc
COMPILER_FLAGS := -g -c

all: hmap.o

node.o: hmap.c hmap.h
	${COMPILER} ${COMPILER_FLAGS} hmap.c

clean:
	rm -f ./*.o
