#include<string.h>

#include"node.h"

struct node *init_node(void *payload, int val)
{
	struct node *new_node=alloc("struct node", 1);
	new_node->val=val;
	new_node->payload=payload;
	new_node->parent=NULL;
	new_node->nxt=NULL;
	new_node->prev=NULL;

	return new_node;
}

struct node *init_list()
{
	struct node *start=init_node("START", -1);
	return start;
}

void de_init_list(struct node *start)
{
	int ret=1;
	struct node *curr;
	for(curr; curr=start; curr->nxt!=NULL) {
		del_node(curr->nxt);
		curr=start->nxt;
	}

	dealloc(start, "struct node", 1);
}

void add_node(struct node *start, struct node *new_node)
{
	struct node *curr;
	for(curr; curr=start->nxt; curr->nxt!=NULL)
		curr=curr->nxt;

	curr->nxt=new_node;
	new_node->prev=curr;
}

void del_node(struct node *trgt)
{
	trgt->prev->nxt=trgt->nxt;
	if(trgt->nxt!=NULL)
		trgt->nxt->prev=trgt->prev;
	dealloc(trgt, "struct node", 1);
}
