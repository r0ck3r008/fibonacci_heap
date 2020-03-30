#include<stdio.h>
#include<unistd.h>
#include<sodium.h>

#include"mem/mem.h"

#define ELEMS 100000
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
			test_heap=init_heap(rand_num, NULL);
		else
			insert(test_heap, rand_num, NULL);
	}

	u_limit=100;
	uint32_t rand_limit=randombytes_uniform(100);
	for(int i=0; i<rand_limit; i++) {
		struct node *max=remove_max(test_heap);
		if(max==NULL) {
			printf("Broke at %d\n", i);
			break;
		}

		printf("Key: %d at %d\n", max->key, i);
		dealloc("struct node", max, 1);
	}


	de_init_heap(test_heap);
}
