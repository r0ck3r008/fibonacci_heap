#include<stdio.h>

#include"node.h"

struct node *init_node(void *payload, int val)
{
	struct node *new_node=alloc("struct node", 1);
	new_node->payload=payload;
	new_node->val=val;
	new_node->nxt=NULL;
	new_node->prev=NULL;
	new_node->child=NULL;
	new_node->parent=NULL;
	new_node->children=0;
	new_node->loser=0;

	return new_node;
}

struct node *move_to_start(struct node *curr)
{
	struct node *tmp;
	for(tmp=curr; tmp->prev!=NULL; tmp=tmp->prev);

	return tmp;
}

struct node *move_to_finish(struct node *curr)
{
	struct node *tmp;
	for(tmp=curr; tmp->nxt!=NULL; tmp=tmp->nxt);

	return tmp;
}

void add_node(struct node *curr, struct node *new_node)
{
	struct node *end=move_to_finish(curr);

	new_node->prev=end;
	new_node->nxt=end->nxt;
	end->nxt=new_node;
}

void make_start(struct node *curr)
{
	struct node *start=move_to_start(curr);

	swap_nodes(start, curr);
}

void swap_nodes(struct node *node1, struct node *node2)
{
	//fix nxt
	if(node1->nxt!=NULL)
		node1->nxt->prev=node2;
	if(node2->nxt!=NULL)
		node2->nxt->prev=node1;
	struct node *tmp=node1->nxt;
	node1->nxt=node2->nxt;
	node2->nxt=tmp;
	//fix prev
	if(node1->prev!=NULL)
		node1->prev->nxt=node2;
	if(node2->prev!=NULL)
		node2->prev->nxt=node1;
	tmp=node1->prev;
	node1->prev=node2->prev;
	node2->prev=tmp;
}

struct node *find_max(struct node *curr)
{
	struct node *start=move_to_start(curr);
	struct node *curr_max=start;
	for(curr=start; curr!=NULL; curr=curr->nxt) {
		if(curr_max->val < curr->val)
			curr_max=curr;
	}

	make_start(curr_max);
	return curr_max;
}

void print_list(struct node *curr)
{
	struct node *start=move_to_start(curr);
	if(start->parent!=NULL)
		printf("Parent Value: %d\t", start->parent->val);
	for(curr=start; curr->nxt!=NULL; curr=curr->nxt) {
		printf("%d->", curr->val);
	}

	printf("%d\n", curr->val);
}

void de_init_list(struct node *curr)
{
	struct node *start=move_to_start(curr);

	for(curr=start; start->nxt!=NULL; ) {
		dealloc_node(start->nxt);
	}

	dealloc(start, "struct node", 1);
}

void detach_node(struct node *curr)
{
	if(curr->nxt!=NULL)
		curr->nxt->prev=curr->prev;
	if(curr->prev!=NULL)
		curr->prev->nxt=curr->nxt;
}

void dealloc_node(struct node *curr)
{
	detach_node(curr);
	dealloc(curr, "struct node", 1);
}
