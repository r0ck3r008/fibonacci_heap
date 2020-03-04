#include<stdio.h>

#include"helper.h"
#include"heap.h"

struct heap *init_heap(void *payload, int val)
{
	struct heap *new_heap=alloc("struct heap", 1);
	new_heap->trees=init_list(payload, val);

	return new_heap;
}

void de_init_heap(struct heap *heap_in)
{
	traverse(heap_in, de_init_list);
	dealloc(heap_in, "struct heap", 1);
}

void insert(struct heap *heap_in, struct node *new_node)
{
	add_node(heap_in->trees, new_node);
	if(heap_in->trees->val<new_node->val)
		heap_in->trees=new_node;
}
