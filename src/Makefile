COMPILER := gcc
COMPILER_FLAGS := -g -c
LINKER_FLAGS := -g -o
HEAP_OBJS := mem/heap/heap.o mem/heap/node.o mem/heap/helper.o mem/heap/alloc.o
HMAP_OBJS := mem/hmap/hmap.o mem/hmap/helper.o mem/hmap/node.o mem/hmap/alloc.o

all: heap_objs hmap_objs hashtagcounter clean_objs

hashtagcounter: main.o
	${COMPILER} ./main.o ${HEAP_OBJS} ${HMAP_OBJS} ${LINKER_FLAGS} ./hashtagcounter

main.o: main.c
	${COMPILER} ${COMPILER_FLAGS} ./main.c

tests: heap_objs hmap_objs tests_bin
	${COMPILER} tests/test_heap.o ${HEAP_OBJS} -lsodium ${LINKER_FLAGS} ./test_heap
	make clean_objs

tests_bin:
	make -C tests/

heap_objs:
	make -C mem/ heap_objs

hmap_objs:
	make -C mem/ hmap_objs

clean_objs:
	make -C mem/ clean
	make -C tests/ clean
	rm -f ./*.o

clean: clean_objs
	rm -f ${shell find . -perm 755 ! -type d}
