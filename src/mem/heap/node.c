#include<stdio.h>

#include"node.h"

struct heap_node *heap_init_node(int key, char *hash)
{
	struct heap_node *new_node=heap_alloc("struct heap_node", 1);
	new_node->key=key;
	new_node->hash=heap_alloc("char", 64);
	sprintf(new_node->hash, "%s", hash);
	new_node->child_cut=0;
	new_node->degree=0;
	new_node->child=NULL;
	new_node->parent=NULL;
	heap_mk_dbl_cir_lst(new_node);
}

//converts a single node to doubly circular list
void heap_mk_dbl_cir_lst(struct heap_node *start)
{
	start->nxt=start;
	start->prev=start;
}

struct heap_node *heap_detach_node(struct heap_node *curr, int ret)
{
	curr->prev->nxt=curr->nxt;
	curr->nxt->prev=curr->prev;
	struct heap_node *tmp=curr->nxt;
	curr->nxt=NULL;
	curr->prev=NULL;
	curr->parent=NULL;

	if(ret)
		return tmp;
	else
		return NULL;
}
struct heap_node *heap_de_init_node(struct heap_node *curr)
{
	struct heap_node *ret=heap_detach_node(curr, 1);
	heap_dealloc("struct heap_node", curr, 1);

	return ret;
}

void heap_de_init_list(struct heap_node *start)
{
	struct heap_node *curr=start->nxt;
	while(curr!=start)
		curr=heap_de_init_node(curr);

	heap_de_init_node(start);
}

void heap_add_node(struct heap_node *start, struct heap_node *new)
{
	start->nxt->prev=new;
	new->nxt=start->nxt;
	new->prev=start;
	start->nxt=new;
}

struct heap_node *heap_find_max(struct heap_node *curr)
{
	struct heap_node *start=curr;
	struct heap_node *curr_max=start;
	curr=curr->nxt;
	for(curr; curr!=start; curr=curr->nxt) {
		if(curr_max->key < curr->key)
			curr_max=curr;
	}

	return curr_max;
}
