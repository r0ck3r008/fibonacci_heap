#include<stdio.h>
#include<string.h>

#include"alloc.h"
#include"node.h"

struct hmap_node *hmap_init_node(char *key, struct heap_node *node_addr)
{
	struct hmap_node *ret=hmap_alloc("struct hmap_node", 1);
	ret->key=hmap_alloc("char", 64);
	sprintf(ret->key, "%s", key);
	ret->node_addr=node_addr;
	ret->nxt=NULL;
	ret->prev=NULL;

	return ret;
}

void hmap_de_init_list(struct hmap_node *start)
{
	struct hmap_node *curr=start->nxt;
	while(start->nxt!=NULL) {
		hmap_dealloc("struct hmap_node", curr, 1);
		curr=start->nxt;
	}

	heap_dealloc("char", start->node_addr->hash, 64);
	heap_dealloc("struct heap_node", start->node_addr, 1);
	hmap_dealloc("char", start->key, 64);
	hmap_dealloc("struct hmap_node", start, 1);
}

void hmap_add_node(struct hmap_node *start, struct hmap_node *new)
{
	struct hmap_node *curr=start;
	for(curr; curr->nxt!=NULL; curr=curr->nxt);
	curr->nxt=new;
	new->prev=curr;
}

struct hmap_node *hmap_find_node(struct hmap_node *start, char *key)
{
	struct hmap_node *curr=start;
	int flag=0;
	for(curr; curr!=NULL; curr=curr->nxt) {
		if(!strcmp(curr->key, key)) {
			flag=1;
			break;
		}
	}

	if(!flag)
		return NULL;
	return curr;
}

struct hmap_node *hmap_remove_node(struct hmap_node *start, char *key)
{
	if(start==NULL)
		return NULL;
	struct hmap_node *curr=hmap_find_node(start, key);
	if(curr!=NULL) {
		if(curr->prev!=NULL)
			curr->prev->nxt=curr->nxt;
		if(curr->nxt!=NULL)
			curr->nxt->prev=curr->prev;
	}

	return curr;
}
