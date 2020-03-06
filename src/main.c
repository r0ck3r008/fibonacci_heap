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
		if(!i) {
			test_heap=init_heap(NULL, rand_num);
		} else {

			insert(test_heap, NULL, rand_num);
		}
	}

	print_heap(test_heap);
	printf("Enter value to search: \t");
	int val;
	scanf("%d", &val);
	struct node *match=search_heap(test_heap, NULL, val);

	for(int i=0; i<5; i++) {
		struct node *max=remove_max(test_heap);
		printf("Key: %d\n", max->val);
		print_heap(test_heap);
		dealloc_node(max);
	}

	dealloc(test_heap, "struct heap", 1);
}
