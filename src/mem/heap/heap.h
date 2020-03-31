#ifndef _HEAP_H
#define _HEAP_H

struct heap
{
	struct heap_node *max;
};

struct heap *heap_init(int, char *);
void heap_de_init(struct heap *);
struct heap_node *heap_insert(struct heap *, int,
				char *);
struct heap_node *heap_remove_max(struct heap *);
void heap_inc_key(struct heap *,
			struct heap_node *, int);

#endif
