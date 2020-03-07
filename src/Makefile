COMPILER := gcc
COMPILER_FLAGS := -g -c
LINKER_FLAGS := -g -o
ALL_OBJS := mem/alloc/alloc.o mem/node/node.o mem/heap/heap.o mem/heap/helper.o

all: main_out clean_objs

main_out: mem_objs main.o
	${COMPILER} ${ALL_OBJS} main.o ${LINKER_FLAGS} main.out

main.o: main.c
	${COMPILER} ${COMPILER_FLAGS} main.c

mem_objs:
	make -C mem/

clean_objs:
	rm -f ./*.o
	make -C mem/ clean
	make -C tests/ clean

clean: clean_objs
	rm -f ./*.out
