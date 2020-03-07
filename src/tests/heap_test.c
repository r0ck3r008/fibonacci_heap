#include<stdio.h>
#include<unistd.h>
#include<sodium.h>

#include"../mem/mem.h"

int main(int argc, char *argv[])
{
	if(sodium_init()<0) {
		fprintf(stderr, "Error in initiating the sodiumlib!\n");
		_exit(-1);
	}

	uint32_t upper_bound=100000;
	struct heap *test_heap;
	uint32_t last_val=0;
	for(int i=0; i<100; i++) {
		uint32_t rand_num=randombytes_uniform(upper_bound);
		if(!i) {
			test_heap=init_heap(NULL, rand_num);
		} else {

			insert(test_heap, NULL, rand_num);
		}

		if(i && i%10==0) {
			uint32_t rand_bit=randombytes_uniform(2);
			if(rand_bit) {
				struct node *max=remove_max(test_heap);
				if(max==NULL) {
					printf("Exiting at: %d\n", i);
					break;
				} else {
					printf("Key: %d\n", max->val);
				}
			} else {
				inc_key(test_heap, NULL, last_val, 1);
			}
		}
		last_val=rand_num;
	}

	print_heap(test_heap);

	de_init_heap(test_heap);
}
