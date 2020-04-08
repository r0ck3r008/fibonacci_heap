#include<stdio.h>
#include<unistd.h>
#include<sodium.h>

#include"mem/heap.h"

#define ELEMS 1000000

int main(int argc, char *argv[])
{
	if(sodium_init()<0) {
		fprintf(stderr, "[-]Error in starting sodiumlib!\n");
		_exit(-1);
	}

	struct heap *test_heap;
	uint32_t u_limit=100000;
	for(int i=0; i<ELEMS; i++) {
		uint32_t rand_num=randombytes_uniform(u_limit);
		if(!rand_num)
			continue;
		if(!i)
			test_heap=heap_init(rand_num, NULL);
		else
			heap_insert(test_heap, rand_num, NULL);
	}

	for(int i=0; i<ELEMS; i++) {
		struct heap_node *max=heap_remove_max(test_heap);
		if(max==NULL) {
			printf("Broke at %d\n", i);
			break;
		}

		printf("Key: %d at %d\n", max->key, i);
		heap_dealloc("struct heap_node", max, 1);
	}


	heap_de_init(test_heap);
}
