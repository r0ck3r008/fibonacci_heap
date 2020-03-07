COMPILER := gcc
COMPILER_FLAGS := -g -c
LINKER_FLAGS := -g -o
MEM_OBJS := mem/heap/heap.o mem/heap/helper.o mem/node/node.o mem/alloc/alloc.o

all: heap_test_out clean_objs

heap_test_out: mem_objs heap_test.o
	${COMPILER} ${MEM_OBJS} heap_test.o -lsodium ${LINKER_FLAGS} heap_test.out

heap_test.o: heap_test.c
	${COMPILER} ${COMPILER_FLAGS} heap_test.c

mem_objs:
	make -C mem/

clean_objs:
	rm -f ./*.o
	make -C mem/ clean

clean: clean_objs
	rm -f ./*.out
