#include<stdio.h>
#include<unistd.h>
#include<sodium.h>

#include"mem/mem.h"

int main(int argc, char *argv[])
{
	if(sodium_init()<0) {
		fprintf(stderr, "Error in initiating the sodiumlib!\n");
		_exit(-1);
	}

	uint32_t upper_bound=1000;
	struct heap *test_heap;
	for(int i=0; i<5; i++) {
		uint32_t rand_num=randombytes_uniform(upper_bound);
		printf("Rand num: %d\n", rand_num);
		if(!i) {
			test_heap=init_heap(NULL, rand_num);
		} else {

			insert(test_heap, NULL, rand_num);
		}
	}

	print_heap(test_heap);

	for(int i=0; i<5; i++) {
		struct node *max=remove_max(test_heap);
		print_heap(test_heap);
		printf("Key: %d\n", max->val);
	}


	de_init_heap(test_heap);
}
