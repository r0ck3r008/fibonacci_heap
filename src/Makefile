COMPILER := gcc
COMPILER_FLAGS := -g -c
LINKER_FLAGS := -g -lsodium -o
ALL_OBJS := mem/alloc/alloc.o mem/node/node.o mem/heap/heap.o mem/heap/helper.o

all: mem_objs hashtagcounter clean_objs

hashtagcounter:
	${COMPILER} ${ALL_OBJS} ${LINKER_FLAGS} ./hashtagcounter

tests: mem_objs tests_bin
	${COMPILER} tests/test_heap.o ${ALL_OBJS} ${LINKER_FLAGS} ./test_heap
	make clean_objs

tests_bin:
	make -C tests/

mem_objs:
	make -C mem/

clean_objs:
	make -C mem/ clean
	make -C tests/ clean
	rm -f ./*.o

clean: clean_objs
	rm -f ${shell find . -perm 755 ! -type d}
