#ifndef HMAP_H
#define HMAP_H

#include"../heap.h"

#define MAX_SIZE 100

struct hmap
{
	struct hmap_node **map;
	struct heap *heap_in;
};

struct hmap *hmap_hmap(char *, int);
void hmap_de_init(struct hmap *);
void hmap_insert(struct hmap *, char *, int);

#endif
