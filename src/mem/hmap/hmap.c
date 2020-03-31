#include<stdio.h>
#include<stdlib.h>

#include"node.h"
#include"helper.h"
#include"hmap.h"

struct hmap *hmap_init(char *key, int val)
{
	struct hmap *new_hmap=alloc("struct hmap", 1);
	new_hmap->heap_in=init_heap(val);
	new_hmap->map=(struct hmap_node **)malloc(sizeof(struct hmap_node *));

	int mapping=hash_it(key);
	for(int i=0; i<MAX_SIZE; i++) {
		if(i==mapping)
			//appaend the first entry in hmap
			new_hmap->map[i]=hmap_init_node(key,
							new_hmap->heap_in->max);
		else
			new_hmap->map[i]=NULL;
	}

	return new_hmap;
}

void hmap_de_init(struct hmap *hmap_in)
{
	de_init_heap(hmap_in->heap_in);

	for(int i=0; i<MAX_SIZE; i++) {
		if(hmap_in->map[i]!=NULL) {
			//delete the list
			hmap_de_init_list(hmap_in->map[i]);
		}
	}
	free(hmap_in->map);

	dealloc("struct hmap", (void *)hmap_in, 1);
}
