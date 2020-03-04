#include<string.h>

#include"node.h"

struct node *init_list(void *payload, int val)
{
	struct node *new_node=alloc("struct node", 1);
	new_node->val=val;
	new_node->payload=payload;
	new_node->parent=NULL;
	new_node->child=NULL;
	new_node->nxt=NULL;
	new_node->prev=NULL;

	return new_node;
}

void de_init_list(struct node *start)
{
	int ret=1;
	struct node *curr;
	start=move_first(start);
	for(curr; curr=start; curr->nxt!=NULL) {
		del_node(curr->nxt);
		curr=start->nxt;
	}

	dealloc(start, "struct node", 1);
}

struct node *move_first(struct node *start)
{
	struct node *curr;
	for(curr; curr=start->prev; curr->prev!=NULL)
		curr=curr->prev;

	return curr;
}

void add_node(struct node *start, struct node *new_node)
{
	struct node *curr;
	for(curr; curr=start->nxt; curr->nxt!=NULL)
		curr=curr->nxt;

	curr->nxt=new_node;
	new_node->prev=curr;
	new_node->nxt=NULL;
}

void remove_node(struct node *trgt)
{
	trgt->prev->nxt=trgt->nxt;
	trgt->nxt->prev=trgt->prev;
}

void del_node(struct node *trgt)
{
	remove_node(trgt);
	dealloc(trgt, "struct node", 1);
}
