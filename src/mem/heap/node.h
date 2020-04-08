#ifndef NODE_H
#define NODE_H

#include"../heap.h"

struct heap_node
{
	int key;
	char *hash;
	int child_cut;
	int degree;
	struct heap_node *parent, *nxt,
				*prev, *child;
};

struct heap_node *heap_init_node(int, char *);
void heap_mk_dbl_cir_lst(struct heap_node *);
struct heap_node *heap_detach_node(struct heap_node *,
				int);
struct heap_node *heap_de_init_node(struct heap_node *);
void heap_de_init_list(struct heap_node *);
void heap_add_node(struct heap_node *,
		struct heap_node *);
struct heap_node *heap_find_max(struct heap_node *);
struct heap_node *heap_find_by_deg(struct heap_node *,
					int);

#endif
