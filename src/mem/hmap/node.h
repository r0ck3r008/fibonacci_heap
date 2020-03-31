#ifndef HMAP_NODE_H
#define HMAP_NODE_H

#include"../heap.h"

struct hmap_node
{
	char *key;
	struct heap_node *node_addr;
	struct hmap_node *nxt, *prev;
};

struct hmap_node *hmap_init_node(char *,
				struct heap_node *);
void hmap_de_init_list(struct hmap_node *);
void hmap_add_node(struct hmap_node *, struct hmap_node *);
struct hmap_node *hmap_find_node(struct hmap_node *,
					char *);
struct hmap_node *hmap_remove_node(struct hmap_node *,
					char *);

#endif
