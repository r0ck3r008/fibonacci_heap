#ifndef HEAP_H
#define HEAP_H

#include"../mem.h"

struct heap
{
	//the heap has only one pointer, pointer to the max node
	//rest are all a doubly linked list
	struct node *trees;
};

//Public API
struct heap *init_heap(void *, int);
void de_init_heap(struct heap *);
void insert(struct heap *, struct node *);
struct node *remove_max(struct heap *);
void inc_key(struct heap *, struct node *);

#endif
