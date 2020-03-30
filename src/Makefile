COMPILER := gcc
COMPILER_FLAGS := -g -c
LINKER_FLAGS := -g -lsodium -o
ALL_OBJS := mem/alloc/alloc.o mem/node/node.o mem/heap/heap.o mem/heap/helper.o

all: main_bin clean_objs

main_bin: main.o mem_objs
	${COMPILER} main.o ${ALL_OBJS} ${LINKER_FLAGS} main.out

main.o: main.c
	${COMPILER} ${COMPILER_FLAGS} main.c

mem_objs:
	make -C mem/

clean_objs:
	make -C mem/ clean
	rm -f ./*.o

clean: clean_objs
	rm -f ./*.out
