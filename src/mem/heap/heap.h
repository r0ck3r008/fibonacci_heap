#ifndef _HEAP_H
#define _HEAP_H

struct heap
{
	struct node *max;
};

struct heap *init_heap(int);
void de_init_heap(struct heap *);
struct node *insert(struct heap *, int);
struct node *remove_max(struct heap *);

#endif
