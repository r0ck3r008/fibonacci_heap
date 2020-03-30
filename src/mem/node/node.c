#include<stdio.h>

#include"node.h"

struct node *init_node(int key, void *payload)
{
	struct node *new_node=alloc("struct node", 1);
	new_node->key=key;
	new_node->payload=payload;
	new_node->child_cut=0;
	new_node->degree=0;
	new_node->child=NULL;
	new_node->parent=NULL;
	mk_dbl_cir_lst(new_node);
}

//converts a single node to doubly circular list
void mk_dbl_cir_lst(struct node *start)
{
	start->nxt=start;
	start->prev=start;
}

struct node *detach_node(struct node *curr, int ret)
{
	curr->prev->nxt=curr->nxt;
	curr->nxt->prev=curr->prev;
	struct node *tmp=curr->nxt;
	curr->nxt=NULL;
	curr->prev=NULL;
	curr->parent=NULL;

	if(ret)
		return tmp;
	else
		return NULL;
}
struct node *de_init_node(struct node *curr)
{
	struct node *ret=detach_node(curr, 1);
	dealloc("struct node", (void *)curr, 1);

	return ret;
}

void de_init_list(struct node *start)
{
	struct node *curr=start->nxt;
	while(curr!=start)
		curr=de_init_node(curr);

	de_init_node(start);
}

void add_node(struct node *start, struct node *new)
{
	start->nxt->prev=new;
	new->nxt=start->nxt;
	new->prev=start;
	start->nxt=new;
}

struct node *find_max(struct node *curr)
{
	struct node *start=curr;
	struct node *curr_max=start;
	curr=curr->nxt;
	for(curr; curr!=start; curr=curr->nxt) {
		if(curr_max->key < curr->key)
			curr_max=curr;
	}

	return curr_max;
}
