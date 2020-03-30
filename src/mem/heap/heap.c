#include<stdio.h>

#include"helper.h"
#include"heap.h"

struct heap *init_heap(int key, void *payload)
{
	struct heap *new=alloc("struct heap", 1);
	new->max=init_node(key, payload);

	return new;
}

void de_init_heap(struct heap *heap_in)
{
	if(heap_in->max!=NULL)
		traverse(heap_in, de_init_list);

	dealloc("struct heap", heap_in, 1);
}

struct node *insert(struct heap *heap_in, int key, void *payload)
{
	struct node *new=init_node(key, payload);

	add_node(heap_in->max, new);
	if(new->key>heap_in->max->key)
		heap_in->max=new;

	return new;
}

struct node *remove_max(struct heap *heap_in)
{
	if(heap_in->max==NULL)
		//empty heap
		return NULL;
	struct node *curr_max=heap_in->max;
	if(curr_max->degree)
		detach_children(curr_max);
	struct node *curr;
	if((curr=detach_node(curr_max, 1))==curr_max) {
		//there is only one node
		heap_in->max=NULL;
		goto exit;
	}

	heap_in->max=find_max(curr);
	curr=heap_in->max->nxt;
	while(1) {
		struct node *tmp=curr->nxt;
		int flag=0;
		for(tmp; tmp!=curr; tmp=tmp->nxt) {
			//loop through the list to compare with curr
			//printf("Tmp: %d\tCurr: %d\n", tmp->key, curr->key);
			if(tmp->degree==curr->degree) {
				//we always choose the winning tree as current
				curr=meld(tmp, curr);
				flag=1;
				break;
			}
		}
		if(!flag && curr!=heap_in->max)
			//move ahead if current has no more left to meld
			curr=curr->nxt;
		else
			break;
	}
exit:
	return curr_max;
}

void inc_key(struct heap *heap_in, struct node *trgt, int set_to)
{
	trgt->key=set_to;

	if(trgt->parent!=NULL && trgt->key > trgt->parent->key) {
		struct node *curr=trgt->parent;
		while(curr!=NULL && curr->child_cut!=0) {
			struct node *tmp=curr->parent;
			detach_node(curr, 0);
			add_node(heap_in->max, curr);
			curr->child_cut=0;
			curr=tmp;
		}
		detach_node(trgt, 0);
		add_node(heap_in->max, trgt);
	}
	if(trgt->key > heap_in->max->key)
		heap_in->max=trgt;
}
