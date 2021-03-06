#include<stdio.h>
#include<stdlib.h>

#include"alloc.h"
#include"node.h"
#include"helper.h"
#include"hmap.h"

struct hmap *hmap_init(char *key, int val)
{
	struct hmap *new_hmap=hmap_alloc("struct hmap", 1);
	new_hmap->heap_in=heap_init(val, key);
	new_hmap->map=(struct hmap_node **)
				malloc(sizeof(struct hmap_node *)*MAX_SIZE);

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
	heap_de_init(hmap_in->heap_in);

	for(int i=0; i<MAX_SIZE; i++) {
		if(hmap_in->map[i]!=NULL)
			//delete the list
			hmap_de_init_list(hmap_in->map[i]);
	}
	free(hmap_in->map);

	hmap_dealloc("struct hmap", hmap_in, 1);
}

void hmap_update(struct hmap *hmap_in, char *key, int val)
{
	int indx=hash_it(key);
	struct hmap_node *curr_node=hmap_find_node(hmap_in->map[indx], key);
	if(curr_node==NULL) {
		//new insert
		struct heap_node *new_node=heap_insert(hmap_in->heap_in, val,
							key);
		struct hmap_node *new_hmap_node=hmap_init_node(key, new_node);
		if(hmap_in->map[indx]==NULL)
			hmap_in->map[indx]=new_hmap_node;
		else
			hmap_add_node(hmap_in->map[indx], new_hmap_node);
	} else {
		heap_inc_key(hmap_in->heap_in, curr_node->node_addr, val);
	}
}

struct hmap_node *hmap_remove_max(struct hmap *hmap_in)
{
	struct heap_node *node=heap_remove_max(hmap_in->heap_in);
	if(node==NULL)
		return NULL;

	int indx=hash_it(node->hash);
	struct hmap_node *curr_node=hmap_remove_node(hmap_in->map[indx],
								node->hash);
	if(hmap_in->map[indx]==curr_node)
		hmap_in->map[indx]=curr_node->nxt;

	curr_node->nxt=NULL;
	curr_node->prev=NULL;
	return curr_node;
}
