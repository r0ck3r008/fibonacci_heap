#ifndef HEAP_H
#define HEAP_H

#include"../mem.h"

struct heap
{
	struct node *max;
};

struct heap *init_heap(int,  void *);
void de_init_heap(struct heap *);
struct node *insert(struct heap *, int, void *);
struct node *remove_max(struct heap *);

#endif
